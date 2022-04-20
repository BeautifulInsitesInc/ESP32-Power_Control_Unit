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

const int AC1 = 16;
const int AC2 = 17; //17
const int AC3 = 18;
const int AC4 = 19;
const int AC5 = 23;
const int AC6 = 25;

// DC  12 Volt
const int DC1 = 26;//26
const int DC2 = 27;
const int DC3 = 32;
const int DC4 = 33;
const int DC5 = 14;
const int DC6 = 15;

//Toggle switches starting values
String plugStatus1 = "off";
String plugStatus2 = "off";
String plugStatus3 = "off";
String plugStatus4 = "off";
String plugStatus5 = "off";
String plugStatus6 = "off";

//sliders starting value
String message = "";
String sliderValue1 = "0";
String sliderValue2 = "0";
String sliderValue3 = "0";
String sliderValue4 = "0";
String sliderValue5 = "0";

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
  pinMode(AC1, OUTPUT);
  pinMode(AC2, OUTPUT);
  pinMode(AC3, OUTPUT);
  pinMode(AC4, OUTPUT);
  pinMode(AC5, OUTPUT);
  pinMode(AC6, OUTPUT);

  pinMode(DC1, OUTPUT);
  pinMode(DC2, OUTPUT);
  pinMode(DC3, OUTPUT);
  pinMode(DC4, OUTPUT);
  pinMode(DC5, OUTPUT);

  // Set Plug outputs to HIGH
  digitalWrite(AC1, HIGH);
  digitalWrite(AC2, HIGH);
  digitalWrite(AC3, HIGH);
  digitalWrite(AC4, HIGH);
  digitalWrite(AC5, HIGH);
  digitalWrite(AC6, HIGH);

  // Set DC outpins to LOW
  digitalWrite(DC1, LOW);
  digitalWrite(DC2, LOW);
  digitalWrite(DC3, LOW);
  digitalWrite(DC4, LOW);
  digitalWrite(DC5, LOW);

// configure LED PWM functionalitites
  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcSetup(ledChannel3, freq, resolution);
  ledcSetup(ledChannel4, freq, resolution);
  ledcSetup(ledChannel5, freq, resolution);


  // attach the channel to the GPIO to be controlled
  ledcAttachPin(DC1, ledChannel1);
  ledcAttachPin(DC2, ledChannel2);
  ledcAttachPin(DC3, ledChannel3);
  ledcAttachPin(DC4, ledChannel4);
  ledcAttachPin(DC5, ledChannel5);
}
#endif