/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

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
