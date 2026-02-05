#include "ffi_native_logging.h"
#include "hilog_sink.h"
#include "ffi_log_sink.h"

namespace webrtc {
struct StaticObjectContainer {
    std::unique_ptr<ffiLogSink> logSink;
    std::unique_ptr<HilogSink> hilogSink;
};

StaticObjectContainer& GetStaticObjects()
{
    static StaticObjectContainer* static_objects = new StaticObjectContainer();
    return *static_objects;
}

void ffiNativeLogging::EnableLogThreads()
{
    rtc::LogMessage::LogThreads(true);
    return ;
}

void ffiNativeLogging::EnableLogTimeStamps()
{
    rtc::LogMessage::LogTimestamps(true);
    return ;
}

void ffiNativeLogging::EnableLogToDebugOutput(int LoggingSeverity)
{
    auto& hilogSink = GetStaticObjects().hilogSink;
    if (hilogSink) {
        rtc::LogMessage::RemoveLogToStream(hilogSink.get());
    }

    auto severity = LoggingSeverity;
    if (severity >= rtc::LS_VERBOSE && severity <= rtc::LS_NONE) {
        if (!hilogSink) {
            hilogSink = std::make_unique<HilogSink>();
        }
        rtc::LogMessage::AddLogToStream(hilogSink.get(), rtc::LS_VERBOSE);
    }
    return ;
}

}
