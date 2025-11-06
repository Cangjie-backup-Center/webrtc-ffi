/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "ffi_session_description.h"

namespace webrtc {


    std::string ffiSessionDescription::GetSdp(){
        return sdp_;
    }
    std::string ffiSessionDescription::GetType(){
        return type_;
    }
}