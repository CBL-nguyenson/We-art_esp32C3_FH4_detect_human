#include <Arduino.h>

// https://github.com/HomeSpan/HomeSpan/blob/master/docs/ServiceList.md#fan-b7

struct SEAN_DEV_FAN : Service ::Fan
{
    uint8_t PinDetect;
    uint8_t Fan_Button_Start_Stop;
    uint8_t Fan_Button_1;
    uint8_t Fan_Button_2;
    uint8_t Fan_Button_3;

    SpanCharacteristic *Active_Fan;
    SpanCharacteristic *Speed_fan;
    // SpanCharacteristic *Current_Fan_State;

    SEAN_DEV_FAN(uint8_t Fan_Button_1, uint8_t Fan_Button_2, uint8_t Fan_Button_3, uint8_t Fan_Button_Start_Stop) : Service ::Fan()
    {

        Active_Fan = new Characteristic::Active();
        Speed_fan = new Characteristic::RotationSpeed(0);
        Speed_fan->setRange(0, 100, 5);

        new SpanButton(Fan_Button_1);
        new SpanButton(Fan_Button_2);
        new SpanButton(Fan_Button_3);
        new SpanButton(Fan_Button_Start_Stop);

        this->Fan_Button_1 = Fan_Button_1;
        this->Fan_Button_2 = Fan_Button_2;
        this->Fan_Button_3 = Fan_Button_3;
        this->Fan_Button_Start_Stop = Fan_Button_Start_Stop;
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
                Active_Fan->setVal(1);
                Speed_fan->setVal(33);
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
                Active_Fan->setVal(1);
                Speed_fan->setVal(66);
            }
        }

        if (pin == Fan_Button_3)
        {
            if (pressType == SpanButton::SINGLE)
            { // if a SINGLE press of the button...
                Active_Fan->setVal(1);
                Speed_fan->setVal(100);
            }
        }

        if (pin == Fan_Button_Start_Stop)
        {
            if (Active_Fan->getNewVal() == true)
            {
                Active_Fan->setVal(0);
                Speed_fan->setVal(0);
            }
            else if (Active_Fan->getNewVal() == false)
            {
                Active_Fan->setVal(1);
                Speed_fan->setVal(50);
            }
        }
    }
    //--------------------------Update-----------------------
    boolean update()
    {

        // digitalWrite(ledPin,power->getNewVal());
        return (true);
    }
    //--------------------------LOOP-----------------------
    void loop()
    {

    } // loop
};

// void click_Bt_1(){
//     Active_Fan -> setVal(1);
//     Speed_fan -> setVal(33);
// }
// void click_Bt_2(){
//     Active_Fan -> setVal(1);
//     Speed_fan -> setVal(66);
// }
// void click_Bt_3(){
//     Active_Fan -> setVal(1);
//     Speed_fan -> setVal(100);
// }
// void click_Bt_Start_Stop(){
//     if (Active_Fan->getNewVal() == 1){
//         Active_Fan -> setVal(0);
//         Speed_fan -> setVal(0);
//     }
//     else if (Active_Fan->getNewVal() == 0){
//         Active_Fan -> setVal(1);
//         Speed_fan -> setVal(50);
//     }
// }