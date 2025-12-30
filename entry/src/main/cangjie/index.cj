/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package ohos_app_cangjie_entry

internal import ohos.base.*
internal import ohos.component.*
internal import ohos.state_manage.*
internal import ohos.system_date_time.SystemDateTime
import ohos.state_macro_manage.*
import ohos.net.webSocket.*
import ohos.ability.getStageContext
import ohos.ability_access_ctrl.AbilityAccessCtrl
import std.collection.*
import std.math.*
import std.sync.*

import stdx.serialization.serialization.*
import stdx.encoding.json.*

import std.random.Random
import kit.AbilityKit.*
import ohos.concurrency.launch
import ohos.prompt_action.PromptAction
import kit.AudioKit.*
import ohos.file_fs.*
import webrtc_cj.*
import ohos.state_macro_manage_ndk.r


let Index_WebRTC_TAG: String = "[Index]"
// 用于测试的信令服务器
let SIGNAL_SERVER = "wss://youzhi.life:8443"

// 用于测试的STUN服务器地址
let STUN_SERVER = "stun:stun.l.google.com:19302"

func getContext(): AbilityContext {
    match (globalAbilityContext) {
        case Some(context) => context
        case _ => throw Exception("can not get globalAbilityContext")
    }
}


func printlnError(e: Exception): Unit {
    let arr  = e.getStackTrace()
    for (item in arr) {
        AppLog.error("${item.fileName}:: ${item.declaringClass}::${item.methodName}::${item.lineNumber}")
    }
}


class CJ_MessageData <: Serializable<CJ_MessageData> {
    public var sdp: ?RTCSessionDescription
    public var ice: ?RTCIceCandidateInit
    var hasSdp: Bool = false

    public init(sdp: ?RTCSessionDescription, ice: ?RTCIceCandidateInit ) {
        this.sdp = sdp
        this.ice = ice
        this.hasSdp = sdp.isSome()
    }

    /* 实现 Serializable 接口的序列化方法 */
    public func serialize(): DataModel {
        return DataModelStruct()
                .add(field<?RTCSessionDescription>("sdp", sdp))
                .add(field<?RTCIceCandidateInit>("ice", ice))
                .add(field<Bool>("hasSdp", hasSdp))
    }

    /* 实现反序列化方法 */
    public static func deserialize(dm: DataModel): CJ_MessageData {
        let dms = match (dm) {
            case data: DataModelStruct => data
            case _ => throw Exception("this data is not DataModelStruct")
        }
        if (Bool.deserialize(dms.get("hasSdp"))) {
            return CJ_MessageData(
                RTCSessionDescription.deserialize(dms.get("sdp")),
                Option<RTCIceCandidateInit>.None,
            )
        }else {
            return CJ_MessageData(
                Option<RTCSessionDescription>.None,
                RTCIceCandidateInit.deserialize(dms.get("ice"))
            )
        }
    }
}

@Entry
@Component
class EntryView {
    @State
    var buttonTitle: String = "Connect"
    @State
    var statusText: String = ""
    @State
    var myId: String = ""
    @State
    var peerId: String = ""
    @State
    var muteBtnTitle: String = "Mute"
    private var muted: Bool = false
    private var mXComponentController1: VideoRenderController = VideoRenderController()
    private var mXComponentController2: VideoRenderController = VideoRenderController()
    private var ws: WebSocket = createWebSocket()
    private var localAudioSource: ?AudioSource = None
    private var localAudioSource2: ?AudioSource = None
    private var localVideoSource: ?VideoSource = None
    private var localAudioTrack: ?MediaStreamTrack = None
    private var localAudioTrack2: ?MediaStreamTrack = None
    private var localVideoTrack: ?MediaStreamTrack = None
    private var remoteAudioTrack: ?MediaStreamTrack = None
    private var remoteVideoTrack: ?MediaStreamTrack = None
    @State
    var adm: ?AudioDeviceModule = Option<AudioDeviceModule>.None
    @State
    var pcf: ?PeerConnectionFactory = Option<PeerConnectionFactory>.None
    private var pc: ?RTCPeerConnection = Option<RTCPeerConnection>.None
    private var recvChannel: ?RTCDataChannel = Option<RTCDataChannel>.None
    private var sendChannel: ?RTCDataChannel = Option<RTCDataChannel>.None
    private var displayMediaStream: MediaStream = MediaStream()
    private var mediaDevices: MediaDevices = MediaDevices()
    private var onDataChannelMessageReceived: (RTCDataChannel, MessageEvent) -> Unit = {pc, event =>}
    private var localCameraVideoTrack: ?MediaStreamTrack = Option<MediaStreamTrack>.None
    private var retVideoTrack: Array<MediaStreamTrack> = Array<MediaStreamTrack>()
    
    private var connectTime: Int64 = 0
    private var xBeforeSetVideoTime: Int64 = 0
    private var xEndSetVideoTime: Int64 = 0

    func build() {
        Column() {
            Row() {
                Text("状态")
                    .fontSize(32)
                    .fontWeight(FontWeight.Normal)
                    .margin(right: 24)
                Text(this.statusText)
                    .fontSize(32)
                    .fontWeight(FontWeight.Bold)
            }.alignSelf(ItemAlign.Start)

            Row() {
                Text("本机ID")
                    .fontSize(32)
                    .fontWeight(FontWeight.Normal)
                    .margin(right: 24)
                    .align(Alignment.Start)
                Text(this.myId)
                    .fontSize(32)
                    .fontWeight(FontWeight.Bold)
            }
                .alignSelf(ItemAlign.Start)
                .padding(top: 10)

            Row() {
                TextInput(placeholder: '请输入对端ID')
                    .width(200)
                    .height(54)
                    .fontSize(28)
                    .fontWeight(FontWeight.Normal)
                    .setType(InputType.Number)
                    .layoutWeight(20)
                    .onChange({
                        value => this.peerId = value
                    })

                Button(this.buttonTitle)
                    .width(150)
                    .height(54)
                    .fontSize(20)
                    .fontWeight(FontWeight.Bold)
                    .margin(top: 20)
                    .onClick(
                        {
                            =>
                                if (this.buttonTitle == 'Disconnect') {
                                    this
                                        .ws
                                        .close({
                                            errorCode: Option<AsyncError>, data: Option<Bool> => match (errorCode) {
                                                case Some(e) => 0 // error
                                                case _ => match (data) {
                                                    case Some(value) => 1 // success
                                                    case _ => 0 // error
                                                }
                                            }
                                        })
                                    this.buttonTitle = 'Connect'
                                    return
                                }
                                if (this
                                    .peerId
                                    .size < 2 || this
                                    .peerId
                                    .size > 4) {
                                    PromptAction.showToast(message: "请输入2到4位数ID")
                                    return
                                }
                                this.sendMessage('SESSION ' + this.peerId)
                                this.buttonTitle = 'Disconnect'
                                this.connectTime = SystemDateTime.getTime(isNano: true)
                        }
                    )
                    .margin(left: 10, right: 20)

                Row() {
                    Checkbox(name: 'remote_offerer', group: 'checkboxGroup')
                        .select(false)
                        .selectedColor(0x39a2db)
                        .onChange({
                            value => AppLog.info('remote_offerer change is ${value}')
                        })
                        .margin(right: 8)
                    Text("Remote offerer")
                        .fontSize(20)
                        .fontWeight(FontWeight.Normal)
                }
                    .layoutWeight(20)
                    .visibility(Visibility.Hidden)
            }
                .alignSelf(ItemAlign.Start)
                .padding(top: 24)

            Row() {
                Button(this.muteBtnTitle)
                    .width(150)
                    .height(54)
                    .fontSize(20)
                    .fontWeight(FontWeight.Bold)
                    .margin(top: 20)
                    .onClick(
                        {
                            =>
                                AppLog.error("${Index_WebRTC_TAG} audio muted: ${this.muted}")
                                this.muted = !this.muted
                                this.muteBtnTitle = if (this.muted) {
                                    'Unmute'
                                } else {
                                    'Mute'
                                }
                             this.pc?.setAudioPlayout(!this.muted)
                             this.pc?.setAudioRecording(!this.muted)
                        }
                    )
                    .margin(left: 10, right: 20)
            }
                .alignSelf(ItemAlign.Start)
                .padding(top: 24)

            Row() {
                XComponent(
                    id: "local-video",
                    `type`: XComponentType.SURFACE,
                    controller: this.mXComponentController1
                )
                    .width(480.px)
                    .height(480.px)
                XComponent(
                    id: "remote-video",
                    `type`: XComponentType.SURFACE,
                    controller: this.mXComponentController2
                )
                    .width(480.px)
                    .height(480.px)
            }
                .alignSelf(ItemAlign.Start)
                .padding(top: 10)
        }
            .width(100.percent)
            .height(100.percent)
            .margin(left: 24, right: 24, top: 24, bottom: 24)
            .justifyContent(FlexAlign.Start)
    }

    protected override func aboutToAppear(): Unit {
        let audioManager = getAudioManager()
        let audioSessionManager = audioManager.getRoutingManager()

        let stageContext = getStageContext(getContext())
        let atManager = AbilityAccessCtrl.createAtManager()
        let permissionList = ["ohos.permission.MICROPHONE", "ohos.permission.CAMERA"]
        var resultCallback = {
            errorCode: Option<AsyncError>, data: Option<AccessCtrlPermissionRequestResult> => match (errorCode) {
                case Some(e) => AppLog.info("permissionResultCallBack request error: errcode is ${e.code}")
                case _ => match (data) {
                    case Some(value) =>
                        var granted = true
                        for (index in 0..value
                                .permissions
                                .size) {
                            AppLog.info(
                                "${Index_WebRTC_TAG} request permission [" + value.permissions[index] + "] with result: " +
                                    "${value.authResults[index]}")
                            if (value.authResults[index] != 0) {
                                granted = false
                            }
                        }
                        if (!granted) {
                            this.setError("Permission Not Granted")
                            return
                        }
                        AppLog.info("${Index_WebRTC_TAG} Connecting to server")
                        this.setStatus("Connecting to server")
                        this
                            .ws
                            .connect(SIGNAL_SERVER, {
                                errorCode: Option<AsyncError>, data: Option<Bool> => match (errorCode) {
                                    case Some(e) => 0 // error
                                    case _ => match (data) {
                                        case Some(value) => 1 // success
                                        case _ => 0 // error
                                    }
                                }
                            })
                    case _ => AppLog.info("permissionResultCallBack request error: data is null")
                }
            }
        }
        atManager.requestPermissionsFromUser(stageContext, permissionList, resultCallback)
        let openCallBack = WebSocketAsyncCallback<HashMap<UInt32, String>>({
            errorCode: Option<AsyncError>, data: Option<HashMap<UInt32, String>> => match (errorCode) {
                case Some(e) => 0 // error
                case _ => match (data) {
                    case Some(value) =>
                        AppLog.info("${Index_WebRTC_TAG} websocket open")
                        this.myId = this.getRandomId()
                        this.sendMessage("HELLO " + this.myId)
                        this.setStatus("Registering with server")
                    case _ => errorCode // error
                }
            }
        })

        let messageCallBack = WebSocketAsyncCallback<MessageData>({
            errorCode: Option<AsyncError>, data: Option<MessageData> => match (errorCode) {
                case Some(e) => 0 // error
                case _ => match (data) {
                    case Some(value) =>
                        AppLog.error("${Index_WebRTC_TAG} websocket receive message: ${value}")
                        if (value.toString() == "HELLO") {
                            this.setStatus("Registered with server, waiting for call")
                            this.createPeerConnection()
                        } else if (value.toString() == 'SESSION_OK') {
                            this.setStatus("Starting negotiation")
                            this.sendOffer()
                        } else if (value.toString() == 'OFFER_REQUEST') {
                            this.sendOffer()
                        } else {
                            if (value.toString().startsWith('ERROR')) {
                                this.handleIncomingError(value.toString())
                            } else {
                                try {
                                    match (value) {
                                        case STRING_DATA(stringdata) =>
                                            var jv = JsonValue.fromStr(stringdata)
                                            var dm = DataModel.fromJson(jv)
                                            let msgData: CJ_MessageData = CJ_MessageData.deserialize(dm)
                                            if (msgData.sdp.isSome()) {
                                                this.receiveSdp(msgData)
                                            } else if (msgData.ice.isSome()) {
                                                this.receiveIce(msgData)
                                            }
                                        case ARRAY_DATA(arraydata) =>
                                            AppLog.error('${Index_WebRTC_TAG} receive unknown message: ' + value.toString())
                                            this.handleIncomingError("Unknown incoming JSON")
                                        case _ =>
                                            AppLog.error('${Index_WebRTC_TAG} receive unknown message: ' + value.toString())
                                            this.handleIncomingError("Unknown incoming JSON")
                                    }
                                } catch (error: Exception) {
                                    printlnError(error)
                                    AppLog.error('${Index_WebRTC_TAG} receive invalid message: ' + value.toString())
                                }
                            }
                        }
                    case _ => 0 // error
                }
            }
        })

        let closeCallBack = WebSocketAsyncCallback<CloseResult>({
            errorCode: Option<AsyncError>, data: Option<CloseResult> => match (errorCode) {
                case Some(e) => 0 // error
                case _ => match (data) {
                    case Some(value) =>
                        AppLog.error("${Index_WebRTC_TAG} websocket closed")
                        this.setStatus("Disconnected from server")
                        this.pc?.close()
                        Timer.once(Duration.second, {
                            => this
                                .ws
                                .connect(SIGNAL_SERVER, {
                                    errorCode: Option<AsyncError>, data: Option<Bool> => match (errorCode) {
                                        case Some(e) => 0 // error
                                        case _ => match (data) {
                                            case Some(value) => 1 // success
                                            case _ => 0 // error
                                        }
                                    }
                                })
                        })
                    case _ => 0 // error
                }
            }
        })

        let errorCallBack = WebSocketErrorCallback(
            {
                err: BusinessException =>
                    AppLog.error("${Index_WebRTC_TAG} websocket err: ' + ${err.code}")
                    this.setError("Unable to connect to server: " + err.message)
                    Timer.once(Duration.second, {
                        => this
                            .ws
                            .connect(SIGNAL_SERVER, {
                                errorCode: Option<AsyncError>, data: Option<Bool> => match (errorCode) {
                                    case Some(e) => 0 // error
                                    case _ => match (data) {
                                        case Some(value) => 1 // success
                                        case _ => 0 // error
                                    }
                                }
                            })
                    })
            }
        )
        this.ws.on(OnOffType.OPEN, openCallBack)
        this.ws.on(OnOffType.CLOSE, closeCallBack)
        this.ws.on(OnOffType.ERROR, errorCallBack)
        this.ws.on(OnOffType.MESSAGE, messageCallBack)

        let audioDeviceModule = AudioDeviceModule(true, true)
        this.adm = audioDeviceModule
        let ret = PeerConnectionFactory(audioDeviceModule)
        this.pcf = ret
        ret.SetDefault()
        let filesDir = getContext().filesDir
        let file = FileFs.open("${filesDir}/test.txt", mode: (READ_WRITE.mode | CREATE.mode))
        this.pcf?.startAecDump(file.fd, -1)

    }

    protected override func aboutToDisappear() {
        this.pcf?.stopAecDump()
        this.ws.close({
                errorCode: Option<AsyncError>, data: Option<Bool> => match (errorCode) {
                    case Some(e) => 0 // error
                    case _ => match (data) {
                        case Some(value) => 1 // success
                        case _ => 0 // error
                    }
                }
            })
        this.ws.off(OnOffType.OPEN)
        this.ws.off(OnOffType.CLOSE)
        this.ws.off(OnOffType.ERROR)
        this.ws.off(OnOffType.MESSAGE)
    }

    public func onPageShow(): Unit {
        AppLog.info('${Index_WebRTC_TAG} onPageShow')
    }

    public func onPageHide(): Unit {
        AppLog.info('${Index_WebRTC_TAG} onPageHide')
    }

    func handleIncomingError(error: String) {
        this.setError('ERROR: ' + error)
        this.ws.close({
                errorCode: Option<AsyncError>, data: Option<Bool> => match (errorCode) {
                    case Some(e) => 0 // error
                    case _ => match (data) {
                        case Some(value) => 1 // success
                        case _ => 0 // error
                    }
                }
            })
    }

    func sendOffer(): Unit {
         try {
            let offer = this.pc.getOrThrow().createOffer()
            match (offer) {
                case Ok(v) =>
                    this.pc?.setLocalDescription(v)
                    let cjmsg = CJ_MessageData(v, Option<RTCIceCandidateInit>.None)
                    let dm = cjmsg.serialize()
                    let obj: JsonValue = dm.toJson()
                    this.sendMessage(obj.toJsonString())
                case Error(str) => AppLog.error("${Index_WebRTC_TAG} str: ${str}")
            }
         } catch (e: Exception) {
            AppLog.error('${Index_WebRTC_TAG} sendOffer: ${e}')
         }
    }

    func sendMessage(message: String) {
        this.ws.send(MessageData.STRING_DATA(message), {
            errorCode: Option<AsyncError>, data: Option<Bool> => if (let Some(e) <- errorCode) {
                AppLog.error("${Index_WebRTC_TAG} websocket send errorCode: ${e.code}")
            } else {
                if (let Some(value) <- data) {
                    AppLog.info("${Index_WebRTC_TAG} websocket send:${message}")
                    if (value) {
                        AppLog.info("${Index_WebRTC_TAG} websocket send success:${message}")
                    } else {
                        AppLog.error("${Index_WebRTC_TAG} websocket send error:${errorCode.isNone()}")
                    }
                }
            }
        })
    }

    func getRandomId(): String {
        let random = Random().nextFloat64()
        return Int64(floor(random * (9000.0 - 10.0) + 10.0)).toString()
    }

    func setStatus(text: String): Unit {
        AppLog.info("${Index_WebRTC_TAG} ${text}")
        this.statusText = text
    }

    func setError(error: String) {
        AppLog.error("${Index_WebRTC_TAG} ${error}")
        this.statusText = error
    }

    func prepareLocalMedia(): Unit {
        if (this.localAudioTrack.isNone()) {
            var ffiao: FFIAudioOptions = FFIAudioOptions()
            ffiao.noise_suppression = true
            ffiao.echo_cancellation = true
            this.localAudioSource = this.pcf.getOrThrow().createAudioSource(ffiao)
            this.localAudioTrack = this.pcf.getOrThrow().createAudioTrack("audio", this.localAudioSource.getOrThrow())
        }
        if (this.localCameraVideoTrack.isNone()) {
            this.localVideoSource = this.pcf.getOrThrow().createVideoSource(CJ_MediaTrackConstraintSet(width:1280.0, height:720.0, facingMode:"user"), false)
            this.localCameraVideoTrack = this.pcf.getOrThrow().createVideoTrack("video", this.localVideoSource.getOrThrow())
            this.mXComponentController1.setVideoTrack(this.localCameraVideoTrack.getOrThrow())
            this.mXComponentController1.setMirror(true)
            this.mXComponentController1.setScalingMode(FFIScalingModeEnum.ASPECTFIT)
        }
    }

    func prepareDisplayMedia(): Unit {
        if (this.displayMediaStream.isNone()) {
            this.displayMediaStream = mediaDevices.getDisplayMedia(CJ_MediaTrackConstraintSet(width: 720.0, height: 1280.0, ohosScreenCaptureAudioFilter: "current-app"), true, true)
            this.retVideoTrack = this.displayMediaStream.getVideoTracks()
            this.localVideoTrack = this.retVideoTrack[0]
            this.mXComponentController1.setVideoTrack(this.retVideoTrack[0])
            this.mXComponentController1.setScalingMode(FFIScalingModeEnum.ASPECTFIT)

            let audioTracks = this.displayMediaStream.getAudioTracks()
            if (audioTracks.size > 0) {
                 this.localAudioTrack = audioTracks[0]
                 AppLog.error('${Index_WebRTC_TAG} audioTrack: ${this.localAudioTrack.getOrThrow().getID()}')
            }
            if (audioTracks.size > 1) {
                 this.localAudioTrack2 = audioTracks[1]
                 AppLog.error('${Index_WebRTC_TAG} audioTrack2: ${this.localAudioTrack.getOrThrow().getID()}')
            }
        }
    }


    func createPeerConnection(): Future<Unit> {
        spawn {
            // prepareLocalMedia().get()
            prepareDisplayMedia()
            this.pc = this.pcf?.createPeerConnection(RTCConfiguration(iceServers: [RTCIceServer(urls: [STUN_SERVER])]))
            if (this.pc.isNone()) {
                AppLog.error('${Index_WebRTC_TAG} failed to create RTCPeerConnection')
                return
            }
            this.pc?.onTrack = {
                pc, event =>
                  AppLog.info('${Index_WebRTC_TAG} ontrack: ${event.track.kind}')
                    if (event.track.kind == 'video') {
                        this.remoteVideoTrack = event.track
                        xBeforeSetVideoTime = SystemDateTime.getTime(isNano: true)
                        this.mXComponentController2.setVideoTrack(event.track)
                        xEndSetVideoTime = SystemDateTime.getTime(isNano: true)
                        AppLog.info("XComponent total cost: ${(this.xEndSetVideoTime - this.xBeforeSetVideoTime)}ns")
                        AppLog.info("total cost: ${(this.xEndSetVideoTime - this.connectTime)}ns")
                    } else if (event.track.kind == 'audio') {
                        this.remoteAudioTrack = event.track
                    }
                }
        this.pc?.onSignalingChange = {
            pc, event => AppLog.info('${Index_WebRTC_TAG} onsignalingstatechange: ${this.pc?.signalingState}')
        }
        this.pc?.onconnectionstatechange = { pc, event =>
                      AppLog.info('${Index_WebRTC_TAG} onconnectionstatechange: ${this.pc?.connectionState}')
            if (this.pc?.connectionState.toString() == 'FAILED') {
                this.setError("Peer connection failed")
                this.ws.close({
                        errorCode: Option<AsyncError>, data: Option<Bool> => match (errorCode) {
                            case Some(e) => 0 // error
                            case _ => match (data) {
                                case Some(value) => 1 // success
                                case _ => 0 // error
                            }
                        }
                    })
            }
        }
        this.pc?.onnegotiationneeded = { pc, event =>
//              AppLog.info('${Index_WebRTC_TAG} onnegotiationneeded: this= ${this.pc}')
//              AppLog.info('${Index_WebRTC_TAG} onnegotiationneeded: event= ${event}')
        }
        this.pc?.onIceCandidate = { pc, event =>
//              AppLog.info('${Index_WebRTC_TAG} onicecandidate: this=')
//              AppLog.info('${Index_WebRTC_TAG} onicecandidate: event=${event}')
          if (let Some(v) <- event.candidate) {
            let dm = CJ_MessageData(Option<RTCSessionDescription>.None, v.toRTCIceCandidateInit()).serialize()
            let obj: JsonValue = dm.toJson()
            this.sendMessage(obj.toJsonString())
          }
        }
        this.pc?.onIceCandidateError = { pc, event =>
//              AppLog.error('${Index_WebRTC_TAG} onicecandidateerror: event= ${event}')
        }
        this.pc?.oniceconnectionstatechange = { pc, event =>
          AppLog.info('${Index_WebRTC_TAG} oniceconnect/ionstatechange: ${this.pc?.iceConnectionState}')
          if (this.pc?.iceConnectionState.toString() == 'FAILED') {
            this.setError("Ice connection failed")
            this.ws.close(
                {
                    errorCode: Option<AsyncError>, data: Option<Bool> => match (errorCode) {
                        case Some(e) => 0 // error
                        case _ => match (data) {
                            case Some(value) => 1 // success
                            case _ => 0 // error
                        }
                    }
            })
          }
        }
        this.pc?.onicegatheringstatechange = { pc, event =>
          AppLog.info('${Index_WebRTC_TAG} onicegatheringstatechange: ${this.pc?.iceGatheringState}')
          match (this.pc.getOrThrow().iceGatheringState) {
            case FFIRTCIceGatheringState.NEW =>
              AppLog.info('${Index_WebRTC_TAG} onicegatheringstatechange: gathering is either just starting or has been reset')
            case FFIRTCIceGatheringState.GATHERING =>
              AppLog.info('${Index_WebRTC_TAG} onicegatheringstatechange: gathering has begun or is ongoing')
            case FFIRTCIceGatheringState.COMPLETE =>
              AppLog.info('${Index_WebRTC_TAG} onicegatheringstatechange: gathering has ended')
            case _ => ()
          }
        }
        this.pc?.ondatachannel = {
            pc, event =>
                AppLog.info('${Index_WebRTC_TAG} ondatachannel: this=')
                // AppLog.info('${Index_WebRTC_TAG} ondatachannel: event= ${event}')
                this.setStatus("Data channel created")
                this.recvChannel = event
                this.recvChannel?.onopen = this.onDataChannelOpen
                this.recvChannel?.onmessage = {pc, event => this.setStatus("Received data channel message")}
                this.recvChannel?.onerror = this.onDataChannelError
                this.recvChannel?.onclose = this.onDataChannelClose
        }
        if (let Some(v) <- this.localAudioTrack) {
             let rtpSender1 = this.pc?.addTrack(v)
             AppLog.info('${Index_WebRTC_TAG} rtpSender1: ${rtpSender1}')
        }
        if (let Some(v) <- this.localAudioTrack2) {
             let rtpSender2 = this.pc?.addTrack(v)
             AppLog.info('${Index_WebRTC_TAG} rtpSender2: ${rtpSender2}')
        }
        if (let Some(v) <- this.localVideoTrack) {
             let rtpSender3 = this.pc?.addTrack(v)
             AppLog.info('${Index_WebRTC_TAG} rtpSender3: ${rtpSender3}')
        }
        if (let Some(v) <- this.localCameraVideoTrack) {
             let rtpSender4 = this.pc?.addTrack(v)
             AppLog.info('${Index_WebRTC_TAG} rtpSender3: ${rtpSender4}')
        }

//         AppLog.info('${Index_WebRTC_TAG} transceivers: ${this.pc?.getTransceivers()}')
        this.sendChannel = this.pc?.createDataChannel("send")
//         AppLog.info('${Index_WebRTC_TAG} sendChannel: ${this.sendChannel}')
        this.sendChannel?.onopen = {
            pc, event =>
                // this is Index
                AppLog.info('${Index_WebRTC_TAG} =dataChannel.OnOpen: this=')
                // AppLog.info("${Index_WebRTC_TAG} =dataChannel.OnOpen: ${event}")
                this.sendChannel?.send("Hi! (from ArkTS)")
                let data1 = Array<UInt8>(20, repeat: 0)
                this.sendChannel?.send(data1)
                let data2 = Array<UInt8>(20, repeat: 1)
                this.sendChannel?.send(data2)
                let data3 = Array<UInt8>(20, repeat: 2)
                this.sendChannel?.send(data3)
        }
        this.sendChannel?.onmessage = {pc, event => this.setStatus("Received data channel message")}
        this.sendChannel?.onerror = this.onDataChannelError
        this.sendChannel?.onclose = this.onDataChannelClose
        }
    }

    func onDataChannelOpen(pc: RTCDataChannel, event: Event): Unit {
        // this is webrtc.RTCDataChannel
        // AppLog.info("${Index_WebRTC_TAG} dataChannel.OnOpen: ${event}")
        pc.send("Hi! (from ArkTS)")
    }

    func onDataChannelError(pc: RTCDataChannel, event: Event): Unit {
        // this is webrtc.RTCDataChannel
        AppLog.info("${Index_WebRTC_TAG} dataChannel.OnError")
    }

    func onDataChannelClose(pc: RTCDataChannel, event: Event): Unit {
        // this is webrtc.RTCDataChannel
        AppLog.info("${Index_WebRTC_TAG} dataChannel.OnClose")
    }

    func sendAnswer(): Unit {
        spawn {
            this.setStatus("Got SDP offer, creating answer")
            try {
                let desc = this.pc.getOrThrow().createAnswer()
                match (desc) {
                    case Ok(v) =>
                        this.pc?.setLocalDescription(v)
                        let cjmsg = CJ_MessageData(v, Option<RTCIceCandidateInit>.None)
                        let dm = cjmsg.serialize()
                        let obj: JsonValue = dm.toJson()
                        this.setStatus("Sending SDP answer")
                        this.sendMessage(obj.toJsonString())
                    case Error(str) => AppLog.error("${Index_WebRTC_TAG} str: ${str}")
                }
            } catch (e: Exception) {
            	AppLog.error('${Index_WebRTC_TAG} createAnswer: ${e}')
            }
        }
    }


    func receiveSdp(cjmsg: CJ_MessageData): Unit {
            // CJ_RTCSessionDescription.GET()
            var sdp = cjmsg.sdp.getOrThrow()
             if (sdp.RTCSdpType == "offer") {
                    AppLog.info("receive offer")
                    this.pc?.setRemoteDescription(sdp, {event =>
                        if (event.errorDetail != FFIRTCErrorDetailType.NONE) {
                            AppLog.info("Set remote description error: ${event.msg}")
                            this.setError("Set remote description error: ${event.msg}")
                        } else {
                            this.setStatus("Remote SDP set")
                            this.sendAnswer()
                        }
                    })
             } else if (sdp.RTCSdpType == "answer") {
                    AppLog.info("receive answer")
                    this.pc?.setRemoteDescription(sdp, {event =>
                        if (event.errorDetail != FFIRTCErrorDetailType.NONE) {
                            AppLog.info("Set remote description error: ${event.msg}")
                            this.setError("Set remote description error: ${event.msg}")
                        } else{
                            this.setStatus("Remote SDP set");
                        }
                    })
             }
    }

    func receiveIce(cjmsg: CJ_MessageData): Unit {
            AppLog.error('${Index_WebRTC_TAG} receive icecandidate')
            var ice = cjmsg.ice.getOrThrow()
            this.pc?.addIceCandidate(ice)
    }
}
