#include "ffi_ice_candidate.h"
#define KCOMPONENT_ID_RTP 1
#define KCOMPONENT_ID_RTCP 2


namespace webrtc {
char cjkEnumIceCandidateRtp[] = "rtp";
char cjkEnumIceCandidateRtcp[] = "rtcp";

char cjkEnumIceCandidateTypeHost[] = "host";
char cjkEnumIceCandidateTypeSrflx[] = "srflx";
char cjkEnumIceCandidateTypePrflx[] = "prflx";
char cjkEnumIceCandidateTypeRelay[] = "relay";

std::optional<CJToCppCandidateObject*> CJToCppCandidate(const std::string& sdpMid,
                    int32_t sdpMLineIndex, 
                    const std::string& sdp,
                    const cricket::Candidate& candidate) 
{
    if (sdp.empty()) {
        RTC_LOG(LS_ERROR) << "got an empty ICE candidate";
        return nullptr;
    }

    CJToCppCandidateObject* obj = new CJToCppCandidateObject();
    obj->sdpMLineIndex = sdpMLineIndex;
    obj->sdpMid = strdup(sdpMid.c_str());
    obj->candidate = strdup(sdp.c_str());
    obj->foundation = strdup(candidate.foundation().c_str());
    if (candidate.component() == KCOMPONENT_ID_RTP) {
        obj->component = strdup(cjkEnumIceCandidateRtp);
    } 
    if (candidate.component() == KCOMPONENT_ID_RTCP) {
        obj->component = strdup(cjkEnumIceCandidateRtcp);
    }
    
    obj->priority = candidate.priority();
    obj->address = strdup(candidate.address().hostname().c_str());
    obj->protocol = strdup(candidate.protocol().c_str());
    obj->port = candidate.address().port();
    obj->tcpType = strdup(candidate.tcptype().c_str());
    obj->relatedAddress = strdup(candidate.related_address().hostname().c_str());
    obj->relatedPort = candidate.related_address().port();
    obj->usernameFragment = strdup(candidate.username().c_str());

    if (candidate.type() == cricket::LOCAL_PORT_TYPE) {
        obj->type = cjkEnumIceCandidateTypeHost;
    } else if (candidate.type() == cricket::STUN_PORT_TYPE) {
        obj->type = cjkEnumIceCandidateTypeSrflx;
    } else if (candidate.type() == cricket::RELAY_PORT_TYPE) {
        obj->type = cjkEnumIceCandidateTypeRelay;
    } else if (candidate.type() == cricket::PRFLX_PORT_TYPE) {
        obj->type = cjkEnumIceCandidateTypePrflx;
    } else {
        // invalid type
    }

    // extension attribute
    obj->adapterType = strdup(rtc::AdapterTypeToString(candidate.network_type()).c_str());
    obj->serverUrl = strdup(candidate.url().c_str());

    return obj;
}


}

