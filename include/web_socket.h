#ifndef WEB_STUFF_H
#define WEB_STUFF_H

#include <Arduino.h>
#include <Arduino_JSON.h>

AsyncWebSocket ws("/ws");
AsyncWebSocketClient* wsClient;

//Json Variable to Hold Slider Values
JSONVar stateValues;
JSONVar sensorValues;
JSONVar timerValues;


//get Sensor Values
String getSensorValues(){
  sensorValues["airTempC"] = String(dht_tempC);
  sensorValues["airTempF"] = String(dht_tempF);
  sensorValues["humidity"] = String(dht_humidity,0);
  sensorValues["fullDate"] = String(fullDate);
  String jsonString = JSON.stringify(sensorValues);
  return jsonString;
}

//Get Slider Values
String getStateValues(){
  //AC plugs
  stateValues["elementStatus1"] = String(elementStatus1);
  stateValues["elementStatus2"] = String(elementStatus2);
  stateValues["elementStatus3"] = String(elementStatus3);
  stateValues["elementStatus4"] = String(elementStatus4);
  stateValues["elementStatus5"] = String(elementStatus5);
  stateValues["elementStatus6"] = String(elementStatus6);
  stateValues["elementStatus7"] = String(elementStatus7);
  stateValues["elementStatus8"] = String(elementStatus8);

  //DC sliders
  stateValues["sliderValue5"] = String(sliderValue5);
  stateValues["sliderValue6"] = String(sliderValue6);
  stateValues["sliderValue7"] = String(sliderValue7);
  stateValues["sliderValue8"] = String(sliderValue8);

  //Trigger Values
  stateValues["triggerSelection1"] = String(triggerSelection1);
  stateValues["triggerSelection2"] = String(triggerSelection2);
  stateValues["triggerSelection3"] = String(triggerSelection3);
  stateValues["triggerSelection4"] = String(triggerSelection4);
  stateValues["triggerSelection5"] = String(triggerSelection5);
  stateValues["triggerSelection6"] = String(triggerSelection6);
  stateValues["triggerSelection7"] = String(triggerSelection7);
  stateValues["triggerSelection8"] = String(triggerSelection8);

  stateValues["cycleOn1"] = String (cycleOn1); stateValues["cycleOff1"] = String (cycleOff1);
  stateValues["cycleOn2"] = String (cycleOn2); stateValues["cycleOff2"] = String (cycleOff2);
  stateValues["cycleOn3"] = String (cycleOn3); stateValues["cycleOff3"] = String (cycleOff3);
  stateValues["cycleOn4"] = String (cycleOn4); stateValues["cycleOff4"] = String (cycleOff4);
  stateValues["cycleOn5"] = String (cycleOn5); stateValues["cycleOff5"] = String (cycleOff5);
  stateValues["cycleOn6"] = String (cycleOn6); stateValues["cycleOff6"] = String (cycleOff6);
  stateValues["cycleOn7"] = String (cycleOn7); stateValues["cycleOff7"] = String (cycleOff7);
  stateValues["cycleOn8"] = String (cycleOn8); stateValues["cycleOff8"] = String (cycleOff8);

  String jsonString = JSON.stringify(stateValues);
  toutln("Just ran GetstateValues :"); toutln(stateValues);
  return jsonString;
}

String getTimerValues(){
  int countdownOn1 = (cycleOnMillis1-millis()) /oneMinute; int countdownOff1 = (cycleOffMillis1-millis())/oneMinute;
  if (countdownOn1 > cycleOn1) countdownOn1 = 0; if(countdownOff1 >cycleOff1) countdownOff1 = 0;
  timerValues["countdownOn1"] = String(countdownOn1); timerValues["countdownOff1"] = String(countdownOff1);
  String jsonString = JSON.stringify(timerValues);
  return jsonString;
}

void notifyClients(String settings) {ws.textAll(settings);}

// callback function that will run whenever we receive new data from the clients via WebSocket protocol.
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    message = (char*)data;
    tout("websocket.h recieved message : "); toutln(message);
    String messageType = message.substring(0,3);
    tout("messageType : ");toutln(messageType);

    // ============== TURN ELEMENTS ON OR OFF ==============
    if (message.indexOf("S") >=0) {// "S" - status change. ie: S1on If the message is status change (on/off)
      String elementNumber = message.substring(1,2);
      String elementStatus = message.substring(2);
      tout("Status message recieved, elementNumber: "); tout(elementNumber); tout(" Element status: ");toutln(elementStatus);

      switch (elementNumber.toInt()){
        // AC Plugs
        case 1: if (triggerSelection1 == "manual0") elementStatus1 = elementStatus; break;
        case 2: if (triggerSelection2 == "manual0") elementStatus2 = elementStatus; break;
        case 3: if (triggerSelection3 == "manual0") elementStatus3 = elementStatus; break;
        case 4: if (triggerSelection4 == "manual0") elementStatus4 = elementStatus; break;
        case 5: if (triggerSelection5 == "manual0") elementStatus5 = elementStatus; break;
        case 6: if (triggerSelection6 == "manual0") elementStatus6 = elementStatus; break;
        case 7: if (triggerSelection7 == "manual0") elementStatus7 = elementStatus; break;
        case 8: if (triggerSelection8 == "manual0") elementStatus8 = elementStatus; break;
      }
    }
    // ============  CHANGE DC SLIDER VALUES ================
    if (message.indexOf("M") >=0) {// "M" - Motor control ie: M178- change if slider is moved
      String elementNumber = message.substring(1,2);
      String sliderValue = message.substring(2);
      tout("Slider movement message recieved. Elementnumber: ");tout(elementNumber);tout(" slidervalue: ");toutln(sliderValue);

      switch (elementNumber.toInt()){
        case 5: sliderValue5 = sliderValue; dutyCycle1 = map(sliderValue5.toInt(), 0, 100, 0, 255); break;
        case 6: sliderValue6 = sliderValue; dutyCycle2 = map(sliderValue6.toInt(), 0, 100, 0, 255); break;
        case 7: sliderValue7 = sliderValue; dutyCycle3 = map(sliderValue7.toInt(), 0, 100, 0, 255); break;
        case 8: sliderValue8 = sliderValue; dutyCycle4 = map(sliderValue8.toInt(), 0, 100, 0, 255); break;
      }
    }

    // SAVE AND LOAD SETTINGS MESSAGE
    if (strcmp((char*)data, "saveSettings") == 0) savePreferences();
    if (strcmp((char*)data, "loadSettings") == 0) loadPreferences();

    // ============= CHANGE TRIGGER SELECTION =================
    if (message.indexOf("T") >=0){// ie: T12 - First digit element, 2nd index of trigger selection
      String elementNumber = message.substring(1,2);
      String triggerSelectionIndex = message.substring(2,3);
      tout("Message recieved Trigger element number :");tout(elementNumber);tout(" Substring :");toutln(triggerSelectionIndex);
      
      switch (elementNumber.toInt()){
        case 1: switch (triggerSelectionIndex.toInt()){
                  case 0: triggerSelection1 = "manual0"; break;
                  case 1: triggerSelection1 = "alwaysON1"; elementStatus1 = "on"; break;
                  case 2: triggerSelection1 = "timeClock2"; break;
                  case 3: triggerSelection1 = "timeCycle3"; break;
                  case 4: triggerSelection1 = "sensor4"; break;
                  case 5: triggerSelection1 = "linked5"; break;
                }
                break;
        case 2: switch (triggerSelectionIndex.toInt()){
                  case 0: triggerSelection2 = "manual0"; break;
                  case 1: triggerSelection2 = "alwaysON1"; elementStatus2 = "on"; break;
                  case 2: triggerSelection2 = "timeClock2"; break;
                  case 3: triggerSelection2 = "timeCycle3"; break;
                  case 4: triggerSelection2 = "sensor4"; break;
                  case 5: triggerSelection2 = "linked5"; break;
                }
                break;
        case 3: switch (triggerSelectionIndex.toInt()){
                  case 0: triggerSelection3 = "manual0"; break;
                  case 1: triggerSelection3 = "alwaysON1"; elementStatus3 = "on"; break;
                  case 2: triggerSelection3 = "timeClock2"; break;
                  case 3: triggerSelection3 = "timeCycle3"; break;
                  case 4: triggerSelection3 = "sensor4"; break;
                  case 5: triggerSelection3 = "linked5"; break;
                }
                break;
        case 4: switch (triggerSelectionIndex.toInt()){
                  case 0: triggerSelection4 = "manual0"; break;
                  case 1: triggerSelection4 = "alwaysON1"; elementStatus4 = "on"; break;
                  case 2: triggerSelection4 = "timeClock2"; break;
                  case 3: triggerSelection4 = "timeCycle3"; break;
                  case 4: triggerSelection4 = "sensor4"; break;
                  case 5: triggerSelection4 = "linked5"; break;
                }
                break;
        case 5: switch (triggerSelectionIndex.toInt()){
                  case 0: triggerSelection5 = "manual0"; break;
                  case 1: triggerSelection5 = "alwaysON1"; elementStatus5 = "on"; break;
                  case 2: triggerSelection5 = "timeClock2"; break;
                  case 3: triggerSelection5 = "timeCycle3"; break;
                  case 4: triggerSelection5 = "sensor4"; break;
                  case 5: triggerSelection5 = "linked5"; break;
                }
                break;
        case 6: switch (triggerSelectionIndex.toInt()){
                  case 0: triggerSelection6 = "manual0"; break;
                  case 1: triggerSelection6 = "alwaysON1"; elementStatus6 = "on"; break;
                  case 2: triggerSelection6 = "timeClock2"; break;
                  case 3: triggerSelection6 = "timeCycle3"; break;
                  case 4: triggerSelection6 = "sensor4"; break;
                  case 5: triggerSelection6 = "linked5"; break;
                }
                break;
        case 7: switch (triggerSelectionIndex.toInt()){
                  case 0: triggerSelection7 = "manual0"; break;
                  case 1: triggerSelection7 = "alwaysON1"; elementStatus7 = "on"; break;
                  case 2: triggerSelection7 = "timeClock2"; break;
                  case 3: triggerSelection7 = "timeCycle3"; break;
                  case 4: triggerSelection7 = "sensor4"; break;
                  case 5: triggerSelection7 = "linked5"; break;
                }
                break;
        case 8: switch (triggerSelectionIndex.toInt()){
                  case 0: triggerSelection8 = "manual0"; break;
                  case 1: triggerSelection8 = "alwaysON1"; elementStatus8 = "on"; break;
                  case 2: triggerSelection8 = "timeClock2"; break;
                  case 3: triggerSelection8 = "timeCycle3"; break;
                  case 4: triggerSelection8 = "sensor4"; break;
                  case 5: triggerSelection8 = "linked5"; break;
                }
                break;
      } 
    }

    if (messageType = "cyc"){
      toutln("message cycle recieved ");toutln(message);
      int separatorIndex1 = message.indexOf("-");
      int separatorIndex2 = message.indexOf("-",separatorIndex1+1);
      int separatorIndex3 = message.indexOf("-",separatorIndex2+1);
      String elementNumber = message.substring(separatorIndex1+1,separatorIndex1+2);
      String cycleOn = message.substring(separatorIndex2+1,separatorIndex3);
      String cycleOff = message.substring(separatorIndex3+1);
      
      toutln(""); toutln(""); tout("elementxxxxxxxxxxxxxxxx number :");toutln(elementNumber);toutln("");
      tout("cycleON :");tout(cycleOn);tout("  cycleOff :");toutln(cycleOff);
      switch (elementNumber.toInt()){
        case 1: cycleOn1 = cycleOn.toInt(); cycleOff1 = cycleOff.toInt(); 
                cycleOnMillis1 = millis() + (cycleOn1*oneSecond); cycleOffMillis1 = millis()+(cycleOn1+cycleOff1)*oneSecond; elementStatus1 = "on"; break;
        case 2: cycleOn2 = cycleOn.toInt(); cycleOff2 = cycleOff.toInt(); 
                cycleOnMillis2 = millis() + (cycleOn2*oneSecond); cycleOffMillis2 = millis()+(cycleOn2+cycleOff2)*oneSecond; elementStatus2 = "on"; break;
        case 3: cycleOn3 = cycleOn.toInt(); cycleOff3 = cycleOff.toInt();
                cycleOnMillis3 = millis() + (cycleOn3*oneSecond); cycleOffMillis3 = millis()+(cycleOn3+cycleOff3)*oneSecond; elementStatus3 = "on"; break;
        case 4: cycleOn4 = cycleOn.toInt(); cycleOff4 = cycleOff.toInt(); 
                cycleOnMillis4 = millis() + (cycleOn4*oneSecond); cycleOffMillis4 = millis()+(cycleOn4+cycleOff4)*oneSecond; elementStatus4 = "on"; break;
        case 5: cycleOn5 = cycleOn.toInt(); cycleOff5 = cycleOff.toInt(); 
                cycleOnMillis5 = millis() + (cycleOn5*oneSecond); cycleOffMillis5 = millis()+(cycleOn5+cycleOff5)*oneSecond; elementStatus5 = "on"; break;
        case 6: cycleOn6 = cycleOn.toInt(); cycleOff6 = cycleOff.toInt();
                cycleOnMillis6 = millis() + (cycleOn6*oneSecond); cycleOffMillis6 = millis()+(cycleOn6+cycleOff6)*oneSecond; elementStatus6 = "on"; break;
        case 7: cycleOn7 = cycleOn.toInt(); cycleOff7 = cycleOff.toInt(); 
                cycleOnMillis7 = millis() + (cycleOn7*oneSecond); cycleOffMillis7 = millis()+(cycleOn7+cycleOff7)*oneSecond; elementStatus7 = "on"; break;
        case 8: cycleOn8 = cycleOn.toInt(); cycleOff8 = cycleOff.toInt(); 
                cycleOnMillis8 = millis() + (cycleOn8*oneSecond); cycleOffMillis8 = millis()+(cycleOn8+cycleOff8)*oneSecond; elementStatus8 = "on"; break;
      }
      
      
      

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
