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

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address;0x3C for esp32
Adafruit_SSD1306 Display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void splashScreen() {
  Display.clearDisplay();
  Display.setTextSize(2); // Draw 2X-scale text
  Display.setTextColor(SSD1306_WHITE);
  Display.setCursor(0, 0);
  Display.println(F(" PROTOTYPE"));
  delay(500);
  //Display.setTextSize(1.5);
  Display.println(F(" POWER"));
  
  delay(500);
  //Display.stopscroll();
  Display.println(F(" CONTROL"));
  delay(500);
  Display.println(F(" CENTER"));
  Display.display();      // Show initial text
  //Display.startscrollright(0,1);
  delay(3000);
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