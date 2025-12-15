/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */
package webrtc_cj
import ohos.base.throwNativeError

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

public class RTCIceCandidate <: Serializable<RTCIceCandidate> {
    public var candidate: String
    public var sdpMid: String
    public var sdpMLineIndex: Int64
    public var foundation: String
    public var component: Int64
    public var priority: Int64
    public var address: String
    public var iceProtocol: String
    public var port: Int64
    public var iceCandidateType: Int64
    public var iceTcpCandidateType: String
    public var relatedAddress: String
    public var relatedPort: Int64
    public var usernameFragment: String
    init(cpp: CJ_RTCIceCandidate) {
        this.candidate = cpp.candidate.toString()
        this.sdpMid = cpp.sdpMid.toString()
        this.sdpMLineIndex = cpp.sdpMLineIndex
        this.foundation = cpp.foundation.toString()
        this.component = cpp.component
        this.priority = cpp.priority
        this.address = cpp.address.toString()
        this.iceProtocol = cpp.iceProtocol.toString()
        this.port = cpp.port
        this.iceCandidateType = cpp.iceCandidateType
        this.iceTcpCandidateType = cpp.iceTcpCandidateType.toString()
        this.relatedAddress = cpp.relatedAddress.toString()
        this.relatedPort = cpp.relatedPort
        this.usernameFragment = cpp.usernameFragment.toString()
    }


    init(candidate: String, sdpMid: String, sdpMLineIndex: Int64, foundation: String, component: Int64, priority: Int64, address: String, iceProtocol: String, port: Int64, iceCandidateType: Int64, iceTcpCandidateType: String, relatedAddress: String, relatedPort: Int64, usernameFragment: String) {
        this.candidate = candidate
        this.sdpMid = sdpMid
        this.sdpMLineIndex = sdpMLineIndex
        this.foundation = foundation
        this.component = component
        this.priority = priority
        this.address = address
        this.iceProtocol = iceProtocol
        this.port = port
        this.iceCandidateType = iceCandidateType
        this.iceTcpCandidateType = iceTcpCandidateType
        this.relatedAddress = relatedAddress
        this.relatedPort = relatedPort
        this.usernameFragment = usernameFragment
    }

     /* 实现 Serializable 接口的序列化方法 */
    public func serialize(): DataModel {
        return DataModelStruct().add(field<String>("candidate", candidate))
                                .add(field<String>("sdpMid", sdpMid))
                                .add(field<Int64>("sdpMLineIndex", sdpMLineIndex))
                                .add(field<String>("foundation", foundation))
                                .add(field<Int64>("component", component))
                                .add(field<Int64>("priority", priority))
                                .add(field<String>("address", address))
                                .add(field<String>("iceProtocol", iceProtocol))
                                .add(field<Int64>("port", port))
                                .add(field<Int64>("iceCandidateType", iceCandidateType))
                                .add(field<String>("iceTcpCandidateType", iceTcpCandidateType))
                                .add(field<String>("relatedAddress", relatedAddress))
                                .add(field<Int64>("relatedPort", relatedPort))
                                .add(field<String>("usernameFragment", usernameFragment))
    }

    public func toRTCIceCandidateInit(): RTCIceCandidateInit {
        //     public init(isBuild: Bool, candidate: String, sdpMLineIndex: Int32, sdpMid: String, usernameFragment: String) {
        return RTCIceCandidateInit(true, this.candidate, Int32(this.sdpMLineIndex), this.sdpMid, this.usernameFragment)
    }

    /* 实现反序列化方法 */
    public static func deserialize(dm: DataModel): RTCIceCandidate {
        let dms = match (dm) {
            case data: DataModelStruct => data
            case _ => throw Exception("this data is not DataModelStruct")
        }
        let result = RTCIceCandidate(
                            String.deserialize(dms.get("candidate")),
                            String.deserialize(dms.get("sdpMid")),
                            Int64.deserialize(dms.get("sdpMLineIndex")),
                            String.deserialize(dms.get("foundation")),
                            Int64.deserialize(dms.get("component")),
                            Int64.deserialize(dms.get("priority")),
                            String.deserialize(dms.get("address")),
                            String.deserialize(dms.get("iceProtocol")),
                            Int64.deserialize(dms.get("port")),
                            Int64.deserialize(dms.get("iceCandidateType")),
                            String.deserialize(dms.get("iceTcpCandidateType")),
                            String.deserialize(dms.get("relatedAddress")),
                            Int64.deserialize(dms.get("relatedPort")),
                            String.deserialize(dms.get("usernameFragment"))
                )
        return result
    }
}

@C
struct CJ_RTCPeerConnectionIceEvent {
    let TYPE: CString = unsafe {zeroValue<CString>()}
    let candidate: CJ_RTCIceCandidate = unsafe {zeroValue<CJ_RTCIceCandidate>()}
}

public class RTCPeerConnectionIceEvent {
    public var TYPE: String = ""
    public var candidate: ?RTCIceCandidate = None
    public var url: ?String = None
    init(cpp: CJ_RTCPeerConnectionIceEvent) {
        if(!cpp.candidate.undefined) {
            this.candidate = RTCIceCandidate(cpp.candidate)
            this.url = cpp.candidate.serverUrl.toString()
            this.TYPE = cpp.TYPE.toString()
        }
    }
}

public class OnIceCandidateEvent {
    OnIceCandidateEvent(public let TYPE: String){}
}

@C
public struct CJ_MediaStreamTrack {
    let ptr_id: Int64 = -1
    let kind: CString = unsafe {zeroValue<CString>()}
    let id: CString = unsafe {zeroValue<CString>()}
    let enabled: Bool = false
    let readyState: CString = unsafe {zeroValue<CString>()}
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
    public let receiver: RTCRtpReceiver
    public let transceiver: RtpTransceiver

    public RTCTrackEvent(TYPE: String,  streams: Array<Int64>, mediaStreamTrack_ptr: Int64, RtpReceiver_ptr: Int64, RtpTransceiver_ptr: Int64) {
        var tmpMST: CJ_MediaStreamTrack
        this.TYPE = TYPE
        this.streams = streams
        this.track = VideoTrack(mediaStreamTrack_ptr)
        this.receiver = RTCRtpReceiver(RtpReceiver_ptr)
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

@C
struct CJ_AudioSamples {
    let sampleRate: Int32 = unsafe {zeroValue<Int32>()};
    let audioFormat: Int32 = unsafe {zeroValue<Int32>()};
    let channelCount: Int32 = unsafe {zeroValue<Int32>()};
    let data: CPointer<UInt8> = unsafe {zeroValue<CPointer<UInt8>>()};
    let dataLength: Int32 = unsafe {zeroValue<Int32>()};
}











