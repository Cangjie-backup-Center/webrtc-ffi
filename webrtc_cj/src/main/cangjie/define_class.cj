/**
 * Created on 2025/8/21
 */
package webrtc_cj

public class RTCIceServer {
    public prop urls: Array<String> {
        get() {
            let arr = Array<String>(this.cpp.urls_size, repeat: "")
            unsafe {
                for (i in 0..this.cpp.urls_size) {
                    arr[i] = this.cpp.urls.read(i).toString()
                }
            }
            return arr
        }
    }
    public prop username: String { get() { return this.cpp.username.toString() } }
    public prop credential: String { get() { return this.cpp.credential.toString() } }
    var urls_handle: CPointerHandle<CString>
    var cpp: CJ_RTCIceServer
    public init(urls!: Array<String> = [], username!: String = "", credential!: String = "") {
        unsafe {
            let arr = Array<CString>(urls.size, repeat: zeroValue<CString>())
            for (i in 0..arr.size) {
                arr[i] = LibC.mallocCString(urls[i])
            }
            this.urls_handle = acquireArrayRawData(arr)
            this.cpp = CJ_RTCIceServer(acquireArrayRawData(arr).pointer, arr.size, LibC.mallocCString(username), username.size, LibC.mallocCString(credential), credential.size)
        }
    }
    ~init() {
        unsafe {
            for (i in 0..this.cpp.urls_size) {
                LibC.free(this.cpp.urls.read(i))
            }
            releaseArrayRawData(this.urls_handle)
            LibC.free(this.cpp.username)
            LibC.free(this.cpp.credential)
            this.cpp = zeroValue<CJ_RTCIceServer>()
        }
    }
}

public class RTCRtpHeaderExtensionParameters {
    public prop id: Int64 {get() {this.cpp.id}}
    public prop uri: String {get() {this.cpp.uri.toString()}}
    public prop encrypted: Bool{get() {this.cpp.encrypted}}
    var cpp:CJ_RTCRtpHeaderExtensionParameters
    public init(id: Int64, uri: String,encrypted: Bool ){
        unsafe {
            this.cpp = CJ_RTCRtpHeaderExtensionParameters(id, LibC.mallocCString(uri), uri.size, encrypted)
        }
    }
    ~init() {
        unsafe {
            LibC.free(this.cpp.uri)
        }
    }
}

public class RTCRtcpParameters {
    public prop cname: String {get() {this.cpp.cname.toString()}}
    public prop reducedSize: Bool{get() {this.cpp.reducedSize}}
    var cpp:CJ_RTCRtcpParameters
    public init(cname: String,reducedSize: Bool ){
        unsafe {
            this.cpp = CJ_RTCRtcpParameters(LibC.mallocCString(cname), cname.size, reducedSize)
        }
    }
    ~init() {
        unsafe {
            LibC.free(this.cpp.cname)
            this.cpp = zeroValue<CJ_RTCRtcpParameters>()
        }
    }
}

public class RTCRtpCodecParameters {
    public prop clockRate: Int64 {get(){this.cpp.clockRate}}
    public prop channels: Int64 {get(){this.cpp.channels}}
    public prop mimeType: String {get(){this.cpp.mimeType.toString()}}
    public prop sdpFmtpLine: String {get(){this.cpp.sdpFmtpLine.toString()}}
    public prop payloadType: Int64 {get(){this.cpp.clockRate}}

    var cpp:CJ_RTCRtpCodecParameters
    public init(clockRate: Int64, channels: Int64, mimeType: String, sdpFmtpLine: String, payloadType: Int64) {
        unsafe {
            this.cpp = CJ_RTCRtpCodecParameters(clockRate,channels, LibC.mallocCString(mimeType), mimeType.size, LibC.mallocCString(sdpFmtpLine), sdpFmtpLine.size, payloadType )
        }
    }
    ~init() {
        unsafe {
            LibC.free(this.cpp.mimeType)
            LibC.free(this.cpp.sdpFmtpLine)
            this.cpp = zeroValue<CJ_RTCRtpCodecParameters>()
        }
    }
}

public class RTCRtpEncodingParameters {
    public prop rid: String {
        get() {unsafe{this.cpp.rid.toString()}}
    }
    public prop active: Bool {
        get() {this.cpp.active}
    }
    public prop maxBitrate: Int64{
        get() {this.cpp.maxBitrate}
    }
    public prop maxFramerate: Int64{
        get() {this.cpp.maxFramerate}
    }
    public prop scaleResolutionDownBy: Int64{
        get() {this.cpp.scaleResolutionDownBy}
    }

    var cpp: CJ_RTCRtpEncodingParameters
    public init(rid: String, active: Bool, maxBitrate: Int64, maxFramerate: Int64, scaleResolutionDownBy: Int64){
        unsafe {
            this.cpp = CJ_RTCRtpEncodingParameters(LibC.mallocCString(rid), rid.size, active, maxBitrate, maxFramerate, scaleResolutionDownBy)
        }
    }
    ~init() {
        unsafe {
            LibC.free(this.cpp.rid)
            this.cpp = zeroValue<CJ_RTCRtpEncodingParameters>()
        }
    }
}

public class RTCRtpSendParameters {
    private var codecs_: Array<RTCRtpCodecParameters>
    private var headerExtensions_: Array<RTCRtpHeaderExtensionParameters>
    private var rtcp_: RTCRtcpParameters
    private var encodings_: Array<RTCRtpEncodingParameters>

    public prop codecs: Array<RTCRtpCodecParameters> {get(){this.codecs_}}
    public prop headerExtensions: Array<RTCRtpHeaderExtensionParameters> {get(){this.headerExtensions_}}
    public prop rtcp: RTCRtcpParameters {get(){this.rtcp_}}
    public prop encodings: Array<RTCRtpEncodingParameters> {get(){this.encodings_}}
    public prop transactionId: String {get(){this.cpp.transactionId.toString()}}

    private var codecs_cpp: CPointerHandle<CJ_RTCRtpCodecParameters>
    private var headerExtensions_cpp: CPointerHandle<CJ_RTCRtpHeaderExtensionParameters>
    private var encodings_cpp: CPointerHandle<CJ_RTCRtpEncodingParameters>

    var cpp: CJ_RTCRtpSendParameters
    public init(codecs: Array<RTCRtpCodecParameters>, headerExtensions: Array<RTCRtpHeaderExtensionParameters>, rtcp: RTCRtcpParameters, encodings: Array<RTCRtpEncodingParameters>, transactionId: String) {
        this.codecs_ = codecs
        this.headerExtensions_ = headerExtensions
        this.encodings_ = encodings
        this.rtcp_ = rtcp
        unsafe {
            let codecs_cpp = Array<CJ_RTCRtpCodecParameters>(codecs.size, repeat: zeroValue<CJ_RTCRtpCodecParameters>())
            for (i in 0..codecs.size) {
                codecs_cpp[i] = codecs[i].cpp
            }
            let headerExtensions_cpp = Array<CJ_RTCRtpHeaderExtensionParameters>(codecs.size, repeat: zeroValue<CJ_RTCRtpHeaderExtensionParameters>())
            for (i in 0..codecs.size) {
                headerExtensions_cpp[i] = headerExtensions[i].cpp
            }
            let encodings_cpp = Array<CJ_RTCRtpEncodingParameters>(codecs.size, repeat: zeroValue<CJ_RTCRtpEncodingParameters>())
            for (i in 0..codecs.size) {
                encodings_cpp[i] = encodings[i].cpp
            }
            this.codecs_cpp = acquireArrayRawData(codecs_cpp)
            this.headerExtensions_cpp = acquireArrayRawData(headerExtensions_cpp)
            this.encodings_cpp = acquireArrayRawData(encodings_cpp)
            this.cpp = CJ_RTCRtpSendParameters(
                this.codecs_cpp.pointer,
                codecs_.size,
                this.headerExtensions_cpp.pointer,
                headerExtensions_.size,
                rtcp.cpp,
                this.encodings_cpp.pointer,
                encodings_.size,
                LibC.mallocCString(transactionId),
                transactionId.size
            )
        }
    }

    ~init() {
        unsafe {
            this.codecs_ = zeroValue<Array<RTCRtpCodecParameters>>()
            this.headerExtensions_ = zeroValue<Array<RTCRtpHeaderExtensionParameters>>()
            this.rtcp_ = zeroValue<RTCRtcpParameters>()
            this.encodings_ = zeroValue<Array<RTCRtpEncodingParameters>>()
            releaseArrayRawData(this.codecs_cpp)
            releaseArrayRawData(this.headerExtensions_cpp)
            releaseArrayRawData(this.encodings_cpp)
            this.cpp = zeroValue<CJ_RTCRtpSendParameters>()
        }
    }
}

public class RTCDtlsFingerprint {
    public prop algorithm: String {get(){this.cpp.algorithm.toString()}}
    public prop value: String {get(){this.cpp.value.toString()}}
    var cpp: CJ_RTCDtlsFingerprint
    public init(algorithm: String, value: String) {
        unsafe {
            this.cpp = CJ_RTCDtlsFingerprint(LibC.mallocCString(algorithm), algorithm.size, LibC.mallocCString(value), value.size)
        }
    }
    ~init() {
        unsafe {
            this.cpp = zeroValue<CJ_RTCDtlsFingerprint>()
            LibC.free(this.cpp.algorithm)
            LibC.free(this.cpp.value)
        }
    }
}

public class RTCCertificate {

    public prop expires: Int64 {get(){this.cpp.expires}}
    public prop credential: Array<RTCDtlsFingerprint> {get(){credential_}}

    var credential_: Array<RTCDtlsFingerprint>
    var cpp: CJ_RTCCertificate
    var credential_cpp: CPointerHandle<CJ_RTCDtlsFingerprint>

    public init(expires: Int64, credential: Array<RTCDtlsFingerprint>) {
        this.credential_ = credential
        unsafe {
            let arr = Array<CJ_RTCDtlsFingerprint>(credential.size, repeat: zeroValue<CJ_RTCDtlsFingerprint>())
            for (i in 0..arr.size) {
                arr[i] = credential[i].cpp
            }
            this.credential_cpp = acquireArrayRawData(arr)
            this.cpp = CJ_RTCCertificate(expires, this.credential_cpp.pointer, credential.size)
        }
    }
    ~init() {
        unsafe {
            this.credential_ = zeroValue<Array<RTCDtlsFingerprint>>()
            releaseArrayRawData(this.credential_cpp)
            this.cpp = zeroValue<CJ_RTCCertificate>()
        }
    }

}

public class RTCConfiguration {
    private var iceServers_: Array<RTCIceServer>
    private var certificates_: Array<RTCCertificate>

    private var iceServers_cpp: CPointerHandle<CJ_RTCIceServer>
    private var certificates_cpp: CPointerHandle<CJ_RTCCertificate>

    var cpp: CJ_RTCConfiguration
    public init(iceServers!: Array<RTCIceServer> = [],
                iceTransportPolicy!: ?FFIRTCIceTransportPolicy = None,
                bundlePolicy!: ?FFIRTCBundlePolicy = None,
                rtcpMuxPolicy!: ?FFIRTCRtcpMuxPolicy = None,
                certificates!: Array<RTCCertificate> = [],
                iceCandidatePoolSize!: Int64 = 0) {
        this.iceServers_= iceServers
        this.certificates_ = certificates
        unsafe {
            let arr1 = Array<CJ_RTCIceServer>(iceServers.size, repeat: zeroValue<CJ_RTCIceServer>())
            for (i in 0..arr1.size) {
                arr1[i] = iceServers[i].cpp
            }
            let arr2 = Array<CJ_RTCCertificate>(iceServers.size, repeat: zeroValue<CJ_RTCCertificate>())
            for (i in 0..arr2.size) {
                arr2[i] = certificates[i].cpp
            }
            this.iceServers_cpp = acquireArrayRawData(arr1)
            this.certificates_cpp = acquireArrayRawData(arr2)
            this.cpp = CJ_RTCConfiguration(
                this.iceServers_cpp.pointer,
                arr1.size,
                if (let Some(v) <- iceTransportPolicy) {
                    FFIRTCIceTransportPolicy.GET(v)
                }else {
                    -1
                },
                if (let Some(v) <- bundlePolicy) {
                    FFIRTCBundlePolicy.GET(v)
                }else {
                    -1
                },
                if (let Some(v) <- rtcpMuxPolicy) {
                    FFIRTCRtcpMuxPolicy.GET(v)
                }else {
                    -1
                },
                this.certificates_cpp.pointer,
                arr2.size,
                iceCandidatePoolSize
            )
        }
    }
    ~init() {
        unsafe {
            this.iceServers_ = zeroValue<Array<RTCIceServer>>()
            this.certificates_ = zeroValue<Array<RTCCertificate>>()
            releaseArrayRawData(this.iceServers_cpp)
            releaseArrayRawData(this.certificates_cpp)
            this.cpp = zeroValue<CJ_RTCConfiguration>()
        }
    }
}

public class CreateVideoSourceParameters {
    public prop width: Float64 {get(){this.cpp.width}}
    public prop height: Float64 {get(){this.cpp.height}}
    public prop facingMode: String {get(){this.cpp.facingMode.toString()}}
    public prop isScreencast: Bool {get(){this.cpp.isScreencast}}

    var cpp: FFICreateVideoSourceParameters

    public init(width: Float64, height: Float64, facingMode: String, isScreencast: Bool) {
        unsafe {
            this.cpp = FFICreateVideoSourceParameters(width, height, LibC.mallocCString(facingMode), isScreencast)
        }
    }
    ~init(){
        unsafe {
            LibC.free(this.cpp.facingMode)
        }
    }

}
