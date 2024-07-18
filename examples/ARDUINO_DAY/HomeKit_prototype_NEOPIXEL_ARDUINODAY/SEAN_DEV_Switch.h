struct SEAN_DEV_Switch : Service::Switch
{ // ON/OFF LED

  int ledPin;
  int Switch_Pin;
  SpanCharacteristic *Switch_power; // reference to the On Characteristic

  SEAN_DEV_Switch(uint8_t Switch_Pin, uint8_t ledPin) : Service::Switch()
  { // constructor() method
    new SpanButton(Switch_Pin);
    Switch_power = new Characteristic::On();
    this->ledPin = ledPin;
    pinMode(ledPin, OUTPUT);

  } // end constructor

  boolean update()
  { // update() method

    digitalWrite(ledPin, Switch_power->getNewVal());

    return (true); // return true

  } // update
  void button(int pin, int pressType) override
  {

    LOG1("Found button press on pin: "); // always a good idea to log messages
    LOG1(pin);
    LOG1("  type: ");
    LOG1(pressType == SpanButton::LONG ? "LONG" : (pressType == SpanButton::SINGLE) ? "SINGLE"
                                                                                    : "DOUBLE");
    LOG1("\n");

    if (pin == Switch_Pin)
    {
      if (pressType == SpanButton::SINGLE)
      { // if a SINGLE press of the button...
        if (Switch_power->getNewVal() == 1)
        {
          Switch_power->setVal(0);
        }else{
          Switch_power->setVal(1);
        }
      }
      else if (pressType == SpanButton::DOUBLE)
      { // if a DOUBLE press of the button...
      }
      else if (pressType == SpanButton::LONG)
      { // if a LONG press of th button...
      }
    }
  }
};