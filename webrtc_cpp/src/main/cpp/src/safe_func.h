#ifndef SOFT_FUNC_H
#define SOFT_FUNC_H
#include "ffi_exception.h"

#define SOFT_MEMCPY_SUCCESS 0
#define SOFT_MEMCPY_NULL_POINTER -1
#define SOFT_MEMCPY_INSUFFICIENT_SPACE -2

#define SOFT_MEMSET_SUCCESS 0
#define SOFT_MEMSET_NULL_POINTER -1
#define SOFT_MEMSET_INSUFFICIENT_SPACE -2

template<typename T>
int32_t safe_memcpy(void *dest, uint32_t dest_size, const T *src, uint32_t src_size) {
    if(!dest || !src) {
        CANGJIE_THROW("safe_memcpy null pointer passed to safe_memcpy.");
        return SOFT_MEMCPY_NULL_POINTER;
    }
    if(dest_size < src_size) {
        CANGJIE_THROW("safe_memcpy insufficient space in the target buffer.");
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
int32_t safe_memset(void *dest, uint32_t dest_size, T ch, uint32_t count) {
    if(!dest){
        CANGJIE_THROW("safe_memset null pointer passed to safe_memset.");
        return SOFT_MEMSET_NULL_POINTER;
    }
    if(count > dest_size) {
        CANGJIE_THROW("safe_memset offset out of bounds.");
        return SOFT_MEMSET_INSUFFICIENT_SPACE;
    }

    T *dest_ptr = reinterpret_cast<T*>(dest);
    for (uint32_t i = 0; i < count; ++i) {
        dest_ptr[i] = ch;
    }
    return SOFT_MEMSET_SUCCESS;
}

template<typename T>
int32_t safe_strncpy(T *dest, uint32_t dest_size, const T *src, uint32_t src_size) {
    if(!dest || !src) {
        CANGJIE_THROW("safe_strncpy null pointer passed to safe_strncpy.");
        return SOFT_MEMCPY_NULL_POINTER;
    }
    if(dest_size < src_size) {
        CANGJIE_THROW("safe_strncpy insufficient space in the target buffer.");
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