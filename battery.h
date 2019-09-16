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
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMono9pt7b.h>

#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

#if defined(ESP32)
GxEPD2_BW<GxEPD2_420, GxEPD2_420::HEIGHT> display(GxEPD2_420(/*CS=15*/ 5, /*DC=4*/ 17, /*RST=5*/ 16, /*BUSY=16*/ 4));
//GxEPD2_BW<GxEPD2_750, GxEPD2_750::HEIGHT> display(GxEPD2_750(/*CS=*/ 15, /*DC=*/ 27, /*RST=*/ 26, /*BUSY=*/ 25));
#endif

//EXample value and descriptions
const char HeaderPower[] = "- Strom/Boardnetz -";
const char Voltage[] = "Boardspannung (V):";
float Volt = 13.7;
int k =100;
const char StatusVoltage[] = "Netzstatus: Using Battery";

void init_display_battery(){
  display.init(115200);
  display.setRotation(1);
  ina219.begin();
}

void printBatteryCallback(const void*){
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    //draw Battery
    //display.drawLine(5, 270, (display.width()-5), 270, GxEPD_BLACK); //Horizontal Linie
    display.drawLine(5, 290, (display.width()-5), 290, GxEPD_BLACK); //Vertial Linie
    display.drawRect((display.width()/2)-50, 125, 100, 50, GxEPD_BLACK); //Batterie Körper
    for(int i=5;i<k;i=i+5){
      display.drawLine((((display.width()/2)-50)+i), 130,(((display.width()/2)-50)+i), 170, GxEPD_BLACK); //Batterie Ladebalken
    }
    display.drawRect((display.width()/2)-55, 145, 5, 10, GxEPD_BLACK); //Batterie Spitze
    //draw text - Power todo
}

void printBlackBatteryCallback(const void*){
        display.fillScreen(GxEPD_WHITE);
        display.drawRect((display.width()/2)-50, 125, 100, 50, GxEPD_BLACK); //Batterie Körper
        display.drawRect((display.width()/2)-55, 145, 5, 10, GxEPD_BLACK); //Batterie Spitze
}

void printWhiteBatteryCallback(const void*){
        display.fillScreen(GxEPD_WHITE);
        display.drawRect((display.width()/2)-50, 125, 100, 50, GxEPD_WHITE); //Batterie Körper
        display.drawRect((display.width()/2)-55, 145, 5, 10, GxEPD_WHITE); //Batterie Spitze
}


void printBattery(){
    display.setPartialWindow(0, 125, display.width(), 50); 
    display.drawPaged(printBatteryCallback, 0); 
    if(k==0){
        display.drawPaged(printBlackBatteryCallback, 0);
        delay(500); 
        display.drawPaged(printWhiteBatteryCallback, 0); 
        delay(500);
    }
}

void printVoltageCallback(const void*)
{
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(Voltage + String(Volt, 2), 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = 200;
  display.fillScreen(GxEPD_WHITE);
  display.setCursor(x, y);
  display.println(Voltage + String(ina219.getBusVoltage_V(), 2));
}

void printVoltage()
{
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(Voltage + String(Volt, 2), 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = 200;
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setPartialWindow(0, y - 14, display.width(), 20);
  display.drawPaged(printVoltageCallback, 0);
}

void printPowerStatusCallback(const void*)
{
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(StatusVoltage, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = 220;
  display.fillScreen(GxEPD_WHITE);
  display.setCursor(x, y);
  display.println(StatusVoltage);
}

void printPowerStatus()
{
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(StatusVoltage, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = 220;
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setPartialWindow(0, y - 10, display.width(), 20);
  display.drawPaged(printPowerStatusCallback, 0);
}
