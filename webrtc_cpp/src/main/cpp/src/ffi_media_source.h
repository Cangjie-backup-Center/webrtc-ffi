/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC4CJ_FFI_MEDIA_SOURCE_H
#define WEBRTC4CJ_FFI_MEDIA_SOURCE_H

#include "api/media_stream_interface.h"
#include "video/video_track_source.h"
#include "audio_device/ohos_local_audio_source.h"

namespace webrtc {
class OhosLocalAudioSource;

// class FFIAudioSource {
// public:
//    FFIAudioSource(rtc::scoped_refptr<OhosLocalAudioSource> source);
//    ~FFIAudioSource();

//    static FFIAudioSource* NewInstance(rtc::scoped_refptr<OhosLocalAudioSource> source); 

// protected:
   
// private:
//    rtc::scoped_refptr<OhosLocalAudioSource> source_;


// };

// class FFIVideoSource :  public VideoCapturer::Observer{
// public:
//    FFIVideoSource(rtc::scoped_refptr<OhosVideoTrackSource> source);
//    ~FFIVideoSource();

//    static FFIVideoSource* NewInstance(rtc::scoped_refptr<OhosVideoTrackSource> source);
//    rtc::scoped_refptr<OhosVideoTrackSource> Get() const
//    {
//        return source_;
//    }

// protected:
//    void OnCapturerStarted(bool success) override;
//    void OnCapturerStopped() override;


// }

}

#endif
