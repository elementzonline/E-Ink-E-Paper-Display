/*
  Example Program for a Tricolor E-Ink Display
  with 200*200px Resolution & 1.54" Display

  Last Edited Date: July 31, 2022
*/

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_ThinkInk.h"
#include "main.h"

/*
  ESP32 - E-Ink Display Connections

  BS1 or BS Pin
  L -> 4-wire SPI (SCL, SDA, DC, CS)
  H -> 3-wire SPI (SCL, SDA, CS) (DC Tied to Low)

  BS Pin -> GND
*/
#define EPD_RESET 26 // Diplay Reset
#define EPD_BUSY 4   // Display Rendering
#define EPD_CS 5     // Chip Select
#define EPD_DC 25    // Data / Command
#define EPD_D0 18    // (SCK / SCL)
#define EPD_D1 23    // (MOSI / SDA)
#define SRAM_CS -1   // No SRAM

Adafruit_SSD1681 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

void setup(void)
{
  Serial.begin(115200);

  Serial.println();
  Serial.println("=================================================");
  Serial.print(" E-Ink 1.54\" Display ");
  Serial.print("Example");
  Serial.println();
  Serial.println("=================================================");
  Serial.println();

  /*
    Display Initialization
  */
  Serial.print("Intializing Display");
  display.begin();

  Serial.print(" - ");
  Serial.print(display.width());
  Serial.print("x");
  Serial.print(display.height());
  Serial.println();

  /*
    Invert if Flexible Display is used
  */
#if defined(FLEXIBLE_213) || defined(FLEXIBLE_290)
  display.setBlackBuffer(1, false);
  display.setColorBuffer(1, false);
#endif

  display.setRotation(2);
}

void loop()
{
  /*
    Bitmap
  */
  display.clearBuffer();
  display.setTextColor(EPD_RED);
  display.drawBitmap(
      0,
      (int)((display.height() - LOGO_HEIGHT) / 4),
      Bitmap_Elementz_Logo_E, LOGO_WIDTH_E, LOGO_HEIGHT, 2);
  display.drawBitmap(
      LOGO_WIDTH_E,
      (int)((display.height() - LOGO_HEIGHT) / 4),
      Bitmap_Elementz_Logo_lementz, LOGO_WIDTH, LOGO_HEIGHT, 1);

  display.setCursor((display.width() - 144) / 2 + 12, (display.height() / 2) + 36);
  display.setTextSize(2);
  display.setTextColor(EPD_RED);
  display.print("Tri ");
  display.setTextColor(EPD_BLACK);
  display.print("Color!");

  /*
    Render Display
  */
  display.display();
  delay(8000);

  /*
    Text
  */
  display.clearBuffer();
  // display.setTextWrap(true);
  display.setCursor((display.width() - 144) / 2, (display.height() - 24) / 2);
  display.setTextSize(2);
  display.setTextColor(EPD_BLACK);
  display.print("Hello ");

  display.setTextColor(EPD_RED);
  display.print("World!");

  /*
    Render Display
  */
  display.display();
  delay(8000);

  /*
    Render Display
  */
  display.display();
  delay(8000);

  /*
    Rectangles
  */
  display.clearBuffer();
  display.fillRect(display.width() / 3, 0, display.width() / 3, display.height(), EPD_BLACK);
  display.fillRect((display.width() * 2) / 3, 0, display.width() / 3, display.height(), EPD_RED);

  /*
    Render Display
  */
  display.display();
  delay(8000);
}

