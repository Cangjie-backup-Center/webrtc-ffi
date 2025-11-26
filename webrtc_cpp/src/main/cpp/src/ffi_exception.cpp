/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "ffi_exception.h"

extern "C" {
    void (*throw_cangjie_exception)(const char *obj);
    void setThrowCangjieException(void (*func)(const char *obj))
    {
        throw_cangjie_exception = func;
    }
}

void CANGJIE_THROW(std::string msg)
{
    if (throw_cangjie_exception) {
        if (!msg.empty()) {
            throw_cangjie_exception(msg.c_str());
        } else {
            throw_cangjie_exception("");
        }
    }
    std::string().swap(msg);
}