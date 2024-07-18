#include <Arduino.h>
#include <WiFiManager.h>
#include "HomeSpan.h"
#include "SEAN_DEV_Sensor.h"
#include "SEAN_DEV_FAN.h"
#include "SEAN_DEV_LED.h"
#include "SEAN_DEV_Switch.h"
#include "SEAN_DEV_Pixel.h"

// https://github.com/HomeSpan/HomeSpan/blob/master/docs/ServiceList.md#motionsensor-85

void setup()
{
  Serial.begin(115200);
  // Serial1.begin(115200, SERIAL_8N1, 20 , 21);

  // setCpuFrequencyMhz(80);

  homeSpan.begin(Category::Bridges, "TEST_HomeSpan MakerLab_V2");

  homeSpan.setLogLevel(1);

  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Name("ARDUINO_DAY_NEOPIXEL");
  new Characteristic::Model("MakerLab_test_device");
  new Characteristic::SerialNumber("MKE_IOT_1.2.0");

  // new SpanAccessory();
  // new Service::AccessoryInformation();
  // new Characteristic::Identify();
  // new Characteristic::Name("DECTEC RD-03");
  // new SEAN_DEV_Motion_Sensor(1);

  // new SpanAccessory();
  // new Service::AccessoryInformation();
  // new Characteristic::Identify();
  // new Characteristic::Name("Fan supper cool");
  // new SEAN_DEV_FAN(10, 7, 6, 0, 5, 4, 3);

  // Fan_Button_1           pin: 10
  // Fan_Button_2           pin: 7
  // Fan_Button_3           pin: 6
  // Fan_Button_Start_Stop  pin: 0

  // new SpanAccessory();
  // new Service::AccessoryInformation();
  // new Characteristic::Identify();
  // new Characteristic::Name("USB-1");
  // new SEAN_DEV_DimmableLED(10);

  // new SpanAccessory();
  // new Service::AccessoryInformation();
  // new Characteristic::Identify();
  // new Characteristic::Name("USB-2");
  // new SEAN_DEV_DimmableLED(20);

  // new SpanAccessory();
  // new Service::AccessoryInformation();
  // new Characteristic::Identify();
  // new Characteristic::Name("relay");
  // new SEAN_DEV_Switch(1, 21);

  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Name("Neopixel");
  new SEAN_DEV_Pixel(13, 600);

  // ------------------------------------------------------
  // homeSpan.autoPoll();
  homeSpan.setApSSID("MakerLab_homekit");
  homeSpan.setApPassword("27272727");

  // homeSpan.setControlPin(9); // nút điều khiển
  // homeSpan.setStatusPin(13);  // led trạng thái
  homeSpan.setPairingCode("27041601");
}

void loop()
{
  // put your main code here, to run repeatedly:
  homeSpan.poll();
}
