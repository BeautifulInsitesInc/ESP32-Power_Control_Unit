#ifndef WEB_STUFF_H
#define WEB_STUFF_H

#include <Arduino.h>
#include <Arduino_JSON.h>

AsyncWebSocket ws("/ws");
AsyncWebSocketClient* wsClient;

//Json Variable to Hold Slider Values
JSONVar sliderValues;
JSONVar sensorValues;

//get Sensor Values
String getSensorValues(){
  sensorValues["airTempC"] = String(dht_tempC);
  sensorValues["airTempF"] = String(dht_tempF);
  sensorValues["humidity"] = String(dht_humidity,0);
  String jsonString = JSON.stringify(sensorValues);
  return jsonString;
}

//Get Slider Values
String getSliderValues(){
  //AC plugs
  sliderValues["plugStatus1"] = String(plugStatus1);
  sliderValues["plugStatus2"] = String(plugStatus2);
  sliderValues["plugStatus3"] = String(plugStatus3);
  sliderValues["plugStatus4"] = String(plugStatus4);

  //DC sliders
  sliderValues["sliderValue1"] = String(sliderValue1);
  sliderValues["sliderValue2"] = String(sliderValue2);
  sliderValues["sliderValue3"] = String(sliderValue3);
  sliderValues["sliderValue4"] = String(sliderValue4);

  String jsonString = JSON.stringify(sliderValues);
  toutln("Just ran GetSliderValues");
  return jsonString;
}



void notifyClients(String sliderValues) {
  ws.textAll(sliderValues);
}

// callback function that will run whenever we receive new data from the clients via WebSocket protocol.
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    message = (char*)data;
    tout("websocket.h recieved message : "); toutln(message);
    
    if (message.indexOf("1p") >= 0) {
      plugStatus1 = message.substring(2);
      notifyClients(getSliderValues());
    }

    if (message.indexOf("2p") >= 0) {
      plugStatus2 = message.substring(2);
      notifyClients(getSliderValues());
    }

    if (message.indexOf("3p") >= 0) {
      plugStatus3 = message.substring(2);
      notifyClients(getSliderValues());
    }
    if (message.indexOf("4p") >= 0) {
      plugStatus4 = message.substring(2);
      notifyClients(getSliderValues());
    }
    //Sliders :

    if (message.indexOf("1s") >= 0) {
      sliderValue1 = message.substring(2);
      dutyCycle1 = map(sliderValue1.toInt(), 0, 100, 0, 255);
      notifyClients(getSliderValues());
    }
    if (message.indexOf("2s") >= 0) {
      sliderValue2 = message.substring(2);
      dutyCycle2 = map(sliderValue2.toInt(), 0, 100, 0, 255);
      notifyClients(getSliderValues());
    }

    if (message.indexOf("3s") >= 0) {
      sliderValue3 = message.substring(2);
      dutyCycle3 = map(sliderValue3.toInt(), 0, 100, 0, 255);
      notifyClients(getSliderValues());
    }

    if (message.indexOf("4s") >= 0) {
      sliderValue4 = message.substring(2);
      dutyCycle4 = map(sliderValue4.toInt(), 0, 100, 0, 255);
      notifyClients(getSliderValues());
    }

    if (strcmp((char*)data, "getValues") == 0) {
      notifyClients(getSliderValues());
    }

    //if (message = "saveSettings"){
    if (strcmp((char*)data, "saveSettings") == 0) {
      toutln("message recieved savesettings running save preferences");
      savePreferences();
       
    }

    //if (message = "loadSettings") {
    if (strcmp((char*)data, "loadSettings") == 0) {
      toutln("message reciebed to load settings");
      loadPreferences();
    }

  }
}

/*The type argument represents the event that occurs. It can take the following values:
WS_EVT_CONNECT when a client has logged in;
WS_EVT_DISCONNECT when a client has logged out;
WS_EVT_DATA when a data packet is received from the client;
WS_EVT_PONG in response to a ping request;
WS_EVT_ERROR when an error is received from the client.
*/
void onEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      toutln("its handling a message now");
      outln("its handling a message now:");
      
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

uint64_t counter = 0;

void websocketloop() {
  // If client is connected ...
  if(wsClient != nullptr && wsClient->canSend()) {
    // .. send hello message :-)
    wsClient->text("Hello client");
  }
  // Wait 10 ms
  delay(10);
}


#endif
