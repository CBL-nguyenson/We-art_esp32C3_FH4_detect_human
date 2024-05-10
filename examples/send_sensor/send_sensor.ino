#include <Arduino.h>
#include "HomeSpan.h"
#include "SEAN_DEV_Sensor.h"
// https://github.com/HomeSpan/HomeSpan/blob/master/docs/ServiceList.md#motionsensor-85




void setup()
{
  Serial.begin(115200);
  setCpuFrequencyMhz(80);

  homeSpan.begin(Category::Bridges, "HomeSpan Sensor_detect");
homeSpan.setStatusPin(8);
  homeSpan.setPairingCode("27272727");

  new SpanAccessory(); 
    new Service::AccessoryInformation();
      new Characteristic::Identify();            
      new Characteristic::Name("Ramdom_value"); 
      new Characteristic::Model("MakerLab_test_device");    
      new Characteristic::SerialNumber("MKE_IOT_1.0.0"); 


  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("Detec_sensor_heheeheheheheeh");
    new SEAN_DEV_Sensor();     



//--------------------------------

}

void loop()
{
  // put your main code here, to run repeatedly:
 homeSpan.poll();  
}
