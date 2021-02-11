// Copyright (c) 2020-2021, NVIDIA CORPORATION.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <nv_node/utilities/args.hpp>

#include <cudf/groupby.hpp>

#include <napi.h>

namespace nv {

/**
 * @brief An owning wrapper around a cudf::groupy::groupby.
 *
 */
class GroupBy : public Napi::ObjectWrap<GroupBy> {
 public:
  /**
   * @brief Initialize and export the Groupby JavaScript constructor and prototype.
   *
   * @param env The active JavaScript environment.
   * @param exports The exports object to decorate.
   * @return Napi::Object The decorated exports object.
   */
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  /**
   * @brief Construct a new Groupby instance
   *
   */
  static Napi::Object New();

  /**
   * @brief Construct a new Groupby instance from JavaScript.
   *
   */
  GroupBy(CallbackArgs const& args);

  /**
   * @brief Destructor called when the JavaScript VM garbage collects this Column
   * instance.
   *
   * @param env The active JavaScript environment.
   */
  void Finalize(Napi::Env env) override;

 private:
  static Napi::FunctionReference constructor;

  std::unique_ptr<cudf::groupby::groupby> groupby_;

  Napi::Value agg(Napi::CallbackInfo const& info);
  Napi::Value get_groups(Napi::CallbackInfo const& info);
};

}  // namespace nv
