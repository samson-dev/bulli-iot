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

#include "bulliimg.h" // Load bulli image
#include "battery.h" // Load Battery Part

#include "bitmaps/Bitmaps640x384.h" // 7.5"  b/w

//EXample value and descriptions
const char Temperature[] = "18,8 Grad / 51%";
const char Datum[] = "09.09.2019";
const char Uhrzeit[] = "16:23";
int delaytime = 5000;
bool netz = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  init_display_battery();
  init_display();
}

void loop() {
  netz = true;
  printBattery();
  printPowerStatus();
  if(Volt >= 4)
    printVoltage();
  else 
       netz = false;
  //Volt--;
  if(k>0)
    k=k-5;
  display.setRotation(1);
  //display.drawImage(myBitmap, 317, 210, 83, 90);
  if(netz ==true)
    delaytime = 200;
   else
    delaytime = 5000;
  delay(delaytime);
}

void init_display() { //INIT Display technically and basic structure
  //Display Init
  display.init(115200); // uses standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
  display.setRotation(1);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  //Print template structure
  printHeader();
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HeaderPower, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setCursor(x, 105);
  display.print(HeaderPower);
  display.display();
  //display.setRotation(1);
  display.drawImage(myBitmap, 317, 210, 83, 90);
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
    display.fillRect(0, 0, (display.width()-90), 88, GxEPD_BLACK);
}
