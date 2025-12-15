#ifndef WEBRTC_AUDIO_SOURCE_H
#define WEBRTC_AUDIO_SOURCE_H

#include "api/media_stream_interface.h"

#include "video/video_track_source.h"
#include "audio_device/ohos_local_audio_source.h"
#include "utils/marcos.h"

namespace webrtc {

class OhosLocalAudioSource;

template <typename T>
class FFIMediaSource  {
public:

    virtual ~FFIMediaSource(){}
    explicit FFIMediaSource(/*const FFI::CallbackInfo& info*/) {}
};

class FFIAudioSource : public FFIMediaSource<FFIAudioSource> {
public:
    FFIAudioSource(webrtc::FFIAudioSource *p1) {}

    static FFIAudioSource* NewInstance(rtc::scoped_refptr<OhosLocalAudioSource> source);

    ~FFIAudioSource() override;

    rtc::scoped_refptr<OhosLocalAudioSource> Get() const;

protected:

    explicit FFIAudioSource(rtc::scoped_refptr<OhosLocalAudioSource> ohlocalsource);

    void GetState();
    void Release();

private:

    rtc::scoped_refptr<OhosLocalAudioSource> source_;
};

class FFIVideoSource : public FFIMediaSource<FFIVideoSource>, public VideoCapturer::Observer {
public:
    static FFIVideoSource* NewInstance(rtc::scoped_refptr<OhosVideoTrackSource> source);

    ~FFIVideoSource() override;

    rtc::scoped_refptr<OhosVideoTrackSource> Get() const
    {
        return source_;
    }

protected:

    explicit FFIVideoSource(rtc::scoped_refptr<OhosVideoTrackSource> ohlocalsource);

    void GetState();
    void Release();

protected:
    void OnCapturerStarted(bool success) override;
    void OnCapturerStopped() override;

    void
    OnFrameCaptured(rtc::scoped_refptr<VideoFrameBuffer> buffer, int64_t timestampUs, VideoRotation rotation) override
    {
    }

private:
    rtc::scoped_refptr<OhosVideoTrackSource> source_;
    rtc::Thread* signalThread_{};

    mutable std::mutex eventMutex_;
};

} // namespace webrtc

#endif // WEBRTC_AUDIO_SOURCE_H
