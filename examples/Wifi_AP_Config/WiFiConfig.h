#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <WiFi.h>
#include <WebServer.h>

class WiFiConfig {
  public:
    WiFiConfig(const char* ap_ssid, const char* ap_password);
    void begin();
    void handleClient();

  private:
    const char* ap_ssid;
    const char* ap_password;
    WebServer server;

    void handleRoot();
    void handleConfigure();
    void handleRefresh();
    String generateHTML();
};

#endif // WIFI_CONFIG_H
