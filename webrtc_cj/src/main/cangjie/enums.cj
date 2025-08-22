/**
 * Created on 2025/8/19
 */
package webrtc_cj

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

extend FFIRTCErrorDetailType {
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
}

extend FFIRTCIceProtocol {
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
}

extend FFIRTCIceCandidateType {
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
}

extend FFIRTCIceTcpCandidateType {
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
}

extend FFIRTCIceComponent {
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
}

extend FFIRTCIceGathererState {
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
}

extend FFIRTCIceTransportState {
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
}

extend FFIRTCIceRole {
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
}

extend FFIRTCSdpType {
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
}

extend FFIBinaryType {
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
}

extend FFIDataChannelState {
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
}

extend FFIRTCDtlsTransportState {
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
}

extend FFIRTCIceGatheringState {
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
}

extend FFIRTCIceConnectionState {
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
}

extend FFIRTCSignalingState {
    public static func GET(index: Int64): FFIRTCSignalingState {
        return match (index) {
            case 0 => CLOSED
            case 1 => HAVE_LOCAL_OFFER
            case 2 => HAVE_LOCAL_PRANSWER
            case 3 => HAVE_REMOTE_OFFER
            case 4 => HAVE_REMOTE_PRANSWER
            case 5 => STABLE
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCSignalingState): Int64 {
        return match (index) {
            case CLOSED => 0
            case HAVE_LOCAL_OFFER => 1
            case HAVE_LOCAL_PRANSWER => 2
            case HAVE_REMOTE_OFFER => 3
            case HAVE_REMOTE_PRANSWER => 4
            case STABLE => 5
        }
    }
}

extend FFIRTCPeerConnectionState {
    public static func GET(index: Int64): FFIRTCPeerConnectionState {
        return match (index) {
            case 0 => CLOSED
            case 1 => CONNECTED
            case 2 => CONNECTING
            case 3 => DISCONNECTED
            case 4 => FAILED
            case 5 => NEW
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCPeerConnectionState): Int64 {
        return match (index) {
            case CLOSED => 0
            case CONNECTED => 1
            case CONNECTING => 2
            case DISCONNECTED => 3
            case FAILED => 4
            case NEW => 5
        }
    }
}

extend FFIRTCBundlePolicy {
    public static func GET(index: Int64): FFIRTCBundlePolicy {
        return match (index) {
            case 0 => BALANCED
            case 1 => MAX_BUNDLE
            case 2 => MAX_COMPAT
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCBundlePolicy): Int64 {
        return match (index) {
            case BALANCED => 0
            case MAX_BUNDLE => 1
            case MAX_COMPAT => 2
        }
    }
}

extend FFIRTCRtcpMuxPolicy {
    public static func GET(index: Int64): FFIRTCRtcpMuxPolicy {
        return match (index) {
            case 0 => REQUIRE
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCRtcpMuxPolicy): Int64 {
        return match (index) {
            case REQUIRE => 0
        }
    }
}

extend FFIRTCIceTransportPolicy {
    public static func GET(index: Int64): FFIRTCIceTransportPolicy {
        return match (index) {
            case 0 => ALL
            case 1 => RELAY
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCIceTransportPolicy): Int64 {
        return match (index) {
            case ALL => 0
            case RELAY => 1
        }
    }
}

extend FFIDegradationPreference {
    public static func GET(index: Int64): FFIDegradationPreference {
        return match (index) {
            case 0 => BALANCED
            case 1 => MAINTAIN_FRAMERATE
            case 2 => MAINTAIN_RESOLUTION
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIDegradationPreference): Int64 {
        return match (index) {
            case BALANCED => 0
            case MAINTAIN_FRAMERATE => 1
            case MAINTAIN_RESOLUTION => 2
        }
    }
}

extend FFIRTCRtpTransceiverDirection {
    public static func GET(index: Int64): FFIRTCRtpTransceiverDirection {
        return match (index) {
            case 0 => INACTIVE
            case 1 => RECVONLY
            case 2 => SENDONLY
            case 3 => SENDRECV
            case 4 => STOPPED
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCRtpTransceiverDirection): Int64 {
        return match (index) {
            case INACTIVE => 0
            case RECVONLY => 1
            case SENDONLY => 2
            case SENDRECV => 3
            case STOPPED => 4
        }
    }
}

extend FFIRTCSctpTransportState {
    public static func GET(index: Int64): FFIRTCSctpTransportState {
        return match (index) {
            case 0 => CONNECTING
            case 1 => CONNECTED
            case 2 => CLOSED
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCSctpTransportState): Int64 {
        return match (index) {
            case CONNECTING => 0
            case CONNECTED => 1
            case CLOSED => 2
        }
    }
}

extend FFIRTCStatsType {
    public static func GET(index: Int64): FFIRTCStatsType {
        return match (index) {
            case 0 => CANDIDATE_PAIR
            case 1 => CERTIFICATE
            case 2 => CODEC
            case 3 => DATA_CHANNEL
            case 4 => INBOUND_RTP
            case 5 => LOCAL_CANDIDATE
            case 6 => MEDIA_PLAYOUT
            case 7 => MEDIA_SOURCE
            case 8 => OUTBOUND_RTP
            case 9 => PEER_CONNECTION
            case 10 => REMOTE_CANDIDATE
            case 11 => REMOTE_INBOUND_RTP
            case 12 => REMOTE_OUTBOUND_RTP
            case 13 => TRANSPORT
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIRTCStatsType): Int64 {
        return match (index) {
            case CANDIDATE_PAIR => 0
            case CERTIFICATE => 1
            case CODEC => 2
            case DATA_CHANNEL => 3
            case INBOUND_RTP => 4
            case LOCAL_CANDIDATE => 5
            case MEDIA_PLAYOUT => 6
            case MEDIA_SOURCE => 7
            case OUTBOUND_RTP => 8
            case PEER_CONNECTION => 9
            case REMOTE_CANDIDATE => 10
            case REMOTE_INBOUND_RTP => 11
            case REMOTE_OUTBOUND_RTP => 12
            case TRANSPORT => 13
        }
    }
}

extend FFIrtcstatsicecandidatepairstate {
    public static func GET(index: Int64): FFIrtcstatsicecandidatepairstate {
        return match (index) {
            case 0 => FAILED
            case 1 => FROZEN
            case 2 => IN_PROGRESS
            case 3 => SUCCEEDED
            case 4 => WAITING
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIrtcstatsicecandidatepairstate): Int64 {
        return match (index) {
            case FAILED => 0
            case FROZEN => 1
            case IN_PROGRESS => 2
            case SUCCEEDED => 3
            case WAITING => 4
        }
    }
}

extend FFIMediaStreamTrackState {
    public static func GET(index: Int64): FFIMediaStreamTrackState {
        return match (index) {
            case 0 => LIVE
            case 1 => ENDED
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIMediaStreamTrackState): Int64 {
        return match (index) {
            case LIVE => 0
            case ENDED => 1
        }
    }
}

extend FFIMediaDeviceKind {
    public static func GET(index: Int64): FFIMediaDeviceKind {
        return match (index) {
            case 0 => AUDIOINPUT
            case 1 => AUDIOOUTPUT
            case 2 => VIDEOINPUT
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIMediaDeviceKind): Int64 {
        return match (index) {
            case AUDIOINPUT => 0
            case AUDIOOUTPUT => 1
            case VIDEOINPUT => 2
        }
    }
}

extend FFIMediaSourceState {
    public static func GET(index: Int64): FFIMediaSourceState {
        return match (index) {
            case 0 => INITIALIZING
            case 1 => LIVE
            case 2 => ENDED
            case 3 => MUTED
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIMediaSourceState): Int64 {
        return match (index) {
            case INITIALIZING => 0
            case LIVE => 1
            case ENDED => 2
            case MUTED => 3
        }
    }
}

extend FFIVideoFacingModeEnum {
    public static func GET(index: Int64): FFIVideoFacingModeEnum {
        return match (index) {
            case 0 => USER
            case 1 => ENVIRONMENT
            case 2 => LEFT
            case 3 => RIGHT
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIVideoFacingModeEnum): Int64 {
        return match (index) {
            case USER => 0
            case ENVIRONMENT => 1
            case LEFT => 2
            case RIGHT => 3
        }
    }
}

extend FFIVideoResizeModeEnum {
    public static func GET(index: Int64): FFIVideoResizeModeEnum {
        return match (index) {
            case 0 => NONE
            case 1 => CROP_AND_SCALE
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIVideoResizeModeEnum): Int64 {
        return match (index) {
            case NONE => 0
            case CROP_AND_SCALE => 1
        }
    }
}

extend FFIAudioErrorType {
    public static func GET(index: Int64): FFIAudioErrorType {
        return match (index) {
            case 0 => INIT
            case 1 => START_EXCEPTION
            case 2 => START_STATE_MISMATCH
            case 3 => GENERAL
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIAudioErrorType): Int64 {
        return match (index) {
            case INIT => 0
            case START_EXCEPTION => 1
            case START_STATE_MISMATCH => 2
            case GENERAL => 3
        }
    }
}

extend FFIAudioState {
    public static func GET(index: Int64): FFIAudioState {
        return match (index) {
            case 0 => START
            case 1 => STOP
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIAudioState): Int64 {
        return match (index) {
            case START => 0
            case STOP => 1
        }
    }
}

extend FFIScreenCaptureMode {
    public static func GET(index: Int64): FFIScreenCaptureMode {
        return match (index) {
            case 0 => HOME_SCREEN
            case 1 => SPECIFIED_SCREEN
            case 2 => SPECIFIED_WINDOW
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIScreenCaptureMode): Int64 {
        return match (index) {
            case HOME_SCREEN => 0
            case SPECIFIED_SCREEN => 1
            case SPECIFIED_WINDOW => 2
        }
    }
}

extend FFIScreenCaptureAudioFilterEnum {
    public static func GET(index: Int64): FFIScreenCaptureAudioFilterEnum {
        return match (index) {
            case 0 => CURRENT_APP
            case 1 => NOTIFICATION
            case _ => throw Webrtc4cjException("not found.")
        }
    }

    public static func GET(index: FFIScreenCaptureAudioFilterEnum): Int64 {
        return match (index) {
            case CURRENT_APP => 0
            case NOTIFICATION => 1
        }
    }
}

