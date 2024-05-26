#include <Arduino.h>

// https://github.com/HomeSpan/HomeSpan/blob/master/docs/ServiceList.md#fan-b7

struct SEAN_DEV_FAN : Service ::Fan
{
    uint8_t Value_Speed_fan = 0;
    bool State_Active_Fan = true;

    uint8_t PinDetect;
    uint8_t Fan_Button_Start_Stop;
    uint8_t Fan_Button_1;
    uint8_t Fan_Button_2;
    uint8_t Fan_Button_3;

    uint8_t Fan_State_1;
    uint8_t Fan_State_2;
    uint8_t Fan_State_3;

    SpanCharacteristic *Active_Fan;
    SpanCharacteristic *Speed_fan;
    // SpanCharacteristic *Current_Fan_State;

    SEAN_DEV_FAN(
        uint8_t Fan_Button_1,
        uint8_t Fan_Button_2,
        uint8_t Fan_Button_3,
        uint8_t Fan_Button_Start_Stop,
        uint8_t Fan_State_1,
        uint8_t Fan_State_2,
        uint8_t Fan_State_3)
        : Service ::Fan()
    {

        //------------------------------------------------
        new SpanButton(Fan_Button_1);
        new SpanButton(Fan_Button_2);
        new SpanButton(Fan_Button_3);
        new SpanButton(Fan_Button_Start_Stop);

        this->Fan_Button_1 = Fan_Button_1;
        this->Fan_Button_2 = Fan_Button_2;
        this->Fan_Button_3 = Fan_Button_3;
        this->Fan_Button_Start_Stop = Fan_Button_Start_Stop;
        //------------------------------------------------
        this->Fan_State_1 = Fan_State_1;
        pinMode(Fan_State_1, OUTPUT);

        this->Fan_State_2 = Fan_State_2;
        pinMode(Fan_State_2, OUTPUT);

        this->Fan_State_3 = Fan_State_3;
        pinMode(Fan_State_3, OUTPUT);

        Active_Fan = new Characteristic::Active();
        Speed_fan = new Characteristic::RotationSpeed(0);
        Speed_fan->setRange(0, 100, uint8_t((100 / 3) + 0.7));
    }

    void button(int pin, int pressType) override
    {

        LOG1("Found button press on pin: "); // always a good idea to log messages
        LOG1(pin);
        LOG1("  type: ");
        LOG1(pressType == SpanButton::LONG ? "LONG" : (pressType == SpanButton::SINGLE) ? "SINGLE"
                                                                                        : "DOUBLE");
        LOG1("\n");

        if (pin == Fan_Button_1)
        {
            if (pressType == SpanButton::SINGLE)
            { // if a SINGLE press of the button...
                Active_Fan->setVal(true);
                State_Active_Fan = true;
                Speed_fan->setVal(33);
                Value_Speed_fan = 33;
            }
            else if (pressType == SpanButton::DOUBLE)
            { // if a DOUBLE press of the button...
            }
            else if (pressType == SpanButton::LONG)
            { // if a LONG press of th button...
            }
        }

        if (pin == Fan_Button_2)
        {
            if (pressType == SpanButton::SINGLE)
            { // if a SINGLE press of the button...
                Active_Fan->setVal(true);
                State_Active_Fan = true;
                Speed_fan->setVal(50);
                Value_Speed_fan = 50;
            }
        }

        if (pin == Fan_Button_3)
        {
            if (pressType == SpanButton::SINGLE)
            { // if a SINGLE press of the button...
                Active_Fan->setVal(true);
                State_Active_Fan = true;
                Speed_fan->setVal(100);
                Value_Speed_fan = 100;
            }
        }

        if (pin == Fan_Button_Start_Stop)
        {
            if (Active_Fan->getNewVal() == true)
            {
                Active_Fan->setVal(false);
                State_Active_Fan = false;
                Speed_fan->setVal(0);
                Value_Speed_fan = 0;
            }
            else if (Active_Fan->getNewVal() == false)
            {
                Active_Fan->setVal(true);
                State_Active_Fan = true;
                Speed_fan->setVal(50);
                Value_Speed_fan = 50;
            }
        }
    }
    //--------------------------Update-----------------------
    boolean update()
    {
        Value_Speed_fan = Speed_fan->getNewVal();
        State_Active_Fan = Active_Fan->getNewVal();
        return (true);
    }
    //--------------------------LOOP-----------------------
    void loop()
    {
        if (Active_Fan->timeVal() > 100)
        {
            if (Speed_fan->getVal() == 99)
            {
                Speed_fan->setVal(100);
                State_Active_Fan = 100;
            }
            if (!State_Active_Fan)
            {
                digitalWrite(Fan_State_1, LOW);
                digitalWrite(Fan_State_2, LOW);
                digitalWrite(Fan_State_3, LOW);
                // Speed_fan->setVal(0);
                // Value_Speed_fan = 0;
            }
            else
            {
                if ((Value_Speed_fan > 5) && (Value_Speed_fan <= 43))
                {
                    digitalWrite(Fan_State_1, HIGH);
                    digitalWrite(Fan_State_2, LOW);
                    digitalWrite(Fan_State_3, LOW);
                }
                else if ((Value_Speed_fan > 35) && (Value_Speed_fan < 66))
                {
                    digitalWrite(Fan_State_1, LOW);
                    digitalWrite(Fan_State_2, HIGH);
                    digitalWrite(Fan_State_3, LOW);
                }
                else if (Value_Speed_fan >= 66)
                {
                    digitalWrite(Fan_State_1, LOW);
                    digitalWrite(Fan_State_2, LOW);
                    digitalWrite(Fan_State_3, HIGH);
                }
                else if (Value_Speed_fan <= 5)
                {
                    digitalWrite(Fan_State_1, LOW);
                    digitalWrite(Fan_State_2, LOW);
                    digitalWrite(Fan_State_3, LOW);
                }
            }
        }
    }
};