<div align="center">
<h1>webrtc4cj</h1>
</div>

<p align="center">
<img alt="" src="https://img.shields.io/badge/release-v0.0.2-brightgreen" style="display: inline-block;" />
<img alt="" src="https://img.shields.io/badge/build-pass-brightgreen" style="display: inline-block;" />
<img alt="" src="https://img.shields.io/badge/cjcov-0%25-red" style="display: inline-block;" />
<img alt="" src="https://img.shields.io/badge/project-open-brightgreen" style="display: inline-block;" />
</p>

## 介绍

webrtc4cj 是一个基于仓颉语言以视频直播、屏幕共享为核心功能的第三方库，并在C++层适配了视频的采集、渲染及编解码等模块和仓颉接口


### 特性

实时音频、视频的采集与显示功能


## 软件架构

### 源码目录

```shell
├─AppScope
├─doc                         // 接口文档
├─entry                       // UI模块 
├─webrtc_cj                   // 核心胶水层代码模块
├─webrtc_cpp				  // 核心底层代码模块
└─hvigor                      // 构建工具目录

```


### 接口说明

主要类和函数接口说明详见 [API](./doc/feature_api.md)

## 使用说明

### 编译运行

1. 通过 module 引入

    1. 克隆下载项目
2. 将webrtc_cpp和webrtc_cj模块拷贝到应用项目下
    
    3. 解压模块下目录任意webrtc_cpp/src/cpp/libwebrtc*.rar得到libwebrtc.a文件
4. 编译模块webrtc_cpp得到动态库.so
    5. 修改自身应用 entry 下的 oh-package.json5 文件，在 dependencies 字段添加 "webrtc": "file:../webrtc"

   ```shell
   {
     "name": "entry",
     "version": "1.0.0",
     "description": "Please describe the basic information.",
     "main": "",
     "author": "",
     "license": "",
     "dependencies": {
       "webrtc":"file:../webrtc_cj"
     }
   }
   ```

   6. 在项目中使用 import webrtc.* 引用 webrtc项目

   ```cangjie
   import webrtc_cj.*
   ```

2. 把 webrtc4cj作为三方库依赖引入

    1. 目标工程把 webrtc4cj依赖库作为 git submodule 引入

   ```shell
   > cd $工程根目录
   > mkdir third-party
   > cd third-party
   > git submodule add "https://gitcode.com/Cangjie-TPC/webrtc4cj.git"
   ```

    2. 修改自身应用 entry 下的 cjpm.toml 文件，添加依赖

   ```
   [dependencies]
   	webrtc = {path = "../third-party/webrtc4cj/webrtc/src/main/cangjie", version = "1.0.0"}
   ```

    3.  在项目中使用 webrtc 组件

   ```cangjie
   import webrtc_cj.*
   ```

### 功能示例

用例代码在entry目录下 [功能示例](./entry/src/main/cangjie/index.cj)

## 约束与限制
1. 在下述版本验证通过：

- DevEco Studio 5.1.1 Release
- Cangjie support Plugin: 5.1.0.823


## 开源协议

本项目基于 [Apache License 2.0](/LICENSE) ，请自由的享受和参与开源。

## 参与贡献

欢迎给我们提交 PR，欢迎给我们提交 issue，欢迎参与任何形式的贡献。