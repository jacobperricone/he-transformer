//*****************************************************************************
// Copyright 2018-2020 Intel Corporation
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
//*****************************************************************************

#include <memory>

#include "he_tensor.hpp"
#include "ngraph/ngraph.hpp"
#include "seal/he_seal_backend.hpp"
#include "seal/he_seal_executable.hpp"
#include "test_util.hpp"
#include "util/all_close.hpp"
#include "util/ndarray.hpp"
#include "util/test_control.hpp"
#include "util/test_tools.hpp"

static const char* s_manifest = "${MANIFEST}";

namespace ngraph::runtime::he {

NGRAPH_TEST(${BACKEND_NAME}, create_backend) {
  auto backend = runtime::Backend::create("${BACKEND_NAME}");
  EXPECT_EQ(1, 1);
}

NGRAPH_TEST(${BACKEND_NAME}, create_tensor_memory_ptr) {
  auto backend = runtime::Backend::create("${BACKEND_NAME}");

  Shape shape{2, 2};
  backend->create_tensor(element::f32, shape);
}

NGRAPH_TEST(${BACKEND_NAME}, create_tensor) {
  auto backend = runtime::Backend::create("${BACKEND_NAME}");

  Shape shape{2, 2};
  void* src = nullptr;
  EXPECT_ANY_THROW(backend->create_tensor(element::f32, shape, src));
}

NGRAPH_TEST(${BACKEND_NAME}, create_cipher_tensor) {
  auto backend = runtime::Backend::create("${BACKEND_NAME}");
  auto he_backend = static_cast<HESealBackend*>(backend.get());

  Shape shape{2, 2};
  he_backend->create_cipher_tensor(element::f32, shape);
}

NGRAPH_TEST(${BACKEND_NAME}, create_plain_tensor) {
  auto backend = runtime::Backend::create("${BACKEND_NAME}");
  auto he_backend = static_cast<HESealBackend*>(backend.get());

  Shape shape{2, 2};
  he_backend->create_plain_tensor(element::f32, shape);
}

NGRAPH_TEST(${BACKEND_NAME}, validate_call_input_count) {
  auto backend = runtime::Backend::create("${BACKEND_NAME}");

  Shape shape{2, 2};

  auto a = std::make_shared<op::Parameter>(element::f32, shape);
  auto b = std::make_shared<op::Parameter>(element::f32, shape);
  auto f = std::make_shared<Function>(std::make_shared<op::Add>(a, b),
                                      ParameterVector{a, b});

  auto t_a = backend->create_tensor(element::f32, shape);
  auto t_b = backend->create_tensor(element::f32, shape);
  auto t_c = backend->create_tensor(element::f32, shape);

  auto handle = backend->compile(f);

  EXPECT_ANY_THROW(handle->call_with_validate({t_c}, {t_a}));
}

NGRAPH_TEST(${BACKEND_NAME}, validate_call_input_type) {
  auto backend = runtime::Backend::create("${BACKEND_NAME}");

  Shape shape{2, 2};

  auto a = std::make_shared<op::Parameter>(element::f32, shape);
  auto b = std::make_shared<op::Parameter>(element::f32, shape);
  auto f = std::make_shared<Function>(std::make_shared<op::Add>(a, b),
                                      ParameterVector{a, b});

  auto t_a = backend->create_tensor(element::i32, shape);
  auto t_b = backend->create_tensor(element::f32, shape);
  auto t_c = backend->create_tensor(element::f32, shape);

  auto handle = backend->compile(f);

  EXPECT_ANY_THROW(handle->call_with_validate({t_c}, {t_a, t_b}));
}

NGRAPH_TEST(${BACKEND_NAME}, validate_call_input_shape) {
  auto backend = runtime::Backend::create("${BACKEND_NAME}");

  Shape shape{2, 2};

  auto a = std::make_shared<op::Parameter>(element::f32, shape);
  auto b = std::make_shared<op::Parameter>(element::f32, shape);
  auto f = std::make_shared<Function>(std::make_shared<op::Add>(a, b),
                                      ParameterVector{a, b});

  auto t_a = backend->create_tensor(element::f32, {2, 3});
  auto t_b = backend->create_tensor(element::f32, shape);
  auto t_c = backend->create_tensor(element::f32, shape);

  auto handle = backend->compile(f);

  EXPECT_ANY_THROW(handle->call_with_validate({t_c}, {t_a, t_b}));
}

NGRAPH_TEST(${BACKEND_NAME}, validate_call_output_count) {
  auto backend = runtime::Backend::create("${BACKEND_NAME}");

  Shape shape{2, 2};

  auto a = std::make_shared<op::Parameter>(element::f32, shape);
  auto b = std::make_shared<op::Parameter>(element::f32, shape);
  auto f = std::make_shared<Function>(std::make_shared<op::Add>(a, b),
                                      ParameterVector{a, b});

  auto t_a = backend->create_tensor(element::f32, shape);
  auto t_b = backend->create_tensor(element::f32, shape);
  auto t_c = backend->create_tensor(element::f32, shape);
  auto t_d = backend->create_tensor(element::f32, shape);

  auto handle = backend->compile(f);

  EXPECT_ANY_THROW(handle->call_with_validate({t_c, t_d}, {t_a, t_b}));
}

NGRAPH_TEST(${BACKEND_NAME}, validate_call_output_type) {
  auto backend = runtime::Backend::create("${BACKEND_NAME}");

  Shape shape{2, 2};

  auto a = std::make_shared<op::Parameter>(element::f32, shape);
  auto b = std::make_shared<op::Parameter>(element::f32, shape);
  auto f = std::make_shared<Function>(std::make_shared<op::Add>(a, b),
                                      ParameterVector{a, b});

  auto t_a = backend->create_tensor(element::i32, shape);
  auto t_b = backend->create_tensor(element::f32, shape);
  auto t_c = backend->create_tensor(element::f32, shape);

  auto handle = backend->compile(f);

  EXPECT_ANY_THROW(handle->call_with_validate({t_a}, {t_b, t_c}));
}

NGRAPH_TEST(${BACKEND_NAME}, validate_call_output_shape) {
  auto backend = runtime::Backend::create("${BACKEND_NAME}");

  Shape shape{2, 2};

  auto a = std::make_shared<op::Parameter>(element::f32, shape);
  auto b = std::make_shared<op::Parameter>(element::f32, shape);
  auto f = std::make_shared<Function>(std::make_shared<op::Add>(a, b),
                                      ParameterVector{a, b});

  auto t_a = backend->create_tensor(element::f32, {2, 3});
  auto t_b = backend->create_tensor(element::f32, shape);
  auto t_c = backend->create_tensor(element::f32, shape);

  auto handle = backend->compile(f);

  EXPECT_ANY_THROW(handle->call_with_validate({t_a}, {t_c, t_b}));
}

NGRAPH_TEST(${BACKEND_NAME}, validate_batch_size) {
  auto backend = runtime::Backend::create("${BACKEND_NAME}");

  Shape shape{10000, 1};

  auto a = std::make_shared<op::Parameter>(element::f32, shape);
  auto b = std::make_shared<op::Parameter>(element::f32, shape);
  auto f = std::make_shared<Function>(std::make_shared<op::Add>(a, b),
                                      ParameterVector{a, b});

  auto handle = std::static_pointer_cast<HESealExecutable>(backend->compile(f));

  EXPECT_THROW({ handle->set_batch_size(10000); }, CheckFailure);
}

}  // namespace ngraph::runtime::he
