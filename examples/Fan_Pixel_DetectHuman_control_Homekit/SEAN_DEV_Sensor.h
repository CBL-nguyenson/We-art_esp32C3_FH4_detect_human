#include <Arduino.h>

struct SEAN_DEV_Motion_Sensor : Service ::MotionSensor
{
    int PinDetect;
    SpanCharacteristic *MTSensor;

    SEAN_DEV_Motion_Sensor(int PinDetect) : Service::MotionSensor(){

        MTSensor = new Characteristic::MotionDetected(0);
        // MTSensor->setRange(0, 1);

        this->PinDetect = PinDetect;
        pinMode(PinDetect, INPUT_PULLUP);

    }

    void loop()
    {
        // this->PinDetect = PinDetect;

        if (MTSensor->timeVal() > 100)
        {
            MTSensor->setVal(digitalRead(PinDetect));
            //--------------------------------
            // int State_sensor = digitalRead(PinDetect);
            // MTSensor->setVal(State_sensor);

            // LOG1("SEND Detect Human");
        }
    } // loop
};