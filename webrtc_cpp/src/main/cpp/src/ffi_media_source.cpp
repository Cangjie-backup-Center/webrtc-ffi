#include "ffi_media_source.h"
#include "audio_device/ohos_local_audio_source.h"
#include "rtc_base/logging.h"
#include "ffi_exception.h"

namespace webrtc {

FFIAudioSource* FFIAudioSource::NewInstance(rtc::scoped_refptr<OhosLocalAudioSource> source)
{
    if (!source) {
        CANGJIE_THROW("FFIAudioSource::NewInstance source is null");
    }

    auto ffias = new FFIAudioSource(source);
    return ffias;
}

FFIAudioSource::FFIAudioSource(rtc::scoped_refptr<OhosLocalAudioSource> ohlocalsource)
{
    source_ = ohlocalsource;
}

FFIAudioSource::~FFIAudioSource()
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}

rtc::scoped_refptr<OhosLocalAudioSource> FFIAudioSource::Get() const
{
    return source_;
}

// FFI::Value FFIAudioSource::GetState(const FFI::CallbackInfo& info)
// {
//     RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

//     if (!source_) {
//         NAPI_THROW(Error::New(info.Env(), "Illegal state"), info.Env().Undefined());
//     }

//     auto state = source_->state();
//     switch (state) {
//         case MediaSourceInterface::kInitializing:
//             return String::New(info.Env(), kEnumNameSourceStateInitializing);
//         case MediaSourceInterface::kLive:
//             return String::New(info.Env(), kEnumNameSourceStateLive);
//         case MediaSourceInterface::kEnded:
//             return String::New(info.Env(), kEnumNameSourceStateEnded);
//         case MediaSourceInterface::kMuted:
//             return String::New(info.Env(), kEnumNameSourceStateMuted);
//         default:
//             break;
//     }

//     NAPI_THROW(Error::New(info.Env(), "Invalid state"), info.Env().Undefined());
// }

void FFIAudioSource::Release()
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    if (!source_) {
        CANGJIE_THROW("FFIAudioSource::Release source is null");
    }

    source_ = nullptr;
}

FFIVideoSource* FFIVideoSource::NewInstance(rtc::scoped_refptr<OhosVideoTrackSource> source)
{
    if (!source) {
        CANGJIE_THROW("FFIVideoSource::NewInstance source is null");
    }

    auto ffivs = new FFIVideoSource(source);
    return ffivs;
}

FFIVideoSource::FFIVideoSource(rtc::scoped_refptr<OhosVideoTrackSource> source)
{
    source_ = source;

    if (source_) {
        source_->SetCapturerObserver(this);
    }
}

FFIVideoSource::~FFIVideoSource()
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    source_->SetCapturerObserver(nullptr);
    source_ = nullptr;

//    RemoveAllEventHandlers();
}

// FFI::Value FFIVideoSource::GetState(const FFI::CallbackInfo& info)
// {
//     RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

//     if (!source_) {
//         NAPI_THROW(Error::New(info.Env(), "Illegal state"), info.Env().Undefined());
//     }

//     auto source = static_cast<VideoTrackSourceInterface*>(source_.get());
//     auto state = source->state();
//     switch (state) {
//         case MediaSourceInterface::kInitializing:
//             return String::New(info.Env(), kEnumNameSourceStateInitializing);
//         case MediaSourceInterface::kLive:
//             return String::New(info.Env(), kEnumNameSourceStateLive);
//         case MediaSourceInterface::kEnded:
//             return String::New(info.Env(), kEnumNameSourceStateEnded);
//         case MediaSourceInterface::kMuted:
//             return String::New(info.Env(), kEnumNameSourceStateMuted);
//         default:
//             break;
//     }

//     NAPI_THROW(Error::New(info.Env(), "Invalid state"), info.Env().Undefined());
// }

void FFIVideoSource::Release()
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    if (!source_) {
        CANGJIE_THROW("FFIVideoSource::Release source is null");
    }

    source_->AddRef();

    source_->SetCapturerObserver(nullptr);
    source_ = nullptr;

//    RemoveAllEventHandlers();
}

void FFIVideoSource::OnCapturerStarted(bool success)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " success: " << success;
}

void FFIVideoSource::OnCapturerStopped()
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}

} // namespace webrtc
