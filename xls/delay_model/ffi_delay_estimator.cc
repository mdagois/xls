// Copyright 2023 The XLS Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "xls/delay_model/ffi_delay_estimator.h"

#include <cstdint>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "xls/ir/op.h"

namespace xls {
absl::StatusOr<int64_t> FfiDelayEstimator::GetOperationDelayInPs(
    Node* node) const {
  if (node->op() != Op::kInvoke) {
    return absl::UnimplementedError("FFI delay estimate only for kInvoke");
  }
  if (!fallback_delay_estimate_.has_value()) {
    return absl::NotFoundError("No --ffi_fallback_delay_ps provided.");
  }
  // TODO(hzeller): 2023-07-11: Here, extract function name and operands
  // and read best estimation from a file needs to be provided/generated by the
  // user.
  return *fallback_delay_estimate_;
}
}  // namespace xls
