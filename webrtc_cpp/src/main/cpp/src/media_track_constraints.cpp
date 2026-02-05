/**
 * Copyright (c) Huawei Technologies Co., Ltd. 2024-2025. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "media_track_constraints.h"

#include <map>
#include <sstream>
#include <vector>

#include "rtc_base/strings/string_builder.h"
#include "rtc_base/logging.h"

namespace webrtc {


// A naked value is treated as an "ideal" value in the basic constraints,
// but as an exact value in "advanced" constraints.
// https://www.w3.org/TR/mediacapture-streams/#constrainable-interface
enum class NakedValueDisposition {
    kTreatAsIdeal,
    kTreatAsExact
};

const size_t kMaxConstraintStringLength = 500;
const size_t kMaxConstraintStringSeqLength = 100;

const char kConstraintsMin[] = "min";
const char kConstraintsMax[] = "max";
const char kConstraintsExact[] = "exact";
const char kConstraintsIdeal[] = "ideal";
const char kConstraintsAdvanced[] = "advanced";

const std::map<std::string, bool> SUPPORTED_CONSTRAINTS_MAP = {
    {NapiMediaConstraints::kAttributeNameWidth, true},
    {NapiMediaConstraints::kAttributeNameHeight, true},
    {NapiMediaConstraints::kAttributeNameAspectRatio, true},
    {NapiMediaConstraints::kAttributeNameFrameRate, true},
    {NapiMediaConstraints::kAttributeNameFacingMode, true},
    {NapiMediaConstraints::kAttributeNameResizeMode, false},
    {NapiMediaConstraints::kAttributeNameSampleRate, false},
    {NapiMediaConstraints::kAttributeNameSampleSize, false},
    {NapiMediaConstraints::kAttributeNameEchoCancellation, true},
    {NapiMediaConstraints::kAttributeNameAutoGainControl, true},
    {NapiMediaConstraints::kAttributeNameNoiseSuppression, true},
    {NapiMediaConstraints::kAttributeNameLatency, false},
    {NapiMediaConstraints::kAttributeNameChannelCount, false},
    {NapiMediaConstraints::kAttributeNameDeviceId, true},
    {NapiMediaConstraints::kAttributeNameGroupId, true},
    {NapiMediaConstraints::kAttributeNameDisplaySurface, false},
    {NapiMediaConstraints::kAttributeNameBackgroundBlur, false},
    {NapiMediaConstraints::kAttributeNameGoogEchoCancellation, false},
    {NapiMediaConstraints::kAttributeNameGoogAutoGainControl, false},
    {NapiMediaConstraints::kAttributeNameGoogNoiseSuppression, false},
    {NapiMediaConstraints::kAttributeNameGoogHighpassFilter, false},
    {NapiMediaConstraints::kAttributeNameGoogAudioMirroring, false},
    {NapiMediaConstraints::kAttributeNameOhosScreenCaptureMode, true},
    {NapiMediaConstraints::kAttributeNameOhosScreenCaptureDisplayId, true},
    {NapiMediaConstraints::kAttributeNameOhosScreenCaptureMissionId, true},
    {NapiMediaConstraints::kAttributeNameOhosScreenCaptureAudioFilter, true},
    {NapiMediaConstraints::kAttributeNameOhosScreenCaptureWindowFilter, true},
    {NapiMediaConstraints::kAttributeNameOhosScreenCaptureSkipPrivacyMode, true},
    {NapiMediaConstraints::kAttributeNameOhosScreenCaptureAutoRotation, true},
};

bool IsConstraintSupported(const std::string& name)
{
    auto it = SUPPORTED_CONSTRAINTS_MAP.find(name);
    if (it != SUPPORTED_CONSTRAINTS_MAP.end()) {
        return it->second;
    }
    return true;
}




bool ValidateString(const std::string& str, std::string& errorMessage)
{
    if (str.length() > kMaxConstraintStringLength) {
        errorMessage = "Constraint string too long.";
        return false;
    }
    return true;
}

bool ValidateStringSeq(const std::vector<std::string>& strs, std::string& errorMessage)
{
    if (strs.size() > kMaxConstraintStringSeqLength) {
        errorMessage = "Constraint string sequence too long.";
        return false;
    }

    for (const std::string& str : strs) {
        if (!ValidateString(str, errorMessage)) {
            return false;
        }
    }

    return true;
}

std::vector<std::string> NapiMediaConstraints::GetSupportedConstraints()
{
    std::vector<std::string> result;
    for (const auto& constraints : SUPPORTED_CONSTRAINTS_MAP) {
        if (constraints.second) {
            result.push_back(constraints.first);
        }
    }
    return result;
}

bool NapiMediaConstraints::IsConstraintSupported(const std::string& name)
{
    return ::webrtc::IsConstraintSupported(name);
}


} // namespace webrtc
