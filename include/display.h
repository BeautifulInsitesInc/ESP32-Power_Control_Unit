#ifndef IZOKEE_DISPLAY_H
#define IZOKEE_DISPLAY_H

/*
 ----- Notes - 12C_12864_128x64_Display
 display.clearDisplay(); // Clear display buffer

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn line
    delay(1);
  }
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- FONTS ---
#include <Fonts/FreeSans9pt7b.h>
#define FONT1 &FreeSans9pt7b
#define LINE1 14
#define LINE2 32
#define LINE3 47
#define LINE4 62

#include <Fonts/FreeSansBold9pt7b.h>
#define FONT1B &FreeSansBold9pt7b

#include <Fonts/Picopixel.h>
#define FONT_PICO &Picopixel

#include <Fonts/FreeMonoOblique9pt7b.h>
#define FONT2 &FreeMonoOblique9pt7b

#include <Fonts/FreeMonoBold9pt7b.h>
#define FONT2B &FreeMonoBold9pt7b



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address;0x3C for esp32

Adafruit_SSD1306 Display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void rectangle(){
  Display.clearDisplay();
  Display.setFont(FONT1B);
  Display.setTextSize(1); 
  Display.setTextColor(BLACK);
  Display.fillRect(1, 1, 128, 15, WHITE);
}

void splashScreen() {
  rectangle();
  delay(2000);
  Display.setCursor(7, LINE1);
  Display.println(F("PROTOTYPE"));
  Display.display();
  delay(800);
  Display.setFont(FONT1);
  Display.setTextColor(WHITE);
  Display.setCursor(25,LINE2);
  Display.println(F(" POWER"));
  Display.display();
  delay(800);
  Display.setCursor(18,LINE3);
  Display.println(F(" CONTROL"));
  Display.display();
  delay(800);
  Display.setCursor(22,LINE4);
  Display.println(F(" CENTER"));
  Display.display();      // Show initial text
  delay(3000);
}

void normalText(){
  Display.setTextColor(WHITE);
  Display.setFont(FONT1);
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
}



void displaySetup() {

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally



  
  if(!Display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    outln(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  

  splashScreen();
 
}





void displayLoop() {
}







































#endif