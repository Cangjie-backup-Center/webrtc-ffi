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
class TestEvent {
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
        let rTCErrorEvent: RTCErrorEvent = RTCErrorEvent("typ", FFIRTCErrorDetailType.DATA_CHANNEL_FAILURE, 1, 2, 3, 4)
        let audioErrorEvent: AudioErrorEvent = AudioErrorEvent("", FFIAudioErrorType.GENERAL)
        let audioStateChangeEvent: AudioStateChangeEvent = AudioStateChangeEvent("", FFIAudioState.START)
        let audioCapturerSamplesReadyEvent: AudioCapturerSamplesReadyEvent =AudioCapturerSamplesReadyEvent("", 1, 2, 3)
        let cj_RTCDataChannelEvent: CJ_RTCDataChannelEvent = CJ_RTCDataChannelEvent()
        let cj_Event: CJ_Event = CJ_Event()
        let cj_RTCPeerConnectionIceEvent: CJ_RTCPeerConnectionIceEvent = CJ_RTCPeerConnectionIceEvent()
        let onIceCandidateEvent: OnIceCandidateEvent = OnIceCandidateEvent("")
        let cj_MediaStreamTrack: CJ_MediaStreamTrack = CJ_MediaStreamTrack()
        let cj_RTCTrackEvent: CJ_RTCTrackEvent = CJ_RTCTrackEvent()
        let cj_RTCPeerConnectionIceErrorEvent: CJ_RTCPeerConnectionIceErrorEvent = CJ_RTCPeerConnectionIceErrorEvent()
        let rTCPeerConnectionIceErrorEvent: RTCPeerConnectionIceErrorEvent = RTCPeerConnectionIceErrorEvent("typ", "add", 1, "uri", 200, "str")
        let cj_MessageEvent: CJ_MessageEvent = CJ_MessageEvent()
        let messageEvent: MessageEvent = MessageEvent("", MessageEventData.STRING("str"))
        let messageEvent2: MessageEvent = MessageEvent("", MessageEventData.ARRAY_BUFFER([0]))
        let cj_AudioSamples: CJ_AudioSamples = CJ_AudioSamples()
        let rTCIceCandidate: RTCIceCandidate = RTCIceCandidate("can", "mid", 1, "foun", 1, 0, "add", "ice", 5, 6, "type", "related", 7, "frag")
        let dm: DataModel = rTCIceCandidate.serialize()
        RTCIceCandidate.deserialize(dm)
        let cj_RTCIceCandidate: CJ_RTCIceCandidate = CJ_RTCIceCandidate()
    }
}
