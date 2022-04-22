#ifndef WEB_STUFF_H
#define WEB_STUFF_H

#include <Arduino.h>
#include <Arduino_JSON.h>

AsyncWebSocket ws("/ws");
AsyncWebSocketClient* wsClient;

//Json Variable to Hold Slider Values
JSONVar sliderValues;
//JSONVar toggleValues;

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
  return jsonString;
}

void notifyClients(String sliderValues) {
  ws.textAll(sliderValues);
}

// callback function that will run whenever we receive new data from the clients via WebSocket protocol.
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  tout("handlign a socket message");  outln("Runnig handleWebSocketMessage :");
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    message = (char*)data;
    
    // Button on/off:
    /*
    if (strcmp((char*)data, "onboard_led") == 0) {
      outln("handle websocket data being passed for : ");
      toutln("handelWebSocketMessage for Button on/off is being run");
      led_on = !led_on;
      ws.textAll("Sending led_on value : ");ws.textAll(String(led_on));
      //notifyClients();
    }
    */
   
    if (message.indexOf("1p") >= 0) {
      plugStatus1 = message.substring(2);
      tout("Recieved on server : plugStatus1 : "); toutln(plugStatus1); 
      notifyClients(getSliderValues());
    }

    if (message.indexOf("2p") >= 0) {
      plugStatus2 = message.substring(2);
      tout("Recieved on server : plugStatus1 : "); toutln(plugStatus1); 
      //tout("getSliderValues : "); toutln(getSliderValues());
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
    tout("Running handle message, message is : "); toutln(message);

    if (message.indexOf("1s") >= 0) {
      sliderValue1 = message.substring(2);
      dutyCycle1 = map(sliderValue1.toInt(), 0, 100, 0, 255);
      tout("dutyCycle1 : "); toutln(dutyCycle1);
      tout("getSliderValues : "); toutln(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("2s") >= 0) {
      sliderValue2 = message.substring(2);
      dutyCycle2 = map(sliderValue2.toInt(), 0, 100, 0, 255);
      tout("dutyCycle2 : "); toutln(dutyCycle1);
      tout("getSliderValues : "); toutln(getSliderValues());
      notifyClients(getSliderValues());
    }

    if (message.indexOf("3s") >= 0) {
      sliderValue3 = message.substring(2);
      dutyCycle3 = map(sliderValue3.toInt(), 0, 100, 0, 255);
      tout("dutyCycle3 : "); toutln(dutyCycle1);
      tout("getSliderValues : "); toutln(getSliderValues());
      notifyClients(getSliderValues());
    }

    if (message.indexOf("4s") >= 0) {
      sliderValue4 = message.substring(2);
      dutyCycle4 = map(sliderValue4.toInt(), 0, 100, 0, 255);
      tout("dutyCycle4 : "); toutln(dutyCycle1);
      tout("getSliderValues : "); toutln(getSliderValues());
      notifyClients(getSliderValues());
    }

    if (strcmp((char*)data, "getValues") == 0) {
      toutln("handleWebSocketMessage: getValues is being run");
      notifyClients(getSliderValues());
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


/*
void webStuffLoop(){
    WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output26, HIGH);
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "off";
              digitalWrite(output26, LOW);
            } else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO 27 on");
              output27State = "on";
              digitalWrite(output27, HIGH);
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              output27State = "off";
              digitalWrite(output27, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>GPIO 26 - State " + output26State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output26State=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>GPIO 27 - State " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
            if (output27State=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

}

*/
/* The processor() function is responsible for searching for placeholders on the HTML text and
replace them with whatever we want before sending the web page to the browser. 
*/

/*
String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if (led_on){
      return "ON";
    }
    else{
      return "OFF";
    }
  }
}
*/









#endif
