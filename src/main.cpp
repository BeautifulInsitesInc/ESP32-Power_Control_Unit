#include "main.h"

void setup()
{
  Serial.begin(115200);
  outln("Starting");
  displaySetup();
  outln("Displaying Splash Screen");

  // Setup all the pins
  pinSetup(); 

  wifiManagerSetup(); // WiFi Manager, SPIFF uploader, OTA Updates

   // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  
  server.serveStatic("/", SPIFFS, "/");

  AsyncElegantOTA.begin(&server);
  
  /* *********** start websocket server  ************
  bind a handling function to our websocket endpoint, 
  in order for our code to run when a websocket event occurs.
  We do this by calling the onEvent method on our AsyncWebSocket object.
   initializes the WebSocket protocol.
  */
  ws.onEvent(onEvent);
  server.addHandler(&ws);

  server.begin();
  TelnetServer.begin();

  digitalWrite(LED_BUILTIN, LOW);

  dhtSetup();

}
String previousState = "off";
void loop()
{
  wifiManagerLoop();
  AsyncElegantOTA.loop();
  telnetLoop();
  
  //getDHTReadings();
  
/******** WEB SOCKET LOOP ******/
 //;ws.loop(); server.handleClient();
 /*
  //-----------------------------------------------
  if(led_on == false) digitalWrite(LED_BUILTIN, LOW);
  else digitalWrite(LED_BUILTIN, HIGH);
  //-----------------------------------------------
  String led_status = "OFF";
  if(led_on == true) led_status = "ON";
  JSONtxt = "{\"LEDonoff\":\""+led_status+"\"}";
  // need to send it to the client now
  //websocket.broadcastTXT(JSONtxt);
  //AsyncWebSocket.broadcastTXT(JSONtxt);
  //websocket.send(JSONtxt);
*/

  

  if (plugStatus1 == "on") {
    digitalWrite(AC1, LOW);
    if (previousState != plugStatus1){
      tout("Turning plug 1 on!");
      previousState = plugStatus1;
    }
  }  
  else {
    digitalWrite(AC1, HIGH);
    if (previousState != plugStatus1){
      tout("Turning plug 1 Off!!!");
      previousState = plugStatus1;
    } 
  }

  if (plugStatus2 == "on")  digitalWrite(AC2, LOW);
  else digitalWrite(AC1, HIGH);
  if (plugStatus3 == "on")  digitalWrite(AC3, LOW);
  else digitalWrite(AC1, HIGH);
  if (plugStatus4 == "on")  digitalWrite(AC4, LOW);
  else digitalWrite(AC1, HIGH);
  if (plugStatus5 == "on")  digitalWrite(AC5, LOW);
  else digitalWrite(AC1, HIGH);
  if (plugStatus6 == "on")  digitalWrite(AC6, LOW);
  else digitalWrite(AC1, HIGH);

  //Slider update
  ledcWrite(ledChannel1, dutyCycle1);
  ledcWrite(ledChannel2, dutyCycle2);
  ledcWrite(ledChannel3, dutyCycle3);
  ledcWrite(ledChannel4, dutyCycle3);
  ledcWrite(ledChannel5, dutyCycle3);



  if(magic_word != previous_magic_word){
    magicWord();
    previous_magic_word = magic_word;
  } 



  /*Note that we all call the cleanupClients() method. Here’s why 
  (explanation from the ESPAsyncWebServer library GitHub page):
  Browsers sometimes do not correctly close the WebSocket connection, 
  even when the close() function is called in JavaScript. 
  This will eventually exhaust the web server’s resources and will cause the server to crash.
  Periodically calling the cleanupClients() function from the main loop()limits the number 
  of clients by closing the oldest client when the maximum number of clients has been exceeded.
  This can be called every cycle, however, if you wish to use less power, then calling as infrequently
  as once per second is sufficient.
  */
  ws.cleanupClients();
  
}