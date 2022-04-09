#include "main.h"

void setup()
{
  Serial.begin(115200);
  outln("Starting");
  displaySetup();
  outln("Displaying Splash Screen");
  wifiManagerSetup(); // WiFi Manager, SPIFF uploader, OTA Updates
  //telnetSetup();
  
}

void loop()
{
  
  wifiManagerLoop();
  //telnetLoop();

  
}