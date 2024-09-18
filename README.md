## 项目概述

本项目旨在通过C语言在Linux环境下实现MQTT协议，以实现与华为云IOT平台的高效通信。MQTT（Message Queuing Telemetry Transport）是一种轻量级的发布/订阅消息传输协议，广泛用于物联网通信。此项目通过自定义的C语言库与应用程序，展示了如何在嵌入式设备或服务器上建立MQTT客户端，进行设备认证、消息订阅与发布等功能。

## 关键特性

1. **MQTT协议实现**：使用C语言实现MQTT的核心功能，包括连接、订阅、发布和心跳维持。
2. **华为云IOT平台集成**：项目配置了与华为云IOT平台的连接参数，如服务器地址、端口、客户端ID、用户名和密码，确保设备能够顺利接入云平台。
3. **消息处理**：实现了消息的接收与发送逻辑，支持JSON格式的消息体，便于传输结构化数据。
4. **错误处理**：包含了网络连接和MQTT通信过程中的错误处理机制，确保通信的稳定性和可靠性。
5. **跨平台兼容性**：代码基于Linux平台开发，具有较好的跨平台特性，可轻松移植到其他支持C语言的操作系统。

## 技术细节

- **编程语言**：C语言
- **主要库文件**：`mqtt.cpp`, `main.cpp`, `mqtt.h`
- **网络通信**：使用TCP/IP协议栈进行网络通信，通过套接字编程实现数据的发送与接收。
- **MQTT报文处理**：详细实现了MQTT报文的构建与解析，包括连接报文、订阅报文、发布报文等。
- **心跳机制**：通过定时发送心跳报文维持与服务器的连接。

## 使用方法

1. **环境配置**：确保Linux环境已安装GCC编译器和必要的网络开发库。
2. **代码编译**：使用GCC编译器编译源代码，生成可执行文件。
3. **运行程序**：执行编译后的程序，开始与华为云IOT平台进行通信。
4. **参数配置**：根据实际需求调整服务器地址、端口和认证信息。
## 华为云IOT平台配置（详情见说明文档）
