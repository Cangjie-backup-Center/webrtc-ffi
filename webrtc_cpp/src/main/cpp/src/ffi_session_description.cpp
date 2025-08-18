//
// Created on 2025/8/18.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "ffi_session_description.h"

namespace webrtc {


    std::string ffiSessionDescription::GetSdp(){
        return sdp_;
    }
    std::string ffiSessionDescription::GetType(){
        return type_;
    }
}