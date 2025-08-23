/*
 * @Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package ohos_app_cangjie_entry

internal import ohos.base.*
internal import ohos.component.*
internal import ohos.state_manage.*
import ohos.state_macro_manage.*
import ohos.net.webSocket.*
import ohos.ability.getStageContext
import ohos.ability_access_ctrl.AbilityAccessCtrl
import std.collection.*
import std.math.*
import std.sync.*
import std.random.Random
import kit.AbilityKit.*
import ohos.concurrency.launch
import ohos.prompt_action.PromptAction
import kit.AudioKit.*
import ohos.file_fs.*
import webrtc_cj.*

let Index_WebRTC_TAG: String = "[Index]"
// 用于测试的信令服务器
let SIGNAL_SERVER = "wss://youzhi.life:8443"
// 用于测试的Web客户端地址
// https://webrtc.youzhi.life/
// 用于测试的STUN服务器地址
let STUN_SERVER = "stun:stun.l.google.com:19302"

func getContext(): AbilityContext {
    match (globalAbilityContext) {
        case Some(context) => context
        case _ => throw Exception("can not get globalAbilityContext")
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
    private var pc: ?RTCPeerConnection = None
    private var recvChannel: ?RTCDataChannel = None
    private var sendChannel: ?RTCDataChannel = None
    private var displayMediaStream: MediaStream = MediaStream(-1)
    private var mediaDevices: MediaDevices = MediaDevices()
    private var onDataChannelMessageReceived: (RTCDataChannel, MessageEvent) -> Unit = {pc, event =>}
    private var localCameraVideoTrack: ?VideoTrack = None
    private var retVideoTrack: Array<MediaStreamTrack> = Array<MediaStreamTrack>()

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
        // 设置音频策略，允许和其它音频流并发
        // let strategy: AudioSessionStrategy = AudioSessionStrategy(concurrencyMode: AudioConcurrencyMode.CONCURRENCY_MIX_WITH_OTHERS)
        let audioManager = getAudioManager()
        // TODO.. 这里仓颉 api 是音频会话管理器， arkts 描述是音频路由管理器，arkts 调用的是 getSessionManager()
        let audioSessionManager = audioManager.getRoutingManager()
        // audioSessionManager.activateAudioSession(strategy) TODO.. 这里仓颉 api 未提供此方法了

        // Logging.enableLogThreads()
        // Logging.enableLogTimeStamps()
        // Logging.enableLogToDebugOutput(LoggingSeverity.VERBOSE)
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
                        if (value.toString() == "HELLO".toAsciiLower()) {
                            this.setStatus("Registered with server, waiting for call")
                            this.createPeerConnection()
                        } else if (value.toString() == 'SESSION_OK') {
                            this.setStatus("Starting negotiation")
                            this.sendOffer()
                        } else if (value.toString() == 'OFFER_REQUEST') {
                            this.sendOffer()
                        } else {
                            if (value
                                .toString()
                                .startsWith('ERROR')) {
                                this.handleIncomingError(value.toString())
                            } else {
                                try {
                                    let msgData: String = value.toString()
                                    if (msgData.contains("sdp")) {
                                        this.receiveSdp(msgData)
                                    } else if (msgData.contains("ice")) {
                                        this.receiveIce(msgData)
                                    } else {
                                        AppLog.error('${Index_WebRTC_TAG} receive unknown message: ' + value.toString())
                                        this.handleIncomingError("Unknown incoming JSON")
                                    }
                                } catch (error: Exception) {
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
        spawn {
            let syncCounter: SyncCounter = SyncCounter(1)
            this.createAudioDeviceModule({
                value => launch {
                    this.adm = value
                    syncCounter.dec()
                }
            })
            syncCounter.waitUntilZero()
            this.createPeerConnectionFactory({
                value => launch {
                    this.pcf = value
                }
            })
        }
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

    func onPageShow(): Unit {
        AppLog.info('${Index_WebRTC_TAG} onPageShow')
    }

    func onPageHide(): Unit {
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

    func sendOffer(): Future<Unit> {
        spawn {
            // TODO.. 昕宇 createOffer setLocalDescription
             try {
                let offer = this.pc?.createOffer()
                if (let Some(v) <- offer) {
//                	v.sdp
                }
            // AppLog.error("${Index_WebRTC_TAG} createOffer: ${offer}")
            // this.pc?.setLocalDescription(offer)
            // this.sendMessage(offer)
             } catch (e: Exception) {
                AppLog.error('${Index_WebRTC_TAG} sendOffer: ${e}')
             }
        }
    }

    func sendMessage(message: String): Future<Unit> {
        spawn {
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
    }

    func getRandomId(): String {
        let random = Random().nextFloat64()
        return floor(random * (9000.0 - 10.0) + 10.0).toString()
    }

    func setStatus(text: String): Unit {
        AppLog.info("${Index_WebRTC_TAG} ${text}")
        this.statusText = text
    }

    func setError(error: String) {
        AppLog.error("${Index_WebRTC_TAG} ${error}")
        this.statusText = error
    }

    func createAudioDeviceModule(callback: (admID: AudioDeviceModule) -> Unit): Future<Unit> {
        spawn {
            callback(AudioDeviceModule(true, true))
            // TODO.. 暂不放开，不需要打印
//                        this.adm.oncapturererror = (event) => {
//                          AppLog.error('oncapturererror: ${event}')
//                        }
            //            this.adm.oncapturerstatechange = (event) => {
            //              AppLog.info('oncapturerstatechange: ${event}')
            //            }
            //            this.adm.oncapturersamplesready = (event) => {
            //              AppLog.debug('oncapturersamplesready: ${event}')
            //            }
            //            this.adm.onrenderererror = (event) => {
            //              AppLog.error('onrenderererror: ${event}')
            //            }
            //            this.adm.onrendererstatechange = (event) => {
            //              AppLog.info('onrendererstatechange: ${event}')
            //            }
            //            Logging.d('this.adm: ${this.adm}')
        }
    }

    func createPeerConnectionFactory(callback: (pcf: PeerConnectionFactory) -> Unit): Future<Unit> {
        spawn {
            let ret: PeerConnectionFactory = PeerConnectionFactory(this.adm.getOrThrow())
            callback(ret)
            ret.SetDefault()
            let filesDir = getContext().filesDir
            let file = FileFs.open("${filesDir}/test.txt", mode: (READ_WRITE.mode | CREATE.mode))
            this.pcf?.startAecDump(file.fd, -1)
        }
    }

    func prepareLocalMedia(): Future<Unit> {
        spawn {
            if (this.localAudioTrack?.getID() == 0) {
                var ffiao: FFIAudioOptions = FFIAudioOptions()
                ffiao.noise_suppression = true
                ffiao.echo_cancellation = true
                this.localAudioSource = AudioSource(this.pcf.getOrThrow(), ffiao)
                this.localAudioTrack = AudioTrack(this.pcf.getOrThrow(), "audio")
            }
            if (this.localCameraVideoTrack?.getID() == 0) {
                let ffiCVSP: CreateVideoSourceParameters = CreateVideoSourceParameters(1280.0, 720.0, "user", false)
                this.localVideoSource = VideoSource(this.pcf.getOrThrow(), ffiCVSP)
                this.localCameraVideoTrack = VideoTrack(this.pcf.getOrThrow(), "video")
                this.mXComponentController1.newNativeVideoRenderer()
                this.mXComponentController1.setVideoTrack(this.localCameraVideoTrack.getOrThrow())
                this.mXComponentController1.setMirror(true)
                this.mXComponentController1.setScalingMode(ScalingMode().aspectFit)
            }
        }
    }

    func prepareDisplayMedia(): Unit {
        if (this.displayMediaStream.getID() == 0) {
            var captureVideo: CJ_TO_CPP_DisplayMediaStreamOptions = CJ_TO_CPP_DisplayMediaStreamOptions(CJ_MediaTrackConstraintSet(width: 720.0, height: 1280.0, ohosScreenCaptureAudioFilter: "current-app"))
            var captureAudio: CJ_TO_CPP_DisplayMediaStreamOptions = CJ_TO_CPP_DisplayMediaStreamOptions(true)
            var captureohosSystemAudio: CJ_TO_CPP_DisplayMediaStreamOptions = CJ_TO_CPP_DisplayMediaStreamOptions(true)
            let that = this

            mediaDevices.getDisplayMedia(captureVideo, captureAudio, captureohosSystemAudio,
                {
                    displayMediaStream =>
                        that.displayMediaStream = displayMediaStream
                        that.retVideoTrack = that.displayMediaStream.getVideoTracks()
                        that.mXComponentController1.newNativeVideoRenderer()
                        that.mXComponentController1.setVideoTrack(that.retVideoTrack[0])
                        that.mXComponentController1.setScalingMode(ScalingMode().aspectFit)
                }
            )

            let audioTracks = this.displayMediaStream.getAudioTracks()
            if (audioTracks.size > 0) {
                // TODO.. 考虑暂不加
                // this.localAudioTrack = audioTracks[0]
                // AppLog.error('${Index_WebRTC_TAG} audioTrack: ${this.localAudioTrack}')
            }
            if (audioTracks.size > 1) {
                // this.localAudioTrack2 = audioTracks[1]
                // AppLog.error('${Index_WebRTC_TAG} audioTrack2: ${this.localAudioTrack}')
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
                    // TODO.. 需要实现 ToString 接口
                    //              AppLog.info('${Index_WebRTC_TAG} ontrack: ${event}')
                    //              // TODO.. kind 需实现
                    // if (event.track.kind == 'video') {
                    this.remoteVideoTrack = event.track
                    this.mXComponentController2.setVideoTrack(event.track)
                    //              // TODO.. kind 需实现
                    //              } else if (event.track.kind == 'audio') {
                    this.remoteAudioTrack = event.track
            }
        }
        this.pc?.onSignalingChange = {
            pc, event => AppLog.info('${Index_WebRTC_TAG} onsignalingstatechange: ${this.pc?.signalingState}')
        }
        this.pc?.onconnectionstatechange = { pc, event =>
                      AppLog.info('${Index_WebRTC_TAG} onconnectionstatechange: ${this.pc?.connectionState}')
            if (this.pc?.connectionState.toString() == 'failed') {
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
//                      AppLog.info('${Index_WebRTC_TAG} onnegotiationneeded: this= ${this.pc}')
//                      AppLog.info('${Index_WebRTC_TAG} onnegotiationneeded: event= ${event}')
                    }
        // TODO.. onIceCandidate 需实现， candidate 需实现
                    this.pc?.onIceCandidate = { pc, event =>
        //              AppLog.info('${Index_WebRTC_TAG} onicecandidate: this=')
        //              AppLog.info('${Index_WebRTC_TAG} onicecandidate: event=${event}')
//                      if (event.candidate) {
//                        this.sendMessage(event.candidate)
//                      }
                    }
        // TODO.. onIceCandidateError 需实现，ToString 接口需实现
                    this.pc?.onIceCandidateError = { pc, event =>
        //              AppLog.error('${Index_WebRTC_TAG} onicecandidateerror: event= ${event}')
                    }
        // TODO.. oniceconnectionstatechange 需实现， iceConnectionState 需实现
                    this.pc?.oniceconnectionstatechange = { pc, event =>
                      AppLog.info('${Index_WebRTC_TAG} oniceconnect/ionstatechange: ${this.pc?.iceConnectionState}')
                      if (this.pc?.iceConnectionState.toString() == 'failed') {
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
        // TODO.. onicegatheringstatechange 需实现， iceGatheringState 需实现
                    this.pc?.onicegatheringstatechange = { pc, event =>
                      AppLog.info('${Index_WebRTC_TAG} onicegatheringstatechange: ${this.pc?.iceGatheringState}')
        //              match (this.pc?.iceGatheringState) {
        //                case "new" =>
        //                  AppLog.info('${Index_WebRTC_TAG} onicegatheringstatechange: gathering is either just starting or has been reset')
        //                case "gathering" =>
        //                  AppLog.info('${Index_WebRTC_TAG} onicegatheringstatechange: gathering has begun or is ongoing')
        //                case "complete" =>
        //                  AppLog.info('${Index_WebRTC_TAG} onicegatheringstatechange: gathering has ended')
        //                case _ => ()
        //              }
                    }
        this.pc?.ondatachannel = {
            pc, event =>
                AppLog.info('${Index_WebRTC_TAG} ondatachannel: this=')
                // AppLog.info('${Index_WebRTC_TAG} ondatachannel: event= ${event}')
                this.setStatus("Data channel created")
                this.recvChannel = event
                this.recvChannel?.onopen = this.onDataChannelOpen
                this.recvChannel?.onmessage = this.onDataChannelMessageReceived
                this.recvChannel?.onerror = this.onDataChannelError
                this.recvChannel?.onclose = this.onDataChannelClose
        }
        if (let Some(v) <- this.localAudioTrack) {
            // TODO.. 昕宇 addTrack
            // let rtpSender1 = this.pc?.addTrack(v)
            // AppLog.info('${Index_WebRTC_TAG} rtpSender1: ${rtpSender1}')
        }
        if (let Some(v) <- this.localAudioTrack2) {
            // TODO.. 昕宇 addTrack
            // let rtpSender2 = this.pc?.addTrack(v)
            // AppLog.info('${Index_WebRTC_TAG} rtpSender2: ${rtpSender2}')
        }
        if (let Some(v) <- this.localVideoTrack) {
            // TODO.. 昕宇 addTrack
//             let rtpSender3 = this.pc.addTrack(v)
            // AppLog.info('${Index_WebRTC_TAG} rtpSender3: ${rtpSender3}')
        }
        // TODO.. 昕宇
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
        this.sendChannel?.onmessage = this.onDataChannelMessageReceived
//        // TODO.. onerror 实现
        this.sendChannel?.onerror = this.onDataChannelError
        this.sendChannel?.onclose = this.onDataChannelClose
        // }
    }

    func onDataChannelOpen(pc: RTCDataChannel, event: Event): Unit {
        // this is webrtc.RTCDataChannel
        // AppLog.info("${Index_WebRTC_TAG} dataChannel.OnOpen: ${event}")
        pc.send("Hi! (from ArkTS)")
    }

    func onDataChannelError(pc: RTCDataChannel, event: Event): Unit {
        // this is webrtc.RTCDataChannel
        // TODO.. event 实现 ToString
        // AppLog.info("${Index_WebRTC_TAG} dataChannel.OnError: ${event}")
    }

    func onDataChannelClose(pc: RTCDataChannel, event: Event): Unit {
        // this is webrtc.RTCDataChannel
        AppLog.info("${Index_WebRTC_TAG} dataChannel.OnClose:")
        // TODO.. event 实现 ToString
        // AppLog.info("${Index_WebRTC_TAG} dataChannel.OnClose ${event}")
    }

    func sendAnswer(): Future<Unit> {
        spawn {
            // TODO.. 昕宇 createAnswer
            this.setStatus("Got SDP offer, creating answer")
            //        this.pc?.createAnswer().then({ desc =>
            //          AppLog.error('${Index_WebRTC_TAG} Success to create answer: ${desc}')
            //          this.pc?.setLocalDescription(desc).then({ =>
            //            this.setStatus("Sending SDP answer")
            //            this.sendMessage(JSON.stringify(this.pc?.localDescription))
            //          })
            //        }).catch((e: Error) => {
            //          AppLog.error('${Index_WebRTC_TAG} Failed to create answer: ' + e.message)
            //          this.setError(e.message)
            //        })
        }
    }

    func receiveSdp(sdp: String): Future<Unit> {
        spawn {
            CJ_RTCSessionDescription.GET(sdp)
        }
    }

    func receiveIce(ice: String): Future<Unit> {
        spawn {
            AppLog.error('${Index_WebRTC_TAG} receive icecandidate')
            // TODO.. 昕宇 addIceCandidate
            //        this.pc?.addIceCandidate(ice).catch((e: Error) => {
            //          AppLog.error("${Index_WebRTC_TAG} add ice candidate error: " + e)
            //          this.setError(e.message)
            //        })
        }
    }
}
