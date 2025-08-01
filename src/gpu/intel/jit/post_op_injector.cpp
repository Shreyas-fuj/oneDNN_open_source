/*******************************************************************************
 * Copyright 2021-2025 Intel Corporation
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
 *******************************************************************************/

#include "gpu/intel/jit/post_op_injector.hpp"
#include "common/impl_registration.hpp"

namespace dnnl {
namespace impl {
namespace gpu {
namespace intel {
namespace jit {

using namespace ngen;

template <typename ngen_generator_t>
int post_op_injector_t<ngen_generator_t>::min_scratch_regs() {
    int regs_cnt = 0;
    for (size_t idx = 0; idx < workers_.size(); ++idx) {
        regs_cnt = nstl::max(regs_cnt, workers_[idx].min_scratch_regs());
    }
    return regs_cnt;
}

template <typename ngen_generator_t>
int post_op_injector_t<ngen_generator_t>::preferred_scratch_regs() {
    int regs_cnt = 0;
    for (size_t idx = 0; idx < workers_.size(); ++idx) {
        regs_cnt = nstl::max(regs_cnt, workers_[idx].preferred_scratch_regs());
    }
    return regs_cnt;
}

template <typename ngen_generator_t>
void post_op_injector_t<ngen_generator_t>::set_scratch(
        const ngen::GRFRange &scratch) {
    for (size_t idx = 0; idx < workers_.size(); ++idx) {
        workers_[idx].set_scratch(scratch);
        if (workers_.size() == 1) workers_[idx].prepare();
    }
    scratch_ = scratch;
}

template <typename ngen_generator_t>
void post_op_injector_t<ngen_generator_t>::compute(const ngen::GRFRange &regs) {
    for (size_t idx = 0; idx < workers_.size(); ++idx) {
        if (workers_.size() > 1) workers_[idx].prepare();
        workers_[idx].compute(regs);
    }
}

template <ngen::HW hw>
using code_gen = ngen::BinaryCodeGenerator<hw>;
REG_XELP_ISA(template struct post_op_injector_t<code_gen<gpu_xe_lp>>);
REG_XEHP_ISA(template struct post_op_injector_t<code_gen<gpu_xe_hp>>);
REG_XEHPG_ISA(template struct post_op_injector_t<code_gen<gpu_xe_hpg>>);
REG_XEHPC_ISA(template struct post_op_injector_t<code_gen<gpu_xe_hpc>>);
REG_XE2_ISA(template struct post_op_injector_t<code_gen<gpu_xe2>>);
REG_XE3_ISA(template struct post_op_injector_t<code_gen<gpu_xe3>>);

#ifdef NGEN_ASM
template struct post_op_injector_t<ngen::AsmCodeGenerator>;
#endif

} // namespace jit
} // namespace intel
} // namespace gpu
} // namespace impl
} // namespace dnnl
