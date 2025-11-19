package ohos_app_cangjie_entry_test.LLT

import std.unittest.*
import std.unittest.common.*
import std.unittest.testmacro.*
import ohos.ui_test.*

@Test
class WebRTCTest {
    @TestCase
    func testCamera(): Unit {
        let driver = Driver.create()
        let componentButton1 = driver.findComponent(On().id("Cover_Camera"))
        componentButton1.click()
        driver.delayMs(10000)
        driver.pressBack()
        driver.delayMs(1000)
    }

    @TestCase
    func testDesktop(): Unit {
        let driver = Driver.create()
        let componentButton1 = driver.findComponent(On().id("Cover_Desktop"))
        componentButton1.click()
        driver.delayMs(3000)
        let componentButton2 = driver.findComponent(On().id("connect"))
        componentButton2.click()
        driver.delayMs(20000)
        driver.pressBack()
        driver.delayMs(1000)
    }

    @TestCase
    func testEnum(): Unit {
        let driver = Driver.create()
        let componentButton1 = driver.findComponent(On().id("Cover_Enum"))
        componentButton1.click()
        driver.delayMs(7000)
        driver.pressBack()
        driver.delayMs(1000)
    }

    @TestCase
    func testFunc_And_Class(): Unit {
        let driver = Driver.create()
        let componentButton1 = driver.findComponent(On().id("Cover_func_and_class"))
        componentButton1.click()
        driver.delayMs(5000)
        driver.pressBack()
        driver.delayMs(1000)
    }

    @TestCase
    func testEvent(): Unit {
        let driver = Driver.create()
        let componentButton1 = driver.findComponent(On().id("Cover_event"))
        componentButton1.click()
        driver.delayMs(5000)
        driver.pressBack()
        driver.delayMs(1000)
    }

    @TestCase
    func testFFI(): Unit {
        let driver = Driver.create()
        let componentButton1 = driver.findComponent(On().id("Cover_FFI"))
        componentButton1.click()
        driver.delayMs(5000)
        driver.pressBack()
    }
}