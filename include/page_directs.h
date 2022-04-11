#ifndef PAGE_DIRECTS_H // This is so if it included in mulitple cpp files, the code will not be duplicated
#define PAGE_DIRECTS_H

#include <Arduino.h>



/* ORIGINAL 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hello World!");
  });

*/




// Route for root / web page
/*
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
*/

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
/*
  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

*/















#endif