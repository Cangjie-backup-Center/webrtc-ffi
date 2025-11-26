/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC4CJ_FFI_DEFINE_STRUCT_H
#define WEBRTC4CJ_FFI_DEFINE_STRUCT_H

#include "api/rtp_parameters.h"
#include "webrtc_func.h"
#include <cstdint>

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
    bool auto_gain_control;
    bool noise_suppression;
    bool highpass_filter;
    bool stereo_swapping;
    int32_t audio_jitter_buffer_max_packets;
    bool audio_jitter_buffer_fast_accelerate;
    int audio_jitter_buffer_min_delay_ms;
    bool audio_network_adaptor;
    std::string audio_network_adaptor_config;
    bool init_recording_on_send;
}FFIAudioOptions;

typedef struct {
    double width;
    double height;
    CHAR_PTR facingMode;
    bool isScreencast;
}FFICreateVideoSourceParameters;

typedef struct {
    double width;
    double height;
    double aspectRatio;
    double frameRate;
    CHAR_PTR facingMode;
    CHAR_PTR resizeMode;
    double sampleRate;
    double sampleSize;
    bool echoCancellation;
    bool autoGainControl;
    bool noiseSuppression;
    double latency;
    double channelCount;
    CHAR_PTR deviceId;
    CHAR_PTR groupId;
    CHAR_PTR ohosScreenCaptureMode;
    double ohosScreenCaptureDisplayId;
    CHAR_PTR ohosScreenCaptureMissionId;
    CHAR_PTR ohosScreenCaptureWindowFilter;
    CHAR_PTR ohosScreenCaptureAudioFilter;
    CHAR_PTR ohosScreenCaptureSkipPrivacyMode;
    bool ohosScreenCaptureAutoRotation;
} CJ_MediaTrackConstraintSet;

typedef struct {
    CJ_MediaTrackConstraintSet obj;
    bool boolean;
    bool isBool;
} CJ_TO_CPP_DisplayMediaStreamOptions;


typedef struct {
    const CHAR_PTR deviceId;
    const CHAR_PTR groupId;
    const CHAR_PTR label;
    const CHAR_PTR kind;
} CJ_EnumerateDevicesInfo;

typedef struct {
    const CHAR_PTR id;
    const CHAR_PTR kind;
    const CHAR_PTR readyState;
    bool enabled;
} CJ_ffiMediaStreamTrackJson;

typedef struct {
    const CHAR_PTR name;
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
    CHAR_PTR *urls;
    int64_t urls_size;
    CHAR_PTR username;
    int64_t username_size;
    CHAR_PTR credential;
    int64_t credential_size;
} CJ_RTCIceServer;

typedef struct {
    CHAR_PTR algorithm;
    int64_t algorithm_size;
    CHAR_PTR value;
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
    CHAR_PTR sdp;
    int64_t sdp_size;
    CHAR_PTR RTCSdpType;
    int64_t RTCSdpType_size;
    bool undefined = true; // 如果 true , 其他值就无效了
} CJ_RTCSessionDescription;

typedef struct {
    CHAR_PTR sdp;
    CHAR_PTR RTCSdpType;
    bool isFail = true; // 如果 true , 其他值就无效了
    CHAR_PTR msg;
} CJ_FFICreateSdpObserver_result;

typedef struct {
    int64_t channel; // ffiDataChannelObserverTemp 指针地址
} CJ_RTCDataChannelEvent;

typedef struct {
    const CHAR_PTR type;
} CJ_Event;

typedef struct {
    int64_t ptr_id;
    CHAR_PTR kind;
    CHAR_PTR id;
    bool enabled;
    CHAR_PTR readyState;
} CJ_MediaStreamTrack;

typedef struct {
    const CHAR_PTR type;
    int64_t *streams;
    int64_t streams_size;
    int64_t MediaStreamTrack_ptr; // CJ_MediaStreamTrack
    int64_t RtpReceiver_ptr;      // ffiRtpReceiver
    int64_t RtpTransceiver_ptr;   // ffiRtpTransceiver
} CJ_RTCTrackEvent;

typedef struct {
    const CHAR_PTR type;
    const CHAR_PTR address;
    int64_t port;
    const CHAR_PTR url;
    int64_t errorCode;
    const CHAR_PTR errorText;
} CJ_RTCPeerConnectionIceErrorEvent;

typedef struct {
    const CHAR_PTR type;
    const uint8_t *data_arr;
    int64_t data_arr_size;
    const bool binary;
    const CHAR_PTR data_str;
} CJ_MessageEvent;

typedef struct {
    bool undefined = true;
    const CHAR_PTR candidate;
    const CHAR_PTR sdpMid;
    int64_t sdpMLineIndex;
    const CHAR_PTR foundation;
    int64_t component;
    int64_t priority;
    const CHAR_PTR address;
    const CHAR_PTR iceProtocol;
    int64_t port;
    int64_t iceCandidateType;
    const CHAR_PTR iceTcpCandidateType;
    const CHAR_PTR relatedAddress;
    int64_t relatedPort;
    const CHAR_PTR usernameFragment;
    // 父类的成员属性
    const CHAR_PTR adapterType;
    const CHAR_PTR serverUrl;
} CJ_RTCIceCandidate ;

typedef struct {
    const CHAR_PTR type;
    CJ_RTCIceCandidate candidate;
} CJ_RTCPeerConnectionIceEvent;

typedef struct {
    CHAR_PTR rid;
    int64_t rid_size;
    bool active;
    int64_t maxBitrate;
    int64_t maxFramerate;
    int64_t scaleResolutionDownBy;
} CJ_RTCRtpEncodingParameters;

typedef struct {
    int64_t clockRate;
    int64_t channels;
    CHAR_PTR mimeType;
    int64_t mimeType_size;
    CHAR_PTR sdpFmtpLine;
    int64_t sdpFmtpLine_size;
    int64_t payloadType;
} CJ_RTCRtpCodecParameters;

typedef struct {
    int64_t id;
    CHAR_PTR uri;
    int64_t uri_size;
    bool encrypted;
} CJ_RTCRtpHeaderExtensionParameters;

typedef struct {
    CHAR_PTR cname;
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
    const CHAR_PTR transactionId;
    int64_t transactionId_size;
} CJ_RTCRtpSendParameters;

typedef struct {
    CHAR_PTR mimeType;
    int64_t clockRate;
    int64_t channels;
    CHAR_PTR sdpFmtpLine;
} CJ_RTCRtpCodec;

typedef struct {
    bool isBuild = false;
    bool ordered;
    int64_t maxPacketLifeTime;
    int64_t maxRetransmits;
    CHAR_PTR protocol;
    bool negotiated;
    int64_t id;
} CJ_RTCDataChannelInit;

typedef struct {
    bool isBuild = false;
    CHAR_PTR candidate = "";
    int32_t sdpMLineIndex = 0;
    CHAR_PTR sdpMid = "";
    CHAR_PTR usernameFragment;
} CJ_RTCIceCandidateInit;

typedef struct {
    int64_t rtcErrorDetailType;
    const CHAR_PTR msg;
} CJ_ErrorMessage;

#endif // WEBRTC4CJ_FFI_DEFINE_STRUCT_H
