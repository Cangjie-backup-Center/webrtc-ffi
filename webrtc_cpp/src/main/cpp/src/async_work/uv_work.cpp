//
// Created on 2025/7/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "uv_work.h"


void Cangjie_CallBack(void* data, void (*calculate_fib)(uv_work_t* req), void (*after_calculate)(uv_work_t* req, int status)) {
    uv_loop_t* loop = uv_default_loop();
    uv_work_t* req = (uv_work_t* )malloc(sizeof(uv_work_t));
    req->data = data;
    uv_queue_work(loop, req, calculate_fib, after_calculate);
}