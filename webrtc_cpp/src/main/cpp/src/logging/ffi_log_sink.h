#ifndef WEBRTC_FFI_LOG_SINK_H_
#define WEBRTC_FFI_LOG_SINK_H_

#include <string>
#include "rtc_base/logging.h"

namespace webrtc {

class ffiLogSink : public rtc::LogSink {
public:
    ffiLogSink();
    ~ffiLogSink() override;

    void OnLogMessage(const std::string& msg) override;
    void OnLogMessage(const std::string& msg, rtc::LoggingSeverity severity, const char* tag) override;
    void OnLogMessage(absl::string_view msg, rtc::LoggingSeverity severity, const char* tag) override;
    void OnLogMessage(const rtc::LogLineRef& line) override;
};

}

#endif // WEBRTC_FFI_LOG_SINK_H_