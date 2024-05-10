#include <Arduino.h>

struct SEAN_DEV_Sensor : Service::MotionSensor
{

    SpanCharacteristic *MT_Sensor; //

    SEAN_DEV_Sensor() : Service::MotionSensor()
    { // constructor() method

        MT_Sensor = new Characteristic::MotionDetected(0);

        Serial.print("Configuring Air Quality Sensor"); // initialization message
        Serial.print("\n");

    } // end constructor

    void loop()
    {

        if (MT_Sensor->timeVal() > 5000)             // modify the MT_Sensor Characteristic every 5 seconds
            MT_Sensor->setVal((double)random(0, 2)); // simulate a change in Air Quality by incrementing the current value by one, and keeping in range 0-5

    } // loop
};