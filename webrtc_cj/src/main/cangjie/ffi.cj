/**
 * Created on 2025/7/19
 */
package webrtc_cj

import stdx.serialization.serialization.*

foreign func setThrowCangjieException(f: CFunc<(CString) -> Unit>): Unit

public class Webrtc4cjException <: Exception {
    public init(message: String) {
        super(message)
    }

    public override func toString(): String {
        return "Webrtc4cjFFIException: ${message}"
    }
}

public class Webrtc4cjFFIException <: Exception {
    static init () {
        unsafe {
            setThrowCangjieException({str: CString => //see ffi_exception.h
                throw Webrtc4cjFFIException(str.toString())
            })
        }
    }

    public init(message: String) {
        super(message)
    }

    public override func toString(): String {
        return "Webrtc4cjFFIException: ${message}"
    }
}

public enum WebrtcResult<T> {
    Ok(T)
    | Error(String)
}

@C // see ffi_define_struct.h
public struct CJ_EnumerateDevicesInfo {
    public let deviceId: CString = unsafe {zeroValue<CString>()}
    public let groupId: CString = unsafe {zeroValue<CString>()}
    public let label: CString = unsafe {zeroValue<CString>()}
    public let kind: CString = unsafe {zeroValue<CString>()}
}

@C // see ffi_define_struct.h
public struct CJ_ffiMediaStreamTrackJson {
    public let id: CString = unsafe {zeroValue<CString>()}
    public let kind: CString = unsafe {zeroValue<CString>()}
    public let readyState: CString = unsafe {zeroValue<CString>()}
    public let enabled: Bool = false
}

@C // see ffi_define_struct.h
public struct CJ_ReturnEnumerateDevicesInfo {
    public let ptr: CPointer<CJ_EnumerateDevicesInfo> = unsafe {zeroValue<CPointer<CJ_EnumerateDevicesInfo>>()}
    public let size: Int64 = 0
}

@C // see ffi_define_struct.h
public struct CJ_ReturnArray {
    public let ptr: CPointer<Int64> = unsafe {zeroValue<CPointer<Int64>>()}
    public let size: Int64 = 0
}

@C // see ffi_define_struct.h
public struct CJ_MediaTrackConstraintSet{
    public var width: Float64
    public var height: Float64
    public var aspectRatio: Float64
    public var frameRate: Float64
    public var facingMode: CString
    public var resizeMode: CString
    public var sampleRate: Int64
    public var sampleSize: Int64
    public var echoCancellation: Bool
    public var autoGainControl: Bool
    public var noiseSuppression: Bool
    public var latency: Float64
    public var channelCount: Int64
    public var deviceId: CString
    public var groupId: CString
    public var ohosScreenCaptureMode: CString
    public var ohosScreenCaptureDisplayId: Int64
    public var ohosScreenCaptureMissionId: CString
    public var ohosScreenCaptureWindowFilter: CString
    public var ohosScreenCaptureAudioFilter: CString
    public var ohosScreenCaptureSkipPrivacyMode: CString
    public var ohosScreenCaptureAutoRotation: Bool

    public init(width!: Float64 = 0.0, height!: Float64 = 0.0, aspectRatio!: Float64 = 0.0, frameRate!: Float64 = 0.0,
        facingMode!: String = "",
        resizeMode!: String = "",
        sampleRate!: Int64 = 0,
        sampleSize!: Int64 = 0,
        echoCancellation!: Bool = false,
        autoGainControl!: Bool = false,
        noiseSuppression!: Bool = false,
        latency!: Float64 = 0.0,
        channelCount!: Int64 = 0,
        deviceId!: String = "",
        groupId!: String = "",
        ohosScreenCaptureMode!: String = "",
        ohosScreenCaptureDisplayId!: Int64 = 0,
        ohosScreenCaptureMissionId!: String = "",
        ohosScreenCaptureWindowFilter!: String = "",
        ohosScreenCaptureAudioFilter!: String = "",
        ohosScreenCaptureSkipPrivacyMode!: String = "",
        ohosScreenCaptureAutoRotation!: Bool = false) {
        this.width = width
        this.height = height
        this.aspectRatio = aspectRatio
        this.frameRate = frameRate
        this.facingMode = unsafe {LibC.mallocCString(facingMode)}
        this.resizeMode = unsafe {LibC.mallocCString(resizeMode)}
        this.sampleRate = sampleRate
        this.sampleSize = sampleSize
        this.echoCancellation = echoCancellation
        this.autoGainControl = autoGainControl
        this.noiseSuppression = noiseSuppression
        this.latency = latency
        this.channelCount = channelCount
        this.deviceId = unsafe {LibC.mallocCString(deviceId)}
        this.groupId = unsafe {LibC.mallocCString(groupId)}
        this.ohosScreenCaptureMode = unsafe {LibC.mallocCString(ohosScreenCaptureMode)}
        this.ohosScreenCaptureDisplayId = ohosScreenCaptureDisplayId
        this.ohosScreenCaptureMissionId = unsafe {LibC.mallocCString(ohosScreenCaptureMissionId)}
        this.ohosScreenCaptureWindowFilter = unsafe {LibC.mallocCString(ohosScreenCaptureWindowFilter)}
        this.ohosScreenCaptureAudioFilter = unsafe {LibC.mallocCString(ohosScreenCaptureAudioFilter)}
        this.ohosScreenCaptureSkipPrivacyMode = unsafe {LibC.mallocCString(ohosScreenCaptureSkipPrivacyMode)}
        this.ohosScreenCaptureAutoRotation = ohosScreenCaptureAutoRotation
    }
}

@C // see ffi_define_struct.h
public struct CJ_SupportedConstraints {
    public let name: CString = unsafe {zeroValue<CString>()}
    public let isSupported: Bool = false
}

@C
public struct CJ_RTCSessionDescription {
    public var sdp: CString = unsafe {zeroValue<CString>()}
    public var sdp_size: Int64 = 0
    public var RTCSdpType: CString = unsafe {zeroValue<CString>()}
    public var RTCSdpType_size: Int64 = 0
    public var undefined: Bool = true

    public init(sdp: String, RTCSdpType: String) {
        unsafe {
            this.sdp = LibC.mallocCString(sdp)
            this.sdp_size = sdp.size
            this.RTCSdpType =LibC.mallocCString(RTCSdpType)
            this.RTCSdpType_size = RTCSdpType.size
            this.undefined = false
        }
    }

    public static func GET(msg: String): CJ_RTCSessionDescription {
        throw Webrtc4cjException("")
    }
}


//typedef struct{
//    int64_t rtcErrorDetailType;
//    const char* msg;
//}CJ_ErrorMessage;
@C
struct CJ_ErrorMessage {
    let rtcErrorDetailType: Int64 = 0
    let msg: CString = unsafe{zeroValue<CString>()}
}

public class ErrorMessage {
    public prop errorDetail: FFIRTCErrorDetailType {get(){
        FFIRTCErrorDetailType.GET(this.cpp.rtcErrorDetailType)
    }}
    public prop msg: String {get() {this.cpp.msg.toString()}}

    private var cpp: CJ_ErrorMessage
    init(msg: CJ_ErrorMessage){
        this.cpp = msg
    }
    ~init() {
        unsafe {
            LibC.free(this.cpp.msg)
        }
    }
}

@C
struct CJ_RTCIceServer {
    public var urls: CPointer<CString>
    public var urls_size: Int64
    public var username: CString
    public var username_size: Int64
    public var credential: CString
    public var credential_size: Int64
    public init(urls: CPointer<CString>, urls_size: Int64, username: CString, username_size: Int64, credential: CString, credential_size: Int64) {
        this.urls = urls
        this.urls_size = urls_size
        this.username = username
        this.username_size = username_size
        this.credential = credential
        this.credential_size = credential_size
    }
}

@C
struct CJ_RTCRtpEncodingParameters {
    public var rid: CString
    public var rid_size: Int64
    public var active: Bool
    public var maxBitrate: Int64
    public var maxFramerate: Int64
    public var scaleResolutionDownBy: Int64

    public init(rid: CString, rid_size: Int64, active: Bool, maxBitrate: Int64, maxFramerate: Int64, scaleResolutionDownBy: Int64) {
        this.rid = rid
        this.rid_size = rid_size
        this.active = active
        this.maxBitrate = maxBitrate
        this.maxFramerate = maxFramerate
        this.scaleResolutionDownBy = scaleResolutionDownBy
    }
}

@C
struct CJ_RTCRtpHeaderExtensionParameters {
    public var id: Int64
    public var uri: CString
    public var uri_size: Int64
    public var encrypted: Bool
    public init(id: Int64, uri: CString, uri_size: Int64,encrypted: Bool ) {
        this.id = id
        this.uri = uri
        this.uri_size = uri_size
        this.encrypted = encrypted
    }
}

@C
struct CJ_RTCRtcpParameters {
    public var cname: CString
    public var cname_size: Int64
    public var reducedSize: Bool
    public init(cname: CString, cname_size: Int64,reducedSize: Bool ) {
        this.cname = cname
        this.cname_size = cname_size
        this.reducedSize = reducedSize
    }
}

@C
struct CJ_RTCRtpCodecParameters {
    public var clockRate: Int64
    public var channels: Int64
    public var mimeType: CString
    public var mimeType_size: Int64
    public var sdpFmtpLine: CString
    public var sdpFmtpLine_size: Int64
    public var payloadType: Int64

    public init(clockRate: Int64, channels: Int64, mimeType: CString, mimeType_size: Int64, sdpFmtpLine: CString, sdpFmtpLine_size: Int64, payloadType: Int64) {
        this.clockRate=clockRate
        this.channels=channels
        this.mimeType=mimeType
        this.mimeType_size=mimeType_size
        this.sdpFmtpLine=sdpFmtpLine
        this.sdpFmtpLine_size=sdpFmtpLine_size
        this.payloadType=payloadType
    }
}

@C
struct CJ_RTCRtpSendParameters {
    var codecs: CPointer<CJ_RTCRtpCodecParameters>
    var codecs_size: Int64
    var headerExtensions: CPointer<CJ_RTCRtpHeaderExtensionParameters>
    var headerExtensions_size: Int64
    var rtcp: CJ_RTCRtcpParameters
    var encodings: CPointer<CJ_RTCRtpEncodingParameters>
    var encodings_size: Int64
    var transactionId: CString
    var transactionId_size: Int64

   public init(codecs: CPointer<CJ_RTCRtpCodecParameters>, codecs_size: Int64, headerExtensions: CPointer<CJ_RTCRtpHeaderExtensionParameters>, headerExtensions_size: Int64, rtcp: CJ_RTCRtcpParameters, encodings: CPointer<CJ_RTCRtpEncodingParameters>, encodings_size: Int64, transactionId: CString, transactionId_size: Int64) {
        this.codecs = codecs
        this.codecs_size = codecs_size
        this.headerExtensions = headerExtensions
        this.headerExtensions_size = headerExtensions_size
        this.rtcp = rtcp
        this.encodings = encodings
        this.encodings_size = encodings_size
        this.transactionId = transactionId
        this.transactionId_size = transactionId_size
    }
}

@C
struct CJ_RTCCertificate {
    public let expires: Int64
    public let credential: CPointer<CJ_RTCDtlsFingerprint>
    public let credential_size: Int64
    public init(expires: Int64, credential: CPointer<CJ_RTCDtlsFingerprint>, credential_size: Int64) {
        this.expires = expires
        this.credential = credential
        this.credential_size = credential_size
    }
}

@C
struct CJ_RTCDtlsFingerprint {
    public let algorithm: CString
    public let algorithm_size: Int64
    public let value: CString
    public let value_size: Int64
    public init(algorithm: CString, algorithm_size: Int64, value: CString, value_size: Int64) {
        this.algorithm = algorithm
        this.algorithm_size = algorithm_size
        this.value = value
        this.value_size = value_size
    }
}

@C
struct CJ_RTCConfiguration {
    let iceServers: CPointer<CJ_RTCIceServer>
    let iceServers_size: Int64
    let iceTransportPolicy: Int64
    let bundlePolicy: Int64
    let rtcpMuxPolicy: Int64
    let certificates: CPointer<CJ_RTCCertificate>
    let certificates_size: Int64
    let iceCandidatePoolSize: Int64
    public init(iceServers: CPointer<CJ_RTCIceServer>, iceServers_size: Int64, iceTransportPolicy: Int64, bundlePolicy: Int64, rtcpMuxPolicy: Int64, certificates: CPointer<CJ_RTCCertificate>, certificates_size: Int64, iceCandidatePoolSize: Int64){
        this.iceServers = iceServers
        this.iceServers_size = iceServers_size
        this.iceTransportPolicy = iceTransportPolicy
        this.bundlePolicy = bundlePolicy
        this.rtcpMuxPolicy = rtcpMuxPolicy
        this.certificates = certificates
        this.certificates_size = certificates_size
        this.iceCandidatePoolSize = iceCandidatePoolSize
    }
}

@C
public struct CJ_TO_CPP_DisplayMediaStreamOptions {
    let obj: CJ_MediaTrackConstraintSet
    let boolean: Bool
    let isBool: Bool
    public init(mtc: CJ_MediaTrackConstraintSet) {
        this.obj = mtc
        this.boolean = false
        this.isBool = false
    }
    public init(boolean: Bool) {
        this.obj = unsafe {zeroValue<CJ_MediaTrackConstraintSet>()}
        this.boolean = boolean
        this.isBool = true
    }
    public init() {
        this.obj = unsafe {zeroValue<CJ_MediaTrackConstraintSet>()}
        this.boolean = true
        this.isBool = true
    }
}

public class MediaTrackConstraints {
    var length: Int64 = 0
    var advanced: CPointer<CJ_MediaTrackConstraintSet> = unsafe {zeroValue<CPointer<CJ_MediaTrackConstraintSet>>()}
    public init(advanced: Array<CJ_MediaTrackConstraintSet>) {
        let arr = LibC.malloc<CJ_MediaTrackConstraintSet>(count: advanced.size)
        unsafe {
            for (i in 0..advanced.size) {
                arr.write(i, advanced[i])
            }
        }
        this.advanced = arr
        this.length = Int64(advanced.size)
    }
}


@C
public struct CJ_RTCIceCandidateInit {
    var isBuild: Bool = false
    var candidate: CString = unsafe {zeroValue<CString>()}
    var sdpMLineIndex: Int32 = 0
    var sdpMid: CString = unsafe {zeroValue<CString>()}
    var usernameFragment: CString = unsafe {zeroValue<CString>()}
    public init() {}
    public init(isBuild: Bool, candidate: CString, sdpMLineIndex: Int32, sdpMid: CString, usernameFragment: CString) {
        this.isBuild = isBuild
        this.candidate = candidate
        this.sdpMLineIndex = sdpMLineIndex
        this.sdpMid = sdpMid
        this.usernameFragment = usernameFragment
    }
}

public class RTCIceCandidateInit <: Serializable<RTCIceCandidateInit> {

    var isBuild_: Bool = false
    var candidate_: String = ""
    var sdpMLineIndex_: Int32 = 0
    var sdpMid_: String = ""
    var usernameFragment_: String = ""

    public prop isBuild: Bool {get() {this.cpp.isBuild}}
    public prop candidate: String {get() {this.cpp.candidate.toString()}}
    public prop sdpMLineIndex: Int32{get() {this.cpp.sdpMLineIndex}}
    public prop sdpMid: String {get() {this.cpp.sdpMid.toString()}}
    public prop usernameFragment: String {get() {this.cpp.usernameFragment.toString()}}
    let cpp: CJ_RTCIceCandidateInit

    public init(cpp: CJ_RTCIceCandidateInit){
        this.cpp =cpp
        this.isBuild_ = cpp.isBuild
        this.candidate_ = cpp.candidate.toString()
        this.sdpMLineIndex_ = cpp.sdpMLineIndex
        this.sdpMid_ = cpp.sdpMid.toString()
        this.usernameFragment_ = cpp.usernameFragment.toString()

    }

    public init(isBuild: Bool, candidate: String, sdpMLineIndex: Int32, sdpMid: String, usernameFragment: String) {
        if (isBuild) {
            unsafe {
                this.cpp = CJ_RTCIceCandidateInit(isBuild, LibC.mallocCString(candidate), sdpMLineIndex, LibC.mallocCString(sdpMid), LibC.mallocCString(usernameFragment))
            }
        } else {
            this.cpp = CJ_RTCIceCandidateInit()
        }
    }

    ~init(){
        unsafe{
            if (this.cpp.isBuild){
                LibC.free(this.cpp.candidate)
                LibC.free(this.cpp.sdpMid)
                LibC.free(this.cpp.usernameFragment)
            }
        }
    }

    /* 实现 Serializable 接口的序列化方法 */
    public func serialize(): DataModel {
        return DataModelStruct()
                .add(field<Bool>("isBuild_", isBuild_))
                .add(field<String>("candidate_", candidate_))
                .add(field<Int32>("sdpMLineIndex_", sdpMLineIndex_))
                .add(field<String>("sdpMid_", sdpMid_))
                .add(field<String>("usernameFragment_", usernameFragment_))
    }

    /* 实现反序列化方法 JSON.*/
    public static func deserialize(dm: DataModel): RTCIceCandidateInit {
        let dms = match (dm) {
            case data: DataModelStruct => data
            case _ => throw Exception("this data is not DataModelStruct")
        }
        let result = RTCIceCandidateInit(
            Bool.deserialize(dms.get("isBuild_")),
            String.deserialize(dms.get("candidate_")),
            Int32.deserialize(dms.get("sdpMLineIndex_")),
            String.deserialize(dms.get("sdpMid_")),
            String.deserialize(dms.get("usernameFragment_")),
        )
        return result
    }
}

@C
public struct CJ_RTCDataChannelInit {
    var isBuild: Bool = false
    var ordered: Bool = false
    var maxPacketLifeTime: Int64 = -1
    var maxRetransmits: Int64 = -1
    var protocol: CString = unsafe{zeroValue<CString>()}
    var negotiated: Bool = false
    var id: Int64 = -1
}

@C
public struct CJ_ArrayMediaStream {
    let ptr: CPointer<Int64> = unsafe {zeroValue<CPointer<Int64>>()}
    let size: Int64 = 0
}

@C
public struct CJ_FFICreateSdpObserver_result {
    let sdp: CString = unsafe{zeroValue<CString>()}
    let RTCSdpType: CString = unsafe{zeroValue<CString>()}
    let isFail: Bool = true // 如果 true , 其他值就无效了
    let msg: CString = unsafe{zeroValue<CString>()}
}

public class RTCSessionDescription <: Serializable<RTCSessionDescription> {
    private var sdp_: String = ""
    private var RTCSdpType_: String = ""
    public prop sdp: String {
        get() {
            if (let Some(v) <- cpp) {
                return v.sdp.toString()
            } else {
                return sdp_
            }
        }
    }

    public prop RTCSdpType: String {
        get() {
            if (let Some(v) <- cpp) {
                return v.RTCSdpType.toString()
            }else {
                return RTCSdpType_
            }
        }
    }

    var cpp: ?CJ_RTCSessionDescription = None
    public init(cpp: CJ_RTCSessionDescription) {
        this.cpp = cpp
        this.sdp_ = cpp.sdp.toString()
        this.RTCSdpType_ = cpp.RTCSdpType.toString()
    }

    public init(sdp: String, RTCSdpType: String) {
        this.sdp_ = sdp
        this.RTCSdpType_ = RTCSdpType
        this.cpp = CJ_RTCSessionDescription(sdp, RTCSdpType)
    }

    ~init() {
        if (let Some(v) <- cpp) {
            if (!v.undefined) {
                unsafe {
                    LibC.free(v.sdp)
                    LibC.free(v.RTCSdpType)
                }
            }
        }
    }

    /* 实现 Serializable 接口的序列化方法 */
    public func serialize(): DataModel {
        return DataModelStruct().add(field<String>("sdp_", sdp_)).add(field<String>("RTCSdpType_", RTCSdpType_))
    }

    /* 实现反序列化方法 */
    public static func deserialize(dm: DataModel): RTCSessionDescription {
        let dms = match (dm) {
            case data: DataModelStruct => data
            case _ => throw Exception("this data is not DataModelStruct")
        }
        let result = RTCSessionDescription(String.deserialize(dms.get("sdp_")), String.deserialize(dms.get("RTCSdpType_")))
        return result
    }
}



public class FFICreateSdpObserverResult {
    public prop result: WebrtcResult<RTCSessionDescription> {
        get() {
             if (this.cpp.isFail) {
                return WebrtcResult.Error(this.cpp.msg.toString())
             } else {
                return WebrtcResult.Ok(RTCSessionDescription(this.cpp.sdp.toString(), this.cpp.RTCSdpType.toString()))
             }
        }
    }

    let cpp: CJ_FFICreateSdpObserver_result
    public init(cpp: CJ_FFICreateSdpObserver_result) {
        this.cpp = cpp
    }

    ~init() {
        unsafe {
            if (this.cpp.isFail) {
                LibC.free(this.cpp.msg)
            } else {
                LibC.free(this.cpp.sdp)
                LibC.free(this.cpp.RTCSdpType)
            }
        }
    }

}
