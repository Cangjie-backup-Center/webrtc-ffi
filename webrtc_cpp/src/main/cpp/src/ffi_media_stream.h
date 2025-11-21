/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC4CJ_FFI_MEDIA_STREAM_H
#define WEBRTC4CJ_FFI_MEDIA_STREAM_H
#include <cstdint>
#include "api/media_stream_interface.h"
#include "pc/media_stream_observer.h"

#include "ffi_exception.h"
#include "ffi_media_stream_track.h"
#include "ffi_define_struct.h"

namespace webrtc {

class FFIMediaStream {
public:
    FFIMediaStream(std::shared_ptr<PeerConnectionFactoryWrapper> factory,
                    rtc::scoped_refptr<MediaStreamInterface> stream)
    {
        factory_ = factory;
        stream_ = stream;
        observer_ = nullptr;
    }

    rtc::scoped_refptr<MediaStreamInterface> Get() const
    {
        return stream_;
    }

    ~FFIMediaStream()
    {
        if (audioMediaStreamTrackPtr != nullptr) {
            delete audioMediaStreamTrackPtr;
            audioMediaStreamTrackPtr = nullptr;
        }
        if (videoMediaStreamTrackPtr != nullptr) {
            delete videoMediaStreamTrackPtr;
            videoMediaStreamTrackPtr = nullptr;
        }
    }

    rtc::scoped_refptr<AudioTrackInterface> atif_;
    rtc::scoped_refptr<VideoTrackInterface> vtif_;

    void AddTrack(int64_t mst);
    void RemoveTrack(int64_t mst);
    int64_t GetTrackById(std::string trackId_str);
    CJ_ReturnArray GetTracks();
    CJ_ReturnArray GetAudioTracks();
    CJ_ReturnArray GetVideoTracks();
    // Napi::Value ToJson(const Napi::CallbackInfo& info);

private:
    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<MediaStreamInterface> stream_;
    std::unique_ptr<MediaStreamObserver> observer_;

    ffiMediaStreamTrack* audioMediaStreamTrackPtr = nullptr;
    ffiMediaStreamTrack* videoMediaStreamTrackPtr = nullptr;
};

}

#endif // WEBRTC4CJ_FFI_MEDIA_STREAM_H