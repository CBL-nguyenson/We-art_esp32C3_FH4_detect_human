#include <Arduino.h>

struct NeoPixel_RGB : Service::LightBulb {  // Addressable single-wire RGB LED Strand (e.g. NeoPixel)

  Characteristic::On power{ 0, true };
  Characteristic::Hue H{ 0, true };
  Characteristic::Saturation S{ 0, true };
  Characteristic::Brightness V{ 0, true };
  
  Pixel *pixel;
  int nPixels;
  int p;


  float h;
  float s;
  float v;

  NeoPixel_RGB(uint8_t pin, int nPixels): Service::LightBulb() {
    Pixel::Color color;
    V.setRange(5, 100, 1);    // sets the range of the Brightness to be from a min of 5%, to a max of 100%, in steps of 1%
    pixel = new Pixel(pin);   // creates Pixel LED on specified pin
    this->nPixels = nPixels;  // save number of Pixels in this LED Strand
                              // manually call update() to set pixel with restored initial values
  }

  boolean update() {

    p = power.getNewVal();

    h = H.getNewVal<float>();  // range = [0,360]
    s = S.getNewVal<float>();  // range = [0,100]
    v = V.getNewVal<float>();  // range = [0,100]



    pixel->set(color.HSV(h * p, s * p, v * p), nPixels);  // sets all nPixels to the same HSV color

    return (true);
  }
};