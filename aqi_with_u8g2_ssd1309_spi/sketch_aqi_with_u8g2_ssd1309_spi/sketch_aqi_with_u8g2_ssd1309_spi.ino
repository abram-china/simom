// To use ArduinoGraphics APIs, please include BEFORE Arduino_LED_Matrix
#include "DFRobot_AirQualitySensor.h"

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#define I2C_ADDRESS 0x19
DFRobot_AirQualitySensor particle(&Wire ,I2C_ADDRESS);
U8G2_SSD1309_128X64_NONAME2_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);  

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

  pinMode(9, OUTPUT);
  digitalWrite(9, 0);	// default output in I2C mode for the SSD1306 test shield: set the i2c adr to 0

  u8g2.begin();

  uint8_t version = particle.gainVersion();
  Serial.print("version is : ");
  Serial.println(version);
  delay(1000);

  u8g2.setFontMode(1);	// Transparent
  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_5x8_tr);

}

void printOled(uint8_t line, String & str) {
  u8g2.drawStr(10,10 + line * 10, str.c_str());

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

  u8g2.clearBuffer();
  mystring = "Mini AQI Station";
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

  u8g2.sendBuffer();

  // Serial.println();
  delay(5000);
}
