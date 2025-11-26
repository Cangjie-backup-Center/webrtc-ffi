/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC4CJ_FFI_CJ_CLASS_H
#define WEBRTC4CJ_FFI_CJ_CLASS_H

#include "stdint.h"
#include <cstdint>

namespace CJ_CLASS_BASE {

class ffiCjClass {
public:
    virtual ~ffiCjClass() = default;
    void SetCJClassID(int64_t id)
    {   // 设置对应cpp的类和仓颉的类之间的id交换
        cj_class_key = id;
    }
    int64_t GetCJClassID() const
    {
        return cj_class_key;
    }
protected:
    int64_t cj_class_key = 0;
};

}

#endif // WEBRTC4CJ_FFI_CJ_CLASS_H
