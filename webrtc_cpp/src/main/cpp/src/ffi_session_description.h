//
// Created on 2025/8/18.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_SESSION_DESCRIPTION_H
#define WEBRTC4CJ_FFI_SESSION_DESCRIPTION_H

#include <string>
namespace webrtc {
class ffiSessionDescription {
public:

    static ffiSessionDescription *NewInstance(std::string sdp, std::string type) {
        return new ffiSessionDescription(sdp, type);
    }

    ffiSessionDescription(std::string sdp, std::string type) {
        sdp_ = sdp;
        type_ = type;
    }

protected:
    std::string GetSdp();
    std::string GetType();

private:
    std::string sdp_;
    std::string type_;
};
}

#endif //WEBRTC4CJ_FFI_SESSION_DESCRIPTION_H
