#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include "time.h"
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

const int dht_pin = 25;
// Assign output variables to GPIO pins

const int AC1 = 16;
const int AC2 = 17; //17
const int AC3 = 18;
const int AC4 = 19;

// DC  12 Volt
const int DC1 = 26;//26
const int DC2 = 27;
const int DC3 = 32;
const int DC4 = 23;//23 25


// ========== TIME SETUP ==========
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -18000; // 3600 seconds per hour
const int   daylightOffset_sec = 3600;
unsigned long time_clock;


String message = "";
//Toggle switches starting values
String elementStatus1 = "off"; 
String elementStatus2 = "off";
String elementStatus3 = "off";
String elementStatus4 = "off";
String elementStatus5 = "off";
String elementStatus6 = "off";
String elementStatus7 = "off";
String elementStatus8 = "off";

String triggerSelection1= "manual0";
String triggerSelection2= "manual0";
String triggerSelection3= "manual0";
String triggerSelection4= "manual0";
String triggerSelection5= "manual0";
String triggerSelection6= "manual0";
String triggerSelection7= "manual0";
String triggerSelection8= "manual0";

String sliderValue5 = "0";
String sliderValue6 = "0";
String sliderValue7 = "0";
String sliderValue8 = "0";

int dutyCycle1;
int dutyCycle2;
int dutyCycle3;
int dutyCycle4;

// setting PWM properties
const int freq = 5000;
const int ledChannel1 = 0;
const int ledChannel2 = 1;
const int ledChannel3 = 2;
const int ledChannel4 = 3;

const int resolution = 8;

//clockTime variables

//clockCycle variables
int cycleOn1, cycleOff1;
int cycleOn2, cycleOff2;
int cycleOn3, cycleOff3;
int cycleOn4, cycleOff4;
int cycleOn5, cycleOff5;
int cycleOn6, cycleOff6;
int cycleOn7, cycleOff7;
int cycleOn8, cycleOff8;

int oneMinute = 1000*60; // 1000*60 for minute
int oneSecond = 1000;

int cycleOnMillis1, cycleOffMillis1;
int cycleOnMillis2, cycleOffMillis2;
int cycleOnMillis3, cycleOffMillis3;
int cycleOnMillis4, cycleOffMillis4;
int cycleOnMillis5, cycleOffMillis5;
int cycleOnMillis6, cycleOffMillis6;
int cycleOnMillis7, cycleOffMillis7;
int cycleOnMillis8, cycleOffMillis8;


// ************* SENSOR VARIABLES ***********************
int dht_timer_start = millis();
int dht_timer_period = 15; //time in seconds between readings

float dht_tempC = 0;
float dht_tempF = 0;
float dht_humidity = 0;

int humidity_calibration_variable = 2;

String fullDate;

// ******* INCLUDE FILES *********************
#include "display.h"
#include "wifi_manager.h"
#include "save_settings.h"
#include "web_socket.h"
#include "sensor_temp.h"


void pinSetup(){
  // Initialize AC plugs and set to HIGH - (off)
  pinMode(AC1, OUTPUT);
  pinMode(AC2, OUTPUT);
  pinMode(AC3, OUTPUT);
  pinMode(AC4, OUTPUT);
  // Set Plug outputs to HIGH
  digitalWrite(AC1, HIGH);
  digitalWrite(AC2, HIGH);
  digitalWrite(AC3, HIGH);
  digitalWrite(AC4, HIGH);

  // Initilize DC plugs and set to Low (off)
  pinMode(DC1, OUTPUT);
  pinMode(DC2, OUTPUT);
  pinMode(DC3, OUTPUT);
  pinMode(DC4, OUTPUT);
  // Set DC outpins to LOW
  digitalWrite(DC1, LOW);
  digitalWrite(DC2, LOW);
  digitalWrite(DC3, LOW);
  digitalWrite(DC4, LOW);

// configure LED PWM functionalitites
  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcSetup(ledChannel3, freq, resolution);
  ledcSetup(ledChannel4, freq, resolution);


  // attach the channel to the GPIO to be controlled
  ledcAttachPin(DC1, ledChannel1);
  ledcAttachPin(DC2, ledChannel2);
  ledcAttachPin(DC3, ledChannel3);
  ledcAttachPin(DC4, ledChannel4);
}
//Time variables
char time_dayOfWeek[10];
char time_month[10];
char time_dayOfMonth[3];
char time_year[5];
char time_hour24[3];
char time_hour12[3];
char time_minute[3];
char time_second[3];




void setLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  strftime(time_dayOfWeek,10,"%A", &timeinfo);
  strftime(time_month, 10, "%B", &timeinfo);
  strftime(time_dayOfMonth, 3, "%d", &timeinfo);
  strftime(time_year, 5, "%Y", &timeinfo);
  strftime(time_hour24, 3, "%H", &timeinfo);
  strftime(time_hour24, 3, "%I", &timeinfo);
  strftime(time_minute, 3, "%M", &timeinfo);
  strftime(time_second, 3, "%S", &timeinfo);

  fullDate = String(time_dayOfWeek)+ ", " + String(time_month) +" "+String(time_dayOfMonth)+" "+String(time_year)+" "+String(time_hour24)+":"+String(time_minute);//+":"+String(time_second);

  tout("Date :");tout(time_dayOfWeek);tout(time_month);tout(time_dayOfMonth);
  tout(time_year);tout(time_hour24);tout(time_minute);toutln(time_second);
  toutln(fullDate);
  notifyClients(getSensorValues());
  
}


#endif