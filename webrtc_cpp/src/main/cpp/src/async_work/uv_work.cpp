//
// Created on 2025/7/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "uv_work.h"
#include <stdlib.h>
#include <pthread.h>

void Cangjie_CallBack(void* data, void (*calculate_fib)(uv_work_t* req), void (*after_calculate)(uv_work_t* req, int status)) {
    uv_loop_t* loop = uv_default_loop();
    uv_work_t* req = (uv_work_t* )malloc(sizeof(uv_work_t));
    req->data = data;
    uv_queue_work(loop, req, calculate_fib, after_calculate);
}

uv_loop_t custom_loop;
uv_async_t async_handle;

void async_cb(uv_async_t* handle) {
    printf("Async callback in loop thread\n");
}

void* loop_thread(void* arg) {
    uv_run(&custom_loop, UV_RUN_DEFAULT);
    return NULL;
}

int main() {
    uv_loop_init(&custom_loop);
    uv_async_init(&custom_loop, &async_handle, async_cb);

    pthread_t thread;
    pthread_create(&thread, NULL, loop_thread, NULL);

    // 主线程触发异步事件
    uv_async_send(&async_handle);

    pthread_join(thread, NULL);
    uv_loop_close(&custom_loop);
    return 0;
}
