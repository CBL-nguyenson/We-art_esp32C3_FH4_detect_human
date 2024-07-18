#include <Arduino.h>

#if defined(CONFIG_IDF_TARGET_ESP32)

#define NEOPIXEL_RGB_PIN 26
#define NEOPIXEL_RGBW_PIN 32
#define DOTSTAR_DATA_PIN 33
#define DOTSTAR_CLOCK_PIN 27
#define DEVICE_SUFFIX ""

#elif defined(CONFIG_IDF_TARGET_ESP32S2)

#define NEOPIXEL_RGB_PIN 17
#define NEOPIXEL_RGBW_PIN 38
#define DOTSTAR_DATA_PIN 3
#define DOTSTAR_CLOCK_PIN 7
#define DEVICE_SUFFIX "-S2"

#elif defined(CONFIG_IDF_TARGET_ESP32C3)

#define NEOPIXEL_RGB_PIN 0
#define NEOPIXEL_RGBW_PIN 3
#define DOTSTAR_DATA_PIN 7
#define DOTSTAR_CLOCK_PIN 2

#define DEVICE_SUFFIX "-C3"

#endif

struct SEAN_DEV_Pixel : Service::LightBulb
{ // Addressable single-wire RGB LED Strand (e.g. NeoPixel)

  Characteristic::On power{0, true};
  Characteristic::Hue H{0, true};
  Characteristic::Saturation S{0, true};
  Characteristic::Brightness V{100, true};
  Pixel *pixel;
  int nPixels;

  SEAN_DEV_Pixel(uint8_t pin, int nPixels) : Service::LightBulb()
  {

    V.setRange(5, 100, 1);   // sets the range of the Brightness to be from a min of 5%, to a max of 100%, in steps of 1%
    pixel = new Pixel(pin);  // creates Pixel LED on specified pin
    this->nPixels = nPixels; // save number of Pixels in this LED Strand
    update();                // manually call update() to set pixel with restored initial values
  }

  boolean update() override
  {

    int p = power.getNewVal();

    float h = H.getNewVal<float>(); // range = [0,360]
    float s = S.getNewVal<float>(); // range = [0,100]
    float v = V.getNewVal<float>(); // range = [0,100]

    Pixel::Color color;

    pixel->set(color.HSV(h * p, s * p, v * p), nPixels); // sets all nPixels to the same HSV color

    return (true);
  }
};

// void loop() override {

//   // Below we set power and level once fading from a button press is completed

//   if (ledPin->fadeStatus() == LedPin::COMPLETED) {
//     power->setVal(1 - power->getVal());
//     level->setVal(power->getVal() ? 100 : 0);
//   }
// }
