#include <Arduino.h>

struct SEAN_DEV_Sensor : Service::MotionSensor
{

    SpanCharacteristic *MT_Sensor; //

    SEAN_DEV_Sensor() : Service::MotionSensor()
    { // constructor() method

        MT_Sensor = new Characteristic::MotionDetected(0);

        Serial.print("Configuring Detect Human");
        Serial.print("\n");

    } // end constructor

    void loop()
    {


        if (MT_Sensor->timeVal() > 500)             // modify the MT_Sensor Characteristic every 5 seconds
            MT_Sensor->setVal((double)random(0, 2)); 

    } // loop
};