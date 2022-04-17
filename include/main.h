#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

// --- DEBUGGING ---
#define DEBUG // Comment out to remove all serial prints

#ifdef DEBUG
  #define out(x) Serial.print(x)
  #define outln(x) Serial.println(x)
  #define tout(x) Telnet.print(x)
  #define toutln(x) Telnet.println(x)
#else
  #define out(x)
  #define outln(x)
  #define tout(x)
  #define toutln(x)
#endif

// --- End Debugging ---

#define LCD_SCREEN// Comment out if no display

#ifdef LCD_SCREEN 
  #define sout(x) Screen.print(x)
  #define soutln(x) Screen.println(x)
#else 
  #define sout(x)
  #define soutln(x)
#endif

// *********** PIN ASSIGNMENTS ***********************
// Assign output variables to GPIO pins

const int plug1 = 16;
const int plug2 = 26; //17
const int plug3 = 18;
const int plug4 = 19;
const int plug5 = 23;
const int plug6 = 25;

// DC  12 Volt
const int DC1 = 26;//26
const int DC2 = 27;
const int DC3 = 32;
const int DC4 = 33;
const int DC5 = 14;
const int DC6 = 15;

const int dht_pin = 4;

// ************* GLOBAL VARIABLES ***********************
int dht_timer_start = millis();
int dht_timer_period = 5; //time in seconds between readings
float dht_tempC = 0;
float dht_tempF = 0;
float dht_humidity = 0;

bool led_on = true;
String JSONtxt;

// ******* INCLUDE FILES *********************
#include "display.h"
#include "wifi_manager.h"
#include "web_socket.h"
#include "sensor_temp.h"

void pinSetup(){
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
}
#endif