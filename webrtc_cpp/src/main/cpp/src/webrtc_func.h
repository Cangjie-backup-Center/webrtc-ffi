/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef SOFT_FUNC_H
#define SOFT_FUNC_H
#include "ffi_exception.h"

#define SOFT_MEMCPY_SUCCESS 0
#define SOFT_MEMCPY_NULL_POINTER -1
#define SOFT_MEMCPY_INSUFFICIENT_SPACE -2

#define SOFT_MEMSET_SUCCESS 0
#define SOFT_MEMSET_NULL_POINTER -1
#define SOFT_MEMSET_INSUFFICIENT_SPACE -2

#define CHAR_PTR char*

template<typename T>
int32_t webrtc_mcp(void *dest, uint32_t dest_size, const T *src, uint32_t src_size)
{
    if (!dest || !src) {
        CANGJIE_THROW("webrtc_mcp null pointer passed to webrtc_mcp.");
        return SOFT_MEMCPY_NULL_POINTER;
    }
    if (dest_size < src_size) {
        CANGJIE_THROW("webrtc_mcp insufficient space in the target buffer.");
        return SOFT_MEMCPY_INSUFFICIENT_SPACE;
    }
    T *dest_ptr = static_cast<T*>(dest);
    const T *src_ptr = static_cast<const T*>(src);
    for (uint32_t i = 0; i < src_size; ++i) {
        dest_ptr[i] = src_ptr[i];
    }
    return SOFT_MEMCPY_SUCCESS;
}

template<typename T>
int32_t webrtc_mst(void *dest, uint32_t dest_size, T ch, uint32_t count)
{
    if (!dest) {
        CANGJIE_THROW("webrtc_mst null pointer passed to webrtc_mst.");
        return SOFT_MEMSET_NULL_POINTER;
    }
    if (count > dest_size) {
        CANGJIE_THROW("webrtc_mst offset out of bounds.");
        return SOFT_MEMSET_INSUFFICIENT_SPACE;
    }

    T *dest_ptr = reinterpret_cast<T*>(dest);
    for (uint32_t i = 0; i < count; ++i) {
        dest_ptr[i] = ch;
    }
    return SOFT_MEMSET_SUCCESS;
}

template<typename T>
int32_t webrtc_scp(T *dest, uint32_t dest_size, const T *src, uint32_t src_size)
{
    if (!dest || !src) {
        CANGJIE_THROW("webrtc_scp null pointer passed to webrtc_scp.");
        return SOFT_MEMCPY_NULL_POINTER;
    }
    if (dest_size < src_size) {
        CANGJIE_THROW("webrtc_scp insufficient space in the target buffer.");
        return SOFT_MEMCPY_INSUFFICIENT_SPACE;
    }
    T *dest_ptr = static_cast<T*>(dest);
    const T *src_ptr = static_cast<const T*>(src);
    for (uint32_t i = 0; i < src_size; ++i) {
        dest_ptr[i] = src_ptr[i];
    }
    dest_ptr[src_size] = '\0';
    return SOFT_MEMCPY_SUCCESS;
}

#endif // SOFT_FUNC_H