/*******************************************************************************
* Copyright 2022-2025 Intel Corporation
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

#ifndef GPU_INTEL_JIT_CODEGEN_CODEGEN_HPP
#define GPU_INTEL_JIT_CODEGEN_CODEGEN_HPP

#include "gpu/intel/jit/codegen/kernel.hpp"
#include "ngen.hpp"

namespace dnnl {
namespace impl {
namespace gpu {
namespace intel {
namespace jit {

template <typename ngen_generator_t>
void convert_ir_to_ngen(const stmt_t &body, ngen_generator_t *host,
        const walk_order_t *kernel_grid_walk_order = nullptr);

REG_XELP_ISA(extern template void convert_ir_to_ngen(const stmt_t &body,
        ir_kernel_t<ngen::HW::XeLP> *host,
        const walk_order_t *kernel_grid_walk_order));
REG_XEHP_ISA(extern template void convert_ir_to_ngen(const stmt_t &body,
        ir_kernel_t<ngen::HW::XeHP> *host,
        const walk_order_t *kernel_grid_walk_order));
REG_XEHPG_ISA(extern template void convert_ir_to_ngen(const stmt_t &body,
        ir_kernel_t<ngen::HW::XeHPG> *host,
        const walk_order_t *kernel_grid_walk_order));
REG_XEHPC_ISA(extern template void convert_ir_to_ngen(const stmt_t &body,
        ir_kernel_t<ngen::HW::XeHPC> *host,
        const walk_order_t *kernel_grid_walk_order));
REG_XE2_ISA(extern template void convert_ir_to_ngen(const stmt_t &body,
        ir_kernel_t<ngen::HW::Xe2> *host,
        const walk_order_t *kernel_grid_walk_order));
REG_XE3_ISA(extern template void convert_ir_to_ngen(const stmt_t &body,
        ir_kernel_t<ngen::HW::Xe3> *host,
        const walk_order_t *kernel_grid_walk_order));

} // namespace jit
} // namespace intel
} // namespace gpu
} // namespace impl
} // namespace dnnl

#endif
