/**
  ******************************************************************************
  * @file    Loader.h
  * @author  Waveshare Team
  * @version V1.0.0
  * @date    23-January-2018
  * @brief   The main file.
  *          This file provides firmware functions:
  *           + Initialization of Serial Port, SPI pins and server
  *           + Main loop
  *
  ******************************************************************************
  */ 

#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMono9pt7b.h>

GxEPD2_BW<GxEPD2_420, GxEPD2_420::HEIGHT> display;

void init_display_battery(display initDisplay){
  display = initDisplay;
}

void printBatteryCallback(const void*){
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    //draw Battery
    //display.drawLine(5, 270, (display.width()-5), 270, GxEPD_BLACK); //Horizontal Linie
    //display.drawLine(320, 125, 320, 270, GxEPD_BLACK); //Vertial Linie
    display.drawRect(10, 125, 150, 50, GxEPD_BLACK); //Batterie Körper
    for(int i=155;i>=10;i=i-5){
      display.drawLine((k-i), 130, (k-i), 170, GxEPD_BLACK); //Batterie Ladebalken
    }
    display.drawRect(5, 145, 5, 10, GxEPD_BLACK); //Batterie Spitze
    //draw text - Power todo
}


void printBattery(display ){
    display.setPartialWindow(0, 125, 160, 50); 
    display.drawPaged(printBatteryCallback, 0); 
}

void printVoltageCallback(const void*)
{
  uint16_t x = 0;
  uint16_t y = 200;
  display.fillScreen(GxEPD_WHITE);
  display.setCursor(x, y);
  display.println(Voltage + String(Volt, 2));
}

void printVoltage()
{
  uint16_t x = 0;
  uint16_t y = 200;
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setPartialWindow(0, y - 14, display.width(), 20);
  display.drawPaged(helloEpaperCallback, 0);
}
