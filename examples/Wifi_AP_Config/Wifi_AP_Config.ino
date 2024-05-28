#include "WiFiConfig.h"

// Tạo đối tượng WiFiConfig
WiFiConfig wifiConfig("ESP32_Config-C3", "12345678");

void setup() {
  wifiConfig.begin();
}

void loop() {
  wifiConfig.handleClient();
}
