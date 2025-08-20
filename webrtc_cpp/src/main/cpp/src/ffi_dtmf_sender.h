//
// Created on 2025/8/18.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_DTMF_SENDER_H
#define WEBRTC4CJ_FFI_DTMF_SENDER_H


#include "dtmf_sender_interface.h"
#include "event/ffi_event_target.h"
#include "ffi_cj_class.h"
#include <cstdint>
namespace webrtc {

class ffiDtmfSender : public FFIEventTarget<ffiDtmfSender>, 
                    public DtmfSenderObserverInterface ,
                    public CJ_CLASS_BASE::FFICangjieClassID{
    
public:
    
    static ffiDtmfSender* NewInstance(rtc::scoped_refptr<DtmfSenderInterface> dtmfSender) {
        return new ffiDtmfSender(dtmfSender);
    }
    
    ffiDtmfSender(rtc::scoped_refptr<DtmfSenderInterface> dtmfSender) {
        dtmfSender_ = dtmfSender;
    }
    
    ~ffiDtmfSender() {}
    
public:
    bool GetCanInsertDTMF();
    const char* GetToneBuffer();

    bool InsertDTMF(const char* tones, int64_t duration, int64_t interToneGap);
    void OnToneChange(const std::string& tone, const std::string& tone_buffer) override;
    void (*cj_func_call_OnToneChange_)(int64_t id, const char* tone) = nullptr;
private:

    rtc::scoped_refptr<DtmfSenderInterface> dtmfSender_;
};


}

#endif //WEBRTC4CJ_FFI_DTMF_SENDER_H
