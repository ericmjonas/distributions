// Copyright (c) 2014, Salesforce.com, Inc.  All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// - Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
// - Neither the name of Salesforce.com nor the names of its contributors
//   may be used to endorse or promote products derived from this
//   software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
// OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
// TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
// USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <distributions/models/gp.hpp>
#include <distributions/vector_math.hpp>

namespace distributions
{

void GammaPoisson::classifier_score (
        const Classifier & classifier,
        const Value & value,
        float * scores_accum,
        rng_t &) const
{
    const size_t size = classifier.groups.size();
    const float value_noalias = value;
    float * __restrict__ scores_accum_noalias = scores_accum;
    const float * __restrict__ score = classifier.score.data();
    const float * __restrict__ post_alpha = classifier.post_alpha.data();
    const float * __restrict__ score_coeff = classifier.score_coeff.data();
    float * __restrict__ temp = classifier.temp.data();

    const float log_factorial_value = fast_log_factorial(value);
    for (size_t i = 0; i < size; ++i) {
        temp[i] = fast_lgamma(post_alpha[i] + value_noalias);
    }
    for (size_t i = 0; i < size; ++i) {
        scores_accum_noalias[i] += score[i]
            + temp[i]
            - log_factorial_value
            + score_coeff[i] * value_noalias;
    }
}

} // namespace distributions
