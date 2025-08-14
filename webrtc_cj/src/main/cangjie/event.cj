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
    public RTCTrackEvent(
        let TYPE: String,
        let streams: Array<Int64>,
        let MediaStreamTrack_ptr: Int64,
        let RtpReceiver_ptr: Int64,
        let RtpTransceiver_ptr: Int64
    ) {}
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
        let TYPE: String,
        let address: String,
        let port: Int64,
        let url: String,
        let errorCode: Int64,
        let errorText: String
    ) {}
}











