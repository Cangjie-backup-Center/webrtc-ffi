/**
 * Copyright (c) Huawei Technologies Co., Ltd. 2024-2025. All rights reserved.
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

#ifndef WEBRTC_EGL_CONTEXT_H
#define WEBRTC_EGL_CONTEXT_H

#include <memory>

#include <EGL/egl.h>

namespace webrtc {

class EglContext : public std::enable_shared_from_this<EglContext> {
public:
    virtual ~EglContext() = default;
    virtual EGLContext GetRawContext() = 0;
};

} // namespace webrtc

#endif // WEBRTC_EGL_CONTEXT_H
