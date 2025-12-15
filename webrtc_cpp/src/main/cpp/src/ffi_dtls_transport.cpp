#include "ffi_dtls_transport.h"

namespace webrtc {

void ffiDtlsTransport::OnStateChange(DtlsTransportInformation info)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    auto dtlsTransportState = info.state();

    Dispatch(
        CallbackEvent<ffiDtlsTransport>::Create([this, dtlsTransportState](ffiDtlsTransport& target) {
            RTC_DCHECK_EQ(this, &target);
            // const char cjEventNameStateChange[] = "statechange";

            if (dtlsTransportState == webrtc::DtlsTransportState::kClosed) {
                target.Stop();
            }
        })
    );
}

void ffiDtlsTransport::OnError(RTCError error)
{
    RTC_DLOG(LS_ERROR) << __FUNCTION__ << ": " << error.message();

    Dispatch(
        CallbackEvent<ffiDtlsTransport>::Create([this](ffiDtlsTransport& target) {
            RTC_DCHECK_EQ(this, &target);
            const char cjEventNameError[] = "error";
        })
    );
}

} // namespace webrtc