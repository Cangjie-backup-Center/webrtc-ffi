/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "ffi_video_encoder_factory.h"
#include "video_codec/hardware_video_encoder_factory.h"

namespace webrtc{

ffiHardwareVideoEncoderFactory::ffiHardwareVideoEncoderFactory(){ 
    enableH264HighProfile_ = false;
    sharedContext_ = EglEnv::GetDefault().GetContext();
}

ffiHardwareVideoEncoderFactory::~ffiHardwareVideoEncoderFactory() {}

std::shared_ptr<EglContext> ffiHardwareVideoEncoderFactory::getSharedContext(){
    return sharedContext_;
}

bool ffiHardwareVideoEncoderFactory::getEnableH264HighProfile(){
    return enableH264HighProfile_;
}

std::unique_ptr<VideoEncoderFactory> createHardwareVideoEncoderFactory(ffiHardwareVideoEncoderFactory* ffiHVEF){
    if(ffiHVEF != nullptr){
        auto sharedContext = ffiHVEF->getSharedContext();
        auto enableH264HighProfile = ffiHVEF->getEnableH264HighProfile();
        return std::make_unique<adapter::HardwareVideoEncoderFactory>(sharedContext, enableH264HighProfile);
    }
    return nullptr;
}   

}

