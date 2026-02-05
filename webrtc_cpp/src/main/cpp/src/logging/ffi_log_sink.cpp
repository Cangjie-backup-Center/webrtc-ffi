#include "ffi_log_sink.h"

namespace webrtc {

void ffiLogSink::OnLogMessage(const std::string& msg)
{
    RTC_DCHECK_NOTREACHED();
}

// void LogSink::OnLogMessage(const string& msg, rtc::LoggingSeverity severity, const char* tag)
// {
//     tsfn_.BlockingCall(new DataType{severity, msg, tag});
// }

// void LogSink::OnLogMessage(absl::string_view msg, rtc::LoggingSeverity severity, const char* tag)
// {
//     tsfn_.BlockingCall(new DataType{severity, std::string(msg), tag});
// }

// void LogSink::OnLogMessage(const rtc::LogLineRef& line)
// {
//     // Inefficient
//     tsfn_.BlockingCall(new DataType{line.severity(), line.DefaultLogLine(), std::string(line.tag())});
// }

}