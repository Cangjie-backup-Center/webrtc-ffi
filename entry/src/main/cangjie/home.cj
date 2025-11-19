/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package ohos_app_cangjie_entry

import ohos.state_macro_manage.*
import ohos.router.Router

@Entry
@Component
class Home {
    func build() {
        Flex(FlexParams(direction: FlexDirection.Column)) {
            Text('摄像头用例测试')
                .width(100.percent)
                .height(60)
                .fontColor(0xffffff)
                .fontSize(30)
                .textAlign(TextAlign.Center)
                .margin(top: 10)
                .onClick({
                    event => Router.push(url: "TestCamera")
                })
                .id("Cover_Camera")
            Text('桌面共享用例测试')
                .width(100.percent)
                .height(60)
                .fontColor(0xffffff)
                .fontSize(30)
                .textAlign(TextAlign.Center)
                .margin(top: 10)
                .onClick({
                    event => Router.push(url: "TestDesktop")
                })
                .id("Cover_Desktop")
            Text('桌面共享用例测试_对端')
                .width(100.percent)
                .height(60)
                .fontColor(0xffffff)
                .fontSize(30)
                .textAlign(TextAlign.Center)
                .margin(top: 10)
                .onClick({
                    event => Router.push(url: "TestDesktop2")
                })
                .id("Cover_Desktop")
            Text('枚举类覆盖率测试')
                .width(100.percent)
                .height(60)
                .fontColor(0xffffff)
                .fontSize(30)
                .textAlign(TextAlign.Center)
                .margin(top: 10)
                .onClick({
                    event => Router.push(url: "TestEnum")
                })
                .id("Cover_Enum")

            Text('cj_func和define_class测试')
                .width(100.percent)
                .height(60)
                .fontColor(0xffffff)
                .fontSize(30)
                .textAlign(TextAlign.Center)
                .margin(top: 10)
                .onClick({
                    event => Router.push(url: "TestFuncAndClass")
                })
                .id("Cover_func_and_class")

            Text('event测试')
                .width(100.percent)
                .height(60)
                .fontColor(0xffffff)
                .fontSize(30)
                .textAlign(TextAlign.Center)
                .margin(top: 10)
                .onClick({
                    event => Router.push(url: "TestEvent")
                })
                .id("Cover_event")

            Text('FFI测试')
                .width(100.percent)
                .height(60)
                .fontColor(0xffffff)
                .fontSize(30)
                .textAlign(TextAlign.Center)
                .margin(top: 10)
                .onClick({
                    event => Router.push(url: "TestFFI")
                })
                .id("Cover_FFI")

        }.backgroundColor(0x000000)
    }
}

