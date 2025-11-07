/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC4CJ_FFI_DEFINE_STRUCT_H
#define WEBRTC4CJ_FFI_DEFINE_STRUCT_H

#include "api/rtp_parameters.h"
#include <cstdint>

//enum class FFIRTCErrorDetailType {
//  NONE,
//  DATA_CHANNEL_FAILURE,
//  DTLS_FAILURE,
//  FINGERPRINT_FAILURE,
//  SCTP_FAILURE,
//  SDP_SYNTAX_ERROR,
//  HARDWARE_ENCODER_NOT_AVAILABLE,
//  HARDWARE_ENCODER_ERROR,
//};
enum class FFIRTCIceProtocol { TCP, UDP };
enum class FFIRTCIceCandidateType { HOST, PRFLX, RELAY, SRFLX };
enum class FFIRTCIceTcpCandidateType { ACTIVE, PASSIVE, SO };
enum class FFIRTCIceComponent { RTP, RTCP };
enum class FFIRTCIceGathererState { COMPLETE, GATHERING, NEW };
enum class FFIRTCIceTransportState { CHECKING, CLOSED, COMPLETED, CONNECTED, DISCONNECTED, FAILED, NEW };
enum class FFIRTCIceRole { UNKNOWN, CONTROLLING, CONTROLLED };
enum class FFIRTCSdpType { OFFER, ANSWER, PRANSWER, ROLLBACK };
enum class FFIBinaryType { BLOB, ARRAYBUFFER };
enum class FFIDataChannelState { CLOSED, CLOSING, CONNECTING, OPEN };
enum class FFIRTCDtlsTransportState { NEW, CONNECTING, CONNECTED, CLOSED, FAILED };
enum class FFIRTCIceGatheringState { NEW, GATHERING, COMPLETE };
enum class FFIRTCIceConnectionState { CHECKING, CLOSED, COMPLETED, CONNECTED, DISCONNECTED, FAILED, NEW };
enum class FFIRTCSignalingState {
    CLOSED,
    HAVE_LOCAL_OFFER,
    HAVE_LOCAL_PRANSWER,
    HAVE_REMOTE_OFFER,
    HAVE_REMOTE_PRANSWER,
    STABLE
};
enum class FFIRTCPeerConnectionState { CLOSED, CONNECTED, CONNECTING, DISCONNECTED, FAILED, NEW };
enum class FFIRTCBundlePolicy { BALANCED, MAX_BUNDLE, MAX_COMPAT };
enum class FFIRTCRtcpMuxPolicy { REQUIRE };
enum class FFIRTCIceTransportPolicy { ALL, RELAY };
enum class FFIDegradationPreference { BALANCED, MAINTAIN_FRAMERATE, MAINTAIN_RESOLUTION };
// enum clasFFIs RTCPriorityType { HIGH, LOW, MEDIUM, VERY_LOW};
enum class FFIRTCRtpTransceiverDirection { INACTIVE, RECVONLY, SENDONLY, SENDRECV, STOPPED };
enum class FFIRTCSctpTransportState { CONNECTING, CONNECTED, CLOSED };
enum class FFIRTCStatsType {
    CANDIDATE_PAIR,
    CERTIFICATE,
    CODEC,
    DATA_CHANNEL,
    INBOUND_RTP,
    LOCAL_CANDIDATE,
    MEDIA_PLAYOUT,
    MEDIA_SOURCE,
    OUTBOUND_RTP,
    PEER_CONNECTION,
    REMOTE_CANDIDATE,
    REMOTE_INBOUND_RTP,
    REMOTE_OUTBOUND_RTP,
    TRANSPORT
};
enum class FFIrtcstatsicecandidatepairstate { FAILED, FROZEN, IN_PROGRESS, SUCCEEDED, WAITING };
enum class FFIMediaStreamTrackState { LIVE, ENDED };
enum class FFIMediaDeviceKind { AUDIOINPUT, AUDIOOUTPUT, VIDEOINPUT };
enum class FFIMediaSourceState { INITIALIZING, LIVE, ENDED, MUTED };
enum class FFIVideoFacingModeEnum { USER, ENVIRONMENT, LEFT, RIGHT };
enum class FFIVideoResizeModeEnum { NONE, CROP_AND_SCALE };
enum class FFIAudioErrorType { INIT, START_EXCEPTION, START_STATE_MISMATCH, GENERAL };
enum class FFIAudioState { START, STOP };
enum class FFIScreenCaptureMode { HOME_SCREEN, SPECIFIED_SCREEN, SPECIFIED_WINDOW };
enum class FFIScreenCaptureAudioFilterEnum { CURRENT_APP, NOTIFICATION };


typedef struct {
    bool echo_cancellation;
    // bool auto_gain_control;
    bool noise_suppression;
    // bool highpass_filter;
    // bool stereo_swapping;
    // int audio_jitter_buffer_max_packets;
    // bool audio_jitter_buffer_fast_accelerate;
    // int audio_jitter_buffer_min_delay_ms;
    // bool audio_network_adaptor;
    // std::string audio_network_adaptor_config;
    // bool init_recording_on_send;
}FFIAudioOptions;

typedef struct {
    double width;
    double height;
    char* facingMode;
    bool isScreencast;
}FFICreateVideoSourceParameters;


typedef struct {
    double width;
    double height;
    double aspectRatio;
    double frameRate;
    char *facingMode;
    char *resizeMode;
    double sampleRate;
    double sampleSize;
    bool echoCancellation;
    bool autoGainControl;
    bool noiseSuppression;
    double latency;
    double channelCount;
    char *deviceId;
    char *groupId;
    char *ohosScreenCaptureMode;
    double ohosScreenCaptureDisplayId;
    char *ohosScreenCaptureMissionId;
    char *ohosScreenCaptureWindowFilter;
    char *ohosScreenCaptureAudioFilter;
    char *ohosScreenCaptureSkipPrivacyMode;
    bool ohosScreenCaptureAutoRotation;
} CJ_MediaTrackConstraintSet;


typedef struct {
    CJ_MediaTrackConstraintSet obj;
    bool boolean;
    bool isBool;
} CJ_TO_CPP_DisplayMediaStreamOptions;


typedef struct {
    const char *deviceId;
    const char *groupId;
    const char *label;
    const char *kind;
} CJ_EnumerateDevicesInfo;

typedef struct {
    const char *id;
    const char *kind;
    const char *readyState;
    bool enabled;
} CJ_ffiMediaStreamTrackJson;

typedef struct {
    const char *name;
    const bool isSupported;
} CJ_SupportedConstraints;

// c侧数组需要返回长度, 结构体
typedef struct {
    CJ_EnumerateDevicesInfo *ptr;
    int64_t size;
} CJ_ReturnEnumerateDevicesInfo;

typedef struct {
    int64_t *ptr;
    int64_t size;
} CJ_ReturnArray;

typedef struct {
    int64_t *ptr;
    int64_t size;
} CJ_ArrayMediaStream;

typedef struct {
    char **urls;
    int64_t urls_size;
    char *username;
    int64_t username_size;
    char *credential;
    int64_t credential_size;
} CJ_RTCIceServer;

typedef struct {
    char *algorithm;
    int64_t algorithm_size;
    char *value;
    int64_t value_size;
} CJ_RTCDtlsFingerprint;


typedef struct {
    int64_t expires;
    CJ_RTCDtlsFingerprint* credential;
    int64_t credential_size;
} CJ_RTCCertificate;

typedef struct {
    CJ_RTCIceServer *iceServers;
    int64_t iceServers_size;
    int64_t iceTransportPolicy;  // 枚举
    int64_t bundlePolicy;  // 枚举
    int64_t rtcpMuxPolicy;  // 枚举
    CJ_RTCCertificate *certificates;
    int64_t certificates_size;
    int64_t iceCandidatePoolSize;
} CJ_RTCConfiguration;

typedef struct {
    char *sdp;
    int64_t sdp_size;
    char *RTCSdpType;
    int64_t RTCSdpType_size;
    bool undefined = true; // 如果 true , 其他值就无效了
} CJ_RTCSessionDescription;

typedef struct {
    char *sdp;
    char *RTCSdpType;
    bool isFail = true; // 如果 true , 其他值就无效了
    char* msg;
} CJ_FFICreateSdpObserver_result;






//typedef struct {
//    int64_t maxChannels;
//    int64_t maxMessageSize;
//    char *RTCSctpTransportState;
//    int64_t RTCSctpTransportState_size;
//    int64_t RTCDtlsTransport_ptr; // rtc::scoped_refptr<SctpTransportInterface>
//    bool undefined = true;        // 如果 true , 其他值就无效了
//} cj_RTCSctpTransport;

typedef struct {
    int64_t channel; // ffiDataChannelObserverTemp 指针地址
} CJ_RTCDataChannelEvent;

typedef struct {
    const char *type;
} CJ_Event;

typedef struct{
    int64_t ptr_id;
    char* kind;
    char* id;
    bool enabled;
    char* readyState;
} CJ_MediaStreamTrack;

typedef struct {
    const char *type;
    int64_t *streams;
    int64_t streams_size;
    int64_t MediaStreamTrack_ptr; // CJ_MediaStreamTrack
    int64_t RtpReceiver_ptr;      // ffiRtpReceiver
    int64_t RtpTransceiver_ptr;   // ffiRtpTransceiver
} CJ_RTCTrackEvent;

typedef struct {
    const char *type;
    const char *address;
    int64_t port;
    const char *url;
    int64_t errorCode;
    const char *errorText;
} CJ_RTCPeerConnectionIceErrorEvent;

typedef struct {
    const char *type;
    const uint8_t *data_arr;
    int64_t data_arr_size;
    const bool binary;
    const char *data_str;
} CJ_MessageEvent;

typedef struct {
    bool undefined = true;
    const char* candidate;
    const char* sdpMid;
    int64_t sdpMLineIndex;
    const char* foundation;
    int64_t component;
    int64_t priority;
    const char* address;
    const char* iceProtocol;
    int64_t port;
    int64_t iceCandidateType;
    const char* iceTcpCandidateType;
    const char* relatedAddress;
    int64_t relatedPort;
    const char* usernameFragment;
    // 父类的成员属性
    const char* adapterType;
    const char* serverUrl;
} CJ_RTCIceCandidate ;

typedef struct {
    const char *type;
    CJ_RTCIceCandidate candidate;
} CJ_RTCPeerConnectionIceEvent;

typedef struct {
    char * rid;
    int64_t rid_size;
    bool active;
    int64_t maxBitrate;
    int64_t maxFramerate;
    int64_t scaleResolutionDownBy;
} CJ_RTCRtpEncodingParameters;

typedef struct {
    int64_t clockRate;
    int64_t channels;
    char* mimeType;
    int64_t mimeType_size;
    char* sdpFmtpLine;
    int64_t sdpFmtpLine_size;
    int64_t payloadType;
} CJ_RTCRtpCodecParameters;

typedef struct {
    int64_t id;
    char* uri;
    int64_t uri_size;
    bool encrypted;
} CJ_RTCRtpHeaderExtensionParameters;

typedef struct {
    char* cname;
    int64_t cname_size;
    bool reducedSize;
} CJ_RTCRtcpParameters;

typedef struct {
    CJ_RTCRtpCodecParameters* codecs;
    int64_t codecs_size;
    CJ_RTCRtpHeaderExtensionParameters* headerExtensions;
    int64_t headerExtensions_size;
    CJ_RTCRtcpParameters rtcp;
    CJ_RTCRtpEncodingParameters* encodings;
    int64_t encodings_size;
    const char* transactionId;
    int64_t transactionId_size;
} CJ_RTCRtpSendParameters;

typedef struct {
    char* mimeType;
    int64_t clockRate;
    int64_t channels;
    char* sdpFmtpLine;
} CJ_RTCRtpCodec;

typedef struct {
    bool isBuild = false;
    bool ordered;
    int64_t maxPacketLifeTime;
    int64_t maxRetransmits;
    char* protocol;
    bool negotiated;
    int64_t id;
} CJ_RTCDataChannelInit;

typedef struct {
    bool isBuild = false;
    char* candidate = "";
    int32_t sdpMLineIndex = 0;
    char* sdpMid = "";
    char* usernameFragment;
} CJ_RTCIceCandidateInit;


typedef struct{
    int64_t rtcErrorDetailType;
    const char* msg;
}CJ_ErrorMessage;


/*namespace webrtc {

struct RtpSendParametersUtils {
    static void CJToNative(const CJ_RTCRtpSendParameters& cj, RtpParameters& native);
    static void NativeToCj(const RtpParameters& native, CJ_RTCRtpSendParameters& cj);
};
struct RtpParametersUtils {
    static void CJToNative(const CJ_RTCRtpSendParameters& cj, RtpParameters& native);
    static void NativeToCj(const RtpParameters& native, CJ_RTCRtpSendParameters& cj);
};

//struct RtpReceiveParametersUtils {
//    static void JsToNative(const Napi::Object& cj, RtpParameters& native);
//    static void NativeToJs(const RtpParameters& native, Napi::Object& cj);
//};
//
//struct RtpCapabilitiesUtils {
//    static void JsToNative(const Napi::Object& cj, RtpCapabilities& native);
//    static void NativeToJs(const RtpCapabilities& native, Napi::Object& cj);
//};
//
//struct RtpCodecCapabilityUtils {
//    static void JsToNative(const Napi::Object& cj, RtpCodecCapability& native);
//    static void NativeToJs(const RtpCodecCapability& native, Napi::Object& cj);
//};
//
struct RtpEncodingParametersUtils {
    constexpr static char kAttributeNameSsrc[] = "ssrc";
    static void CJToNative(const CJ_RTCRtpEncodingParameters& cj, RtpEncodingParameters& native);
    static void NativeToCJ(const RtpEncodingParameters& native, CJ_RTCRtpEncodingParameters& cj);
};

void RtpSendParametersUtils::NativeToCj(const RtpParameters& native, CJ_RTCRtpSendParameters& ret) {
    
    CJ_RTCRtpEncodingParameters arr[native.encodings.size()];
    
    for (uint32_t i = 0; i < native.encodings.size(); i++) {
        CJ_RTCRtpEncodingParameters t;
        RtpEncodingParametersUtils::NativeToCJ(native.encodings[i], t);
        arr[i] = t;
    }
    ret.encodings = arr;
    ret.encodings_size = native.encodings.size();
    ret.transactionId = native.transaction_id.data();
    
}

void RtpParametersUtils::NativeToCj(const RtpParameters &native, CJ_RTCRtpSendParameters &cj) {
    
}


void RtpEncodingParametersUtils::NativeToCJ(const RtpEncodingParameters &native, CJ_RTCRtpEncodingParameters &cj) {
    
}


} // namespace webrtc*/

#endif // WEBRTC4CJ_FFI_DEFINE_STRUCT_H
