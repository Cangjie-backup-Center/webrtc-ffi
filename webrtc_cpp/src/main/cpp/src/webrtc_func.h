#ifndef SOFT_FUNC_H
#define SOFT_FUNC_H
#include "ffi_exception.h"
#include "hilog/log.h"
#define SOFT_MEMCPY_SUCCESS 0
#define SOFT_MEMCPY_NULL_POINTER -1
#define SOFT_MEMCPY_INSUFFICIENT_SPACE -2

#define CHAR_PTR char*
#define OHOS_LOG_DOMAIN 0xD001234

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