#include "main.h"



void setup()
{
  Serial.begin(115200);
  outln("Starting");
  //displaySetup();
  outln("Displaying Splash Screen");

  wifiManagerSetup(); // WiFi Manager, SPIFF uploader, OTA Updates
 
  //webStuffSetup();

  // Start Servers
  //ws.onEvent(onWsEvent); //websocket
  //server.addHandler(&ws);
  //#include "web_stuff.h"

  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  
  server.serveStatic("/", SPIFFS, "/");

  AsyncElegantOTA.begin(&server);
  server.begin();
  TelnetServer.begin();
  initWebSocket();




  outln(F("HTTP server started @ "));
  outln(WiFi.localIP());

  outln(separatorLine);
  outln("Open http://"); outln(WiFi.localIP());
  toutln("/edit to see the file browser"); 
  toutln("Using username = " + http_username + " and password = " + http_password);
  toutln(separatorLine);

  






  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  wifiManagerLoop();
  AsyncElegantOTA.loop();
  telnetLoop();
  
  
  //websocketloop();

  webStuffLoop();





  
}