// MQTTClient.cpp : Defines the entry point for the application.
//


#include "MQTTClient.h"
using namespace std;



static MQTTClient* mqttClient;  // client instance

//=================== wrapper functions over MQTTClient class =============

void mqtt_test_connect_cb_wrapper(struct mosquitto* mosq_pub,
    void* userdata,
    int result) {

    mqttClient->mqtt_test_connect_cb(mosq_pub, userdata, result);
}

void mqtt_test_disconnect_cb_wrapper(struct mosquitto* mosq_pub,
    void* userdata,
    int result) {

    mqttClient->mqtt_test_disconnect_cb(mosq_pub, userdata, result);
}

void mqtt_test_publish_cb_wrapper(struct mosquitto* mosq_pub,
    void* userdata,
    int msg_id) {

    mqttClient->mqtt_test_publish_cb(mosq_pub, userdata, msg_id);
}

void mqtt_test_subscribe_cb_wrapper(struct mosquitto* mosq_pub, 
        void* userdata, int msg_id, int qos_count, const int* qos_granted){

    mqttClient->mqtt_test_subscribe_cb(mosq_pub, userdata, msg_id, qos_count, qos_granted);
}

void mqtt_test_msg_cb_wrapper(struct mosquitto* mosq_pub,
    void* userdata,const struct mosquitto_message* msg) {

    mqttClient->mqtt_test_msg_cb(mosq_pub, userdata, msg);
}


//================= MQTTClient class member definitions ========================
void MQTTClient::mqtt_test_connect_cb(
    struct mosquitto* mosq_pub,
    void* userdata,
    int result) {

    cout << "mqtt_test_connect_cb is invoked" << endl;

    // check if this instance is a publisher or subscriber
    if (Type == MQTT_TEST_TYPE_PUB) {
        cout << "This is PUB client" << endl;
        mqtt_client_publish(); 

    }else{
        cout << "This is SUB client" << endl;
        mqtt_client_subscribe();
    }

    return;

}

void MQTTClient:: mqtt_test_disconnect_cb(
    struct mosquitto* mosq_pub, 
    void* userdata, 
    int result) {
    
    cout << "mqtt_test_disconnect_cb is invoked" << endl;

}

void MQTTClient:: mqtt_test_publish_cb(
    struct mosquitto* mosq_pub, 
    void* userdata, 
    int msg_Id){
    
    cout << "mqtt_test_publish_cb is invoked " << endl;

    Sleep(1000); // publish msg every 10s
    mqtt_client_publish(); 

}
void MQTTClient:: mqtt_test_subscribe_cb(
    struct mosquitto* mosq_pub, 
    void* userdata, int result,
    int qos_level, const int *given_qos) {
    
    cout << "mqtt_test_subscribe_cb is invoked " << endl;
}


// this method is called when the substriber receives a new message
void MQTTClient:: mqtt_test_msg_cb(
    struct mosquitto* mosq_pub, 
    void* userdata, const struct mosquitto_message* msg){
    
    cout << "mqtt_test_msg_cb is invoked : msg Id = " << msg->topic << endl;

    if (!msg->topic || !msg->payload) {
        cout << "invalid msg Id or msg payload received, discarding the msg" << endl;
    }

    // check the msg
    if (strncmp(msg->topic, topic, strnlen(topic, 100)) == 0) {
        cout << "MQTT msg received: " << (char *) msg->payload << endl;
        //printf("msg = %s \n", msg->payload);
    }
}

int MQTTClient::mqtt_client_publish(){

    char mqtt_msg[50] = "hello";
    
    int r = mosquitto_publish(mosq_test, NULL, topic, (strlen(mqtt_msg) + 1), mqtt_msg, 1, false);
    
    if (r != MOSQ_ERR_SUCCESS) {
        cout << "publish failed , err reason = " << r << endl;
    }
    else {
        cout << "publish success , code = " << r << endl;
    }

    return MQTT_CLIENT_SUCCESS;
}

int MQTTClient::mqtt_client_subscribe() {

    // If this instance is a subscriber, subscribe incoming message from 
    int r = mosquitto_subscribe(mosq_test, NULL, topic, 1);

    if (r != MOSQ_ERR_SUCCESS) {
        cout << "subscribe failed , err reason = " << r << endl;
    }
    else {
        cout << "subscribe success , code = " << r << endl;
    }
    return MQTT_CLIENT_SUCCESS;
}


int MQTTClient::mqtt_client_connect() {
    
    int res = mosquitto_connect(mosq_test, "127.0.0.1", 1883, MQTT_BROKER_KEEPALIVE);
    if (res == MOSQ_ERR_SUCCESS) {
        cout << "connect success : start the loop " << res << endl;
        // start the mosquitto loop ; refer https://mosquitto.org/api/files/mosquitto-h.html
        // this is part of the threaded client interface.
        //res = mosquitto_loop_start(mosq_test);  // this is a non-blocking call
        res = mosquitto_loop_forever(mosq_test, 1000, 100); // this is a blocking call.
        cout << "loop start result " << res << endl;

    }
    else { cout << "connect failed: " << res << endl; }

    return res;
}

int MQTTClient::mqtt_client_init() {
    int res;

    cout << "mqtt client is initialized" << endl;

    // call the mosquito library init
    res = mosquitto_lib_init();

    // get a context for mosquitto broker
    mosq_test = mosquitto_new(Client_Id, true, NULL);

    if (!mosq_test) {
        cout << "mosq new command failed" << endl;
        return MQTT_CLIENT_FAILUE;
    }

    // register callbacks and connect to the broker
    mosquitto_connect_callback_set(mosq_test, mqtt_test_connect_cb_wrapper);
    mosquitto_disconnect_callback_set(mosq_test, mqtt_test_disconnect_cb_wrapper);
    mosquitto_publish_callback_set(mosq_test, mqtt_test_publish_cb_wrapper);
    mosquitto_subscribe_callback_set(mosq_test, mqtt_test_subscribe_cb_wrapper);
    mosquitto_message_callback_set(mosq_test, mqtt_test_msg_cb_wrapper);
    
    cout << "call backs registered" << endl;
    
    res = mqtt_client_connect();

    return MQTT_CLIENT_SUCCESS;
}


void mqtt_create_client(char *type){

    if (strcmp(type, "SUB") == 0) {
        mqttClient = new MQTTClient(1, MQTT_TEST_TYPE_SUB);
    }
    else {
        mqttClient = new MQTTClient(1, MQTT_TEST_TYPE_PUB);
    }
    mqttClient->mqtt_client_init();
}

void mqtt_delete_client() {
    // this is the instance of MQTT client
    delete mqttClient;
}

int main(int argc, char *argv[])
{
	cout << "Hello MQTT client : " << argv[1] << endl;
    mqtt_create_client(argv[1]);
    return 0;
}
