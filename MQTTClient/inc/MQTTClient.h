//=================================================================================================
// MQTTClient.h : Include file for standard system include files,
// or project specific include files.

// mqtt agent need to implement the following
// 1) agent onboarding, agent initialization
// 2) subscribe to topics, publish message for the topics, 
// 3) process inbound message, constructing outbound message based on JSON data model.
// 4) Invoke the corresponding event handler on receving inboud message
// 5) Provide callbacks for outbound message to the modules to send outbound message

// call flow
// Initialize ODD agent -> initialize mqtt client, onboarding, message subscritpion, 
// Inbound message -> process inbound JSON msg -> invoke respective modules to take action ->
// callback from modules -> construct outbound JSON msg -> publish to MQTT broker 


// Topic prefix
// strncpy(mqtt_test_device_topic_prefix, mqtt_test_realm, MQTT_TOPIC_MAX_SIZE);
// strncpy(mqtt_test_device_topic_prefix, "/", MQTT_TOPIC_MAX_SIZE);

// other prefixes ...
// strncpy(mqtt_test_device_topic_prefix, mqtt_test_device_id, MQTT_TOPIC_MAX_SIZE);
// strncpy(mqtt_test_device_topic_prefix, "/v0/device_monitor_agent/", MQTT_TOPIC_MAX_SIZE);

// strncpy(mqtt_test_incoming_ifc_topic, mqtt_test_device_topic_prefix, MQTT_TOPIC_MAX_SIZE);
// strncpy(mqtt_test_incoming_ifc_topic, "incomingifc/v0", MQTT_TOPIC_MAX_SIZE);

//=================================================================================================
#pragma once

#include <iostream>
#include <string.h>
#include <windows.h>
#include <windows.data.json.h> //https://learn.microsoft.com/en-us/uwp/api/windows.data.json.jsonobject?view=winrt-22621
#include "C:\Program Files\mosquitto\devel\mosquitto.h"

/*
To add JSON library
https://www.youtube.com/watch?v=GYauneigGTs

https://github.com/open-source-parsers/jsoncpp

Mosquitto on windows
https://cedalo.com/blog/how-to-install-mosquitto-mqtt-broker-on-windows/

*/


//#define MQTT_BROKER_HOSTNAME "DESKTOP-QM4I8E2"   // this is the Id I got typing in cmd
#define MQTT_BROKER_HOSTNAME "localhost"   
#define MQTT_BROKER_PORT      1883    // default port 
// the broker would start caring about the status after 300 seconds 
// without communication between the client and the broker.It waits 
// for the PINGREQ message from the client.If the client is silent, 
// the broker disconnects it after another 150 seconds.Likewise, 
// if the broker does not respond to the client with the PINGRESP message,
// the client shuts down the connection.
#define MQTT_BROKER_KEEPALIVE     300

#define MQTT_CLIENT_FAILUE  0
#define MQTT_CLIENT_SUCCESS 1
#define MQTT_TEST_TYPE_PUB  1
#define MQTT_TEST_TYPE_SUB  2


class MQTTClient {
private:
	char Client_Id[20];
	int Type;  // type is either PUB or SUB
	struct mosquitto* mosq_test = NULL;
	char topic[50] = "/MyMqttTest/Topic1/";  // default topic
	char* msg;

public:
	MQTTClient(int val, int t) : Type(t){
		if (Type == MQTT_TEST_TYPE_PUB) {
			strncpy(Client_Id, "MQTT_TEST_PUB", sizeof(Client_Id));
		}else {
			strncpy(Client_Id, "MQTT_TEST_SUB", sizeof(Client_Id));
		}
	}
	
	int mqtt_client_init();

	int mqtt_client_connect();

	int mqtt_test_my_type() { return Type; }

	int mqtt_client_publish();

	int mqtt_client_subscribe();

	int mqtt_client_process_msg();

	// callbacks for mosq connections
	void mqtt_test_connect_cb(struct mosquitto* mosq_pub, void* userdata, int result);
	void mqtt_test_disconnect_cb(struct mosquitto* mosq_pub, void* userdata, int result);
	void mqtt_test_publish_cb(struct mosquitto* mosq_pub, void* userdata, int msg_Id);
	void mqtt_test_subscribe_cb(struct mosquitto* mosq_pub,void* userdata, 
								int result,int qos_level,const int* given_qos);
	void mqtt_test_msg_cb(struct mosquitto* mosq_pub, void* userdata, 
							const struct mosquitto_message* msg);
	
	// desctructor
	virtual ~MQTTClient() {};
};


/*
JSON schema for messages sent for topics

Shema format - 1
----------------
	{
		"name": "tempereture",
		"description": "device tempereture"
		"type":"float"
	}

Shema format - 2
----------------
	{
		"data1":[{
					"name": "tempereture",
					"description": "device tempereture",
					"type":"float"
		},{
					"name": "speed",
					"description": "device movement",
					"type":"float"
		}]
	}

The actual data from device will be sent as below for the above schema,
	{
		"data1":{
				"tempereture": 25.2,
				"speed":"60.5
		}
	}

This will be translated to REST APIs for topics as below
	deviceId/data1/tempereture
	deviceId/data1/speed


MQTT can also be used fot implementing basic START, STOP, GET and CONFIG APIs. In this case
the controller application (mqtt agenet) would publish these API messages and the device agents
would substribe to them. 

Similarly, the reponse messages for these APIs can also be modelled as PUB/SUB. where the device
agents would publish those reponse messages and the controller application would substribe to them.

e.g of GET API

	{
		"device_service":{
					"name" : "monitoring service",
					"agent": "temp sensor agent"
		},
		"temp_service_request":{
			"req_type":"GET",
			"req_id":1,
			"category":"module1",
			"data_list":[1,5,10],
		}
	}

e.g of START API

	{
		"device_service":{
					"name" : "monitoring service",
					"agent": "temp sensor agent"
		},
		"temp_service_request":{
			"req_type":"GET",
			"req_id":1,
			"category":"module1",
			"data_list":[1,5,10],
			"duration":600,      # send it for 600 seconds
			"period":60          # send it every 60s 
		}
	}
				


*/