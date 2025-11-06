/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include <string>

#ifndef WEBRTC4CJ_FFI_EXCEPTION_H
#define WEBRTC4CJ_FFI_EXCEPTION_H

void CANGJIE_THROW(std::string obj);
extern "C" {
    void setThrowCangjieException(void (*func)(const char *obj));
}

#endif // WEBRTC4CJ_FFI_EXCEPTION_H
