/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "ffi_dtmf_sender.h"
#include "ffi_exception.h"

namespace webrtc {

bool ffiDtmfSender::GetCanInsertDTMF()
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    return dtmfSender_->CanInsertDtmf();
}

const char* ffiDtmfSender::GetToneBuffer()
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    return dtmfSender_->tones().data();
}

bool ffiDtmfSender::InsertDTMF(const char* tones, int64_t duration, int64_t interToneGap)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    if (!dtmfSender_->CanInsertDtmf()) {
        CANGJIE_THROW("InvalidStateError");
    }
    
    if (duration < 0) {
        CANGJIE_THROW("InvalidStateError");
    }

    if (interToneGap < 0) {
        CANGJIE_THROW("InvalidStateError");
    }

    int32_t kDefaultDurationMs = 100;
    int32_t kMinDurationMs = 40;
    int32_t kMaxDurationMs = 6000;
    int32_t kDefaultInterToneGapMs = 70;
    int32_t kMinInterToneGapMs = 30;
    int32_t kMaxInterToneGapMs = 6000;
    
    if (duration > kMaxDurationMs) {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " The value of duration is greater than 6000";
        duration = kMaxDurationMs;
    }
    if (duration < kMinDurationMs) {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " The value of duration is less than 40";
        duration = kMinDurationMs;
    }
    if (interToneGap < kMinInterToneGapMs) {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " The value of interToneGap is less than 30";
        interToneGap = kMinInterToneGapMs;
    }
    if (interToneGap > kMaxInterToneGapMs) {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " The value of interToneGap is greater than 6000";
        interToneGap = kMaxInterToneGapMs;
    }
    bool result = dtmfSender_->InsertDtmf(tones, duration, interToneGap);
    if (result) {
        return result;
    } else {
        CANGJIE_THROW("Failed to insert DTMF");
    }
}

void ffiDtmfSender::OnToneChange(const std::string& tone, const std::string& tone_buffer)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    Dispatch(CallbackEvent<ffiDtmfSender>::Create([this, tone](ffiDtmfSender& target) {
        RTC_DCHECK_EQ(this, &target);
        if (cj_func_call_OnToneChange_) {
            cj_func_call_OnToneChange_(this->GetCJClassID(), tone.data());
        }
    }));
}

}
