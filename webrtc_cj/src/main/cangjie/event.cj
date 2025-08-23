/**
 * Created on 2025/8/13
 */
package webrtc_cj

public open class Event {
    Event(public let TYPE: String) {}
}

public class RTCErrorEvent <: Event {
    public let errorDetail: FFIRTCErrorDetailType
    public let sdpLineNumber: Int64
    public let sctpCauseCode: Int64
    public let receivedAlert: Int64
    public let sentAlert: Int64
    RTCErrorEvent(TYPE: String, errorDetail: FFIRTCErrorDetailType, sdpLineNumber: Int64, sctpCauseCode: Int64, receivedAlert: Int64, sentAlert: Int64) {
        super(TYPE)
        this.errorDetail =errorDetail
        this.sdpLineNumber =sdpLineNumber
        this.sctpCauseCode =sctpCauseCode
        this.receivedAlert =receivedAlert
        this.sentAlert =sentAlert
    }
}

public class AudioErrorEvent <: Event {
    public let error: FFIAudioErrorType
    AudioErrorEvent(TYPE: String, error: FFIAudioErrorType) {
        super(TYPE)
        this.error = error
    }
}
public class AudioStateChangeEvent <: Event {
    public let state: FFIAudioState
    AudioStateChangeEvent(TYPE: String, state: FFIAudioState) {
        super(TYPE)
        this.state = state
    }
}
public class AudioCapturerSamplesReadyEvent <: Event {
    public let audioFormat: Int64
    public let channelCount: Int64
    public let sampleRate: Int64
    public let data: Array<Byte>
    AudioCapturerSamplesReadyEvent(TYPE: String, audioFormat: Int64, channelCount: Int64, sampleRate: Int64, data: Array<Byte>) {
        super(TYPE)
        this.audioFormat = audioFormat
        this.channelCount = channelCount
        this.sampleRate = sampleRate
        this.data = data
    }
}

@C
struct CJ_RTCDataChannelEvent {
    var channel: Int64 = 0
}

@C
struct CJ_Event {
    let eventType: CString = unsafe {zeroValue<CString>()}
}


@C
struct CJ_RTCIceCandidate {
    let undefined: Bool = unsafe {zeroValue<Bool>()}
    let candidate: CString = unsafe {zeroValue<CString>()}
    let sdpMid: CString = unsafe {zeroValue<CString>()}
    let sdpMLineIndex: Int64 = unsafe {zeroValue<Int64>()}
    let foundation: CString = unsafe {zeroValue<CString>()}
    let component: Int64 = unsafe {zeroValue<Int64>()}
    let priority: Int64 = unsafe {zeroValue<Int64>()}
    let address: CString = unsafe {zeroValue<CString>()}
    let iceProtocol: CString = unsafe {zeroValue<CString>()}
    let port: Int64 = unsafe {zeroValue<Int64>()}
    let iceCandidateType: Int64 = unsafe {zeroValue<Int64>()}
    let iceTcpCandidateType: CString = unsafe {zeroValue<CString>()}
    let relatedAddress: CString = unsafe {zeroValue<CString>()}
    let relatedPort: Int64 = unsafe {zeroValue<Int64>()}
    let usernameFragment: CString = unsafe {zeroValue<CString>()}
    // 父类的成员属性
    let adapterType: CString = unsafe {zeroValue<CString>()}
    let serverUrl: CString = unsafe {zeroValue<CString>()}
}

public class RTCIceCandidate {
    public prop undefined: Bool {get() {this.cpp.undefined}}
    public prop candidate: String {get() {this.cpp.candidate.toString()}}
    public prop sdpMid: String {get() {this.cpp.sdpMid.toString()}}
    public prop sdpMLineIndex: Int64 {get() {this.cpp.sdpMLineIndex}}
    public prop foundation: String {get() {this.cpp.foundation.toString()}}
    public prop component: Int64 {get() {this.cpp.component}}
    public prop priority: Int64 {get() {this.cpp.priority}}
    public prop address: String {get() {this.cpp.address.toString()}}
    public prop iceProtocol: String {get() {this.cpp.iceProtocol.toString()}}
    public prop port: Int64 {get() {this.cpp.port}}
    public prop iceCandidateType: Int64 {get() {this.cpp.iceCandidateType}}
    public prop iceTcpCandidateType: String {get() {this.cpp.iceTcpCandidateType.toString()}}
    public prop relatedAddress: String {get() {this.cpp.relatedAddress.toString()}}
    public prop relatedPort: Int64 {get() {this.cpp.relatedPort}}
    public prop usernameFragment: String {get() {this.cpp.usernameFragment.toString()}}
//    public prop adapterType: String {get() {this.cpp.adapterType.toString()}}
//    public prop serverUrl: String {get() {this.cpp.serverUrl.toString()}}
    var cpp: CJ_RTCIceCandidate
    init(cpp: CJ_RTCIceCandidate) {
        this.cpp = cpp
    }
    ~init() {
        unsafe {
            if (!this.cpp.undefined) {
                LibC.free(this.cpp.candidate)
                LibC.free(this.cpp.sdpMid)
                LibC.free(this.cpp.foundation)
                LibC.free(this.cpp.address)
                LibC.free(this.cpp.iceProtocol)
                LibC.free(this.cpp.iceTcpCandidateType)
                LibC.free(this.cpp.relatedAddress)
                LibC.free(this.cpp.usernameFragment)
                LibC.free(this.cpp.adapterType)
                LibC.free(this.cpp.serverUrl)
            }
        }
    }
}

@C
struct CJ_RTCPeerConnectionIceEvent {
    let TYPE: CString = unsafe {zeroValue<CString>()}
    let candidate: CJ_RTCIceCandidate = unsafe {zeroValue<CJ_RTCIceCandidate>()}
}


public class RTCPeerConnectionIceEvent {
    public prop TYPE: String {get(){this.cpp.TYPE.toString()}}
    public var candidate: ?RTCIceCandidate = None
    public var url: ?String = None
    let cpp: CJ_RTCPeerConnectionIceEvent
    init(cpp: CJ_RTCPeerConnectionIceEvent) {
        this.cpp = cpp
        if(!this.cpp.candidate.undefined) {
            this.candidate = RTCIceCandidate(this.cpp.candidate)
            this.url = this.cpp.candidate.serverUrl.toString()
        }
    }
    ~init() {
        unsafe {
            LibC.free(this.cpp.TYPE)
        }
    }
}

public class OnIceCandidateEvent {
    OnIceCandidateEvent(public let TYPE: String){}
}

@C
struct CJ_RTCTrackEvent {
    let TYPE: CString = unsafe {zeroValue<CString>()}
    let streams: CPointer<Int64> = unsafe {zeroValue<CPointer<Int64>>()}
    let streams_size: Int64 = -1
    let MediaStreamTrack_ptr: Int64 = -1
    let RtpReceiver_ptr: Int64 = -1
    let RtpTransceiver_ptr: Int64 = -1
}

public class RTCTrackEvent {
    public let TYPE: String
    public let streams: Array<Int64>
    public let track: MediaStreamTrack
//    public let receiver: RtpReceiver // TODO
    public let transceiver: RtpTransceiver

    public RTCTrackEvent( TYPE: String,  streams: Array<Int64>, MediaStreamTrack_ptr: Int64, RtpReceiver_ptr: Int64, RtpTransceiver_ptr: Int64) {
        this.TYPE = TYPE
        this.streams = streams
        this.track = MediaTrack(MediaStreamTrack_ptr)
        this.transceiver = RtpTransceiver(RtpTransceiver_ptr)
    }
}

@C
struct CJ_RTCPeerConnectionIceErrorEvent {
    let TYPE: CString = unsafe {zeroValue<CString>()}
    let address: CString = unsafe {zeroValue<CString>()}
    let port: Int64 = -1
    let url: CString = unsafe {zeroValue<CString>()}
    let errorCode: Int64 = -1
    let errorText: CString = unsafe {zeroValue<CString>()}
}

public class RTCPeerConnectionIceErrorEvent {
    public RTCPeerConnectionIceErrorEvent(
        public let TYPE: String,
        public let address: String,
        public let port: Int64,
        public let url: String,
        public let errorCode: Int64,
        public let errorText: String
    ) {}
}


@C
struct CJ_MessageEvent {
    let TYPE: CString = unsafe {zeroValue<CString>()}
    let data_arr: CPointer<UInt8>= unsafe {zeroValue<CPointer<UInt8>>()}
    let data_arr_size: Int64= unsafe {zeroValue<Int64>()}
    let binary: Bool= unsafe {zeroValue<Bool>()}
    let data_str: CString= unsafe {zeroValue<CString>()}
}

public enum MessageEventData {
    | STRING(String)
    | ARRAY_BUFFER(Array<UInt8>)
}

public class MessageEvent {
    public MessageEvent(
        public let TYPE: String,
        public let data: MessageEventData
    ) {}
}











