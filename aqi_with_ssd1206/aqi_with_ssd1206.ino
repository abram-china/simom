// To use ArduinoGraphics APIs, please include BEFORE Arduino_LED_Matrix
#include "DFRobot_AirQualitySensor.h"

#define I2C_ADDRESS    0x19
DFRobot_AirQualitySensor particle(&Wire ,I2C_ADDRESS);

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
String mystring;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  while(!particle.begin())
  {
    Serial.println("NO Deivces !");
    delay(1000);
  }
  Serial.println("sensor begin success!");

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (true);
    delay(1000);
  }

  uint8_t version = particle.gainVersion();
  Serial.print("version is : ");
  Serial.println(version);
  delay(1000);

  oled.clearDisplay(); // clear display

  oled.setTextSize(1);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.println("Hello World!"); // text to display
  oled.display();               // show on OLED
}

void printOled(uint8_t line, String & str) {
  oled.setCursor(0, line * 12);        // position to display
  oled.println(str.c_str());       // text to display
}
void loop() {
/**
 *@brief : 获取PM1.0  PM2.5  PM10浓度
 *@param :PARTICLE_PM1_0_STANDARD  标准颗粒物  
          PARTICLE_PM2_5_STANDARD  标准颗粒物  
          PARTICLE_PM10_STANDARD   标准颗粒物  
          PARTICLE_PM1_0_ATMOSPHERE  大气环境下
          PARTICLE_PM2_5_ATMOSPHERE  大气环境下
          PARTICLE_PM10_ATMOSPHERE   大气环境下
*/  
  uint16_t PM2_5_st = particle.gainParticleConcentration_ugm3(PARTICLE_PM2_5_STANDARD);
  uint16_t PM1_0_st = particle.gainParticleConcentration_ugm3(PARTICLE_PM1_0_STANDARD);
  uint16_t PM10_st = particle.gainParticleConcentration_ugm3(PARTICLE_PM10_STANDARD);

  uint16_t PM2_5_at = particle.gainParticleConcentration_ugm3(PARTICLE_PM2_5_ATMOSPHERE);
  uint16_t PM1_0_at = particle.gainParticleConcentration_ugm3(PARTICLE_PM1_0_ATMOSPHERE);
  uint16_t PM10_at = particle.gainParticleConcentration_ugm3(PARTICLE_PM10_ATMOSPHERE);

  oled.clearDisplay(); // clear display
  mystring = "Mirco AQI Station";
  printOled(0, mystring);
  mystring = "PM2.5: "+ String(PM2_5_st, DEC) +"(ug/m3)";
  printOled(2, mystring);

  // Serial.println(mystring);

  mystring = "PM1.0: "+ String(PM1_0_st, DEC) +"(ug/m3)";
  printOled(3, mystring);

  // Serial.print("PM1.0 : ");
  // Serial.print(PM1_0_st);
  // Serial.print("(st)/");
  // Serial.print(PM1_0_at);
  // Serial.println("(at) ug/m3");

  mystring = "PM10 : "+ String(PM10_st, DEC) +"(ug/m3)";
  printOled(4, mystring);

  // Serial.print("PM10 : ");
  // Serial.print(PM10_st);
  // Serial.print("(st)/");
  // Serial.print(PM10_at);
  // Serial.println("(at) ug/m3");

  oled.display();               // show on OLED

  // Serial.println();
  delay(1000);
}
