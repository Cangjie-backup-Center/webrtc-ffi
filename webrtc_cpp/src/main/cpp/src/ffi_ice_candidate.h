#ifndef WEBRTC4CJ_FFI_ICE_CANDIDATE_H
#define WEBRTC4CJ_FFI_ICE_CANDIDATE_H

#include "api/jsep_ice_candidate.h"
#include "ffi_define_struct.h"
#include <cstdint>
#include "api/data_channel_interface.h"
#include "api/jsep.h"
#include "api/jsep_ice_candidate.h"
#include "api/peer_connection_interface.h"
#include "api/rtp_parameters.h"
#include "rtc_base/ssl_identity.h"


namespace webrtc {


CJ_RTCIceCandidate CJToRTCPeerConnectionIceEvent(const std::string& sdpMid,
                    int32_t sdpMLineIndex, 
                    const std::string& sdp,
                    const cricket::Candidate& candidate);

} // namespace webrtc


#endif // WEBRTC4CJ_FFI_ICE_CANDIDATE_H

