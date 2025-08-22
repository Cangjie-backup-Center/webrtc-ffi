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

//typedef struct {
//    const char* type;
//    CJToCppCandidateObject* candidate;
//} CJ_OnIceCandidateEvent;

@C
struct CJ_OnIceCandidateEvent {
    let TYPE: CString = unsafe {zeroValue<CString>()}
    // CJToCppCandidateObject* candidate; // TODO
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











