package ohos_app_cangjie_entry_test.LLT

import ohos_app_cangjie_entry_test.unittest_support.registerTestSuite
internal import webrtc_cj.*

private let register = testsuite()

func testsuite() {
    registerTestSuite { WebRTCTest() }
}