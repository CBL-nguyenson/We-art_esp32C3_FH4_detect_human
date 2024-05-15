#include <Arduino.h>
#include "HomeSpan.h"
#include "SEAN_DEV_Sensor.h"
// https://github.com/HomeSpan/HomeSpan/blob/master/docs/ServiceList.md#motionsensor-85

void setup()
{
  Serial.begin(115200);
  homeSpan.setLogLevel(1);
  // setCpuFrequencyMhz(80);

  homeSpan.begin(Category::Bridges, "HomeSpan Sensor detect");

  homeSpan.setStatusPin(8);
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
      new SEAN_DEV_Motion_Sensor(10);  



//--------------------------------
// homeSpan.autoPoll();
}

void loop()
{
  // put your main code here, to run repeatedly:
  homeSpan.poll();
}
