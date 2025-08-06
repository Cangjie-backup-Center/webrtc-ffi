/*
 * @Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package ohos_app_cangjie_entry

internal import ohos.base.*
internal import ohos.component.*
internal import ohos.state_manage.*
import ohos.state_macro_manage.*
import webrtc_cj.*
import ohos.net.webSocket.*
import ohos.ability.getStageContext
import ohos.ability_access_ctrl.AbilityAccessCtrl
import std.collection.*
import std.math.*
import std.sync.*
import std.random.Random
import kit.AbilityKit.*
import ohos.concurrency.launch

let Index_WebRTC_TAG: String = "[Index]"
// 用于测试的信令服务器
let SIGNAL_SERVER = "wss://youzhi.life:8443"
// 用于测试的Web客户端地址
// https://webrtc.youzhi.life/
// 用于测试的STUN服务器地址
let STUN_SERVER = "stun:stun.l.google.com:19302"

func getContext():AbilityContext {
    match (globalAbilityContext) {
        case Some(context) => context
        case _ => throw
        Exception("can not get globalAbilityContext")
    }
}

@Entry
@Component
class EntryView {
    @State var buttonTitle: String = "Connect"
    @State var statusText: String = ""
    @State var myId: String = ""
    @State var peerId: String = ""
    @State var muteBtnTitle: String = "Mute"
    private var muted: Bool = false
    private var mXComponentController1: VideoRenderController = VideoRenderController()
    private var mXComponentController2: VideoRenderController = VideoRenderController()
    private var ws: WebSocket = createWebSocket()
    private var localAudioSource: AudioSource = AudioSource()
    private var localVideoSource: VideoSource = VideoSource()
    private var localAudioTrack: AudioTrack = AudioTrack()
    private var localVideoTrack: VideoTrack = VideoTrack()
    @State var adm: AudioDeviceModule = AudioDeviceModule()
    @State var pcf: PeerConnectionFactory = PeerConnectionFactory()

    func build() {
        Column() {
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
        let stageContext = getStageContext(getContext())
        let atManager = AbilityAccessCtrl.createAtManager()
        let permissionList = ["ohos.permission.MICROPHONE", "ohos.permission.CAMERA"]
        var resultCallback = {
            errorCode: Option<AsyncError>, data: Option<AccessCtrlPermissionRequestResult> => match (errorCode) {
                case Some(e) =>
                    AppLog.info("permissionResultCallBack request error: errcode is ${e.code}")
                case _ => match(data) {
                    case Some(value) =>
                        var granted = true
                        for (index in 0..value.permissions.size) {
                            AppLog.info("${Index_WebRTC_TAG} request permission [" + value.permissions[index] + "] with result: " +
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
                        this.ws.connect(SIGNAL_SERVER, {
                            errorCode: Option<AsyncError>, data: Option<Bool> => match(errorCode) {
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
        let openCallBack = WebSocketAsyncCallback<HashMap<UInt32, String>>(
            {
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
            }
        )

        let messageCallBack = WebSocketAsyncCallback<MessageData>(
            {
                errorCode: Option<AsyncError>, data: Option<MessageData> => match (errorCode) {
                    case Some(e) => 0 // error
                    case _ => match (data) {
                        case Some(value) => this.createPeerConnection()
                        case _ => 0 // error
                    }
                }
            })
        this.ws.on(OnOffType.OPEN, openCallBack)
        this.ws.on(OnOffType.MESSAGE, messageCallBack)
        spawn {
            let syncCounter: SyncCounter = SyncCounter(1)
                this.createAudioDeviceModule({
                    value => launch {
                        this.adm.createID(value)
                        syncCounter.dec()
                    }
                })
            syncCounter.waitUntilZero()
            this.createPeerConnectionFactory({
                value => launch {
                    this.pcf.createID(value)
                }
            })
        }
    }

    protected override func aboutToDisappear() {
//        cj_StopAecDump(this.pcf.getID())
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
        this.ws.off(OnOffType.OPEN)
        this.ws.off(OnOffType.CLOSE)
        this.ws.off(OnOffType.ERROR)
        this.ws.off(OnOffType.MESSAGE)
    }

    func sendMessage(message:String):Future<Unit> {
        spawn {
            this.ws.send(MessageData.STRING_DATA(message),{
                errorCode:Option<AsyncError>,data:Option<Bool>=> if (let Some(e) <- errorCode) {
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

    func createAudioDeviceModule(callback: (admID:Int64) -> Unit): Future<Unit> {
        spawn {
            callback(cj_newAudioDeviceModule(true , true))
        }
    }

    func createPeerConnectionFactory(callback: (pcfID:Int64) -> Unit): Future<Unit> {
        spawn {
            callback(cj_newPeerConnectionFactory(this.adm.getID() , cj_newHardwareVideoEncoderFactory() , cj_newHardwareVideoDecoderFactory()))
        }
    }

    func prepareLocalMedia(): Future<Unit> {
        spawn {
            if (this.localAudioTrack.getID() == 0) {
                var ffiao: FFIAudioOptions = FFIAudioOptions()
                ffiao.noise_suppression = true
                ffiao.echo_cancellation = true
                this.localAudioSource.createAudioSourceID(this.pcf, ffiao)

                let audioChar: CString = unsafe{LibC.mallocCString("audio")}
                this.localAudioTrack.createAudioTrackID(this.pcf, audioChar)
            }

            if (this.localVideoTrack.getID() == 0) {
                var ffiCVSP:FFICreateVideoSourceParameters = FFICreateVideoSourceParameters()
                ffiCVSP.width = 1280.0
                ffiCVSP.height = 720.0
                ffiCVSP.facingMode = unsafe {LibC.mallocCString("user")}
                ffiCVSP.isScreencast = false
                this.localVideoSource.createVideoSourceID(this.pcf, ffiCVSP)

                let videoChar: CString = unsafe {LibC.mallocCString("video")}
                this.localVideoTrack.createVideoTrackID(this.pcf, videoChar)

                this.mXComponentController1.newNativeVideoRenderer()
                this.mXComponentController1.setVideoTrack(this.localVideoTrack.getID())
                this.mXComponentController1.setMirror(true)
                this.mXComponentController1.setScalingMode(ScalingMode().aspectFit)
            }
        }
    }

    func createPeerConnection():Future<Unit> {
        spawn {
            prepareLocalMedia().get()
        }
    }
}