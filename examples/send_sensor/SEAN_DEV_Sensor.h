#include <Arduino.h>

struct SEAN_DEV_Sensor : Service :: MotionSensor {
    
    SpanCharacteristic *MT_Sensor; //
    int Button_pin_detect;

    SEAN_DEV_Sensor(int Button_pin_detect) : Service::MotionSensor(){

        MT_Sensor = new Characteristic::MotionDetected();

        this->Button_pin_detect = Button_pin_detect;
        pinMode(Button_pin_detect, INPUT_PULLUP);
        Serial.print("Configuring Detect Human");
        Serial.print("\n");

    } 

    void loop()
    {
        this->Button_pin_detect = Button_pin_detect;

        if (MT_Sensor->timeVal() > 300){
            // MT_Sensor->setVal(digitalRead(Button_pin_detect));
            //--------------------------------
            int State_sensor = digitalRead(Button_pin_detect);
            MT_Sensor->setVal(State_sensor);
        // int State_sensor = MT_Sensor->digitalRead(Button_pin_detect);
        // int State_sensor = digitalRead(Button_pin_detect);
            
            // Serial.println("SEND Detect Human");
        }
    } // loop
};