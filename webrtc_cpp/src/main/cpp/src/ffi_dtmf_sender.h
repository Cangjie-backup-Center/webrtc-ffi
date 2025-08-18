//
// Created on 2025/8/18.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_DTMF_SENDER_H
#define WEBRTC4CJ_FFI_DTMF_SENDER_H


#include "dtmf_sender_interface.h"
#include "event/ffi_event_target.h"
namespace webrtc {

class ffiDtmfSender : public FFIEventTarget<ffiDtmfSender>, public DtmfSenderObserverInterface {
    
public:
    
    static ffiDtmfSender* NewInstance(rtc::scoped_refptr<DtmfSenderInterface> dtmfSender) {
        return new ffiDtmfSender(dtmfSender);
    }
    
    ffiDtmfSender(rtc::scoped_refptr<DtmfSenderInterface> dtmfSender) {
        dtmfSender_ = dtmfSender;
    }
    
    ~ffiDtmfSender() override;
    
public:
    //     // JS
    //    Napi::Value GetCanInsertDTMF(const Napi::CallbackInfo& info);
    //    Napi::Value GetToneBuffer(const Napi::CallbackInfo& info);
    //
    //    Napi::Value GetEventHandler(const Napi::CallbackInfo& info);
    //    void SetEventHandler(const Napi::CallbackInfo& info, const Napi::Value& value);
    //
    //    Napi::Value InsertDTMF(const Napi::CallbackInfo& info);
    //    Napi::Value ToJson(const Napi::CallbackInfo& info);
    
    
private:

    rtc::scoped_refptr<DtmfSenderInterface> dtmfSender_;
};


}

#endif //WEBRTC4CJ_FFI_DTMF_SENDER_H
