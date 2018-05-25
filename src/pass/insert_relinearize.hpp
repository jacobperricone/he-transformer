/*******************************************************************************
* Copyright 2017-2018 Intel Corporation
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

#pragma once

#include "ngraph/pass/pass.hpp"

namespace ngraph
{
    class Function;

    namespace runtime
    {
        namespace he
        {
            namespace pass
            {
                class InsertRelinearize : public ngraph::pass::CallGraphPass
                {
                public:
                    virtual bool
                        run_on_call_graph(const std::list<std::shared_ptr<Node>>& nodes) override;
                };
            }
        }
    }
}