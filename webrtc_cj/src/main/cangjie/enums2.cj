/**
 * Created on 2025/12/16
 */
package webrtc_cj
import kit.AudioKit.*

public enum FFIRTCErrorDetailType {
    | NONE
    | DATA_CHANNEL_FAILURE
    | DTLS_FAILURE
    | FINGERPRINT_FAILURE
    | SCTP_FAILURE
    | SDP_SYNTAX_ERROR
    | HARDWARE_ENCODER_NOT_AVAILABLE
    | HARDWARE_ENCODER_ERROR
}

public enum FFIRTCIceProtocol {
    TCP | UDP
}

public enum FFIRTCIceCandidateType {
    HOST | PRFLX | RELAY | SRFLX
}

public enum FFIRTCIceTcpCandidateType {
    ACTIVE | PASSIVE | SO
}

public enum FFIRTCIceComponent {
    RTP | RTCP
}

public enum FFIRTCIceGathererState {
    COMPLETE | GATHERING | NEW
}

public enum FFIRTCIceTransportState {
    CHECKING | CLOSED | COMPLETED | CONNECTED | DISCONNECTED | FAILED | NEW
}

public enum FFIRTCIceRole {
    UNKNOWN | CONTROLLING | CONTROLLED
}

public enum FFIRTCSdpType {
    OFFER | ANSWER | PRANSWER | ROLLBACK
}

public enum FFIBinaryType {
    BLOB | ARRAYBUFFER
}

public enum FFIDataChannelState {
    CLOSED | CLOSING | CONNECTING | OPEN
}

public enum FFIRTCDtlsTransportState {
    NEW | CONNECTING | CONNECTED | CLOSED | FAILED
}

public enum FFIRTCIceGatheringState {
    NEW | GATHERING | COMPLETE
}

public enum FFIRTCIceConnectionState {
    CHECKING | CLOSED | COMPLETED | CONNECTED | DISCONNECTED | FAILED | NEW
}

public enum FFIRTCSignalingState {
    CLOSED
    | HAVE_LOCAL_OFFER
    | HAVE_LOCAL_PRANSWER
    | HAVE_REMOTE_OFFER
    | HAVE_REMOTE_PRANSWER
    | STABLE
}

public enum FFIRTCPeerConnectionState {
    CLOSED | CONNECTED | CONNECTING | DISCONNECTED | FAILED | NEW
}

public enum FFIRTCBundlePolicy {
    BALANCED | MAX_BUNDLE | MAX_COMPAT
}

public enum FFIRTCRtcpMuxPolicy {
    REQUIRE
}

public enum FFIRTCIceTransportPolicy {
    ALL | RELAY
}

public enum FFIDegradationPreference {
    BALANCED | MAINTAIN_FRAMERATE | MAINTAIN_RESOLUTION
}

public enum FFIRTCRtpTransceiverDirection {
    INACTIVE | RECVONLY | SENDONLY | SENDRECV | STOPPED
}

public enum FFIRTCSctpTransportState {
    CONNECTING | CONNECTED | CLOSED
}

public enum FFIRTCStatsType {
    CANDIDATE_PAIR
    | CERTIFICATE
    | CODEC
    | DATA_CHANNEL
    | INBOUND_RTP
    | LOCAL_CANDIDATE
    | MEDIA_PLAYOUT
    | MEDIA_SOURCE
    | OUTBOUND_RTP
    | PEER_CONNECTION
    | REMOTE_CANDIDATE
    | REMOTE_INBOUND_RTP
    | REMOTE_OUTBOUND_RTP
    | TRANSPORT
}

public enum FFIrtcstatsicecandidatepairstate {
    FAILED | FROZEN | IN_PROGRESS | SUCCEEDED | WAITING
}

public enum FFIMediaStreamTrackState {
    LIVE | ENDED
}

public enum FFIMediaDeviceKind {
    AUDIOINPUT | AUDIOOUTPUT | VIDEOINPUT
}

public enum FFIMediaSourceState {
    INITIALIZING | LIVE | ENDED | MUTED
}

public enum FFIVideoFacingModeEnum {
    USER | ENVIRONMENT | LEFT | RIGHT
}

public enum FFIVideoResizeModeEnum {
    NONE | CROP_AND_SCALE
}

public enum FFIAudioErrorType {
    INIT | START_EXCEPTION | START_STATE_MISMATCH | GENERAL
}

public enum FFIAudioState {
    START | STOP
}

public enum FFIScreenCaptureMode {
    HOME_SCREEN | SPECIFIED_SCREEN | SPECIFIED_WINDOW
}

public enum FFIScreenCaptureAudioFilterEnum {
    CURRENT_APP | NOTIFICATION
}

public enum FFIScalingModeEnum {
    FILL | ASPECTFILL | ASPECTFIT
}

public enum LoggingSeverity {
    VERBOSE | INFO | WARNING | ERROR | NONE
}

public enum VideoEncoderAndDecoderMode {
    Software | Hardware
}

public enum ffiSourceType {
    SOURCE_TYPE_INVALID | SOURCE_TYPE_MIC | SOURCE_TYPE_VOICE_RECOGNITION |
    SOURCE_TYPE_VOICE_COMMUNICATION | SOURCE_TYPE_VOICE_MESSAGE | SOURCE_TYPE_CAMCORDER
}

public enum ffiStreamUsage {
    STREAM_USAGE_UNKNOWN | STREAM_USAGE_MUSIC | STREAM_USAGE_VOICE_COMMUNICATION |
    STREAM_USAGE_VOICE_ASSISTANT | STREAM_USAGE_ALARM | STREAM_USAGE_VOICE_MESSAGE |
    STREAM_USAGE_RINGTONE | STREAM_USAGE_NOTIFICATION | STREAM_USAGE_ACCESSIBILITY |
    STREAM_USAGE_MOVIE | STREAM_USAGE_GAME | STREAM_USAGE_AUDIOBOOK|
    STREAM_USAGE_NAVIGATION | STREAM_USAGE_VIDEO_COMMUNICATION
}

public enum ffiAudioSampleFormat {
    SAMPLE_FORMAT_INVALID | SAMPLE_FORMAT_U8 | SAMPLE_FORMAT_S16LE |
    SAMPLE_FORMAT_S24LE | SAMPLE_FORMAT_S32LE | SAMPLE_FORMAT_F32LE
}

extend ffiAudioSampleFormat <: ToString & Equatable<ffiAudioSampleFormat> {
    public static func GET(index: Int32): ffiAudioSampleFormat {
        return match (index) {
            case -1 => SAMPLE_FORMAT_INVALID
            case 0 => SAMPLE_FORMAT_U8
            case 1 => SAMPLE_FORMAT_S16LE
            case 2 => SAMPLE_FORMAT_S24LE
            case 3 => SAMPLE_FORMAT_S32LE
            case 4 => SAMPLE_FORMAT_F32LE
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: AudioSampleFormat): Int32 {
        return match (index) {
            case AudioSampleFormat.SAMPLE_FORMAT_INVALID => -1
            case AudioSampleFormat.SAMPLE_FORMAT_U8 => 0
            case AudioSampleFormat.SAMPLE_FORMAT_S16LE => 1
            case AudioSampleFormat.SAMPLE_FORMAT_S24LE => 2
            case AudioSampleFormat.SAMPLE_FORMAT_S32LE => 3
            case AudioSampleFormat.SAMPLE_FORMAT_F32LE => 4
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public func toString(): String {
        return match (this) {
            case SAMPLE_FORMAT_INVALID => "SAMPLE_FORMAT_INVALID"
            case SAMPLE_FORMAT_U8 => "SAMPLE_FORMAT_U8"
            case SAMPLE_FORMAT_S16LE => "SAMPLE_FORMAT_S16LE"
            case SAMPLE_FORMAT_S24LE => "SAMPLE_FORMAT_S24LE"
            case SAMPLE_FORMAT_S32LE => "SAMPLE_FORMAT_S32LE"
            case SAMPLE_FORMAT_F32LE => "SAMPLE_FORMAT_F32LE"
        }
    }

    public operator func ==(rhs: ffiAudioSampleFormat): Bool {
        return match ((this, rhs)) {
            case (SAMPLE_FORMAT_INVALID, SAMPLE_FORMAT_INVALID) => true
            case (SAMPLE_FORMAT_U8, SAMPLE_FORMAT_U8) => true
            case (SAMPLE_FORMAT_S16LE, SAMPLE_FORMAT_S16LE) => true
            case (SAMPLE_FORMAT_S24LE, SAMPLE_FORMAT_S24LE) => true
            case (SAMPLE_FORMAT_S32LE, SAMPLE_FORMAT_S32LE) => true
            case (SAMPLE_FORMAT_F32LE, SAMPLE_FORMAT_F32LE) => true
            case _ => false
        }
    }

    public operator func !=(rhs: ffiAudioSampleFormat): Bool {
        return !(this == rhs)
    }
}

extend ffiStreamUsage <: ToString & Equatable<ffiStreamUsage> {
   public static func GET(index: Int32): ffiStreamUsage {
        return match (index) {
            case 0 => STREAM_USAGE_UNKNOWN
            case 1 => STREAM_USAGE_MUSIC
            case 2 => STREAM_USAGE_VOICE_COMMUNICATION
            case 3 => STREAM_USAGE_VOICE_ASSISTANT
            case 4 => STREAM_USAGE_ALARM
            case 5 => STREAM_USAGE_VOICE_MESSAGE
            case 6 => STREAM_USAGE_RINGTONE
            case 7 => STREAM_USAGE_NOTIFICATION
            case 8 => STREAM_USAGE_ACCESSIBILITY
            case 9 => STREAM_USAGE_MOVIE
            case 10 => STREAM_USAGE_GAME
            case 11 => STREAM_USAGE_AUDIOBOOK
            case 12 => STREAM_USAGE_NAVIGATION
            case 13 => STREAM_USAGE_VIDEO_COMMUNICATION
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: StreamUsage): Int32 {
        return match (index) {
            case StreamUsage.STREAM_USAGE_UNKNOWN => 0
            case StreamUsage.STREAM_USAGE_MUSIC => 1
            case StreamUsage.STREAM_USAGE_VOICE_COMMUNICATION => 2
            case StreamUsage.STREAM_USAGE_VOICE_ASSISTANT => 3
            case StreamUsage.STREAM_USAGE_ALARM => 4
            case StreamUsage.STREAM_USAGE_VOICE_MESSAGE => 5
            case StreamUsage.STREAM_USAGE_RINGTONE => 6
            case StreamUsage.STREAM_USAGE_NOTIFICATION => 7
            case StreamUsage.STREAM_USAGE_ACCESSIBILITY => 8
            case StreamUsage.STREAM_USAGE_MOVIE => 9
            case StreamUsage.STREAM_USAGE_GAME => 10
            case StreamUsage.STREAM_USAGE_AUDIOBOOK => 11
            case StreamUsage.STREAM_USAGE_NAVIGATION => 12
            case StreamUsage.STREAM_USAGE_VIDEO_COMMUNICATION => 13
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public func toString(): String {
        return match (this) {
            case STREAM_USAGE_UNKNOWN => "STREAM_USAGE_UNKNOWN"
            case STREAM_USAGE_MUSIC => "STREAM_USAGE_MUSIC"
            case STREAM_USAGE_VOICE_COMMUNICATION => "STREAM_USAGE_VOICE_COMMUNICATION"
            case STREAM_USAGE_VOICE_ASSISTANT => "STREAM_USAGE_VOICE_ASSISTANT"
            case STREAM_USAGE_ALARM => "STREAM_USAGE_ALARM"
            case STREAM_USAGE_VOICE_MESSAGE => "STREAM_USAGE_VOICE_MESSAGE"
            case STREAM_USAGE_RINGTONE => "STREAM_USAGE_RINGTONE"
            case STREAM_USAGE_NOTIFICATION => "STREAM_USAGE_NOTIFICATION"
            case STREAM_USAGE_ACCESSIBILITY => "STREAM_USAGE_ACCESSIBILITY"
            case STREAM_USAGE_MOVIE => "STREAM_USAGE_MOVIE"
            case STREAM_USAGE_GAME => "STREAM_USAGE_GAME"
            case STREAM_USAGE_AUDIOBOOK => "STREAM_USAGE_AUDIOBOOK"
            case STREAM_USAGE_NAVIGATION => "STREAM_USAGE_NAVIGATION"
            case STREAM_USAGE_VIDEO_COMMUNICATION => "STREAM_USAGE_VIDEO_COMMUNICATION"
        }
    }

    public operator func ==(rhs: ffiStreamUsage): Bool {
        return match ((this, rhs)) {
            case (STREAM_USAGE_UNKNOWN, STREAM_USAGE_UNKNOWN) => true
            case (STREAM_USAGE_MUSIC, STREAM_USAGE_MUSIC) => true
            case (STREAM_USAGE_VOICE_COMMUNICATION, STREAM_USAGE_VOICE_COMMUNICATION) => true
            case (STREAM_USAGE_VOICE_ASSISTANT, STREAM_USAGE_VOICE_ASSISTANT) => true
            case (STREAM_USAGE_ALARM, STREAM_USAGE_ALARM) => true
            case (STREAM_USAGE_VOICE_MESSAGE, STREAM_USAGE_VOICE_MESSAGE) => true
            case (STREAM_USAGE_RINGTONE, STREAM_USAGE_RINGTONE) => true
            case (STREAM_USAGE_NOTIFICATION, STREAM_USAGE_NOTIFICATION) => true
            case (STREAM_USAGE_ACCESSIBILITY, STREAM_USAGE_ACCESSIBILITY) => true
            case (STREAM_USAGE_MOVIE, STREAM_USAGE_MOVIE) => true
            case (STREAM_USAGE_GAME, STREAM_USAGE_GAME) => true
            case (STREAM_USAGE_AUDIOBOOK, STREAM_USAGE_AUDIOBOOK) => true
            case (STREAM_USAGE_NAVIGATION, STREAM_USAGE_NAVIGATION) => true
            case (STREAM_USAGE_VIDEO_COMMUNICATION, STREAM_USAGE_VIDEO_COMMUNICATION) => true
            case _ => false
        }
    }

    public operator func !=(rhs: ffiStreamUsage): Bool {
        return !(this == rhs)
    }
}

extend ffiSourceType <: ToString & Equatable<ffiSourceType> {
   public static func GET(index: Int32): ffiSourceType {
        return match (index) {
            case -1 => SOURCE_TYPE_INVALID
            case 0 => SOURCE_TYPE_MIC
            case 1 => SOURCE_TYPE_VOICE_RECOGNITION
            case 7 => SOURCE_TYPE_VOICE_COMMUNICATION
            case 10 => SOURCE_TYPE_VOICE_MESSAGE
            case 13 => SOURCE_TYPE_CAMCORDER
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: SourceType): Int32 {
        return match (index) {
            case SourceType.SOURCE_TYPE_INVALID => -1
            case SourceType.SOURCE_TYPE_MIC => 0
            case SourceType.SOURCE_TYPE_VOICE_RECOGNITION => 1
            case SourceType.SOURCE_TYPE_VOICE_COMMUNICATION => 7
            case SourceType.SOURCE_TYPE_VOICE_MESSAGE => 10
            case SourceType.SOURCE_TYPE_CAMCORDER => 13
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public func toString(): String {
        return match (this) {
            case SOURCE_TYPE_INVALID => "SOURCE_TYPE_INVALID"
            case SOURCE_TYPE_MIC => "SOURCE_TYPE_MIC"
            case SOURCE_TYPE_VOICE_RECOGNITION => "SOURCE_TYPE_VOICE_RECOGNITION"
            case SOURCE_TYPE_VOICE_COMMUNICATION => "SOURCE_TYPE_VOICE_COMMUNICATION"
            case SOURCE_TYPE_VOICE_MESSAGE => "SOURCE_TYPE_VOICE_MESSAGE"
            case SOURCE_TYPE_CAMCORDER => "SOURCE_TYPE_CAMCORDER"
        }
    }

    public operator func ==(rhs: ffiSourceType): Bool {
        return match ((this, rhs)) {
            case (SOURCE_TYPE_INVALID, SOURCE_TYPE_INVALID) => true
            case (SOURCE_TYPE_MIC, SOURCE_TYPE_MIC) => true
            case (SOURCE_TYPE_VOICE_RECOGNITION, SOURCE_TYPE_VOICE_RECOGNITION) => true
            case (SOURCE_TYPE_VOICE_COMMUNICATION, SOURCE_TYPE_VOICE_COMMUNICATION) => true
            case (SOURCE_TYPE_VOICE_MESSAGE, SOURCE_TYPE_VOICE_MESSAGE) => true
            case (SOURCE_TYPE_CAMCORDER, SOURCE_TYPE_CAMCORDER) => true
            case _ => false
        }
    }

    public operator func !=(rhs: ffiSourceType): Bool {
        return !(this == rhs)
    }
}


extend VideoEncoderAndDecoderMode <: ToString & Equatable<VideoEncoderAndDecoderMode> {
   public static func GET(index: Int32): VideoEncoderAndDecoderMode {
        return match (index) {
            case 0 => Software
            case 1 => Hardware
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: VideoEncoderAndDecoderMode): Bool {
        return match (index) {
            case Software => false
            case Hardware => true
        }
    }

    public func toString(): String {
        return match (this) {
            case Software => "Software"
            case Hardware => "Hardware"
        }
    }

    public operator func ==(rhs: VideoEncoderAndDecoderMode): Bool {
        return match ((this, rhs)) {
            case (Software, Software) => true
            case (Hardware, Hardware) => true
            case _ => false
        }
    }

    public operator func !=(rhs: VideoEncoderAndDecoderMode): Bool {
        return !(this == rhs)
    }
}

extend LoggingSeverity <: ToString & Equatable<LoggingSeverity> {
    public static func GET(index: Int32): LoggingSeverity {
        return match (index) {
            case 0 => VERBOSE
            case 1 => INFO
            case 2 => WARNING
            case 3 => ERROR
            case 4 => NONE
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: LoggingSeverity): Int32 {
        return match (index) {
            case VERBOSE => 0
            case INFO => 1
            case WARNING => 2
            case ERROR => 3
            case NONE => 4
        }
    }

    public func toString(): String {
        return match (this) {
            case VERBOSE => "VERBOSE"
            case INFO => "INFO"
            case WARNING => "WARNING"
            case ERROR => "ERROR"
            case NONE => "NONE"
        }
    }

    public operator func ==(rhs: LoggingSeverity): Bool {
        return match ((this, rhs)) {
            case (VERBOSE, VERBOSE) => true
            case (INFO, INFO) => true
            case (WARNING, WARNING) => true
            case (ERROR, ERROR) => true
            case (NONE, NONE) => true
            case _ => false
        }
    }

    public operator func !=(rhs: LoggingSeverity): Bool {
        return !(this == rhs)
    }
}

extend FFIScalingModeEnum <: ToString & Equatable<FFIScalingModeEnum> {
    public static func GET(index: Int32): FFIScalingModeEnum {
        return match (index) {
            case 0 => FILL
            case 1 => ASPECTFILL
            case 2 => ASPECTFIT
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIScalingModeEnum): Int32 {
        return match (index) {
            case FILL => 0
            case ASPECTFILL => 1
            case ASPECTFIT => 2
        }
    }

    public func toString(): String {
        return match (this) {
            case FILL => "FILL"
            case ASPECTFILL => "ASPECTFILL"
            case ASPECTFIT => "ASPECTFIT"
        }
    }

    public operator func ==(rhs: FFIScalingModeEnum): Bool {
        return match ((this, rhs)) {
            case (FILL, FILL) => true
            case (ASPECTFILL, ASPECTFILL) => true
            case (ASPECTFIT, ASPECTFIT) => true
            case _ => false
        }
    }

    public operator func !=(rhs: FFIScalingModeEnum): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCErrorDetailType <: ToString & Equatable<FFIRTCErrorDetailType> {
    public static func GET(index: Int64): FFIRTCErrorDetailType {
        return match (index) {
            case 0 => NONE
            case 1 => DATA_CHANNEL_FAILURE
            case 2 => DTLS_FAILURE
            case 3 => FINGERPRINT_FAILURE
            case 4 => SCTP_FAILURE
            case 5 => SDP_SYNTAX_ERROR
            case 6 => HARDWARE_ENCODER_NOT_AVAILABLE
            case 7 => HARDWARE_ENCODER_ERROR
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCErrorDetailType): Int64 {
        return match (index) {
            case NONE => 0
            case DATA_CHANNEL_FAILURE => 1
            case DTLS_FAILURE => 2
            case FINGERPRINT_FAILURE => 3
            case SCTP_FAILURE => 4
            case SDP_SYNTAX_ERROR => 5
            case HARDWARE_ENCODER_NOT_AVAILABLE => 6
            case HARDWARE_ENCODER_ERROR => 7
        }
    }

    public func toString(): String {
        return match (this) {
            case NONE => "NONE"
            case DATA_CHANNEL_FAILURE => "DATA_CHANNEL_FAILURE"
            case DTLS_FAILURE => "DTLS_FAILURE"
            case FINGERPRINT_FAILURE => "FINGERPRINT_FAILURE"
            case SCTP_FAILURE => "SCTP_FAILURE"
            case SDP_SYNTAX_ERROR => "SDP_SYNTAX_ERROR"
            case HARDWARE_ENCODER_NOT_AVAILABLE => "HARDWARE_ENCODER_NOT_AVAILABLE"
            case HARDWARE_ENCODER_ERROR => "HARDWARE_ENCODER_ERROR"
        }
    }

    public operator func ==(rhs: FFIRTCErrorDetailType): Bool {
        return match ((this, rhs)) {
            case (NONE, NONE) => true
            case (DATA_CHANNEL_FAILURE, DATA_CHANNEL_FAILURE) => true
            case (DTLS_FAILURE, DTLS_FAILURE) => true
            case (FINGERPRINT_FAILURE, FINGERPRINT_FAILURE) => true
            case (SCTP_FAILURE, SCTP_FAILURE) => true
            case (SDP_SYNTAX_ERROR, SDP_SYNTAX_ERROR) => true
            case (HARDWARE_ENCODER_NOT_AVAILABLE, HARDWARE_ENCODER_NOT_AVAILABLE) => true
            case (HARDWARE_ENCODER_ERROR, HARDWARE_ENCODER_ERROR) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCErrorDetailType): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCIceProtocol <: ToString & Equatable<FFIRTCIceProtocol> {
    public static func GET(index: Int64): FFIRTCIceProtocol {
        return match (index) {
            case 0 => TCP
            case 1 => UDP
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCIceProtocol): Int64 {
        return match (index) {
            case TCP => 0
            case UDP => 1
        }
    }

    public func toString(): String {
        return match (this) {
            case TCP => "TCP"
            case UDP => "UDP"
        }
    }

    public operator func ==(rhs: FFIRTCIceProtocol): Bool {
        return match ((this, rhs)) {
            case (TCP, TCP) => true
            case (UDP, UDP) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCIceProtocol): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCIceCandidateType <: ToString & Equatable<FFIRTCIceCandidateType> {
    public static func GET(index: Int64): FFIRTCIceCandidateType {
        return match (index) {
            case 0 => HOST
            case 1 => PRFLX
            case 2 => RELAY
            case 3 => SRFLX
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCIceCandidateType): Int64 {
        return match (index) {
            case HOST => 0
            case PRFLX => 1
            case RELAY => 2
            case SRFLX => 3
        }
    }

    public func toString(): String {
        return match (this) {
            case HOST => "HOST"
            case PRFLX => "PRFLX"
            case RELAY => "RELAY"
            case SRFLX => "SRFLX"
        }
    }

    public operator func ==(rhs: FFIRTCIceCandidateType): Bool {
        return match ((this, rhs)) {
            case (HOST, HOST) => true
            case (PRFLX, PRFLX) => true
            case (RELAY, RELAY) => true
            case (SRFLX, SRFLX) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCIceCandidateType): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCIceTcpCandidateType <: ToString & Equatable<FFIRTCIceTcpCandidateType> {
    public static func GET(index: Int64): FFIRTCIceTcpCandidateType {
        return match (index) {
            case 0 => ACTIVE
            case 1 => PASSIVE
            case 2 => SO
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCIceTcpCandidateType): Int64 {
        return match (index) {
            case ACTIVE => 0
            case PASSIVE => 1
            case SO => 2
        }
    }

    public func toString(): String {
        return match (this) {
            case ACTIVE => "ACTIVE"
            case PASSIVE => "PASSIVE"
            case SO => "SO"
        }
    }

    public operator func ==(rhs: FFIRTCIceTcpCandidateType): Bool {
        return match ((this, rhs)) {
            case (ACTIVE,ACTIVE) => true
            case (PASSIVE,PASSIVE) => true
            case (SO,SO) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCIceTcpCandidateType): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCIceComponent <: ToString & Equatable<FFIRTCIceComponent> {
    public static func GET(index: Int64): FFIRTCIceComponent {
        return match (index) {
            case 0 => RTP
            case 1 => RTCP
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCIceComponent): Int64 {
        return match (index) {
            case RTP => 0
            case RTCP => 1
        }
    }

    public func toString(): String {
        return match (this) {
            case RTP => "RTP"
            case RTCP => "RTCP"
        }
    }

    public operator func ==(rhs: FFIRTCIceComponent): Bool {
        return match ((this, rhs)) {
            case (RTP, RTP) => true
            case (RTCP, RTCP) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCIceComponent): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCIceGathererState <: ToString & Equatable<FFIRTCIceGathererState> {
    public static func GET(index: Int64): FFIRTCIceGathererState {
        return match (index) {
            case 0 => COMPLETE
            case 1 => GATHERING
            case 2 => NEW
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCIceGathererState): Int64 {
        return match (index) {
            case COMPLETE => 0
            case GATHERING => 1
            case NEW => 2
        }
    }

    public func toString(): String {
        return match (this) {
            case COMPLETE => "COMPLETE"
            case GATHERING => "GATHERING"
            case NEW => "NEW"
        }
    }

    public operator func ==(rhs: FFIRTCIceGathererState): Bool {
        return match ((this, rhs)) {
            case (COMPLETE, COMPLETE) => true
            case (GATHERING, GATHERING) => true
            case (NEW, NEW) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCIceGathererState): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCIceTransportState <: ToString & Equatable<FFIRTCIceTransportState> {
    public static func GET(index: Int64): FFIRTCIceTransportState {
        return match (index) {
            case 0 => CHECKING
            case 1 => CLOSED
            case 2 => COMPLETED
            case 3 => CONNECTED
            case 4 => DISCONNECTED
            case 5 => FAILED
            case 6 => NEW
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCIceTransportState): Int64 {
        return match (index) {
            case CHECKING => 0
            case CLOSED => 1
            case COMPLETED => 2
            case CONNECTED => 3
            case DISCONNECTED => 4
            case FAILED => 5
            case NEW => 6
        }
    }

    public func toString(): String {
        return match (this) {
            case CHECKING => "CHECKING"
            case CLOSED => "CLOSED"
            case COMPLETED => "COMPLETED"
            case CONNECTED => "CONNECTED"
            case DISCONNECTED => "DISCONNECTED"
            case FAILED => "FAILED"
            case NEW => "NEW"
        }
    }

    public operator func ==(rhs: FFIRTCIceTransportState): Bool {
        return match ((this, rhs)) {
            case (CHECKING, CHECKING) => true
            case (CLOSED, CLOSED) => true
            case (COMPLETED, COMPLETED) => true
            case (CONNECTED, CONNECTED) => true
            case (DISCONNECTED, DISCONNECTED) => true
            case (FAILED, FAILED) => true
            case (NEW, NEW) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCIceTransportState): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCIceRole <: ToString & Equatable<FFIRTCIceRole> {
    public static func GET(index: Int64): FFIRTCIceRole {
        return match (index) {
            case 0 => UNKNOWN
            case 1 => CONTROLLING
            case 2 => CONTROLLED
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCIceRole): Int64 {
        return match (index) {
            case UNKNOWN => 0
            case CONTROLLING => 1
            case CONTROLLED => 2
        }
    }

    public func toString(): String {
        return match (this) {
            case UNKNOWN => "UNKNOWN"
            case CONTROLLING => "CONTROLLING"
            case CONTROLLED => "CONTROLLED"
        }
    }

    public operator func ==(rhs: FFIRTCIceRole): Bool {
        return match ((this, rhs)) {
            case (UNKNOWN, UNKNOWN) => true
            case (CONTROLLING, CONTROLLING) => true
            case (CONTROLLED, CONTROLLED) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCIceRole): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCSdpType <: ToString & Equatable<FFIRTCSdpType> {
    public static func GET(index: Int64): FFIRTCSdpType {
        return match (index) {
            case 0 => OFFER
            case 1 => ANSWER
            case 2 => PRANSWER
            case 3 => ROLLBACK
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCSdpType): Int64 {
        return match (index) {
            case OFFER => 0
            case ANSWER => 1
            case PRANSWER => 2
            case ROLLBACK => 3
        }
    }

    public func toString(): String {
        return match (this) {
            case OFFER => "OFFER"
            case ANSWER => "ANSWER"
            case PRANSWER => "PRANSWER"
            case ROLLBACK => "ROLLBACK"
        }
    }

    public operator func ==(rhs: FFIRTCSdpType): Bool {
        return match ((this, rhs)) {
            case (OFFER, OFFER) => true
            case (ANSWER, ANSWER) => true
            case (PRANSWER, PRANSWER) => true
            case (ROLLBACK, ROLLBACK) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCSdpType): Bool {
        return !(this == rhs)
    }
}

extend FFIBinaryType <: ToString & Equatable<FFIBinaryType> {
    public static func GET(index: Int64): FFIBinaryType {
        return match (index) {
            case 0 => BLOB
            case 1 => ARRAYBUFFER
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIBinaryType): Int64 {
        return match (index) {
            case BLOB => 0
            case ARRAYBUFFER => 1
        }
    }

    public func toString(): String {
        return match (this) {
            case BLOB => "BLOB"
            case ARRAYBUFFER => "ARRAYBUFFER"
        }
    }

    public operator func ==(rhs: FFIBinaryType): Bool {
        return match ((this, rhs)) {
            case (BLOB, BLOB) => true
            case (ARRAYBUFFER, ARRAYBUFFER) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIBinaryType): Bool {
        return !(this == rhs)
    }
}

extend FFIDataChannelState <: ToString & Equatable<FFIDataChannelState> {
    public static func GET(index: Int64): FFIDataChannelState {
        return match (index) {
            case 0 => CLOSED
            case 1 => CLOSING
            case 2 => CONNECTING
            case 3 => OPEN
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIDataChannelState): Int64 {
        return match (index) {
            case CLOSED => 0
            case CLOSING => 1
            case CONNECTING => 2
            case OPEN => 3
        }
    }

    public func toString(): String {
        return match (this) {
            case CLOSED => "CLOSED"
            case CLOSING => "CLOSING"
            case CONNECTING => "CONNECTING"
            case OPEN => "OPEN"
        }
    }

    public operator func ==(rhs: FFIDataChannelState): Bool {
        return match ((this, rhs)) {
            case (CLOSED, CLOSED) => true
            case (CLOSING, CLOSING) => true
            case (CONNECTING, CONNECTING) => true
            case (OPEN, OPEN) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIDataChannelState): Bool {
        return !(this == rhs)
    }

}

extend FFIRTCDtlsTransportState <: ToString & Equatable<FFIRTCDtlsTransportState> {
    public static func GET(index: Int64): FFIRTCDtlsTransportState {
        return match (index) {
            case 0 => NEW
            case 1 => CONNECTING
            case 2 => CONNECTED
            case 3 => CLOSED
            case 4 => FAILED
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCDtlsTransportState): Int64 {
        return match (index) {
            case NEW => 0
            case CONNECTING => 1
            case CONNECTED => 2
            case CLOSED => 3
            case FAILED => 4
        }
    }
    public func toString(): String {
        return match (this) {
            case NEW => "NEW"
            case CONNECTING => "CONNECTING"
            case CONNECTED => "CONNECTED"
            case CLOSED => "CLOSED"
            case FAILED => "FAILED"
        }
    }

    public operator func ==(rhs: FFIRTCDtlsTransportState): Bool {
        return match ((this, rhs)) {
            case (NEW, NEW) => true
            case (CONNECTING, CONNECTING) => true
            case (CONNECTED, CONNECTED) => true
            case (CLOSED, CLOSED) => true
            case (FAILED, FAILED) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCDtlsTransportState): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCIceGatheringState <: ToString & Equatable<FFIRTCIceGatheringState> {
    public static func GET(index: Int64): FFIRTCIceGatheringState {
        return match (index) {
            case 0 => NEW
            case 1 => GATHERING
            case 2 => COMPLETE
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCIceGatheringState): Int64 {
        return match (index) {
            case NEW => 0
            case GATHERING => 1
            case COMPLETE => 2
        }
    }
    public func toString(): String {
        return match (this) {
            case NEW => "NEW"
            case GATHERING => "GATHERING"
            case COMPLETE => "COMPLETE"
        }
    }

    public operator func ==(rhs: FFIRTCIceGatheringState): Bool {
        return match ((this, rhs)) {
            case (NEW, NEW) => true
            case (GATHERING, GATHERING) => true
            case (COMPLETE, COMPLETE) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCIceGatheringState): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCIceConnectionState <: ToString & Equatable<FFIRTCIceConnectionState> {
    public static func GET(index: Int64): FFIRTCIceConnectionState {
        return match (index) {
            case 0 => CHECKING
            case 1 => CLOSED
            case 2 => COMPLETED
            case 3 => CONNECTED
            case 4 => DISCONNECTED
            case 5 => FAILED
            case 6 => NEW
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCIceConnectionState): Int64 {
        return match (index) {
            case CHECKING => 0
            case CLOSED => 1
            case COMPLETED => 2
            case CONNECTED => 3
            case DISCONNECTED => 4
            case FAILED => 5
            case NEW => 6
        }
    }
    public func toString(): String {
        return match (this) {
            case CHECKING => "CHECKING"
            case CLOSED => "CLOSED"
            case COMPLETED => "COMPLETED"
            case CONNECTED => "CONNECTED"
            case DISCONNECTED => "DISCONNECTED"
            case FAILED => "FAILED"
            case NEW => "NEW"
        }
    }

    public operator func ==(rhs: FFIRTCIceConnectionState): Bool {
        return match ((this, rhs)) {
            case (CHECKING, CHECKING) => true
            case (CLOSED, CLOSED) => true
            case (COMPLETED, COMPLETED) => true
            case (CONNECTED, CONNECTED) => true
            case (DISCONNECTED, DISCONNECTED) => true
            case (FAILED, FAILED) => true
            case (NEW, NEW) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCIceConnectionState): Bool {
        return !(this == rhs)
    }
}
