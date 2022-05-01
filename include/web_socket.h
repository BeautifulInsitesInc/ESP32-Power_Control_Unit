#ifndef WEB_STUFF_H
#define WEB_STUFF_H

#include <Arduino.h>
#include <Arduino_JSON.h>

AsyncWebSocket ws("/ws");
AsyncWebSocketClient* wsClient;

//Json Variable to Hold Slider Values
JSONVar stateValues;
JSONVar sensorValues;
//JSONVar triggerValues;


//get Sensor Values
String getSensorValues(){
  sensorValues["airTempC"] = String(dht_tempC);
  sensorValues["airTempF"] = String(dht_tempF);
  sensorValues["humidity"] = String(dht_humidity,0);
  String jsonString = JSON.stringify(sensorValues);
  return jsonString;
}

//Get Slider Values
String getStateValues(){
  //AC plugs
  stateValues["plugStatus1"] = String(plugStatus1);
  stateValues["plugStatus2"] = String(plugStatus2);
  stateValues["plugStatus3"] = String(plugStatus3);
  stateValues["plugStatus4"] = String(plugStatus4);

  //DC sliders
  stateValues["sliderValue1"] = String(sliderValue1);
  stateValues["sliderValue2"] = String(sliderValue2);
  stateValues["sliderValue3"] = String(sliderValue3);
  stateValues["sliderValue4"] = String(sliderValue4);

  //Trigger Values
  stateValues["triggerPlug1"] = String(triggerPlug1);
  stateValues["triggerPlug2"] = String(triggerPlug2);
  stateValues["triggerPlug3"] = String(triggerPlug3);
  stateValues["triggerPlug4"] = String(triggerPlug4);

  String jsonString = JSON.stringify(stateValues);
  toutln("Just ran GetstateValues :"); toutln(stateValues);
  return jsonString;
}


void notifyClients(String settings) {
  ws.textAll(settings);
}

// callback function that will run whenever we receive new data from the clients via WebSocket protocol.
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    message = (char*)data;
    tout("websocket.h recieved message : "); toutln(message);

    // *****  TURN ELEMENTS ON OR OFF *******
    if (message.indexOf("S") >=0) {// If the message is status change (on/off)
      String elementNumber = message.substring(1,2);
      String elementStatus = message.substring(2);
      tout("Status message recieved, elementNumber: "); tout(elementNumber); tout(" Element status: ");toutln(elementStatus);

      switch (elementNumber.toInt()){
        // AC Plugs
        case 1: if (triggerPlug1 == "manual0") plugStatus1 = elementStatus; break;
        case 2: if (triggerPlug2 == "manual0") plugStatus2 = elementStatus; break;
        case 3: if (triggerPlug3 == "manual0") plugStatus3 = elementStatus; break;
        case 4: if (triggerPlug4 == "manual0") plugStatus4 = elementStatus; break;
        // DC Plugs
        case 5: if (triggerAC1 == "manual0") sliderStatus1 = elementStatus; break;
        case 6: if (triggerAC2 == "manual0") sliderStatus2 = elementStatus; break;
        case 7: if (triggerAC3 == "manual0") sliderStatus3 = elementStatus; break;
        case 8: if (triggerAC4 == "manual0") sliderStatus4 = elementStatus; break;
      }
    }
    //Sliders :

    if (message.indexOf("1s") >= 0) {
      sliderValue1 = message.substring(2);
      dutyCycle1 = map(sliderValue1.toInt(), 0, 100, 0, 255);
      //notifyClients(getStateValues());
    }
    if (message.indexOf("2s") >= 0) {
      sliderValue2 = message.substring(2);
      dutyCycle2 = map(sliderValue2.toInt(), 0, 100, 0, 255);
      //notifyClients(getStateValues());
    }

    if (message.indexOf("3s") >= 0) {
      sliderValue3 = message.substring(2);
      dutyCycle3 = map(sliderValue3.toInt(), 0, 100, 0, 255);
      //notifyClients(getStateValues());
    }

    if (message.indexOf("4s") >= 0) {
      sliderValue4 = message.substring(2);
      dutyCycle4 = map(sliderValue4.toInt(), 0, 100, 0, 255);
      //notifyClients(getStateValues());
    }

    if (strcmp((char*)data, "getValues") == 0) {
      //notifyClients(getStateValues());
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

    if (message.indexOf("T") >=0){
      String plugNumber = message.substring(1,2);
      String triggerSelectionIndex = message.substring(2,3);
      tout("Message recieved Trigger plug number :");tout(plugNumber);tout(" Substring :");toutln(triggerSelectionIndex);
      toutln("message was ");toutln(message);
      switch (plugNumber.toInt()){

        case 1: // switch 1
          switch (triggerSelectionIndex.toInt()){
              case 0: //manual
                toutln("plug 1 index 0 chosen");
                triggerPlug1 = "manual0";
                break;
              case 1: // always on
                toutln("plug 1 index 1 has been chosen");
                plugStatus1 = "on";
                triggerPlug1 = "alwaysON1";
                break;
          }

          break;
        case 2: // switch 2
          switch (triggerSelectionIndex.toInt()){
              case 0: //manual
                toutln("plug 2 index 0 chosen");
                triggerPlug2 = "manual0";
                break;
              case 1:
                toutln("plug 2 index 1 has been chosen");
                plugStatus2 = "on";
                triggerPlug2 = "alwaysON1";
                break;
          }
          break;

        case 3: // switch 3
          switch (triggerSelectionIndex.toInt()){
            case 0: //manual
              toutln("plug 3 index 0 chosen");
              triggerPlug3 = "manual0";
              break;
            case 1:
              toutln("plug 3 index 1 has been chosen");
              plugStatus3 = "on";
              triggerPlug3 = "alwaysON1";
              break;
          }
          break;

        case 4:
          switch (triggerSelectionIndex.toInt()){
            case 0: //manual
              toutln("plug 4 index 0 chosen");
              triggerPlug4 = "manual0";
              break;
            case 1:
              toutln("plug 4 index 1 has been chosen");
              plugStatus4 = "on";
              triggerPlug4 = "alwaysON1";
              break;
          }
          break;
          
        case 5:
          break;
        case 6:
          break;
        case 7:
          break;
        case 8:
          break;
        case 9:
          break;
        
        
        default:
          break;
      }
      //notifyClients(getStateValues());

    }
    notifyClients(getStateValues());
    notifyClients(getSensorValues());
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
