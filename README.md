# VerdantOS

基于 **Qt 上位机 + STM32 + FreeRTOS** 的嵌入式绿植养护系统 Demo。

项目以家庭绿植养护为应用场景，设计了上位机与嵌入式设备之间的控制通信链路，并以此实践 Qt/C++、STM32、UART 串口通信、FreeRTOS 任务与消息队列等嵌入式软件开发基础。

> 个人项目，用于学习嵌入式软件开发。当前版本以**核心控制链路的实现与验证**为主。

## 当前实现

目前已完成一条从上位机到嵌入式设备的完整控制链路：

```text
Qt 上位机
   │
   │ QSerialPort / UART
   ▼
STM32 USART1
   │
   │ UART 接收中断
   ▼
HAL_UART_RxCpltCallback()
   │
   │ FreeRTOS Message Queue
   ▼
Device Control Task
   │
   │ GPIO
   ▼
板载 LED
```

用户在 Qt 上位机中点击控制按钮后，上位机通过串口向 STM32 发送控制指令；STM32 通过 UART 接收中断获取数据，并将指令放入 FreeRTOS Message Queue，由设备控制任务读取并执行 GPIO 控制。

当前 Demo 实现：

* `0x01`：开启设备
* `0x02`：关闭设备
* STM32 端通过 FreeRTOS Message Queue 在中断接收与任务处理之间传递控制指令
* 以开发板板载 LED 作为执行器进行端到端验证

## 技术栈

| 模块     | 技术                       |
| ------ | ------------------------ |
| 上位机    | Qt 6 / C++               |
| 串口通信   | QSerialPort / USART      |
| MCU    | STM32                    |
| RTOS   | FreeRTOS / CMSIS-RTOS2   |
| RTOS机制 | Task / Message Queue     |
| 外设     | UART / GPIO              |
| 开发工具   | STM32CubeMX、STM32CubeIDE |

## 项目架构

项目当前采用 Qt 上位机与 STM32 下位机的基本分层结构。

### 上位机

负责：

* 图形界面
* 用户操作
* 串口配置与通信
* 向 STM32 发送设备控制指令

### 下位机

负责：

* USART 串口接收
* UART 接收中断处理
* FreeRTOS 消息队列传递
* 设备控制任务
* GPIO 输出

当前下位机的核心数据流：

```text
UART RX
  ↓
UART Interrupt
  ↓
HAL_UART_RxCpltCallback()
  ↓
Message Queue
  ↓
Device Control Task
  ↓
GPIO
```

将**中断中的数据接收**与**实际设备控制逻辑**分离，使控制逻辑运行在 FreeRTOS 任务中，为后续接入更多设备和控制任务留下扩展空间。

## 通信设计

项目早期设计了一套固定长度的设备控制数据帧，用于描述控制模式、设备 ID、操作、周期、时长以及重复次数/档位等信息。

指令字段设计如下：

```text
bit 7       bit 6 ~ 1       bit 0
模式/类型    设备 ID（6 bit）   操作
```

其中：

* bit 7：控制模式

  * `0`：手动管理
  * `1`：自动管理
* bit 6 ~ 1：设备 ID
* bit 0：操作

  * `0`：关闭
  * `1`：开启

协议还设计了周期、时长以及重复次数/档位等字段。

> 当前 Demo 主要用于验证 Qt → UART → STM32 → FreeRTOS → GPIO 的完整链路，实际运行版本采用 `0x01` / `0x02` 两个基础控制指令，完整的数据帧协议尚未继续实现。

## 开发过程


首先完成 Qt 上位机界面和串口通信配置，随后完成 STM32 USART1 配置，并通过 UART 接收中断获取上位机发送的数据。

在联调过程中，对 UART 中断、FreeRTOS Message Queue 以及任务调度进行了逐步验证，最终确认：

```text
Qt
 ↓
USART
 ↓
STM32 UART RX Interrupt
 ↓
FreeRTOS Message Queue
 ↓
Device Control Task
 ↓
GPIO
```

整条链路能够正常工作，并通过开发板板载 LED 完成实际硬件验证。

## 项目状态

### 已完成

* Qt 图形化上位机
* Qt `QSerialPort` 串口通信
* STM32 USART1 配置
* UART 接收中断
* FreeRTOS 任务
* FreeRTOS Message Queue
* 上位机控制指令接收与处理
* GPIO 控制
* Qt → STM32 → FreeRTOS → GPIO 端到端联调
* 开发板硬件验证

### 已设计 / 后续可扩展

以下内容进行了方案设计，但当前 Demo 未继续实现：

* 多路传感器采集
* 温度 / 湿度 / 光照数据展示
* 浇水、补光、风扇等执行器控制
* 自动养护规则
* 更完整的串口通信协议及校验机制
* 多任务 / 多队列扩展
* 日志与告警
* 基于 Toulmin 论证模型的植物问题分析

## Toulmin 植物问题分析设计

项目还设计了一个面向植物问题分析的功能，用于探索**论证模型与嵌入式环境数据结合**的可能性。

设计思路是将植物的当前状态、环境参数以及养护记录组织为论证结构，例如：

* **主张（Claim）**：植物当前可能存在的问题
* **依据（Data）**：环境参数、养护记录等
* **正当理由（Warrant）**：环境参数与植物症状之间的关联规则
* **限定（Qualifier）**：对分析结论的可信程度进行描述

## 开发环境

### Qt

* Qt 6

### STM32

* STM32CubeMX
* FreeRTOS / CMSIS-RTOS2
