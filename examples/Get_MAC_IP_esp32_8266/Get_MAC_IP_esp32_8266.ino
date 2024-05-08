

#include <WiFi.h>
void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.print("Địa chỉ MAC của ESP Board:  ");
  Serial.println(WiFi.macAddress());
  delay(3000);
}
