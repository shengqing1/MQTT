#include "mqtt.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
// 设置服务器的地址和端口
#define SERVER_IP "117.78.5.125"
#define SERVER_PORT 1883
// MQTT鉴权三元组(此处需要根据情况修改，直接运行不会成功)
#define ClientID "667c3a7d671df42eb372386_dev1_0_0_2024091800"
#define Username "667c3a7d671df42eb372386_dev1"
#define Password "e9c621f8212c344cac5ed6b72599593c6dc832576c82e1d1c0d3b780c15e21e5"

#define SET_TOPIC "$oc/devices/667c3a7d671df42eb372386_dev1/sys/messages/down"		// 主题订阅
#define POST_TOPIC "$oc/devices/667c3a7d671df42eb372386_dev1/sys/properties/report" // 主题发布

extern int connectSocket; // 存储套接字描述符
double DHT11_T = 10.0;	  // 环境温度

int main()
{
	// 创建TCP套接字，并检查是否创建成功
	connectSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (connectSocket < 0)
	{
		perror("socket creation failed");
		return 1;
	}

	struct sockaddr_in service;
	memset(&service, 0, sizeof(service));
	service.sin_family = AF_INET;
	inet_pton(AF_INET, SERVER_IP, &service.sin_addr);
	service.sin_port = htons(SERVER_PORT);

	// 设置服务器的地址和端口,尝试连接到服务器
	if (connect(connectSocket, (struct sockaddr *)&service, sizeof(service)) < 0)
	{
		perror("connect failed");
		close(connectSocket);
		return 1;
	}

	std::cout << "connected to server" << std::endl;
	MQTT_Init();
	while (1)
	{
		// 尝试连接到MQTT服务器，如果连接失败，则等待1秒后重试。
		if (MQTT_Connect((char *)ClientID, (char *)Username, (char *)Password) == 0)
		{
			break;
		}
		sleep(1);
		std::cout << "MQTT服务器登录校验中....\n";
	}

	std::cout << "连接成功\n";

	// 订阅主题
	int stat = MQTT_SubscribeTopic((char *)SET_TOPIC, 1, 1);
	if (stat)
	{
		std::cout << "订阅失败\n";
		close(connectSocket);
		return 1;
	}
	std::cout << "订阅成功\n";

	while (1)
	{
		// 每隔5秒发布一次消息，并更新温度值
		std::cout << "start send message" << std::endl;
		char mqtt_message[1024];
		// 构造一个包含温度数据的JSON消息，并发布到指定的主题
		sprintf(mqtt_message, "{\"services\": [{\"service_id\": \"stm32\",\"properties\":{\"DHT11_T\":%.1f}}]}", DHT11_T += 0.2);

		MQTT_PublishData((char *)POST_TOPIC, mqtt_message, 0);
		std::cout << "发布消息成功" << std::endl;
		sleep(5);
	}

	close(connectSocket);
	return 0;
}