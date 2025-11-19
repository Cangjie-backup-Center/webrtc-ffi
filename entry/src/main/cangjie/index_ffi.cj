/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */
package ohos_app_cangjie_entry

internal import ohos.base.*
internal import ohos.component.*
internal import ohos.state_manage.*
import ohos.state_macro_manage.*
import webrtc_cj.*
internal import stdx.serialization.serialization.DataModel

@Entry
@Component
class TestFFI {
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
        let webrtc4cjException: Webrtc4cjException = Webrtc4cjException("webrtc exception")
        AppLog.error("${webrtc4cjException.toString()}")
        let webrtc4cjFFIException: Webrtc4cjFFIException = Webrtc4cjFFIException("webrtcffi exception")
        AppLog.error("${webrtc4cjFFIException.toString()}")
        let cj_EnumerateDevicesInfo: CJ_EnumerateDevicesInfo = CJ_EnumerateDevicesInfo()
        let cj_ffiMediaStreamTrackJson: CJ_ffiMediaStreamTrackJson = CJ_ffiMediaStreamTrackJson()
        let cj_ReturnEnumerateDevicesInfo: CJ_ReturnEnumerateDevicesInfo = CJ_ReturnEnumerateDevicesInfo()
        let cj_ReturnArray: CJ_ReturnArray = CJ_ReturnArray()
        let cj_SupportedConstraints: CJ_SupportedConstraints = CJ_SupportedConstraints()
        try {
            CJ_RTCSessionDescription.GET("hello")
        } catch (e: Exception) {
        }
        let cj_ErrorMessage: CJ_ErrorMessage = CJ_ErrorMessage()
        let errorMessage: ErrorMessage = ErrorMessage(cj_ErrorMessage)
        let cj_TO_CPP_DisplayMediaStreamOptions: CJ_TO_CPP_DisplayMediaStreamOptions = CJ_TO_CPP_DisplayMediaStreamOptions()
        let mediaTrackConstraints: MediaTrackConstraints = MediaTrackConstraints()
        let cj_RTCIceCandidateInit: CJ_RTCIceCandidateInit = CJ_RTCIceCandidateInit()
        let cj_FFICreateSdpObserver_result: CJ_FFICreateSdpObserver_result = CJ_FFICreateSdpObserver_result()
        let rTCSessionDescription: RTCSessionDescription = RTCSessionDescription(CJ_RTCSessionDescription("hello", "rtc"))
        rTCSessionDescription.sdp
        rTCSessionDescription.RTCSdpType
    }
}
