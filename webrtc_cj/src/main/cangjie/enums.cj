/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */
package webrtc_cj

extend FFIRTCSignalingState <: ToString & Equatable<FFIRTCSignalingState> {
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
    public func toString(): String {
        return match (this) {
            case CLOSED => "CLOSED"
            case HAVE_LOCAL_OFFER => "HAVE_LOCAL_OFFER"
            case HAVE_LOCAL_PRANSWER => "HAVE_LOCAL_PRANSWER"
            case HAVE_REMOTE_OFFER => "HAVE_REMOTE_OFFER"
            case HAVE_REMOTE_PRANSWER => "HAVE_REMOTE_PRANSWER"
            case STABLE => "STABLE"
        }
    }

    public operator func ==(rhs: FFIRTCSignalingState): Bool {
        return match ((this, rhs)) {
            case (CLOSED, CLOSED) => true
            case (HAVE_LOCAL_OFFER, HAVE_LOCAL_OFFER) => true
            case (HAVE_LOCAL_PRANSWER, HAVE_LOCAL_PRANSWER) => true
            case (HAVE_REMOTE_OFFER, HAVE_REMOTE_OFFER) => true
            case (HAVE_REMOTE_PRANSWER, HAVE_REMOTE_PRANSWER) => true
            case (STABLE, STABLE) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCSignalingState): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCPeerConnectionState <: ToString & Equatable<FFIRTCPeerConnectionState> {
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
    public func toString(): String {
        return match (this) {
            case CLOSED => "CLOSED"
            case CONNECTED => "CONNECTED"
            case CONNECTING => "CONNECTING"
            case DISCONNECTED => "DISCONNECTED"
            case FAILED => "FAILED"
            case NEW => "NEW"
        }
    }

    public operator func ==(rhs: FFIRTCPeerConnectionState): Bool {
        return match ((this, rhs)) {
            case (CLOSED, CLOSED) => true
            case (CONNECTED, CONNECTED) => true
            case (CONNECTING, CONNECTING) => true
            case (DISCONNECTED, DISCONNECTED) => true
            case (FAILED, FAILED) => true
            case (NEW, NEW) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCPeerConnectionState): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCBundlePolicy <: ToString & Equatable<FFIRTCBundlePolicy> {
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
    public func toString(): String {
        return match (this) {
            case BALANCED => "BALANCED"
            case MAX_BUNDLE => "MAX_BUNDLE"
            case MAX_COMPAT => "MAX_COMPAT"
        }
    }

    public operator func ==(rhs: FFIRTCBundlePolicy): Bool {
        return match ((this, rhs)) {
            case (BALANCED, BALANCED) => true
            case (MAX_BUNDLE, MAX_BUNDLE) => true
            case (MAX_COMPAT, MAX_COMPAT) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCBundlePolicy): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCRtcpMuxPolicy <: ToString & Equatable<FFIRTCRtcpMuxPolicy> {
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
    public func toString(): String {
        return match (this) {
            case REQUIRE => "REQUIRE"
        }
    }

    public operator func ==(rhs: FFIRTCRtcpMuxPolicy): Bool {
        return match ((this, rhs)) {
            case (REQUIRE, REQUIRE) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCRtcpMuxPolicy): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCIceTransportPolicy <: ToString & Equatable<FFIRTCIceTransportPolicy> {
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
    public func toString(): String {
        return match (this) {
            case ALL => "ALL"
            case RELAY => "RELAY"
        }
    }

    public operator func ==(rhs: FFIRTCIceTransportPolicy): Bool {
        return match ((this, rhs)) {
            case (ALL, ALL) => true
            case (RELAY, RELAY) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCIceTransportPolicy): Bool {
        return !(this == rhs)
    }
}

extend FFIDegradationPreference <: ToString & Equatable<FFIDegradationPreference> {
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
    public func toString(): String {
        return match (this) {
            case BALANCED => "BALANCED"
            case MAINTAIN_FRAMERATE => "MAINTAIN_FRAMERATE"
            case MAINTAIN_RESOLUTION => "MAINTAIN_RESOLUTION"
        }
    }

    public operator func ==(rhs: FFIDegradationPreference): Bool {
        return match ((this, rhs)) {
            case (BALANCED, BALANCED) => true
            case (MAINTAIN_FRAMERATE, MAINTAIN_FRAMERATE) => true
            case (MAINTAIN_RESOLUTION, MAINTAIN_RESOLUTION) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIDegradationPreference): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCRtpTransceiverDirection <: ToString & Equatable<FFIRTCRtpTransceiverDirection> {
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
    public func toString(): String {
        return match (this) {
            case INACTIVE => "INACTIVE"
            case RECVONLY => "RECVONLY"
            case SENDONLY => "SENDONLY"
            case SENDRECV => "SENDRECV"
            case STOPPED => "STOPPED"
        }
    }

    public operator func ==(rhs: FFIRTCRtpTransceiverDirection): Bool {
        return match ((this, rhs)) {
            case (INACTIVE, INACTIVE) => true
            case (RECVONLY, RECVONLY) => true
            case (SENDONLY, SENDONLY) => true
            case (SENDRECV, SENDRECV) => true
            case (STOPPED, STOPPED) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCRtpTransceiverDirection): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCSctpTransportState <: ToString & Equatable<FFIRTCSctpTransportState> {
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
    public func toString(): String {
        return match (this) {
            case CONNECTING => "CONNECTING"
            case CONNECTED => "CONNECTED"
            case CLOSED => "CLOSED"
        }
    }

    public operator func ==(rhs: FFIRTCSctpTransportState): Bool {
        return match ((this, rhs)) {
            case (CONNECTING, CONNECTING) => true
            case (CONNECTED, CONNECTED) => true
            case (CLOSED, CLOSED) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCSctpTransportState): Bool {
        return !(this == rhs)
    }
}

extend FFIRTCStatsType <: ToString & Equatable<FFIRTCStatsType> {
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
    public func toString(): String {
        return match (this) {
            case CANDIDATE_PAIR => "CANDIDATE_PAIR"
            case CERTIFICATE => "CERTIFICATE"
            case CODEC => "CODEC"
            case DATA_CHANNEL => "DATA_CHANNEL"
            case INBOUND_RTP => "INBOUND_RTP"
            case LOCAL_CANDIDATE => "LOCAL_CANDIDATE"
            case MEDIA_PLAYOUT => "MEDIA_PLAYOUT"
            case MEDIA_SOURCE => "MEDIA_SOURCE"
            case OUTBOUND_RTP => "OUTBOUND_RTP"
            case PEER_CONNECTION => "PEER_CONNECTION"
            case REMOTE_CANDIDATE => "REMOTE_CANDIDATE"
            case REMOTE_INBOUND_RTP => "REMOTE_INBOUND_RTP"
            case REMOTE_OUTBOUND_RTP => "REMOTE_OUTBOUND_RTP"
            case TRANSPORT => "TRANSPORT"
        }
    }

    public operator func ==(rhs: FFIRTCStatsType): Bool {
        return match ((this, rhs)) {
            case (CANDIDATE_PAIR, CANDIDATE_PAIR) => true
            case (CERTIFICATE, CERTIFICATE) => true
            case (CODEC, CODEC) => true
            case (DATA_CHANNEL, DATA_CHANNEL) => true
            case (INBOUND_RTP, INBOUND_RTP) => true
            case (LOCAL_CANDIDATE, LOCAL_CANDIDATE) => true
            case (MEDIA_PLAYOUT, MEDIA_PLAYOUT) => true
            case (MEDIA_SOURCE, MEDIA_SOURCE) => true
            case (OUTBOUND_RTP, OUTBOUND_RTP) => true
            case (PEER_CONNECTION, PEER_CONNECTION) => true
            case (REMOTE_CANDIDATE, REMOTE_CANDIDATE) => true
            case (REMOTE_INBOUND_RTP, REMOTE_INBOUND_RTP) => true
            case (REMOTE_OUTBOUND_RTP, REMOTE_OUTBOUND_RTP) => true
            case (TRANSPORT, TRANSPORT) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIRTCStatsType): Bool {
        return !(this == rhs)
    }
}

extend FFIrtcstatsicecandidatepairstate <: ToString & Equatable<FFIrtcstatsicecandidatepairstate> {
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
    public func toString(): String {
        return match (this) {
            case FAILED => "FAILED"
            case FROZEN => "FROZEN"
            case IN_PROGRESS => "IN_PROGRESS"
            case SUCCEEDED => "SUCCEEDED"
            case WAITING => "WAITING"
        }
    }

    public operator func ==(rhs: FFIrtcstatsicecandidatepairstate): Bool {
        return match ((this, rhs)) {
            case (FAILED, FAILED) => true
            case (FROZEN, FROZEN) => true
            case (IN_PROGRESS, IN_PROGRESS) => true
            case (SUCCEEDED, SUCCEEDED) => true
            case (WAITING, WAITING) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIrtcstatsicecandidatepairstate): Bool {
        return !(this == rhs)
    }
}

extend FFIMediaStreamTrackState <: ToString & Equatable<FFIMediaStreamTrackState> {
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
    public func toString(): String {
        return match (this) {
            case LIVE => "LIVE"
            case ENDED => "ENDED"
        }
    }

    public operator func ==(rhs: FFIMediaStreamTrackState): Bool {
        return match ((this, rhs)) {
            case (LIVE, LIVE) => true
            case (ENDED, ENDED) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIMediaStreamTrackState): Bool {
        return !(this == rhs)
    }
}

extend FFIMediaDeviceKind <: ToString & Equatable<FFIMediaDeviceKind> {
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
    public func toString(): String {
        return match (this) {
            case AUDIOINPUT => "AUDIOINPUT"
            case AUDIOOUTPUT => "AUDIOOUTPUT"
            case VIDEOINPUT => "VIDEOINPUT"
        }
    }

    public operator func ==(rhs: FFIMediaDeviceKind): Bool {
        return match ((this, rhs)) {
            case (AUDIOINPUT, AUDIOINPUT) => true
            case (AUDIOOUTPUT, AUDIOOUTPUT) => true
            case (VIDEOINPUT, VIDEOINPUT) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIMediaDeviceKind): Bool {
        return !(this == rhs)
    }
}

extend FFIMediaSourceState <: ToString & Equatable<FFIMediaSourceState> {
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
    public func toString(): String {
        return match (this) {
            case INITIALIZING => "INITIALIZING"
            case LIVE => "LIVE"
            case ENDED => "ENDED"
            case MUTED => "MUTED"
        }
    }

    public operator func ==(rhs: FFIMediaSourceState): Bool {
        return match ((this, rhs)) {
            case (INITIALIZING, INITIALIZING) => true
            case (LIVE, LIVE) => true
            case (ENDED, ENDED) => true
            case (MUTED, MUTED) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIMediaSourceState): Bool {
        return !(this == rhs)
    }
}

extend FFIVideoFacingModeEnum <: ToString & Equatable<FFIVideoFacingModeEnum> {
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
    public func toString(): String {
        return match (this) {
            case USER => "USER"
            case ENVIRONMENT => "ENVIRONMENT"
            case LEFT => "LEFT"
            case RIGHT => "RIGHT"
        }
    }

    public operator func ==(rhs: FFIVideoFacingModeEnum): Bool {
        return match ((this, rhs)) {
            case (USER, USER) => true
            case (ENVIRONMENT, ENVIRONMENT) => true
            case (LEFT, LEFT) => true
            case (RIGHT, RIGHT) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIVideoFacingModeEnum): Bool {
        return !(this == rhs)
    }
}

extend FFIVideoResizeModeEnum <: ToString & Equatable<FFIVideoResizeModeEnum> {
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
    public func toString(): String {
        return match (this) {
            case NONE => "NONE"
            case CROP_AND_SCALE => "CROP_AND_SCALE"
        }
    }

    public operator func ==(rhs: FFIVideoResizeModeEnum): Bool {
        return match ((this, rhs)) {
            case (NONE, NONE) => true
            case (CROP_AND_SCALE, CROP_AND_SCALE) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIVideoResizeModeEnum): Bool {
        return !(this == rhs)
    }
}

extend FFIAudioErrorType <: ToString & Equatable<FFIAudioErrorType> {
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
    public func toString(): String {
        return match (this) {
            case INIT => "INIT"
            case START_EXCEPTION => "START_EXCEPTION"
            case START_STATE_MISMATCH => "START_STATE_MISMATCH"
            case GENERAL => "GENERAL"
        }
    }

    public operator func ==(rhs: FFIAudioErrorType): Bool {
        return match ((this, rhs)) {
            case (INIT, INIT) => true
            case (START_EXCEPTION, START_EXCEPTION) => true
            case (START_STATE_MISMATCH, START_STATE_MISMATCH) => true
            case (GENERAL, GENERAL) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIAudioErrorType): Bool {
        return !(this == rhs)
    }
}

extend FFIAudioState <: ToString & Equatable<FFIAudioState> {
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
    public func toString(): String {
        return match (this) {
            case START => "START"
            case STOP => "STOP"
        }
    }

    public operator func ==(rhs: FFIAudioState): Bool {
        return match ((this, rhs)) {
            case (START, START) => true
            case (STOP, STOP) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIAudioState): Bool {
        return !(this == rhs)
    }
}

extend FFIScreenCaptureMode <: ToString & Equatable<FFIScreenCaptureMode> {
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
    public func toString(): String {
        return match (this) {
            case HOME_SCREEN => "HOME_SCREEN"
            case SPECIFIED_SCREEN => "SPECIFIED_SCREEN"
            case SPECIFIED_WINDOW => "SPECIFIED_WINDOW"
        }
    }

    public operator func ==(rhs: FFIScreenCaptureMode): Bool {
        return match ((this, rhs)) {
            case (HOME_SCREEN, HOME_SCREEN) => true
            case (SPECIFIED_SCREEN, SPECIFIED_SCREEN) => true
            case (SPECIFIED_WINDOW, SPECIFIED_WINDOW) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIScreenCaptureMode): Bool {
        return !(this == rhs)
    }
}

extend FFIScreenCaptureAudioFilterEnum <: ToString & Equatable<FFIScreenCaptureAudioFilterEnum> {
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
    public func toString(): String {
        return match (this) {
            case CURRENT_APP => "CURRENT_APP"
            case NOTIFICATION => "NOTIFICATION"
        }
    }

    public operator func ==(rhs: FFIScreenCaptureAudioFilterEnum): Bool {
        return match ((this, rhs)) {
            case (CURRENT_APP, CURRENT_APP) => true
            case (NOTIFICATION, NOTIFICATION) => true
            case _ => false
        }
    }
    public operator func !=(rhs: FFIScreenCaptureAudioFilterEnum): Bool {
        return !(this == rhs)
    }
}