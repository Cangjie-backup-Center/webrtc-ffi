//
// Created on 2025/8/18.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_CJ_CLASS_H
#define WEBRTC4CJ_FFI_CJ_CLASS_H

#include "stdint.h"
#include <cstdint>

namespace CJ_CLASS_BASE {

class FFICangjieClassID {
public:
    virtual ~FFICangjieClassID() = default;
    void SetCJClassID(int64_t id) {   // 设置对应cpp的类和仓颉的类之间的id交换
        cj_class_key = id;
    }
    int64_t GetCJClassID() const {
        return cj_class_key;
    }
protected:
    int64_t cj_class_key = 0;
};


}

#endif //WEBRTC4CJ_FFI_CJ_CLASS_H
