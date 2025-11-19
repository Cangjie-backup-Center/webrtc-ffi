/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */
package ohos_app_cangjie_entry

internal import ohos.base.*
internal import ohos.component.*
internal import ohos.state_manage.*
import ohos.state_macro_manage.*
import webrtc_cj.*

@Entry
@Component
class TestFuncAndClass {
    @State
    var flag: Bool = false
    @State
    var res: String = ""

    func build() {
        Column() {
            Text(if (flag) { res } else { "不及预期的值" }).fontSize(20)
        }
    }
    protected override func aboutToAppear(): Unit {
        let fFICreateVideoSourceParameters: FFICreateVideoSourceParameters = FFICreateVideoSourceParameters(0.0, 1.0, unsafe { LibC.mallocCString("") }, false)
        let fFIAudioOptions: FFIAudioOptions = FFIAudioOptions()
        let rTCIceServer: RTCIceServer = RTCIceServer()
        AppLog.error("rTCIceServer.urls ---- ${rTCIceServer.urls}")
        AppLog.error("rTCIceServer.username ---- ${rTCIceServer.username}")
        AppLog.error("rTCIceServer.credential ---- ${rTCIceServer.credential}")
        let rTCRtpHeaderExtensionParameters: RTCRtpHeaderExtensionParameters = RTCRtpHeaderExtensionParameters(22, "", true)
        AppLog.error("rTCRtpHeaderExtensionParameters.id ---- ${rTCRtpHeaderExtensionParameters.id}")
        AppLog.error("rTCRtpHeaderExtensionParameters.uri ---- ${rTCRtpHeaderExtensionParameters.uri}")
        AppLog.error("rTCRtpHeaderExtensionParameters.encrypted ---- ${rTCRtpHeaderExtensionParameters.encrypted}")
        let rTCRtcpParameters: RTCRtcpParameters = RTCRtcpParameters("tcpParam", true)
        AppLog.error("rTCRtcpParameters.cname ---- ${rTCRtcpParameters.cname}")
        AppLog.error("rTCRtcpParameters.reducedSize ---- ${rTCRtcpParameters.reducedSize}")
        let rTCRtpCodecParameters: RTCRtpCodecParameters = RTCRtpCodecParameters(0, 1, "t", "sdp", 2)
        AppLog.error("rTCRtpCodecParameters.payloadType ---- ${rTCRtpCodecParameters.payloadType}")
        AppLog.error("rTCRtpCodecParameters.clockRate ---- ${rTCRtpCodecParameters.clockRate}")
        AppLog.error("rTCRtpCodecParameters.channels ---- ${rTCRtpCodecParameters.channels}")
        AppLog.error("rTCRtpCodecParameters.sdpFmtpLine ---- ${rTCRtpCodecParameters.sdpFmtpLine}")
        AppLog.error("rTCRtpCodecParameters.mimeType ---- ${rTCRtpCodecParameters.mimeType}")
        let rTCRtpEncodingParameters: RTCRtpEncodingParameters = RTCRtpEncodingParameters("11", false, 0, 1, 2)
        AppLog.error("rTCRtpEncodingParameters.rid ---- ${rTCRtpEncodingParameters.rid}")
        AppLog.error("rTCRtpEncodingParameters.active ---- ${rTCRtpEncodingParameters.active}")
        AppLog.error("rTCRtpEncodingParameters.maxBitrate ---- ${rTCRtpEncodingParameters.maxBitrate}")
        AppLog.error("rTCRtpEncodingParameters.maxFramerate ---- ${rTCRtpEncodingParameters.maxFramerate}")
        AppLog.error("rTCRtpEncodingParameters.scaleResolutionDownBy ---- ${rTCRtpEncodingParameters.scaleResolutionDownBy}")
        let rTCRtpSendParameters: RTCRtpSendParameters = RTCRtpSendParameters([rTCRtpCodecParameters], [rTCRtpHeaderExtensionParameters], rTCRtcpParameters, [rTCRtpEncodingParameters], "trans")
        rTCRtpSendParameters.codecs
        rTCRtpSendParameters.headerExtensions
        rTCRtpSendParameters.rtcp
        rTCRtpSendParameters.encodings
        rTCRtpSendParameters.transactionId
        let rTCDtlsFingerprint: RTCDtlsFingerprint = RTCDtlsFingerprint("alg", "v")
        AppLog.error("rTCDtlsFingerprint.algorithm ---- ${rTCDtlsFingerprint.algorithm}")
        AppLog.error("rTCDtlsFingerprint.value ---- ${rTCDtlsFingerprint.value}")
        let rTCCertificate: RTCCertificate = RTCCertificate(2, [rTCDtlsFingerprint])
        rTCCertificate.credential
        rTCCertificate.expires
        let createVideoSourceParameters: CreateVideoSourceParameters = CreateVideoSourceParameters(0.0, 1.0, "mode", false)
        AppLog.error("createVideoSourceParameters.width ---- ${createVideoSourceParameters.width}")
        AppLog.error("createVideoSourceParameters.height ---- ${createVideoSourceParameters.height}")
        AppLog.error("createVideoSourceParameters.facingMode ---- ${createVideoSourceParameters.facingMode}")
        AppLog.error("createVideoSourceParameters.isScreencast ---- ${createVideoSourceParameters.isScreencast}")
    }
}
