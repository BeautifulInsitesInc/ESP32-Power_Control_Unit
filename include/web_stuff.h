#ifndef WEB_STUFF_H
#define WEB_STUFF_H

#include <Arduino.h>
#include <Arduino_JSON.h>

AsyncWebSocket ws("/ws");
AsyncWebSocketClient* wsClient;

// Assign output variables to GPIO pins
const int plug1 = 16;
const int plug2 = 17;
const int plug3 = 18;
const int plug4 = 19;
const int plug5 = 23;
const int plug6 = 25;

// DC  12 Volt
const int DC1 = 26;
const int DC2 = 27;
const int DC3 = 32;
const int DC4 = 33;
const int DC5 = 14;
const int DC6 = 15;

//sliders starting value
String message = "";
String sliderValue1 = "0";
String sliderValue2 = "0";
String sliderValue3 = "0";
String sliderValue4 = "0";
String sliderValue5 = "0";
String sliderValue6 = "0";

int dutyCycle1;
int dutyCycle2;
int dutyCycle3;
int dutyCycle4;
int dutyCycle5;
int dutyCycle6;

// setting PWM properties
const int freq = 5000;
const int ledChannel1 = 0;
const int ledChannel2 = 1;
const int ledChannel3 = 2;
const int ledChannel4 = 3;
const int ledChannel5 = 4;
const int ledChannel6 = 5;

const int resolution = 8;

//Json Variable to Hold Slider Values
JSONVar sliderValues;
  
//Get Slider Values
String getSliderValues(){
  sliderValues["sliderValue1"] = String(sliderValue1);
  sliderValues["sliderValue2"] = String(sliderValue2);
  sliderValues["sliderValue3"] = String(sliderValue3);
  sliderValues["sliderValue4"] = String(sliderValue4);
  sliderValues["sliderValue5"] = String(sliderValue5);
  sliderValues["sliderValue6"] = String(sliderValue6);

  String jsonString = JSON.stringify(sliderValues);
  return jsonString;
}


void notifyClients(String sliderValues) {
  ws.textAll(sliderValues);
}


void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  tout("handlign a socket message");
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    //if (strcmp((char*)data, "toggle") == 0) {
      //ledState = !ledState;
      //notifyClients();
    sliderValue1 = message.substring(2);
    dutyCycle1 = map(sliderValue1.toInt(), 0, 100, 0, 255);
    Serial.println(dutyCycle1);
    Serial.print(getSliderValues());
    notifyClients(getSliderValues());
  }
  if (message.indexOf("2s") >= 0) {
    tout("handlewebSocketmessage function called for 2s");
    sliderValue2 = message.substring(2);
    dutyCycle2 = map(sliderValue2.toInt(), 0, 100, 0, 255);
    Serial.println(dutyCycle2);
    Serial.print(getSliderValues());
    notifyClients(getSliderValues());
  }    
  if (message.indexOf("3s") >= 0) {
    sliderValue3 = message.substring(2);
    dutyCycle3 = map(sliderValue3.toInt(), 0, 100, 0, 255);
    Serial.println(dutyCycle3);
    Serial.print(getSliderValues());
    notifyClients(getSliderValues());
  }
  if (strcmp((char*)data, "getValues") == 0) {
    notifyClients(getSliderValues());
  }
}

void onEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      tout("its handling a message now");
      
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }




  
  
  
  /*if(type == WS_EVT_CONNECT){
    wsClient = client;
    out("Websocket just recieved somthing!");
  } else if(type == WS_EVT_DISCONNECT){
    wsClient = nullptr;
  } else if (type == WS_EVT_DATA) {
    handleWebSocketMessage(arg, data, len);
  }
*/
}


void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
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


void webStuffSetup(){
  // Initialize the output variables as outputs
  pinMode(plug1, OUTPUT);
  pinMode(plug2, OUTPUT);
  pinMode(plug3, OUTPUT);
  pinMode(plug4, OUTPUT);
  pinMode(plug5, OUTPUT);
  pinMode(plug6, OUTPUT);

  pinMode(DC1, OUTPUT);
  pinMode(DC2, OUTPUT);
  pinMode(DC3, OUTPUT);
  pinMode(DC4, OUTPUT);
  pinMode(DC5, OUTPUT);
  pinMode(DC6, OUTPUT);

  // Set Plug outputs to HIGH
  digitalWrite(plug1, HIGH);
  digitalWrite(plug2, HIGH);
  digitalWrite(plug3, HIGH);
  digitalWrite(plug4, HIGH);
  digitalWrite(plug5, HIGH);
  digitalWrite(plug6, HIGH);

  // Set DC outpins to LOW
  digitalWrite(DC1, LOW);
  digitalWrite(DC2, LOW);
  digitalWrite(DC3, LOW);
  digitalWrite(DC4, LOW);
  digitalWrite(DC5, LOW);
  digitalWrite(DC6, LOW);

// configure LED PWM functionalitites
  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcSetup(ledChannel3, freq, resolution);
  ledcSetup(ledChannel4, freq, resolution);
  ledcSetup(ledChannel5, freq, resolution);
  ledcSetup(ledChannel6, freq, resolution);


  // attach the channel to the GPIO to be controlled
  ledcAttachPin(DC1, ledChannel1);
  ledcAttachPin(DC2, ledChannel2);
  ledcAttachPin(DC3, ledChannel3);
  ledcAttachPin(DC4, ledChannel4);
  ledcAttachPin(DC5, ledChannel5);
  ledcAttachPin(DC6, ledChannel6);


  initWebSocket();


}


void webStuffLoop(){
/*
  ledcWrite(ledChannel1, dutyCycle1);
  ledcWrite(ledChannel2, dutyCycle2);
  ledcWrite(ledChannel3, dutyCycle3);
  ledcWrite(ledChannel4, dutyCycle4);
  ledcWrite(ledChannel5, dutyCycle5);
  ledcWrite(ledChannel6, dutyCycle6);
*/
  ws.cleanupClients();
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









#endif
