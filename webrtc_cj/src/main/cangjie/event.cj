/**
 * Created on 2025/8/13
 */
package webrtc_cj

public class Event {
    Event(let TYPE: String) {}
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
        this.track = MediaStreamTrack(MediaStreamTrack_ptr)
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











