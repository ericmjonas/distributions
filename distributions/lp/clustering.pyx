from libcpp.vector cimport vector
from libcpp.utility cimport pair
from cython.operator cimport dereference as deref, preincrement as inc

cdef extern from 'distributions/clustering.hpp':
    cppclass rng_t

    cppclass Assignments_cc "distributions::Clustering<int>::Assignments":
        Assignments_cc() nogil except +
        cppclass iterator:
            pair[int, int] & operator*() nogil
            iterator operator++() nogil
            bint operator!=(iterator) nogil
        int & operator[](int) nogil

    cdef vector[int] count_assignments_cc \
            "distributions::Clustering<int>::count_assignments" \
            (Assignments_cc & assignments) nogil

    cppclass PitmanYor_cc "distributions::Clustering<int>::PitmanYor":
        float alpha
        float d
        vector[int] sample_assignments(int size, rng_t & rng) nogil
        float score_counts(vector[int] & counts) nogil
        float score_add_value (
                int group_size,
                int group_count,
                int sample_size) nogil
        float score_remove_value (
                int group_size,
                int group_count,
                int sample_size) nogil

    cppclass LowEntropy_cc "distributions::Clustering<int>::LowEntropy":
        int dataset_size
        vector[int] sample_assignments(int size, rng_t & rng) nogil
        float score_counts(vector[int] & counts) nogil
        float score_add_value (
                int group_size,
                int group_count,
                int sample_size) nogil
        float score_remove_value (
                int group_size,
                int group_count,
                int sample_size) nogil


cpdef list count_assignments(dict assignments):
    cdef Assignments_cc assignments_cc
    cdef int value_id
    cdef int group_id
    for value_id, group_id in assignments.iteritems():
        assignments_cc[value_id] = group_id
    cdef vector[int] counts_cc = count_assignments_cc(assignments_cc)
    cdef list counts = counts_cc
    return counts


cdef class PitmanYor:
    cdef PitmanYor_cc * ptr
    def __cinit__(self):
        self.ptr = new PitmanYor_cc()
    def __dealloc__(self):
        del self.ptr

    def __init__(self, float alpha=0.5, float d=0.0):
        self.alpha = alpha
        self.d = d

    property alpha:
        def __get__(self):
            return self.ptr.alpha
        def __set__(self, float alpha):
            assert 0 < alpha
            self.ptr.alpha = alpha

    property d:
        def __get__(self):
            return self.ptr.d
        def __set__(self, float d):
            assert 0 <= d and d < 1
            self.ptr.d = d

    def score_counts(self, list counts):
        cdef vector[int] counts_cc = counts
        cdef float score = self.ptr.score_counts(counts_cc)
        return score

    def score_add_value(
            self,
            int group_size,
            int group_count,
            int sample_size):
        return self.ptr.score_add_value(group_size, group_count, sample_size)

    def score_remove_value(
            self,
            int group_size,
            int group_count,
            int sample_size):
        return self.ptr.score_remove_value(
            group_size,
            group_count,
            sample_size)


cdef class LowEntropy:
    cdef LowEntropy_cc * ptr
    def __cinit__(self):
        self.ptr = new LowEntropy_cc()
    def __dealloc__(self):
        del self.ptr

    def __init__(self, int dataset_size=0):
        self.dataset_size = dataset_size

    property dataset_size:
        def __get__(self):
            return self.ptr.dataset_size
        def __set__(self, int dataset_size):
            assert dataset_size >= 0
            self.ptr.dataset_size = dataset_size

    def score_counts(self, list counts):
        cdef vector[int] counts_cc = counts
        cdef float score = self.ptr.score_counts(counts_cc)
        return score

    def score_add_value(
            self,
            int group_size,
            int group_count,
            int sample_size):
        return self.ptr.score_add_value(group_size, group_count, sample_size)

    def score_remove_value(
            self,
            int group_size,
            int group_count,
            int sample_size):
        return self.ptr.score_remove_value(
            group_size,
            group_count,
            sample_size)