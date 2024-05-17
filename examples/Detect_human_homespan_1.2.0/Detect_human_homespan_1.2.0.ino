#include <Arduino.h>
#include "HomeSpan.h"
#include "SEAN_DEV_Sensor.h"
// https://github.com/HomeSpan/HomeSpan/blob/master/docs/ServiceList.md#motionsensor-85

void setup()
{
  delay(100);
  Serial.begin(115200);
  // Serial1.begin(115200, SERIAL_8N1, 20 , 21);

  // setCpuFrequencyMhz(80);


  homeSpan.begin(Category::Bridges, "HomeSpan Sensor detect");

  homeSpan.setLogLevel(1);
  
  homeSpan.enableAutoStartAP();
  homeSpan.setApSSID("MakerLab_homekit");
  homeSpan.setApPassword("27272727");

  homeSpan.setControlPin(9);// nút điều khiển 
  homeSpan.setStatusPin(8);// led trạng thái
  // homeSpan.setPairingCode("27272727");

  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();         
      new Characteristic::Name("Ramdom_value_test"); 
      new Characteristic::Model("MakerLab_test_device");    
      new Characteristic::SerialNumber("MKE_IOT_1.1.0"); 
    

  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("DECTEC RD-03");
      new SEAN_DEV_Motion_Sensor(1);  



//--------------------------------
// homeSpan.autoPoll();
}

void loop()
{
  // put your main code here, to run repeatedly:
  homeSpan.poll();
}
