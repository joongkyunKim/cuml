/*
 * Copyright (c) 2018, NVIDIA CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "binary_op.h"
#include "cuda_utils.h"
#include "unary_op.h"


namespace MLCommon {
namespace LinAlg {

/**
 * @defgroup ScalarOps Scalar operations on the input buffer
 * @param out the output buffer
 * @param in the input buffer
 * @param scalar the scalar used in the operations
 * @param len number of elements in the input buffer
 * @param stream cuda stream where to launch work
 * @{
 */
template <typename math_t>
void powerScalar(math_t *out, const math_t *in, math_t scalar, int len,
               cudaStream_t stream = 0) {
  unaryOp(out, in, len,
          [scalar] __device__(math_t in) { return myPow(in, scalar); },
          stream);
}
/** @} */

/**
 * @defgroup BinaryOps Element-wise binary operations on the input buffers
 * @param out the output buffer
 * @param in1 the first input buffer
 * @param in2 the second input buffer
 * @param len number of elements in the input buffers
 * @param stream cuda stream where to launch work
 * @{
 */
template <typename math_t>
void power(math_t *out, const math_t *in1, const math_t *in2, int len,
         cudaStream_t stream = 0) {
  binaryOp(out, in1, in2, len,
           [] __device__(math_t a, math_t b) { return myPow(a, b); }, stream);
}
/** @} */

}; // end namespace LinAlg
}; // end namespace MLCommon