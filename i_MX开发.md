<!--
 * @Author: youngjam
 * @Date: 2020-06-21 15:52:05
 * @LastEditTime: 2020-06-21 16:19:38
 * @Description: imx开发笔记
 * @logs: 
--> 
<!-- TOC -->

- [EBF6ULL Pro硬件资源](#ebf6ull-pro硬件资源)
- [SD卡烧录Debian镜像](#sd卡烧录debian镜像)
  - [Etcher工具](#etcher工具)
  - [野火Debian镜像](#野火debian镜像)
  - [烧录过程](#烧录过程)

<!-- /TOC -->
# EBF6ULL Pro硬件资源
* 板载硬件资源  
    ![avatar](/picture/imx6ull.jpg)
* 硬件资源表
    |资源|说明|
    |:----|:-----|
    |DC12V接口|DC 12V&2A 直流输入，不支持电脑usb供电，电流不够|
    |usb转串口|使用 miniUSB 接口，使用CH340驱动|
    |KEY|reset 1个，onoff 1个，wakeup 1个，mode 1个|
    |rgb灯|由3个独立的r、g、b小灯组成|
    |六轴陀螺仪|型号MPU6050|
    |DB9接口|2路，一路母头DB9，一路工头DB9，使用RS232协议|
    |485接口|2路，2接线柱引出，使用RS485协议|
    |CAN接口|2路，2接线柱引出，使用CAN协议|
    |EBF接口|1个，使用1^6P排母引出，适用于连接使用串口协议的小模块|
    |启动配置|通过一个8位的拨码开关配合实现|
    |以太网|2路百兆以太网，型号KSZ8081RNB|
    |SPDIF收发|1\*SPDIFIN，1\*SPDIFOUT，用于音频光纤输入输出|
    |JTAG接口|1个|
    |音频接口|1\* IN，1\* OUT，3.5mm音频座；1*MIC IN，电容咪头，使用WM8960芯片解码|
    |环境光传感器|型号AP3216C|
    |红外接收|型号HS1838|
    |温湿度接口|可接入DHT11/DS18B20传感器|
    |喇叭接口|可用型号：3080|
    |摄像头接口|可配套使用野火ov5640摄像头|
    |蜂鸣器|有源蜂鸣器，3.3V|
    |USB HOST|4路通过芯片原生内扩|
    |micro USB|原生引出，支持OTG|
    |电位器|1k阻值变动|
    |RTC座子|电池座，通用电池型号CR1220|
    |WIFI & 蓝牙|型号：AP6236，不能与SD卡同时使用|
    |SD卡卡座|microSD卡卡座，支持SD3.0，不能与WIFI同时使用|
    |电容按键|可检测到触摸开关状态|
    |HDMI接口|板载HDMI转换芯片，使用RGB转HDMI，可直接使用HDMI信号线连接至HDMI屏幕|
    |LVDS接口|板载RGB转LVDS芯片|
    |LCD接口|FRC接口，RGB888及I2C触摸信号|
    |GPIO|通过两排2\*40P的2.54间距排针引出，可自主连接各种外部设备|
# SD卡烧录Debian镜像
## Etcher工具
* 跨平台镜像烧录工具
* 官网地址：https://www.balena.io/etcher/
## 野火Debian镜像
* imx6ull-debian-buster-console-armhf-2020-04-09.img.xz：
    debian的纯净版固件，没有带桌面环境和野火的QT APP
* imx6ull-debian-buster-desktop-armhf-2020-04-09.img.xz：
    带有桌面环境的debian固件，系统启动会进入桌面环境
* imx6ull-debian-buster-full-qt-app-armhf-2020-04-09.img.xz：
    具有完整QT App功能的debian固件，系统启动会进入QT App界面，该固件超过nandflash 512M的容量，只可烧录于eMMc
* imx6ull-debian-buster-part-qt-app-armhf-2020-04-09.img.xz：
    该固件移除了音频播放功能的QT App，系统启动会进入QT App界面，大约420M，可烧录于nandflash和eMMc中
* README.txt：文件记录了固件的使用说明及版本改动记录
* SHA256SUMS.txt：记录了各个固件的sha256校验值
## 烧录过程
1. 选择烧录镜像，选择要烧录的SD卡，点击flash进行烧录
2. 当界面出现flash complete表示烧录完成
3. 开发板插入烧录好的sd卡，调整拨码开关为sd卡启动方式，上电后即可正常使用
* 开发板第一次从sd卡启动时，系统会自动进行sd卡扩容，扩容完毕后，系统自动重启生效
* 普通用户：
    ```
    账号：debian
    密码：temppwd
    ```
* root用户：
    ```
    账号：root
    密码：root
    ```
  
