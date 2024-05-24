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
    

    SEAN_DEV_FAN(uint8_t Fan_Button_1, uint8_t Fan_Button_2,uint8_t Fan_Button_3, uint8_t Fan_Button_Start_Stop) : Service ::Fan(){

        Active_Fan = new Characteristic::Active();
        Speed_fan = new Characteristic::RotationSpeed(0);
        Speed_fan->setRange(0,100,5);
   

        new SpanButton(Fan_Button_1);
        new SpanButton(Fan_Button_2);
        new SpanButton(Fan_Button_3);
        new SpanButton(Fan_Button_Start_Stop);

        this->Fan_Button_1 = Fan_Button_1;
        this->Fan_Button_2 = Fan_Button_2;
        this->Fan_Button_3 = Fan_Button_3;
        this->Fan_Button_Start_Stop = Fan_Button_Start_Stop;

        // //__________Button_state_1________
        // this->Fan_Button_1 = Fan_Button_1;
        // pinMode(Fan_Button_1, INPUT_PULLUP);
        // //__________Button_state_2________
        // this->Fan_Button_2 = Fan_Button_2;
        // pinMode(Fan_Button_2, INPUT_PULLUP);
        // //__________Button_state_3________
        // this->Fan_Button_3 = Fan_Button_3;
        // pinMode(Fan_Button_3, INPUT_PULLUP);
        // //____Button_state_Start_Stop_____
        // this->Fan_Button_Start_Stop = Fan_Button_Start_Stop;
        // pinMode(Fan_Button_Start_Stop, INPUT_PULLUP);
    
    }

    void click_Bt_1(){
        Active_Fan -> setVal(1);
        Speed_fan -> setVal(33);
    }
    void click_Bt_2(){
        Active_Fan -> setVal(1);
        Speed_fan -> setVal(66);
    }
    void click_Bt_3(){
        Active_Fan -> setVal(1);
        Speed_fan -> setVal(100);
    }
    void click_Bt_Start_Stop(){
        if (Active_Fan->getNewVal() == 1){
            Active_Fan -> setVal(0);
            Speed_fan -> setVal(0);   
        }
        else if (Active_Fan->getNewVal() == 0){
            Active_Fan -> setVal(1);
            Speed_fan -> setVal(50);   
        } 
    }
//--------------------------Update-----------------------
    boolean update(){            

    // digitalWrite(ledPin,power->getNewVal());        
    return(true);                                   
  } 
//--------------------------LOOP-----------------------
    void loop()
    {

    } // loop
};