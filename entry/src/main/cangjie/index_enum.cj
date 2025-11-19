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
class TestEnum {
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
        let fFIRTCErrorDetailType1 = FFIRTCErrorDetailType.NONE
        let fFIRTCErrorDetailType11 = FFIRTCErrorDetailType.NONE
        let fFIRTCErrorDetailType2 = FFIRTCErrorDetailType.DATA_CHANNEL_FAILURE
        let fFIRTCErrorDetailType22 = FFIRTCErrorDetailType.DATA_CHANNEL_FAILURE
        let fFIRTCErrorDetailType3 = FFIRTCErrorDetailType.DTLS_FAILURE
        let fFIRTCErrorDetailType33 = FFIRTCErrorDetailType.DTLS_FAILURE
        let fFIRTCErrorDetailType4 = FFIRTCErrorDetailType.FINGERPRINT_FAILURE
        let fFIRTCErrorDetailType44 = FFIRTCErrorDetailType.FINGERPRINT_FAILURE
        let fFIRTCErrorDetailType5 = FFIRTCErrorDetailType.SCTP_FAILURE
        let fFIRTCErrorDetailType55 = FFIRTCErrorDetailType.SCTP_FAILURE
        let fFIRTCErrorDetailType6 = FFIRTCErrorDetailType.SDP_SYNTAX_ERROR
        let fFIRTCErrorDetailType66 = FFIRTCErrorDetailType.SDP_SYNTAX_ERROR
        let fFIRTCErrorDetailType7 = FFIRTCErrorDetailType.HARDWARE_ENCODER_NOT_AVAILABLE
        let fFIRTCErrorDetailType77 = FFIRTCErrorDetailType.HARDWARE_ENCODER_NOT_AVAILABLE
        let fFIRTCErrorDetailType8 = FFIRTCErrorDetailType.HARDWARE_ENCODER_ERROR
        let fFIRTCErrorDetailType88 = FFIRTCErrorDetailType.HARDWARE_ENCODER_ERROR
        if (fFIRTCErrorDetailType1 == fFIRTCErrorDetailType2) {
            flag = false
        }
        if (fFIRTCErrorDetailType1 == fFIRTCErrorDetailType11) {
            flag = false
        }
        if (fFIRTCErrorDetailType2 == fFIRTCErrorDetailType22) {
            flag = false
        }
        if (fFIRTCErrorDetailType3 == fFIRTCErrorDetailType33) {
            flag = false
        }
        if (fFIRTCErrorDetailType4 == fFIRTCErrorDetailType44) {
            flag = false
        }
        if (fFIRTCErrorDetailType5 == fFIRTCErrorDetailType55) {
            flag = false
        }
        if (fFIRTCErrorDetailType6 == fFIRTCErrorDetailType66) {
            flag = false
        }
        if (fFIRTCErrorDetailType7 == fFIRTCErrorDetailType77) {
            flag = false
        }
        if (fFIRTCErrorDetailType8 == fFIRTCErrorDetailType88) {
            flag = false
        }
        if (fFIRTCErrorDetailType1 != fFIRTCErrorDetailType8) {
            FFIRTCErrorDetailType.GET(0)
            FFIRTCErrorDetailType.GET(1)
            FFIRTCErrorDetailType.GET(2)
            FFIRTCErrorDetailType.GET(3)
            FFIRTCErrorDetailType.GET(4)
            FFIRTCErrorDetailType.GET(5)
            FFIRTCErrorDetailType.GET(6)
            FFIRTCErrorDetailType.GET(7)
            FFIRTCErrorDetailType.GET(fFIRTCErrorDetailType1)
            FFIRTCErrorDetailType.GET(fFIRTCErrorDetailType2)
            FFIRTCErrorDetailType.GET(fFIRTCErrorDetailType3)
            FFIRTCErrorDetailType.GET(fFIRTCErrorDetailType4)
            FFIRTCErrorDetailType.GET(fFIRTCErrorDetailType5)
            FFIRTCErrorDetailType.GET(fFIRTCErrorDetailType6)
            FFIRTCErrorDetailType.GET(fFIRTCErrorDetailType7)
            FFIRTCErrorDetailType.GET(fFIRTCErrorDetailType8)
        	flag = true
            res = fFIRTCErrorDetailType1.toString() + " " + fFIRTCErrorDetailType2.toString() + " " + fFIRTCErrorDetailType3.toString() + " " + fFIRTCErrorDetailType4.toString() + " " + fFIRTCErrorDetailType5.toString() + " " + fFIRTCErrorDetailType6.toString() + " " + fFIRTCErrorDetailType7.toString() + " " + fFIRTCErrorDetailType8.toString()
        }
        let fFIRTCIceProtocol1 = FFIRTCIceProtocol.TCP
        let fFIRTCIceProtocol11 = FFIRTCIceProtocol.TCP
        let fFIRTCIceProtocol2 = FFIRTCIceProtocol.UDP
        let fFIRTCIceProtocol22 = FFIRTCIceProtocol.UDP
        if (fFIRTCIceProtocol1 == fFIRTCIceProtocol2) {
            flag = false
        }
        if (fFIRTCIceProtocol1 == fFIRTCIceProtocol11) {
            flag = false
        }
        if (fFIRTCIceProtocol2 == fFIRTCIceProtocol22) {
            flag = false
        }
        if (fFIRTCIceProtocol1 != fFIRTCIceProtocol2) {
            FFIRTCIceProtocol.GET(0)
            FFIRTCIceProtocol.GET(1)
            FFIRTCIceProtocol.GET(fFIRTCIceProtocol1)
            FFIRTCIceProtocol.GET(fFIRTCIceProtocol2)
        	flag = true
            res = fFIRTCIceProtocol1.toString() + " " + fFIRTCIceProtocol2.toString()
        }
        let fFIRTCIceCandidateType1 = FFIRTCIceCandidateType.HOST
        let fFIRTCIceCandidateType11 = FFIRTCIceCandidateType.HOST
        let fFIRTCIceCandidateType2 = FFIRTCIceCandidateType.PRFLX
        let fFIRTCIceCandidateType22 = FFIRTCIceCandidateType.PRFLX
        let fFIRTCIceCandidateType3 = FFIRTCIceCandidateType.RELAY
        let fFIRTCIceCandidateType33 = FFIRTCIceCandidateType.RELAY
        let fFIRTCIceCandidateType4 = FFIRTCIceCandidateType.SRFLX
        let fFIRTCIceCandidateType44 = FFIRTCIceCandidateType.SRFLX
        if (fFIRTCIceCandidateType1 == fFIRTCIceCandidateType2) {
            flag = false
        }
        if (fFIRTCIceCandidateType1 == fFIRTCIceCandidateType11) {
            flag = false
        }
        if (fFIRTCIceCandidateType2 == fFIRTCIceCandidateType22) {
            flag = false
        }
        if (fFIRTCIceCandidateType3 == fFIRTCIceCandidateType33) {
            flag = false
        }
        if (fFIRTCIceCandidateType4 == fFIRTCIceCandidateType44) {
            flag = false
        }
        if (fFIRTCIceCandidateType1 != fFIRTCIceCandidateType2) {
            FFIRTCIceCandidateType.GET(0)
            FFIRTCIceCandidateType.GET(1)
            FFIRTCIceCandidateType.GET(2)
            FFIRTCIceCandidateType.GET(3)
            FFIRTCIceCandidateType.GET(fFIRTCIceCandidateType1)
            FFIRTCIceCandidateType.GET(fFIRTCIceCandidateType2)
            FFIRTCIceCandidateType.GET(fFIRTCIceCandidateType3)
            FFIRTCIceCandidateType.GET(fFIRTCIceCandidateType4)
        	flag = true
            res = fFIRTCIceCandidateType1.toString() + " " + fFIRTCIceCandidateType2.toString() + " " + fFIRTCIceCandidateType3.toString() + " " + fFIRTCIceCandidateType4.toString()
        }
        let fFIRTCIceTcpCandidateType1 = FFIRTCIceTcpCandidateType.ACTIVE
        let fFIRTCIceTcpCandidateType11 = FFIRTCIceTcpCandidateType.ACTIVE
        let fFIRTCIceTcpCandidateType2 = FFIRTCIceTcpCandidateType.SO
        let fFIRTCIceTcpCandidateType22 = FFIRTCIceTcpCandidateType.SO
        let fFIRTCIceTcpCandidateType3 = FFIRTCIceTcpCandidateType.PASSIVE
        let fFIRTCIceTcpCandidateType33 = FFIRTCIceTcpCandidateType.PASSIVE
        if (fFIRTCIceTcpCandidateType1 == fFIRTCIceTcpCandidateType2) {
            flag = false
        }
        if (fFIRTCIceTcpCandidateType1 == fFIRTCIceTcpCandidateType11) {
            flag = false
        }
        if (fFIRTCIceTcpCandidateType2 == fFIRTCIceTcpCandidateType22) {
            flag = false
        }
        if (fFIRTCIceTcpCandidateType3 == fFIRTCIceTcpCandidateType33) {}
        if (fFIRTCIceTcpCandidateType1 != fFIRTCIceTcpCandidateType2) {
            FFIRTCIceTcpCandidateType.GET(0)
            FFIRTCIceTcpCandidateType.GET(1)
            FFIRTCIceTcpCandidateType.GET(2)
            FFIRTCIceTcpCandidateType.GET(fFIRTCIceTcpCandidateType1)
            FFIRTCIceTcpCandidateType.GET(fFIRTCIceTcpCandidateType2)
            FFIRTCIceTcpCandidateType.GET(fFIRTCIceTcpCandidateType3)
        	flag = true
            res = fFIRTCIceTcpCandidateType1.toString() + " " + fFIRTCIceTcpCandidateType2.toString() + " " + fFIRTCIceTcpCandidateType3.toString()
        }
        let fFIRTCIceComponent1 = FFIRTCIceComponent.RTP
        let fFIRTCIceComponent11 = FFIRTCIceComponent.RTP
        let fFIRTCIceComponent2 = FFIRTCIceComponent.RTCP
        let fFIRTCIceComponent22 = FFIRTCIceComponent.RTCP
        if (fFIRTCIceComponent1 == fFIRTCIceComponent2) {
            flag = false
        }
        if (fFIRTCIceComponent1 == fFIRTCIceComponent11) {
            flag = false
        }
        if (fFIRTCIceComponent2 == fFIRTCIceComponent22) {
            flag = false
        }
        if (fFIRTCIceComponent1 != fFIRTCIceComponent2) {
            FFIRTCIceComponent.GET(0)
            FFIRTCIceComponent.GET(1)
            FFIRTCIceComponent.GET(fFIRTCIceComponent1)
            FFIRTCIceComponent.GET(fFIRTCIceComponent2)
        	flag = true
            res = fFIRTCIceComponent1.toString() + " " + fFIRTCIceComponent2.toString()
        }
        let fFIRTCIceGathererState1 = FFIRTCIceGathererState.COMPLETE
        let fFIRTCIceGathererState11 = FFIRTCIceGathererState.COMPLETE
        let fFIRTCIceGathererState2 = FFIRTCIceGathererState.NEW
        let fFIRTCIceGathererState22 = FFIRTCIceGathererState.NEW
        let fFIRTCIceGathererState3 = FFIRTCIceGathererState.GATHERING
        let fFIRTCIceGathererState33 = FFIRTCIceGathererState.GATHERING
        if (fFIRTCIceGathererState1 == fFIRTCIceGathererState2) {
            flag = false
        }
        if (fFIRTCIceGathererState1 == fFIRTCIceGathererState11) {
            flag = false
        }
        if (fFIRTCIceGathererState2 == fFIRTCIceGathererState22) {
            flag = false
        }
        if (fFIRTCIceGathererState3 == fFIRTCIceGathererState33) {}
        if (fFIRTCIceGathererState1 != fFIRTCIceGathererState2) {
            FFIRTCIceGathererState.GET(0)
            FFIRTCIceGathererState.GET(1)
            FFIRTCIceGathererState.GET(2)
            FFIRTCIceGathererState.GET(fFIRTCIceGathererState1)
            FFIRTCIceGathererState.GET(fFIRTCIceGathererState2)
            FFIRTCIceGathererState.GET(fFIRTCIceGathererState3)
        	flag = true
            res = fFIRTCIceGathererState1.toString() + " " + fFIRTCIceGathererState2.toString() + " " + fFIRTCIceGathererState3.toString()
        }
        let fFIRTCIceTransportState1 = FFIRTCIceTransportState.CHECKING
        let fFIRTCIceTransportState11 = FFIRTCIceTransportState.CHECKING
        let fFIRTCIceTransportState2 = FFIRTCIceTransportState.CLOSED
        let fFIRTCIceTransportState22 = FFIRTCIceTransportState.CLOSED
        let fFIRTCIceTransportState3 = FFIRTCIceTransportState.COMPLETED
        let fFIRTCIceTransportState33 = FFIRTCIceTransportState.COMPLETED
        let fFIRTCIceTransportState4 = FFIRTCIceTransportState.CONNECTED
        let fFIRTCIceTransportState44 = FFIRTCIceTransportState.CONNECTED
        let fFIRTCIceTransportState5 = FFIRTCIceTransportState.DISCONNECTED
        let fFIRTCIceTransportState55 = FFIRTCIceTransportState.DISCONNECTED
        let fFIRTCIceTransportState6 = FFIRTCIceTransportState.FAILED
        let fFIRTCIceTransportState66 = FFIRTCIceTransportState.FAILED
        let fFIRTCIceTransportState7 = FFIRTCIceTransportState.NEW
        let fFIRTCIceTransportState77 = FFIRTCIceTransportState.NEW
        if (fFIRTCIceTransportState1 == fFIRTCIceTransportState2) {
            flag = false
        }
        if (fFIRTCIceTransportState1 == fFIRTCIceTransportState11) {
            flag = false
        }
        if (fFIRTCIceTransportState2 == fFIRTCIceTransportState22) {
            flag = false
        }
        if (fFIRTCIceTransportState3 == fFIRTCIceTransportState33) {
            flag = false
        }
        if (fFIRTCIceTransportState4 == fFIRTCIceTransportState44) {}
        if (fFIRTCIceTransportState5 == fFIRTCIceTransportState55) {}
        if (fFIRTCIceTransportState6 == fFIRTCIceTransportState66) {}
        if (fFIRTCIceTransportState7 == fFIRTCIceTransportState77) {}
        if (fFIRTCIceTransportState1 != fFIRTCIceTransportState2) {
            FFIRTCIceTransportState.GET(0)
            FFIRTCIceTransportState.GET(1)
            FFIRTCIceTransportState.GET(2)
            FFIRTCIceTransportState.GET(3)
            FFIRTCIceTransportState.GET(4)
            FFIRTCIceTransportState.GET(5)
            FFIRTCIceTransportState.GET(6)
            FFIRTCIceTransportState.GET(fFIRTCIceTransportState1)
            FFIRTCIceTransportState.GET(fFIRTCIceTransportState2)
            FFIRTCIceTransportState.GET(fFIRTCIceTransportState3)
            FFIRTCIceTransportState.GET(fFIRTCIceTransportState4)
            FFIRTCIceTransportState.GET(fFIRTCIceTransportState5)
            FFIRTCIceTransportState.GET(fFIRTCIceTransportState6)
            FFIRTCIceTransportState.GET(fFIRTCIceTransportState7)
        	flag = true
            res = fFIRTCIceTransportState1.toString() + " " + fFIRTCIceTransportState2.toString() + " " + fFIRTCIceTransportState3.toString() + " " + fFIRTCIceTransportState4.toString() + " " + fFIRTCIceTransportState5.toString() + " " + fFIRTCIceTransportState6.toString() + " " + fFIRTCIceTransportState7.toString()
        }
        let fFIRTCIceRole1 = FFIRTCIceRole.UNKNOWN
        let fFIRTCIceRole11 = FFIRTCIceRole.UNKNOWN
        let fFIRTCIceRole2 = FFIRTCIceRole.CONTROLLING
        let fFIRTCIceRole22 = FFIRTCIceRole.CONTROLLING
        let fFIRTCIceRole3 = FFIRTCIceRole.CONTROLLED
        let fFIRTCIceRole33 = FFIRTCIceRole.CONTROLLED
        if (fFIRTCIceRole1 == fFIRTCIceRole2) {
            flag = false
        }
        if (fFIRTCIceRole1 == fFIRTCIceRole11) {
            flag = false
        }
        if (fFIRTCIceRole2 == fFIRTCIceRole22) {
            flag = false
        }
        if (fFIRTCIceRole3 == fFIRTCIceRole33) {}
        if (fFIRTCIceRole1 != fFIRTCIceRole2) {
            FFIRTCIceRole.GET(0)
            FFIRTCIceRole.GET(1)
            FFIRTCIceRole.GET(2)
            FFIRTCIceRole.GET(fFIRTCIceRole1)
            FFIRTCIceRole.GET(fFIRTCIceRole2)
            FFIRTCIceRole.GET(fFIRTCIceRole3)
        	flag = true
            res = fFIRTCIceRole1.toString() + " " + fFIRTCIceRole2.toString() + " " + fFIRTCIceRole3.toString()
        }
        let fFIRTCSdpType1 = FFIRTCSdpType.OFFER
        let fFIRTCSdpType11 = FFIRTCSdpType.OFFER
        let fFIRTCSdpType2 = FFIRTCSdpType.ANSWER
        let fFIRTCSdpType22 = FFIRTCSdpType.ANSWER
        let fFIRTCSdpType3 = FFIRTCSdpType.PRANSWER
        let fFIRTCSdpType33 = FFIRTCSdpType.PRANSWER
        let fFIRTCSdpType4 = FFIRTCSdpType.ROLLBACK
        let fFIRTCSdpType44 = FFIRTCSdpType.ROLLBACK
        if (fFIRTCSdpType1 == fFIRTCSdpType2) {
            flag = false
        }
        if (fFIRTCSdpType1 == fFIRTCSdpType11) {
            flag = false
        }
        if (fFIRTCSdpType2 == fFIRTCSdpType22) {
            flag = false
        }
        if (fFIRTCSdpType3 == fFIRTCSdpType33) {}
        if (fFIRTCSdpType4 == fFIRTCSdpType44) {}
        if (fFIRTCSdpType1 != fFIRTCSdpType2) {
            FFIRTCSdpType.GET(0)
            FFIRTCSdpType.GET(1)
            FFIRTCSdpType.GET(2)
            FFIRTCSdpType.GET(3)
            FFIRTCSdpType.GET(fFIRTCSdpType1)
            FFIRTCSdpType.GET(fFIRTCSdpType2)
            FFIRTCSdpType.GET(fFIRTCSdpType3)
            FFIRTCSdpType.GET(fFIRTCSdpType4)
        	flag = true
            res = fFIRTCSdpType1.toString() + " " + fFIRTCSdpType2.toString() + " " + fFIRTCSdpType3.toString() + " " + fFIRTCSdpType4.toString()
        }
        let fFIBinaryType1 = FFIBinaryType.BLOB
        let fFIBinaryType11 = FFIBinaryType.BLOB
        let fFIBinaryType2 = FFIBinaryType.ARRAYBUFFER
        let fFIBinaryType22 = FFIBinaryType.ARRAYBUFFER
        if (fFIBinaryType1 == fFIBinaryType2) {
            flag = false
        }
        if (fFIBinaryType1 == fFIBinaryType11) {
            flag = false
        }
        if (fFIBinaryType2 == fFIBinaryType22) {}
        if (fFIBinaryType1 != fFIBinaryType2) {
            FFIBinaryType.GET(0)
            FFIBinaryType.GET(1)
            FFIBinaryType.GET(fFIBinaryType1)
            FFIBinaryType.GET(fFIBinaryType2)
        	flag = true
            res = fFIBinaryType1.toString() + " " + fFIBinaryType2.toString()
        }

        let fFIDataChannelState1 = FFIDataChannelState.CLOSED
        let fFIDataChannelState11 = FFIDataChannelState.CLOSED
        let fFIDataChannelState2 = FFIDataChannelState.CLOSING
        let fFIDataChannelState22 = FFIDataChannelState.CLOSING
        let fFIDataChannelState3 = FFIDataChannelState.CONNECTING
        let fFIDataChannelState33 = FFIDataChannelState.CONNECTING
        let fFIDataChannelState4 = FFIDataChannelState.OPEN
        let fFIDataChannelState44 = FFIDataChannelState.OPEN
        if (fFIDataChannelState1 == fFIDataChannelState2) {
            flag = false
        }
        if (fFIDataChannelState1 == fFIDataChannelState11) {
            flag = false
        }
        if (fFIDataChannelState2 == fFIDataChannelState22) {
            flag = false
        }
        if (fFIDataChannelState3 == fFIDataChannelState33) {}
        if (fFIDataChannelState4 == fFIDataChannelState44) {}
        if (fFIDataChannelState1 != fFIDataChannelState2) {
            FFIDataChannelState.GET(0)
            FFIDataChannelState.GET(1)
            FFIDataChannelState.GET(2)
            FFIDataChannelState.GET(3)
            FFIDataChannelState.GET(fFIDataChannelState1)
            FFIDataChannelState.GET(fFIDataChannelState2)
            FFIDataChannelState.GET(fFIDataChannelState3)
            FFIDataChannelState.GET(fFIDataChannelState4)
        	flag = true
            res = fFIDataChannelState1.toString() + " " + fFIDataChannelState2.toString() + " " + fFIDataChannelState3.toString() + " " + fFIDataChannelState4.toString()
        }
        let fFIRTCDtlsTransportState1 = FFIRTCDtlsTransportState.NEW
        let fFIRTCDtlsTransportState11 = FFIRTCDtlsTransportState.NEW
        let fFIRTCDtlsTransportState2 = FFIRTCDtlsTransportState.CONNECTING
        let fFIRTCDtlsTransportState22 = FFIRTCDtlsTransportState.CONNECTING
        let fFIRTCDtlsTransportState3 = FFIRTCDtlsTransportState.CONNECTED
        let fFIRTCDtlsTransportState33 = FFIRTCDtlsTransportState.CONNECTED
        let fFIRTCDtlsTransportState4 = FFIRTCDtlsTransportState.CLOSED
        let fFIRTCDtlsTransportState44 = FFIRTCDtlsTransportState.CLOSED
        let fFIRTCDtlsTransportState5 = FFIRTCDtlsTransportState.FAILED
        let fFIRTCDtlsTransportState55 = FFIRTCDtlsTransportState.FAILED
        if (fFIRTCDtlsTransportState1 == fFIRTCDtlsTransportState2) {
            flag = false
        }
        if (fFIRTCDtlsTransportState1 == fFIRTCDtlsTransportState11) {
            flag = false
        }
        if (fFIRTCDtlsTransportState2 == fFIRTCDtlsTransportState22) {
            flag = false
        }
        if (fFIRTCDtlsTransportState3 == fFIRTCDtlsTransportState33) {}
        if (fFIRTCDtlsTransportState4 == fFIRTCDtlsTransportState44) {}
        if (fFIRTCDtlsTransportState5 == fFIRTCDtlsTransportState55) {}
        if (fFIRTCDtlsTransportState1 != fFIRTCDtlsTransportState2) {
            FFIRTCDtlsTransportState.GET(0)
            FFIRTCDtlsTransportState.GET(1)
            FFIRTCDtlsTransportState.GET(2)
            FFIRTCDtlsTransportState.GET(3)
            FFIRTCDtlsTransportState.GET(4)
            FFIRTCDtlsTransportState.GET(fFIRTCDtlsTransportState1)
            FFIRTCDtlsTransportState.GET(fFIRTCDtlsTransportState2)
            FFIRTCDtlsTransportState.GET(fFIRTCDtlsTransportState3)
            FFIRTCDtlsTransportState.GET(fFIRTCDtlsTransportState4)
            FFIRTCDtlsTransportState.GET(fFIRTCDtlsTransportState5)
        	flag = true
            res = fFIRTCDtlsTransportState1.toString() + " " + fFIRTCDtlsTransportState2.toString() + " " + fFIRTCDtlsTransportState3.toString() + " " + fFIRTCDtlsTransportState4.toString() + " " + fFIRTCDtlsTransportState5.toString()
        }
        let fFIRTCIceGatheringState1 = FFIRTCIceGatheringState.GATHERING
        let fFIRTCIceGatheringState11 = FFIRTCIceGatheringState.GATHERING
        let fFIRTCIceGatheringState2 = FFIRTCIceGatheringState.GATHERING
        let fFIRTCIceGatheringState22 = FFIRTCIceGatheringState.GATHERING
        let fFIRTCIceGatheringState3 = FFIRTCIceGatheringState.COMPLETE
        let fFIRTCIceGatheringState33 = FFIRTCIceGatheringState.COMPLETE
        if (fFIRTCIceGatheringState1 == fFIRTCIceGatheringState2) {
            flag = false
        }
        if (fFIRTCIceGatheringState1 == fFIRTCIceGatheringState11) {
            flag = false
        }
        if (fFIRTCIceGatheringState2 == fFIRTCIceGatheringState22) {
            flag = false
        }
        if (fFIRTCIceGatheringState3 == fFIRTCIceGatheringState33) {}
        if (fFIRTCIceGatheringState1 != fFIRTCIceGatheringState2) {
            FFIRTCIceGatheringState.GET(0)
            FFIRTCIceGatheringState.GET(1)
            FFIRTCIceGatheringState.GET(2)
            FFIRTCIceGatheringState.GET(fFIRTCIceGatheringState1)
            FFIRTCIceGatheringState.GET(fFIRTCIceGatheringState2)
            FFIRTCIceGatheringState.GET(fFIRTCIceGatheringState3)
        	flag = true
            res = fFIRTCIceGatheringState1.toString() + " " + fFIRTCIceGatheringState2.toString() + " " + fFIRTCIceGatheringState3.toString()
        }
        let fFIRTCIceConnectionState1 = FFIRTCIceConnectionState.CHECKING
        let fFIRTCIceConnectionState11 = FFIRTCIceConnectionState.CHECKING
        let fFIRTCIceConnectionState2 = FFIRTCIceConnectionState.CLOSED
        let fFIRTCIceConnectionState22 = FFIRTCIceConnectionState.CLOSED
        let fFIRTCIceConnectionState3 = FFIRTCIceConnectionState.COMPLETED
        let fFIRTCIceConnectionState33 = FFIRTCIceConnectionState.COMPLETED
        let fFIRTCIceConnectionState4 = FFIRTCIceConnectionState.CONNECTED
        let fFIRTCIceConnectionState44 = FFIRTCIceConnectionState.CONNECTED
        let fFIRTCIceConnectionState5 = FFIRTCIceConnectionState.DISCONNECTED
        let fFIRTCIceConnectionState55 = FFIRTCIceConnectionState.DISCONNECTED
        let fFIRTCIceConnectionState6 = FFIRTCIceConnectionState.FAILED
        let fFIRTCIceConnectionState66 = FFIRTCIceConnectionState.FAILED
        let fFIRTCIceConnectionState7 = FFIRTCIceConnectionState.NEW
        let fFIRTCIceConnectionState77 = FFIRTCIceConnectionState.NEW
        if (fFIRTCIceConnectionState1 == fFIRTCIceConnectionState2) {
            flag = false
        }
        if (fFIRTCIceConnectionState1 == fFIRTCIceConnectionState11) {
            flag = false
        }
        if (fFIRTCIceConnectionState2 == fFIRTCIceConnectionState22) {
            flag = false
        }
        if (fFIRTCIceConnectionState3 == fFIRTCIceConnectionState33) {}
        if (fFIRTCIceConnectionState4 == fFIRTCIceConnectionState44) {}
        if (fFIRTCIceConnectionState5 == fFIRTCIceConnectionState55) {}
        if (fFIRTCIceConnectionState6 == fFIRTCIceConnectionState66) {}
        if (fFIRTCIceConnectionState7 == fFIRTCIceConnectionState77) {}
        if (fFIRTCIceConnectionState1 != fFIRTCIceConnectionState2) {
            FFIRTCIceConnectionState.GET(0)
            FFIRTCIceConnectionState.GET(1)
            FFIRTCIceConnectionState.GET(2)
            FFIRTCIceConnectionState.GET(3)
            FFIRTCIceConnectionState.GET(4)
            FFIRTCIceConnectionState.GET(5)
            FFIRTCIceConnectionState.GET(6)
            FFIRTCIceConnectionState.GET(fFIRTCIceConnectionState1)
            FFIRTCIceConnectionState.GET(fFIRTCIceConnectionState2)
            FFIRTCIceConnectionState.GET(fFIRTCIceConnectionState3)
            FFIRTCIceConnectionState.GET(fFIRTCIceConnectionState4)
            FFIRTCIceConnectionState.GET(fFIRTCIceConnectionState5)
            FFIRTCIceConnectionState.GET(fFIRTCIceConnectionState6)
            FFIRTCIceConnectionState.GET(fFIRTCIceConnectionState7)
        	flag = true
            res = fFIRTCIceConnectionState1.toString() + " " + fFIRTCIceConnectionState2.toString() + " " + fFIRTCIceConnectionState3.toString() + " " + fFIRTCIceConnectionState4.toString() + " " + fFIRTCIceConnectionState5.toString() + " " + fFIRTCIceConnectionState6.toString() + " " + fFIRTCIceConnectionState7.toString()
        }
        let fFIRTCSignalingState1 = FFIRTCSignalingState.CLOSED
        let fFIRTCSignalingState11 = FFIRTCSignalingState.CLOSED
        let fFIRTCSignalingState2 = FFIRTCSignalingState.HAVE_LOCAL_OFFER
        let fFIRTCSignalingState22 = FFIRTCSignalingState.HAVE_LOCAL_OFFER
        let fFIRTCSignalingState3 = FFIRTCSignalingState.HAVE_LOCAL_PRANSWER
        let fFIRTCSignalingState33 = FFIRTCSignalingState.HAVE_LOCAL_PRANSWER
        let fFIRTCSignalingState4 = FFIRTCSignalingState.HAVE_REMOTE_OFFER
        let fFIRTCSignalingState44 = FFIRTCSignalingState.HAVE_REMOTE_OFFER
        let fFIRTCSignalingState5 = FFIRTCSignalingState.HAVE_REMOTE_PRANSWER
        let fFIRTCSignalingState55 = FFIRTCSignalingState.HAVE_REMOTE_PRANSWER
        let fFIRTCSignalingState6 = FFIRTCSignalingState.STABLE
        let fFIRTCSignalingState66 = FFIRTCSignalingState.STABLE
        if (fFIRTCSignalingState1 == fFIRTCSignalingState2) {
            flag = false
        }
        if (fFIRTCSignalingState1 == fFIRTCSignalingState11) {
            flag = false
        }
        if (fFIRTCSignalingState2 == fFIRTCSignalingState22) {
            flag = false
        }
        if (fFIRTCSignalingState3 == fFIRTCSignalingState33) {}
        if (fFIRTCSignalingState4 == fFIRTCSignalingState44) {}
        if (fFIRTCSignalingState5 == fFIRTCSignalingState55) {}
        if (fFIRTCSignalingState6 == fFIRTCSignalingState66) {}
        if (fFIRTCSignalingState1 != fFIRTCSignalingState2) {
            FFIRTCSignalingState.GET(0)
            FFIRTCSignalingState.GET(1)
            FFIRTCSignalingState.GET(2)
            FFIRTCSignalingState.GET(3)
            FFIRTCSignalingState.GET(4)
            FFIRTCSignalingState.GET(5)
            FFIRTCSignalingState.GET(fFIRTCSignalingState1)
            FFIRTCSignalingState.GET(fFIRTCSignalingState2)
            FFIRTCSignalingState.GET(fFIRTCSignalingState3)
            FFIRTCSignalingState.GET(fFIRTCSignalingState4)
            FFIRTCSignalingState.GET(fFIRTCSignalingState5)
            FFIRTCSignalingState.GET(fFIRTCSignalingState6)
        	flag = true
            res = fFIRTCSignalingState1.toString() + " " + fFIRTCSignalingState2.toString() + " " + fFIRTCSignalingState3.toString() + " " + fFIRTCSignalingState4.toString() + " " + fFIRTCSignalingState5.toString() + " " + fFIRTCSignalingState6.toString()
        }
        let fFIRTCPeerConnectionState1 = FFIRTCPeerConnectionState.CLOSED
        let fFIRTCPeerConnectionState11 = FFIRTCPeerConnectionState.CLOSED
        let fFIRTCPeerConnectionState2 = FFIRTCPeerConnectionState.CONNECTED
        let fFIRTCPeerConnectionState22 = FFIRTCPeerConnectionState.CONNECTED
        let fFIRTCPeerConnectionState3 = FFIRTCPeerConnectionState.CONNECTING
        let fFIRTCPeerConnectionState33 = FFIRTCPeerConnectionState.CONNECTING
        let fFIRTCPeerConnectionState4 = FFIRTCPeerConnectionState.DISCONNECTED
        let fFIRTCPeerConnectionState44 = FFIRTCPeerConnectionState.DISCONNECTED
        let fFIRTCPeerConnectionState5 = FFIRTCPeerConnectionState.FAILED
        let fFIRTCPeerConnectionState55 = FFIRTCPeerConnectionState.FAILED
        let fFIRTCPeerConnectionState6 = FFIRTCPeerConnectionState.NEW
        let fFIRTCPeerConnectionState66 = FFIRTCPeerConnectionState.NEW
        if (fFIRTCPeerConnectionState1 == fFIRTCPeerConnectionState2) {
            flag = false
        }
        if (fFIRTCPeerConnectionState1 == fFIRTCPeerConnectionState11) {
            flag = false
        }
        if (fFIRTCPeerConnectionState2 == fFIRTCPeerConnectionState22) {
            flag = false
        }
        if (fFIRTCPeerConnectionState3 == fFIRTCPeerConnectionState33) {}
        if (fFIRTCPeerConnectionState4 == fFIRTCPeerConnectionState44) {}
        if (fFIRTCPeerConnectionState5 == fFIRTCPeerConnectionState55) {}
        if (fFIRTCPeerConnectionState6 == fFIRTCPeerConnectionState66) {}
        if (fFIRTCPeerConnectionState1 != fFIRTCPeerConnectionState2) {
            FFIRTCPeerConnectionState.GET(0)
            FFIRTCPeerConnectionState.GET(1)
            FFIRTCPeerConnectionState.GET(2)
            FFIRTCPeerConnectionState.GET(3)
            FFIRTCPeerConnectionState.GET(4)
            FFIRTCPeerConnectionState.GET(5)
            FFIRTCPeerConnectionState.GET(fFIRTCPeerConnectionState1)
            FFIRTCPeerConnectionState.GET(fFIRTCPeerConnectionState2)
            FFIRTCPeerConnectionState.GET(fFIRTCPeerConnectionState3)
            FFIRTCPeerConnectionState.GET(fFIRTCPeerConnectionState4)
            FFIRTCPeerConnectionState.GET(fFIRTCPeerConnectionState5)
            FFIRTCPeerConnectionState.GET(fFIRTCPeerConnectionState6)
        	flag = true
            res = fFIRTCPeerConnectionState1.toString() + " " + fFIRTCPeerConnectionState2.toString() + " " + fFIRTCPeerConnectionState3.toString() + " " + fFIRTCPeerConnectionState4.toString() + " " + fFIRTCPeerConnectionState5.toString() + " " + fFIRTCPeerConnectionState6.toString()
        }
        let fFIRTCBundlePolicy1 = FFIRTCBundlePolicy.BALANCED
        let fFIRTCBundlePolicy11 = FFIRTCBundlePolicy.BALANCED
        let fFIRTCBundlePolicy2 = FFIRTCBundlePolicy.MAX_BUNDLE
        let fFIRTCBundlePolicy22 = FFIRTCBundlePolicy.MAX_BUNDLE
        let fFIRTCBundlePolicy3 = FFIRTCBundlePolicy.MAX_COMPAT
        let fFIRTCBundlePolicy33 = FFIRTCBundlePolicy.MAX_COMPAT
        if (fFIRTCBundlePolicy1 == fFIRTCBundlePolicy2) {
            flag = false
        }
        if (fFIRTCBundlePolicy1 == fFIRTCBundlePolicy11) {
            flag = false
        }
        if (fFIRTCBundlePolicy2 == fFIRTCBundlePolicy22) {
            flag = false
        }
        if (fFIRTCBundlePolicy3 == fFIRTCBundlePolicy33) {}
        if (fFIRTCBundlePolicy1 != fFIRTCBundlePolicy2) {
            FFIRTCBundlePolicy.GET(0)
            FFIRTCBundlePolicy.GET(1)
            FFIRTCBundlePolicy.GET(2)
            FFIRTCBundlePolicy.GET(fFIRTCBundlePolicy1)
            FFIRTCBundlePolicy.GET(fFIRTCBundlePolicy2)
            FFIRTCBundlePolicy.GET(fFIRTCBundlePolicy3)
        	flag = true
            res = fFIRTCBundlePolicy1.toString() + " " + fFIRTCBundlePolicy2.toString() + " " + fFIRTCBundlePolicy3.toString()
        }
        let fFIRTCRtcpMuxPolicy1 = FFIRTCRtcpMuxPolicy.REQUIRE
        let fFIRTCRtcpMuxPolicy2 = FFIRTCRtcpMuxPolicy.REQUIRE
        if (fFIRTCRtcpMuxPolicy1 == fFIRTCRtcpMuxPolicy2) {
            FFIRTCRtcpMuxPolicy.GET(0)
            FFIRTCRtcpMuxPolicy.GET(fFIRTCRtcpMuxPolicy2)
            flag = false
        }
        if (fFIRTCRtcpMuxPolicy1 != fFIRTCRtcpMuxPolicy2) {
        	flag = true
            FFIRTCRtcpMuxPolicy.GET(0)
            FFIRTCRtcpMuxPolicy.GET(fFIRTCRtcpMuxPolicy2)
            res = fFIRTCRtcpMuxPolicy1.toString() + " " + fFIRTCRtcpMuxPolicy2.toString()
        }

        let fFIRTCIceTransportPolicy1 = FFIRTCIceTransportPolicy.ALL
        let fFIRTCIceTransportPolicy11 = FFIRTCIceTransportPolicy.ALL
        let fFIRTCIceTransportPolicy2 = FFIRTCIceTransportPolicy.RELAY
        let fFIRTCIceTransportPolicy22 = FFIRTCIceTransportPolicy.RELAY
        if (fFIRTCIceTransportPolicy1 == fFIRTCIceTransportPolicy2) {
            flag = false
        }
        if (fFIRTCIceTransportPolicy1 == fFIRTCIceTransportPolicy11) {
            flag = false
        }
        if (fFIRTCIceTransportPolicy2 == fFIRTCIceTransportPolicy22) {
            flag = false
        }
        if (fFIRTCIceTransportPolicy1 != fFIRTCIceTransportPolicy2) {
        	flag = true
            FFIRTCIceTransportPolicy.GET(0)
            FFIRTCIceTransportPolicy.GET(1)
            FFIRTCIceTransportPolicy.GET(fFIRTCIceTransportPolicy1)
            FFIRTCIceTransportPolicy.GET(fFIRTCIceTransportPolicy2)
            res = fFIRTCIceTransportPolicy1.toString() + " " + fFIRTCIceTransportPolicy2.toString()
        }
        let fFIDegradationPreference1 = FFIDegradationPreference.BALANCED
        let fFIDegradationPreference11 = FFIDegradationPreference.BALANCED
        let fFIDegradationPreference2 = FFIDegradationPreference.MAINTAIN_RESOLUTION
        let fFIDegradationPreference22 = FFIDegradationPreference.MAINTAIN_RESOLUTION
        let fFIDegradationPreference3 = FFIDegradationPreference.MAINTAIN_FRAMERATE
        let fFIDegradationPreference33 = FFIDegradationPreference.MAINTAIN_FRAMERATE
        if (fFIDegradationPreference1 == fFIDegradationPreference2) {
            flag = false
        }
        if (fFIDegradationPreference1 == fFIDegradationPreference11) {
            flag = false
        }
        if (fFIDegradationPreference2 == fFIDegradationPreference22) {
            flag = false
        }
        if (fFIDegradationPreference3 == fFIDegradationPreference33) {}
        if (fFIDegradationPreference1 != fFIDegradationPreference2) {
        	flag = true
            FFIDegradationPreference.GET(0)
            FFIDegradationPreference.GET(1)
            FFIDegradationPreference.GET(2)
            FFIDegradationPreference.GET(fFIDegradationPreference1)
            FFIDegradationPreference.GET(fFIDegradationPreference2)
            FFIDegradationPreference.GET(fFIDegradationPreference3)
            res = fFIDegradationPreference1.toString() + " " + fFIDegradationPreference2.toString() + " " + fFIDegradationPreference3.toString()
        }
        let fFIRTCRtpTransceiverDirection1 = FFIRTCRtpTransceiverDirection.INACTIVE
        let fFIRTCRtpTransceiverDirection11 = FFIRTCRtpTransceiverDirection.INACTIVE
        let fFIRTCRtpTransceiverDirection2 = FFIRTCRtpTransceiverDirection.RECVONLY
        let fFIRTCRtpTransceiverDirection22 = FFIRTCRtpTransceiverDirection.RECVONLY
        let fFIRTCRtpTransceiverDirection3 = FFIRTCRtpTransceiverDirection.SENDONLY
        let fFIRTCRtpTransceiverDirection33 = FFIRTCRtpTransceiverDirection.SENDONLY
        let fFIRTCRtpTransceiverDirection4 = FFIRTCRtpTransceiverDirection.SENDRECV
        let fFIRTCRtpTransceiverDirection44 = FFIRTCRtpTransceiverDirection.SENDRECV
        let fFIRTCRtpTransceiverDirection5 = FFIRTCRtpTransceiverDirection.STOPPED
        let fFIRTCRtpTransceiverDirection55 = FFIRTCRtpTransceiverDirection.STOPPED
        if (fFIRTCRtpTransceiverDirection1 == fFIRTCRtpTransceiverDirection2) {
            flag = false
        }
        if (fFIRTCRtpTransceiverDirection1 == fFIRTCRtpTransceiverDirection1) {
            flag = false
        }
        if (fFIRTCRtpTransceiverDirection2 == fFIRTCRtpTransceiverDirection22) {
            flag = false
        }
        if (fFIRTCRtpTransceiverDirection3 == fFIRTCRtpTransceiverDirection33) {}
        if (fFIRTCRtpTransceiverDirection4 == fFIRTCRtpTransceiverDirection44) {}
        if (fFIRTCRtpTransceiverDirection5 == fFIRTCRtpTransceiverDirection55) {}
        if (fFIRTCRtpTransceiverDirection1 != fFIRTCRtpTransceiverDirection2) {
        	flag = true
            FFIRTCRtpTransceiverDirection.GET(0)
            FFIRTCRtpTransceiverDirection.GET(1)
            FFIRTCRtpTransceiverDirection.GET(2)
            FFIRTCRtpTransceiverDirection.GET(3)
            FFIRTCRtpTransceiverDirection.GET(4)
            FFIRTCRtpTransceiverDirection.GET(fFIRTCRtpTransceiverDirection1)
            FFIRTCRtpTransceiverDirection.GET(fFIRTCRtpTransceiverDirection2)
            FFIRTCRtpTransceiverDirection.GET(fFIRTCRtpTransceiverDirection3)
            FFIRTCRtpTransceiverDirection.GET(fFIRTCRtpTransceiverDirection4)
            FFIRTCRtpTransceiverDirection.GET(fFIRTCRtpTransceiverDirection5)
            res = fFIRTCRtpTransceiverDirection1.toString() + " " + fFIRTCRtpTransceiverDirection2.toString() + " " + fFIRTCRtpTransceiverDirection3.toString() + " " + fFIRTCRtpTransceiverDirection4.toString() + " " + fFIRTCRtpTransceiverDirection5.toString()
        }
        let fFIRTCSctpTransportState1 = FFIRTCSctpTransportState.CONNECTING
        let fFIRTCSctpTransportState11 = FFIRTCSctpTransportState.CONNECTING
        let fFIRTCSctpTransportState2 = FFIRTCSctpTransportState.CONNECTED
        let fFIRTCSctpTransportState22 = FFIRTCSctpTransportState.CONNECTED
        let fFIRTCSctpTransportState3 = FFIRTCSctpTransportState.CLOSED
        let fFIRTCSctpTransportState33 = FFIRTCSctpTransportState.CLOSED
        if (fFIRTCSctpTransportState1 == fFIRTCSctpTransportState2) {
            flag = false
        }
        if (fFIRTCSctpTransportState1 == fFIRTCSctpTransportState11) {
            flag = false
        }
        if (fFIRTCSctpTransportState2 == fFIRTCSctpTransportState22) {
            flag = false
        }
        if (fFIRTCSctpTransportState3 == fFIRTCSctpTransportState33) {}
        if (fFIRTCSctpTransportState1 != fFIRTCSctpTransportState2) {
        	flag = true
            FFIRTCSctpTransportState.GET(0)
            FFIRTCSctpTransportState.GET(1)
            FFIRTCSctpTransportState.GET(2)
            FFIRTCSctpTransportState.GET(fFIRTCSctpTransportState1)
            FFIRTCSctpTransportState.GET(fFIRTCSctpTransportState2)
            FFIRTCSctpTransportState.GET(fFIRTCSctpTransportState3)
            res = fFIRTCRtpTransceiverDirection1.toString() + " " + fFIRTCSctpTransportState2.toString() + " " + fFIRTCSctpTransportState3.toString()
        }
        let fFIRTCStatsType1 = FFIRTCStatsType.CANDIDATE_PAIR
        let fFIRTCStatsType11 = FFIRTCStatsType.CANDIDATE_PAIR
        let fFIRTCStatsType2 = FFIRTCStatsType.CERTIFICATE
        let fFIRTCStatsType22 = FFIRTCStatsType.CERTIFICATE
        let fFIRTCStatsType3 = FFIRTCStatsType.CODEC
        let fFIRTCStatsType33 = FFIRTCStatsType.CODEC
        let fFIRTCStatsType4 = FFIRTCStatsType.DATA_CHANNEL
        let fFIRTCStatsType44 = FFIRTCStatsType.DATA_CHANNEL
        let fFIRTCStatsType5 = FFIRTCStatsType.INBOUND_RTP
        let fFIRTCStatsType55 = FFIRTCStatsType.INBOUND_RTP
        let fFIRTCStatsType6 = FFIRTCStatsType.LOCAL_CANDIDATE
        let fFIRTCStatsType66 = FFIRTCStatsType.LOCAL_CANDIDATE
        let fFIRTCStatsType7 = FFIRTCStatsType.MEDIA_PLAYOUT
        let fFIRTCStatsType77 = FFIRTCStatsType.MEDIA_PLAYOUT
        let fFIRTCStatsType8 = FFIRTCStatsType.MEDIA_SOURCE
        let fFIRTCStatsType88 = FFIRTCStatsType.MEDIA_SOURCE
        let fFIRTCStatsType9 = FFIRTCStatsType.OUTBOUND_RTP
        let fFIRTCStatsType99 = FFIRTCStatsType.OUTBOUND_RTP
        let fFIRTCStatsType10 = FFIRTCStatsType.PEER_CONNECTION
        let fFIRTCStatsType100 = FFIRTCStatsType.PEER_CONNECTION
        let fFIRTCStatsType101 = FFIRTCStatsType.REMOTE_CANDIDATE
        let fFIRTCStatsType111 = FFIRTCStatsType.REMOTE_CANDIDATE
        let fFIRTCStatsType12 = FFIRTCStatsType.REMOTE_INBOUND_RTP
        let fFIRTCStatsType122 = FFIRTCStatsType.REMOTE_INBOUND_RTP
        let fFIRTCStatsType13 = FFIRTCStatsType.REMOTE_OUTBOUND_RTP
        let fFIRTCStatsType133 = FFIRTCStatsType.REMOTE_OUTBOUND_RTP
        let fFIRTCStatsType14 = FFIRTCStatsType.TRANSPORT
        let fFIRTCStatsType144 = FFIRTCStatsType.TRANSPORT
        if (fFIRTCStatsType1 == fFIRTCStatsType2) {
            flag = false
        }
        if (fFIRTCStatsType1 == fFIRTCStatsType11) {
            flag = false
        }
        if (fFIRTCStatsType2 == fFIRTCStatsType22) {
            flag = false
        }
        if (fFIRTCStatsType3 == fFIRTCStatsType33) {}
        if (fFIRTCStatsType4 == fFIRTCStatsType44) {}
        if (fFIRTCStatsType5 == fFIRTCStatsType55) {}
        if (fFIRTCStatsType6 == fFIRTCStatsType66) {}
        if (fFIRTCStatsType7 == fFIRTCStatsType77) {}
        if (fFIRTCStatsType8 == fFIRTCStatsType88) {}
        if (fFIRTCStatsType9 == fFIRTCStatsType99) {}
        if (fFIRTCStatsType10 == fFIRTCStatsType100) {}
        if (fFIRTCStatsType101 == fFIRTCStatsType111) {}
        if (fFIRTCStatsType12 == fFIRTCStatsType122) {}
        if (fFIRTCStatsType13 == fFIRTCStatsType133) {}
        if (fFIRTCStatsType14 == fFIRTCStatsType144) {}
        if (fFIRTCStatsType1 != fFIRTCStatsType2) {
        	flag = true
            FFIRTCStatsType.GET(0)
            FFIRTCStatsType.GET(1)
            FFIRTCStatsType.GET(2)
            FFIRTCStatsType.GET(3)
            FFIRTCStatsType.GET(4)
            FFIRTCStatsType.GET(5)
            FFIRTCStatsType.GET(6)
            FFIRTCStatsType.GET(7)
            FFIRTCStatsType.GET(8)
            FFIRTCStatsType.GET(9)
            FFIRTCStatsType.GET(10)
            FFIRTCStatsType.GET(11)
            FFIRTCStatsType.GET(12)
            FFIRTCStatsType.GET(13)
            FFIRTCStatsType.GET(fFIRTCStatsType1)
            FFIRTCStatsType.GET(fFIRTCStatsType2)
            FFIRTCStatsType.GET(fFIRTCStatsType3)
            FFIRTCStatsType.GET(fFIRTCStatsType4)
            FFIRTCStatsType.GET(fFIRTCStatsType5)
            FFIRTCStatsType.GET(fFIRTCStatsType6)
            FFIRTCStatsType.GET(fFIRTCStatsType7)
            FFIRTCStatsType.GET(fFIRTCStatsType8)
            FFIRTCStatsType.GET(fFIRTCStatsType9)
            FFIRTCStatsType.GET(fFIRTCStatsType10)
            FFIRTCStatsType.GET(fFIRTCStatsType101)
            FFIRTCStatsType.GET(fFIRTCStatsType12)
            FFIRTCStatsType.GET(fFIRTCStatsType13)
            FFIRTCStatsType.GET(fFIRTCStatsType14)
            res = fFIRTCStatsType1.toString() + " " + fFIRTCStatsType2.toString() + " " + fFIRTCStatsType3.toString() + " " + fFIRTCStatsType4.toString()
            res = res + " " + fFIRTCStatsType5.toString() + " " + fFIRTCStatsType6.toString() + " " + fFIRTCStatsType7.toString() + " " + fFIRTCStatsType8.toString() + " " + fFIRTCStatsType9.toString() + " " + fFIRTCStatsType10.toString() + " " + fFIRTCStatsType101.toString() + " " + fFIRTCStatsType12.toString() + " " + fFIRTCStatsType13.toString() + " " + fFIRTCStatsType14.toString()
        }
        let fFIrtcstatsicecandidatepairstate1 = FFIrtcstatsicecandidatepairstate.FAILED
        let fFIrtcstatsicecandidatepairstate11 = FFIrtcstatsicecandidatepairstate.FAILED
        let fFIrtcstatsicecandidatepairstate2 = FFIrtcstatsicecandidatepairstate.FROZEN
        let fFIrtcstatsicecandidatepairstate22 = FFIrtcstatsicecandidatepairstate.FROZEN
        let fFIrtcstatsicecandidatepairstate3 = FFIrtcstatsicecandidatepairstate.IN_PROGRESS
        let fFIrtcstatsicecandidatepairstate33 = FFIrtcstatsicecandidatepairstate.IN_PROGRESS
        let fFIrtcstatsicecandidatepairstate4 = FFIrtcstatsicecandidatepairstate.SUCCEEDED
        let fFIrtcstatsicecandidatepairstate44 = FFIrtcstatsicecandidatepairstate.SUCCEEDED
        let fFIrtcstatsicecandidatepairstate5 = FFIrtcstatsicecandidatepairstate.WAITING
        let fFIrtcstatsicecandidatepairstate55 = FFIrtcstatsicecandidatepairstate.WAITING
        if (fFIrtcstatsicecandidatepairstate1 == fFIrtcstatsicecandidatepairstate2) {
            flag = false
        }
        if (fFIrtcstatsicecandidatepairstate1 == fFIrtcstatsicecandidatepairstate11) {
            flag = false
        }
        if (fFIrtcstatsicecandidatepairstate2 == fFIrtcstatsicecandidatepairstate22) {
            flag = false
        }
        if (fFIrtcstatsicecandidatepairstate3 == fFIrtcstatsicecandidatepairstate33) {}
        if (fFIrtcstatsicecandidatepairstate4 == fFIrtcstatsicecandidatepairstate44) {}
        if (fFIrtcstatsicecandidatepairstate5 == fFIrtcstatsicecandidatepairstate55) {}
        if (fFIrtcstatsicecandidatepairstate1 != fFIrtcstatsicecandidatepairstate2) {
        	flag = true
            FFIrtcstatsicecandidatepairstate.GET(0)
            FFIrtcstatsicecandidatepairstate.GET(1)
            FFIrtcstatsicecandidatepairstate.GET(2)
            FFIrtcstatsicecandidatepairstate.GET(3)
            FFIrtcstatsicecandidatepairstate.GET(4)
            FFIrtcstatsicecandidatepairstate.GET(fFIrtcstatsicecandidatepairstate1)
            FFIrtcstatsicecandidatepairstate.GET(fFIrtcstatsicecandidatepairstate2)
            FFIrtcstatsicecandidatepairstate.GET(fFIrtcstatsicecandidatepairstate3)
            FFIrtcstatsicecandidatepairstate.GET(fFIrtcstatsicecandidatepairstate4)
            FFIrtcstatsicecandidatepairstate.GET(fFIrtcstatsicecandidatepairstate5)
            res = fFIrtcstatsicecandidatepairstate1.toString() + " " + fFIrtcstatsicecandidatepairstate2.toString() + " " + fFIrtcstatsicecandidatepairstate3.toString() + " " + fFIrtcstatsicecandidatepairstate4.toString() + " " + fFIrtcstatsicecandidatepairstate5.toString()
        }
        let fFIMediaStreamTrackState1 = FFIMediaStreamTrackState.ENDED
        let fFIMediaStreamTrackState11 = FFIMediaStreamTrackState.ENDED
        let fFIMediaStreamTrackState2 = FFIMediaStreamTrackState.LIVE
        let fFIMediaStreamTrackState22 = FFIMediaStreamTrackState.LIVE
        if (fFIMediaStreamTrackState1 == fFIMediaStreamTrackState2) {
            flag = false
        }
        if (fFIMediaStreamTrackState1 == fFIMediaStreamTrackState11) {
            flag = false
        }
        if (fFIMediaStreamTrackState2 == fFIMediaStreamTrackState22) {
            flag = false
        }
        if (fFIMediaStreamTrackState1 != fFIMediaStreamTrackState2) {
        	flag = true
            FFIMediaStreamTrackState.GET(0)
            FFIMediaStreamTrackState.GET(1)
            FFIMediaStreamTrackState.GET(fFIMediaStreamTrackState1)
            FFIMediaStreamTrackState.GET(fFIMediaStreamTrackState2)
            res = fFIMediaStreamTrackState1.toString() + " " + fFIMediaStreamTrackState2.toString()
        }
        let fFIMediaDeviceKind1 = FFIMediaDeviceKind.AUDIOINPUT
        let fFIMediaDeviceKind11 = FFIMediaDeviceKind.AUDIOINPUT
        let fFIMediaDeviceKind2 = FFIMediaDeviceKind.AUDIOOUTPUT
        let fFIMediaDeviceKind22 = FFIMediaDeviceKind.AUDIOOUTPUT
        let fFIMediaDeviceKind3 = FFIMediaDeviceKind.VIDEOINPUT
        let fFIMediaDeviceKind33 = FFIMediaDeviceKind.VIDEOINPUT
        if (fFIMediaDeviceKind1 == fFIMediaDeviceKind2) {
            flag = false
        }
        if (fFIMediaDeviceKind1 == fFIMediaDeviceKind11) {
            flag = false
        }
        if (fFIMediaDeviceKind2 == fFIMediaDeviceKind22) {
            flag = false
        }
        if (fFIMediaDeviceKind3 == fFIMediaDeviceKind33) {}
        if (fFIMediaDeviceKind1 != fFIMediaDeviceKind2) {
        	flag = true
            FFIMediaDeviceKind.GET(0)
            FFIMediaDeviceKind.GET(1)
            FFIMediaDeviceKind.GET(2)
            FFIMediaDeviceKind.GET(fFIMediaDeviceKind1)
            FFIMediaDeviceKind.GET(fFIMediaDeviceKind2)
            FFIMediaDeviceKind.GET(fFIMediaDeviceKind3)
            res = fFIMediaDeviceKind1.toString() + " " + fFIMediaDeviceKind2.toString() + " " + fFIMediaDeviceKind3.toString()
        }
        let fFIMediaSourceState1 = FFIMediaSourceState.INITIALIZING
        let fFIMediaSourceState11 = FFIMediaSourceState.INITIALIZING
        let fFIMediaSourceState2 = FFIMediaSourceState.LIVE
        let fFIMediaSourceState22 = FFIMediaSourceState.LIVE
        let fFIMediaSourceState3 = FFIMediaSourceState.ENDED
        let fFIMediaSourceState33 = FFIMediaSourceState.ENDED
        let fFIMediaSourceState4 = FFIMediaSourceState.MUTED
        let fFIMediaSourceState44 = FFIMediaSourceState.MUTED
        if (fFIMediaSourceState1 == fFIMediaSourceState2) {
            flag = false
        }
        if (fFIMediaSourceState1 == fFIMediaSourceState11) {
            flag = false
        }
        if (fFIMediaSourceState2 == fFIMediaSourceState22) {
            flag = false
        }
        if (fFIMediaSourceState3 == fFIMediaSourceState33) {}
        if (fFIMediaSourceState4 == fFIMediaSourceState44) {}
        if (fFIMediaSourceState1 != fFIMediaSourceState2) {
        	flag = true
            FFIMediaSourceState.GET(0)
            FFIMediaSourceState.GET(1)
            FFIMediaSourceState.GET(2)
            FFIMediaSourceState.GET(3)
            FFIMediaSourceState.GET(fFIMediaSourceState1)
            FFIMediaSourceState.GET(fFIMediaSourceState2)
            FFIMediaSourceState.GET(fFIMediaSourceState3)
            FFIMediaSourceState.GET(fFIMediaSourceState4)
            res = fFIMediaSourceState1.toString() + " " + fFIMediaSourceState2.toString() + " " + fFIMediaSourceState3.toString() + " " + fFIMediaSourceState4.toString()
        }
        let fFIVideoFacingModeEnum1 = FFIVideoFacingModeEnum.USER
        let fFIVideoFacingModeEnum11 = FFIVideoFacingModeEnum.USER
        let fFIVideoFacingModeEnum2 = FFIVideoFacingModeEnum.ENVIRONMENT
        let fFIVideoFacingModeEnum22 = FFIVideoFacingModeEnum.ENVIRONMENT
        let fFIVideoFacingModeEnum3 = FFIVideoFacingModeEnum.LEFT
        let fFIVideoFacingModeEnum33 = FFIVideoFacingModeEnum.LEFT
        let fFIVideoFacingModeEnum4 = FFIVideoFacingModeEnum.RIGHT
        let fFIVideoFacingModeEnum44 = FFIVideoFacingModeEnum.RIGHT
        if (fFIVideoFacingModeEnum1 == fFIVideoFacingModeEnum2) {
            flag = false
        }
        if (fFIVideoFacingModeEnum1 == fFIVideoFacingModeEnum11) {
            flag = false
        }
        if (fFIVideoFacingModeEnum2 == fFIVideoFacingModeEnum22) {
            flag = false
        }
        if (fFIVideoFacingModeEnum3 == fFIVideoFacingModeEnum33) {}
        if (fFIVideoFacingModeEnum4 == fFIVideoFacingModeEnum44) {}
        if (fFIVideoFacingModeEnum1 != fFIVideoFacingModeEnum2) {
        	flag = true
            FFIVideoFacingModeEnum.GET(0)
            FFIVideoFacingModeEnum.GET(1)
            FFIVideoFacingModeEnum.GET(2)
            FFIVideoFacingModeEnum.GET(3)
            FFIVideoFacingModeEnum.GET(fFIVideoFacingModeEnum1)
            FFIVideoFacingModeEnum.GET(fFIVideoFacingModeEnum2)
            FFIVideoFacingModeEnum.GET(fFIVideoFacingModeEnum3)
            FFIVideoFacingModeEnum.GET(fFIVideoFacingModeEnum4)
            res = fFIVideoFacingModeEnum1.toString() + " " + fFIVideoFacingModeEnum2.toString() + " " + fFIVideoFacingModeEnum3.toString() + " " + fFIVideoFacingModeEnum4.toString()
        }
        let fFIVideoResizeModeEnum1 = FFIVideoResizeModeEnum.CROP_AND_SCALE
        let fFIVideoResizeModeEnum11 = FFIVideoResizeModeEnum.CROP_AND_SCALE
        let fFIVideoResizeModeEnum2 = FFIVideoResizeModeEnum.NONE
        let fFIVideoResizeModeEnum22 = FFIVideoResizeModeEnum.NONE
        if (fFIVideoResizeModeEnum1 == fFIVideoResizeModeEnum2) {
            flag = false
        }
        if (fFIVideoResizeModeEnum1 == fFIVideoResizeModeEnum11) {
            flag = false
        }
        if (fFIVideoResizeModeEnum2 == fFIVideoResizeModeEnum22) {
            flag = false
        }
        if (fFIVideoResizeModeEnum1 != fFIVideoResizeModeEnum2) {
        	flag = true
            FFIVideoResizeModeEnum.GET(0)
            FFIVideoResizeModeEnum.GET(1)
            FFIVideoResizeModeEnum.GET(fFIVideoResizeModeEnum1)
            FFIVideoResizeModeEnum.GET(fFIVideoResizeModeEnum2)
            res = fFIVideoResizeModeEnum1.toString() + " " + fFIVideoResizeModeEnum2.toString()
        }
        let fFIAudioErrorType1 = FFIAudioErrorType.INIT
        let fFIAudioErrorType11 = FFIAudioErrorType.INIT
        let fFIAudioErrorType2 = FFIAudioErrorType.START_EXCEPTION
        let fFIAudioErrorType22 = FFIAudioErrorType.START_EXCEPTION
        let fFIAudioErrorType3 = FFIAudioErrorType.START_STATE_MISMATCH
        let fFIAudioErrorType33 = FFIAudioErrorType.START_STATE_MISMATCH
        let fFIAudioErrorType4 = FFIAudioErrorType.GENERAL
        let fFIAudioErrorType44 = FFIAudioErrorType.GENERAL
        if (fFIAudioErrorType1 == fFIAudioErrorType2) {
            flag = false
        }
        if (fFIAudioErrorType1 == fFIAudioErrorType11) {
            flag = false
        }
        if (fFIAudioErrorType2 == fFIAudioErrorType22) {
            flag = false
        }
        if (fFIAudioErrorType3 == fFIAudioErrorType33) {}
        if (fFIAudioErrorType4 == fFIAudioErrorType44) {}
        if (fFIAudioErrorType1 != fFIAudioErrorType2) {
        	flag = true
            FFIAudioErrorType.GET(0)
            FFIAudioErrorType.GET(1)
            FFIAudioErrorType.GET(2)
            FFIAudioErrorType.GET(3)
            FFIAudioErrorType.GET(fFIAudioErrorType1)
            FFIAudioErrorType.GET(fFIAudioErrorType2)
            FFIAudioErrorType.GET(fFIAudioErrorType3)
            FFIAudioErrorType.GET(fFIAudioErrorType4)
            res = fFIAudioErrorType1.toString() + " " + fFIAudioErrorType2.toString() + " " + fFIAudioErrorType3.toString() + " " + fFIAudioErrorType4.toString()
        }
        let fFIAudioState1 = FFIAudioState.STOP
        let fFIAudioState11 = FFIAudioState.STOP
        let fFIAudioState2 = FFIAudioState.START
        let fFIAudioState22 = FFIAudioState.START
        if (fFIAudioState1 == fFIAudioState2) {
            flag = false
        }
        if (fFIAudioState1 == fFIAudioState11) {
            flag = false
        }
        if (fFIAudioState2 == fFIAudioState22) {
            flag = false
        }
        if (fFIAudioState1 != fFIAudioState2) {
        	flag = true
            FFIAudioState.GET(0)
            FFIAudioState.GET(1)
            FFIAudioState.GET(fFIAudioState1)
            FFIAudioState.GET(fFIAudioState2)
            res = fFIAudioState2.toString() + " " + fFIAudioState2.toString()
        }
        let fFIScreenCaptureMode1 = FFIScreenCaptureMode.HOME_SCREEN
        let fFIScreenCaptureMode11 = FFIScreenCaptureMode.HOME_SCREEN
        let fFIScreenCaptureMode2 = FFIScreenCaptureMode.SPECIFIED_SCREEN
        let fFIScreenCaptureMode22 = FFIScreenCaptureMode.SPECIFIED_SCREEN
        let fFIScreenCaptureMode3 = FFIScreenCaptureMode.SPECIFIED_WINDOW
        let fFIScreenCaptureMode33 = FFIScreenCaptureMode.SPECIFIED_WINDOW
        if (fFIScreenCaptureMode1 == fFIScreenCaptureMode2) {
            flag = false
        }
        if (fFIScreenCaptureMode1 == fFIScreenCaptureMode11) {
            flag = false
        }
        if (fFIScreenCaptureMode2 == fFIScreenCaptureMode22) {
            flag = false
        }
        if (fFIScreenCaptureMode3 == fFIScreenCaptureMode33) {}
        if (fFIScreenCaptureMode1 != fFIScreenCaptureMode2) {
        	flag = true
            FFIScreenCaptureMode.GET(0)
            FFIScreenCaptureMode.GET(1)
            FFIScreenCaptureMode.GET(2)
            FFIScreenCaptureMode.GET(fFIScreenCaptureMode1)
            FFIScreenCaptureMode.GET(fFIScreenCaptureMode2)
            FFIScreenCaptureMode.GET(fFIScreenCaptureMode3)
            res = fFIScreenCaptureMode1.toString() + " " + fFIScreenCaptureMode2.toString() + " " + fFIScreenCaptureMode3.toString()
        }
        let fFIScreenCaptureAudioFilterEnum1 = FFIScreenCaptureAudioFilterEnum.NOTIFICATION
        let fFIScreenCaptureAudioFilterEnum11 = FFIScreenCaptureAudioFilterEnum.NOTIFICATION
        let fFIScreenCaptureAudioFilterEnum2 = FFIScreenCaptureAudioFilterEnum.CURRENT_APP
        let fFIScreenCaptureAudioFilterEnum22 = FFIScreenCaptureAudioFilterEnum.CURRENT_APP
        if (fFIScreenCaptureAudioFilterEnum1 == fFIScreenCaptureAudioFilterEnum2) {
            flag = false
        }
        if (fFIScreenCaptureAudioFilterEnum1 == fFIScreenCaptureAudioFilterEnum11) {
            flag = false
        }
        if (fFIScreenCaptureAudioFilterEnum2 == fFIScreenCaptureAudioFilterEnum22) {
            flag = false
        }
        if (fFIScreenCaptureAudioFilterEnum1 != fFIScreenCaptureAudioFilterEnum2) {
        	flag = true
            FFIScreenCaptureAudioFilterEnum.GET(0)
            FFIScreenCaptureAudioFilterEnum.GET(1)
            FFIScreenCaptureAudioFilterEnum.GET(fFIScreenCaptureAudioFilterEnum1)
            FFIScreenCaptureAudioFilterEnum.GET(fFIScreenCaptureAudioFilterEnum2)
            res = fFIScreenCaptureAudioFilterEnum1.toString() + " " + fFIScreenCaptureAudioFilterEnum2.toString()
        }
        let fFIScalingModeEnum1 = FFIScalingModeEnum.ASPECTFILL
        let fFIScalingModeEnum11 = FFIScalingModeEnum.ASPECTFILL
        let fFIScalingModeEnum2 = FFIScalingModeEnum.ASPECTFIT
        let fFIScalingModeEnum22 = FFIScalingModeEnum.ASPECTFIT
        let fFIScalingModeEnum3 = FFIScalingModeEnum.FILL
        let fFIScalingModeEnum33 = FFIScalingModeEnum.FILL
        if (fFIScalingModeEnum1 == fFIScalingModeEnum2) {
            flag = false
        }
        if (fFIScalingModeEnum1 == fFIScalingModeEnum11) {
            flag = false
        }
        if (fFIScalingModeEnum2 == fFIScalingModeEnum22) {
            flag = false
        }
        if (fFIScalingModeEnum3 == fFIScalingModeEnum33) {
            flag = false
        }
        if (fFIScalingModeEnum1 != fFIScalingModeEnum2) {
        	flag = true
            FFIScalingModeEnum.GET(0)
            FFIScalingModeEnum.GET(1)
            FFIScalingModeEnum.GET(2)
            FFIScalingModeEnum.GET(fFIScalingModeEnum1)
            FFIScalingModeEnum.GET(fFIScalingModeEnum2)
            FFIScalingModeEnum.GET(fFIScalingModeEnum3)
            res = fFIScalingModeEnum1.toString() + " " + fFIScalingModeEnum2.toString() + " " + fFIScalingModeEnum3.toString()
        }
        let dataChannelState1 = DataChannelState.GET(0)
        let dataChannelState2 = DataChannelState.GET(1)
        let dataChannelState3 = DataChannelState.GET(2)
        let dataChannelState4 = DataChannelState.GET(3)
        let dataChannelState11 = DataChannelState.GET(dataChannelState1)
        let dataChannelState22 = DataChannelState.GET(dataChannelState2)
        let dataChannelState33 = DataChannelState.GET(dataChannelState3)
        let dataChannelState44 = DataChannelState.GET(dataChannelState4)
        let binaryType1 = BinaryType.GET(0)
        let binaryType2 = BinaryType.GET(1)
        let binaryType11 = BinaryType.GET(binaryType1)
        let binaryType22 = BinaryType.GET(binaryType2)
        let rc1 = RTCRtpReceiver(10)
        let rs1 = RTCSctpTransport(99)
        let webRtcGlobal_id = WebRtcGlobal.getCurrentId()
        let global_1: WebRtcGlobal = WebRtcGlobal()
    }
}
