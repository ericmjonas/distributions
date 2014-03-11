import numpy
cimport numpy
numpy.import_array()
from cython.operator cimport dereference as deref, preincrement as inc
from distributions.hp.special cimport log, gammaln
from distributions.hp.random cimport sample_dirichlet, sample_discrete
from distributions.sparse_counter cimport SparseCounter
from distributions.mixins import ComponentModel, Serializable

#-------------------------------------------------------------------------
# Datatypes

ctypedef int Value

cpdef Value OTHER = -1

cdef class Group:
    cdef SparseCounter * counts
    def __cinit__(self):
        self.counts = new SparseCounter()
    def __dealloc__(self):
        del self.counts

    def load(self, dict raw):
        cdef SparseCounter * counts = self.counts
        counts.clear()
        cdef dict raw_counts = raw['counts']
        cdef str i
        cdef int count
        for i, count in raw_counts.iteritems():
            self.counts.init_count(int(i), count)

    def dump(self):
        cdef dict counts = {}
        cdef SparseCounter.iterator it = self.counts.begin()
        cdef SparseCounter.iterator end = self.counts.end()
        while it != end:
            counts[str(deref(it).first)] = deref(it).second
            inc(it)
        return {'counts': counts}


# Buffer types only allowed as function local variables
#ctypedef numpy.ndarray[numpy.float64_t, ndim=1] Sampler
ctypedef numpy.ndarray Sampler


cdef class Model_cy:
    cdef double gamma
    cdef double alpha
    cdef double beta0
    #cdef numpy.ndarray[double, ndim=1] betas
    cdef numpy.ndarray betas

    def load(self, dict raw):
        self.gamma = raw['gamma']
        self.alpha = raw['alpha']
        self.beta0 = raw['beta0']
        cdef dict raw_betas = raw['betas']
        cdef int i
        cdef list betas = [raw_betas[str(i)] for i in xrange(len(raw_betas))]
        self.betas = numpy.array(betas, dtype=numpy.float)  # dense

    def dump(self):
        return {
            'gamma': self.gamma,
            'alpha': self.alpha,
            'beta0': self.beta0,
            'betas': {str(i): beta for i, beta in enumerate(self.betas)},
        }

    #-------------------------------------------------------------------------
    # Mutation

    def group_init(self, Group group):
        group.counts.clear()

    def group_add_value(self, Group group, Value value):
        assert value != OTHER, 'tried to add OTHER to group'
        group.counts.add(value)

    def group_remove_value(self, Group group, Value value):
        assert value != OTHER, 'tried to remove OTHER to group'
        group.counts.remove(value)

    def group_merge(self, Group destin, Group source):
        destin.counts.merge(source.counts[0])

    #-------------------------------------------------------------------------
    # Sampling

    cpdef Sampler sampler_create(self, Group group=None):
        cdef int size = self.betas.shape[0]
        cdef numpy.ndarray[double, ndim=1] values = \
            numpy.zeros(size + 1, dtype=numpy.double)
        values[:-1] = self.betas * self.alpha
        values[-1] = self.beta0 * self.alpha
        cdef SparseCounter.iterator it
        cdef SparseCounter.iterator end
        if group is not None:
            counts = group.counts
            it = group.counts.begin()
            end = group.counts.end()
            while it != end:
                values[deref(it).first] += deref(it).second
                inc(it)
        cdef numpy.ndarray[double, ndim=1] sampler = \
            numpy.zeros(size + 1, dtype=numpy.double)
        sample_dirichlet(
            size + 1,
            <double *> values.data,
            <double *> sampler.data)
        return sampler

    cpdef Value sampler_eval(self, Sampler sampler):
        cdef int size = len(sampler)
        cdef int index = sample_discrete(size + 1, <double *> sampler.data)
        if index == size:
            return OTHER
        else:
            return index

    def sample_value(self, Group group):
        cdef Sampler sampler = self.sampler_create(group)
        return self.sampler_eval(sampler)

    def sample_group(self, int size):
        cdef Sampler sampler = self.sampler_create()
        cdef list result = []
        cdef int i
        for i in xrange(size):
            result.append(self.sampler_eval(sampler))
        return result

    #-------------------------------------------------------------------------
    # Scoring

    def score_value(self, Group group, Value value):
        cdef SparseCounter * counts = group.counts
        cdef double denom = self.alpha + counts.get_total()
        cdef double numer
        if value == OTHER:
            numer = self.beta0 * self.alpha
        else:
            numer = self.betas[value] * self.alpha + counts.get_count(value)
        return log(numer / denom)

    def score_group(self, Group group):
        assert len(self.betas), 'betas is empty'
        cdef double score = 0.
        cdef SparseCounter * counts = group.counts
        cdef SparseCounter.iterator it = counts.begin()
        cdef SparseCounter.iterator end = counts.end()
        cdef int i
        cdef int count
        cdef double prior_i
        while it != end:
            i = deref(it).first
            count = deref(it).second
            prior_i = self.betas[i] * self.alpha
            score += gammaln(prior_i + count) - gammaln(prior_i)
            inc(it)
        score += gammaln(self.alpha) - gammaln(self.alpha + counts.get_total())

        return score

    #-------------------------------------------------------------------------
    # Examples

    EXAMPLES = [
        {
            'model': {
                'gamma': 0.5,
                'alpha': 0.5,
                'beta0': 0.0,  # must be zero for unit tests
                'betas': {
                    '0': 0.5,
                    '1': 0.5,
                    '2': 0.5,
                },
            },
            'values': [0, 1, 0, 2, 0, 1, 0],
        },
    ]


class DirichletProcessDiscrete(Model_cy, ComponentModel, Serializable):

    #-------------------------------------------------------------------------
    # Datatypes

    Value = int

    Group = Group


Model = DirichletProcessDiscrete
