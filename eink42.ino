/**
  ******************************************************************************
  * @file    Main
  * @author  Samson-dev
  * @version V0.0.1
  * @date    14-Septembre-2019
  * @brief   The main file.
  *          This file provides firmware functions:
  *           + Initialization of Serial Port, SPI pins and server
  *           + Main loop
  *
  ******************************************************************************
  */ 

#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMono9pt7b.h>

#include "bulliimg.h" // Load bulli image
#include "battery.h" // Load Battery Part


#if defined(ESP32)
GxEPD2_BW<GxEPD2_420, GxEPD2_420::HEIGHT> display(GxEPD2_420(/*CS=15*/ 5, /*DC=4*/ 17, /*RST=5*/ 16, /*BUSY=16*/ 4));
//GxEPD2_BW<GxEPD2_750, GxEPD2_750::HEIGHT> display(GxEPD2_750(/*CS=*/ 15, /*DC=*/ 27, /*RST=*/ 26, /*BUSY=*/ 25));
#endif

#include "bitmaps/Bitmaps640x384.h" // 7.5"  b/w

//EXample value and descriptions
const char HeaderPower[] = "- Strom/Boardnetz -";
const char Voltage[] = "Boardspannung (V): ";
float Volt = 13.7;
int k =155;
const char StatusVoltage[] = "Netzstatus: Using Battery";
const char Temperature[] = "18,8 Grad / 51%";
const char Datum[] = "09.09.2019";
const char Uhrzeit[] = "16:23";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  init_display();
}

void loop() {
  printBattery();
  printVoltage();
  Volt--;
  k=k-5;
  delay(5000);
}

void init_display() { //INIT Display technically and basic structure
  //Display Init
  display.init(115200); // uses standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
  display.setRotation(0);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  //Print template structure
  printHeader();
  init_display_battery(display);
  display.setCursor(15, 105);
  display.print(HeaderPower);
  display.display();
  display.drawImage(myBitmap, 310, 0, 90, 83);
}

void printDateBox(){
    display.setTextColor(GxEPD_BLACK);
    display.drawLine(15, 340, (display.width()-15), 340, GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);
    display.setCursor(15, 15);
    display.print(Temperature);
    display.setCursor(20, 15);
    display.print(Datum);
    display.setCursor(350, 15);
    display.print(Uhrzeit);
}

void printHeader(){
    display.fillRect(0, 0, (display.width()-95), 83, GxEPD_BLACK);
}
