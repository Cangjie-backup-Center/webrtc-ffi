#ifndef WEBRTC4CJ_UV_WORK_H
#define WEBRTC4CJ_UV_WORK_H
#include <uv.h>

void Cangjie_CallBack(void* data,
    void (*calculate_fib)(uv_work_t* req),
    void (*after_calculate)(uv_work_t* req, int status));

#endif // WEBRTC4CJ_UV_WORK_H
