//
// Created on 2025/7/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_UV_WORK_H
#define WEBRTC4CJ_UV_WORK_H
#include <uv.h>

void Cangjie_CallBack(void* data, void (*calculate_fib)(uv_work_t* req), void (*after_calculate)(uv_work_t* req, int status));

#endif //WEBRTC4CJ_UV_WORK_H
