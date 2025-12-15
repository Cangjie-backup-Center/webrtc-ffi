#ifndef WEBRTC_FFI_NATIVE_LOGGING_H_
#define WEBRTC_FFI_NATIVE_LOGGING_H_

namespace webrtc {

class ffiNativeLogging {
public:
    explicit ffiNativeLogging();
    static void EnableLogThreads();
    static void EnableLogTimeStamps();
    static void EnableLogToDebugOutput(int LoggingSeverity);
};

} // namespace webrtc


#endif // WEBRTC_FFI_NATIVE_LOGGING_H_