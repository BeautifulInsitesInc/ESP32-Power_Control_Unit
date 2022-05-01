#include "main.h"


//JSONVar settingValues;



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

  loadPreferences();
  getDHTReadings();

}

String previousState = "off";
unsigned long testtimer = millis();
void loop()
{
  wifiManagerLoop();
  //AsyncElegantOTA.loop();
  telnetLoop();
  ws.cleanupClients();
  
  getDHTReadings();

  
  if (elementStatus1 == "on" || triggerStatus1 == "alwasyON1") digitalWrite(AC1, LOW);
  else digitalWrite(AC1, HIGH);
  if (elementStatus2 == "on" || triggerStatus2 == "alwasyON1")  digitalWrite(AC2, LOW);
  else digitalWrite(AC2, HIGH);
  if (elementStatus3 == "on" || triggerStatus3 == "alwasyON1")  digitalWrite(AC3, LOW);
  else digitalWrite(AC3, HIGH);
  if (elementStatus4 == "on" || triggerStatus4 == "alwasyON1")  digitalWrite(AC4, LOW);
  else digitalWrite(AC4, HIGH);


  //Slider update
  if (elementStatus5 == "on" || triggerStatus5 == "alwasysON1") ledcWrite(ledChannel1, dutyCycle1);
  else ledcWrite(ledChannel1, 0);
  if (elementStatus6 == "on" || triggerStatus6 == "alwasysON1") ledcWrite(ledChannel2, dutyCycle2);
  else ledcWrite(ledChannel2, 0);
  if (elementStatus7 == "on" || triggerStatus7 == "alwasysON1") ledcWrite(ledChannel3, dutyCycle3);
  else ledcWrite(ledChannel3, 0);
  if (elementStatus8 == "on" || triggerStatus8 == "alwasysON1") ledcWrite(ledChannel4, dutyCycle4);
  else ledcWrite(ledChannel4, 0);

  if(testtimer>= millis()+10000){
    testtimer = millis();
    notifyClients(getStateValues());
  }

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