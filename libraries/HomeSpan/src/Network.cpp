/*********************************************************************************
 *  MIT License
 *
 *  Copyright (c) 2020-2024 Gregg E. Berman
 *
 *  https://github.com/HomeSpan/HomeSpan
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 ********************************************************************************/

#include <DNSServer.h>

#include "Network.h"
#include "HomeSpan.h"
#include "Utils.h"

using namespace Utils;

///////////////////////////////

void Network::scan()
{

  int n = WiFi.scanNetworks();

  free(ssidList);
  ssidList = (char **)HS_CALLOC(n, sizeof(char *));
  numSSID = 0;

  for (int i = 0; i < n; i++)
  {
    boolean found = false;
    for (int j = 0; j < numSSID; j++)
    {
      if (!strcmp(WiFi.SSID(i).c_str(), ssidList[j]))
        found = true;
    }
    if (!found)
    {
      ssidList[numSSID] = (char *)HS_CALLOC(WiFi.SSID(i).length() + 1, sizeof(char));
      sprintf(ssidList[numSSID], "%s", WiFi.SSID(i).c_str());
      numSSID++;
    }
  }
}

///////////////////////////////

void Network::serialConfigure()
{

  wifiData.ssid[0] = '\0';
  wifiData.pwd[0] = '\0';

  LOG0("*** WiFi Setup - Scanning for Networks...\n\n");

  scan(); // scan for networks

  for (int i = 0; i < numSSID; i++)
    LOG0("  %d) %s\n", i + 1, ssidList[i]);

  while (!strlen(wifiData.ssid))
  {
    LOG0("\n>>> WiFi SSID: ");
    readSerial(wifiData.ssid, MAX_SSID);
    if (atoi(wifiData.ssid) > 0 && atoi(wifiData.ssid) <= numSSID)
    {
      strcpy(wifiData.ssid, ssidList[atoi(wifiData.ssid) - 1]);
    }
    LOG0("%s\n", wifiData.ssid);
  }

  while (!strlen(wifiData.pwd))
  {
    LOG0(">>> WiFi PASS: ");
    readSerial(wifiData.pwd, MAX_PWD);
    LOG0("%s\n", mask(wifiData.pwd, 2).c_str());
  }

  return;
}

///////////////////////////////

boolean Network::allowedCode(char *s)
{
  return (
      strcmp(s, "00000000") && strcmp(s, "11111111") && strcmp(s, "22222222") && strcmp(s, "33333333") &&
      strcmp(s, "44444444") && strcmp(s, "55555555") && strcmp(s, "66666666") && strcmp(s, "77777777") &&
      strcmp(s, "88888888") && strcmp(s, "99999999") && strcmp(s, "12345678") && strcmp(s, "87654321"));
}

///////////////////////////////
//___________________________________________SEAN_____________________________
// WiFiConfig(DEFAULT_AP_SSID, DEFAULT_AP_PASSWORD)
//     : apSSID(apSSID), apPassword(apPassword), server(80) {}

void Network::begin_AP()
{
  // Serial.begin(115200);

  // Khởi động WiFi ở chế độ AP
  WiFi.softAP(apSSID, apPassword);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Thiết lập các route
  server.on("/", [this]()
            { handleRoot(); });
  server.on("/configure_wifi", HTTP_POST, [this]()
            { handleConfigure(); });
  server.on("/refresh", HTTP_GET, [this]()
            { handleRefresh(); });

  // Bắt đầu máy chủ web
  server.begin();

  Serial.println("Server started");
  Serial.println("Connect to AP 'ESP32_Config' and navigate to http://192.168.4.1");
}

void Network::handleClient()
{
  server.handleClient();
}

void Network::handleRoot()
{
  server.send(200, "text/html", generateHTML());
}

void Network::handleConfigure()
{
  user_ssid = server.arg("ssid");
  String ssid_manual = server.arg("ssid_manual");
  user_password = server.arg("password");

  if (user_ssid == "manual")
  {
    user_ssid = ssid_manual;
  }

  server.send(200, "text/html", "Configuration Saved. Please restart the device to connect to WiFi.");

  Serial.println("SSID and Password stored. Please restart to connect.");
}

bool Network::is_config()
{
  if (config_WF == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

String Network::SSID_S()
{
  return user_ssid;
}

String Network::PASS_S()
{
  return user_password;
}
void Network::connectToWiFi()
{
  if (user_ssid.length() == 0)
  {
    Serial.println("No SSID provided. Please configure WiFi first.");
    return;
  }

  if (user_password.length() == 0)
  {
    // Kết nối WiFi không có mật khẩu
    WiFi.begin(user_ssid.c_str());
  }
  else
  {
    // Kết nối WiFi có mật khẩu
     WiFi.begin(wifiData.ssid, wifiData.pwd);
  }

  Serial.print("Connecting to ");
  Serial.println(user_ssid);

  // Đợi và kiểm tra kết nối
  int timeout = 20; // 20 * 500ms = 10s timeout
  while (WiFi.status() != WL_CONNECTED && timeout > 0)
  {
    delay(200);
    Serial.print(".");
    timeout--;
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("\nConnected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("\nFailed to connect to WiFi.");
  }
}

void Network::handleRefresh()
{
  handleRoot();
}

String Network::generateHTML()
{
  String htmlPageStart = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <style>
        body {
            background-color: black;
            color: white;
            font-family: Arial, sans-serif;
        }
        form {
            display: flex;
            flex-direction: column;
            align-items: center;
            margin-top: 30px;
        }
        label {
            font-size: 150%;
            margin: 10px;
        }
        input {
            font-size: 120%;
            margin: 10px;
            padding: 10px;
            border: 1px solid white;
            background-color: black;
            color: white;
        }
        button {
            font-size: 120%;
            margin: 10px;
            padding: 10px 20px;
            border: 1px solid white;
            background-color: black;
            color: white;
            cursor: pointer;
        }
        button:hover {
            background-color: grey;
        }
        img {
            display: block;
            margin: 20px auto;
        }
        select {
            font-size: 120%;
            margin: 10px;
            padding: 10px;
            border: 1px solid white;
            background-color: black;
            color: white;
        }
    </style>
    <script>
        function toggleManualSSIDInput(select) {
            var ssidInput = document.getElementById("ssid_manual");
            if (select.value === "manual") {
                ssidInput.style.display = "block";
            } else {
                ssidInput.style.display = "none";
            }
        }
    </script>
</head>
<body>
    <center>
        <p><b>WiFi Configuration</b></p>
    </center>
    <center>
        <img src="https://www.makerlab.vn/wp-content/uploads/2022/09/Logo-MakerLab-544x180-1.png" alt="MakerLab Logo">
    </center>
    <form action="/configure_wifi" method="post">
        <label for="ssid">WiFi SSID:</label>
        <select id="ssid" name="ssid" onchange="toggleManualSSIDInput(this)">
            <option value="manual">Enter SSID manually</option>
)rawliteral";

  String htmlPageMiddle = R"rawliteral(
        </select>
        <input type="text" id="ssid_manual" name="ssid_manual" style="display:none" placeholder="Enter SSID manually">
        
        <label for="password">Password:</label>
        <input type="password" id="password" name="password">
        
        <button type="submit">Configure</button>
    </form>
    <form action="/refresh" method="get">
        <button type="submit">Refresh WiFi List</button>
    </form>
</body>
</html>
)rawliteral";

  String htmlPage = htmlPageStart;

  int n = WiFi.scanNetworks();
  if (n == 0)
  {
    htmlPage += "<option value=\"\">No networks found</option>";
  }
  else
  {
    for (int i = 0; i < n; ++i)
    {
      htmlPage += "<option value=\"" + String(WiFi.SSID(i)) + "\">" + String(WiFi.SSID(i)) + "</option>";
    }
  }

  htmlPage += htmlPageMiddle;

  return htmlPage;
}
//___________________________________________SEAN_____________________________
//////////////////////////////
void Network::apConfigure()
{
  wifiData.ssid[0] = '\0';
  wifiData.pwd[0] = '\0';
  LOG0("*** Starting Access Point: %s / %s\n", apSSID, apPassword);
  // WiFiConfig wifiConfig(apSSID, apPassword);

  STATUS_UPDATE(start(LED_AP_STARTED), HS_AP_STARTED)

  LOG0("\nScanning for Networks...\n\n");
  //////////////////////////////////// SEANSEAN
  begin_AP();                         
  //////////////////////////////////
  alarmTimeOut = millis() + lifetime; // Access Point will shut down when alarmTimeOut is reached
  apStatus = 0;                       // status will be "timed out" unless changed

  LOG0("\nReady.\n");

  while (1)
  { // loop until we get timed out (which will be accelerated if save/cancel selected)

    if (homeSpan.controlButton && homeSpan.controlButton->triggered(9999, 3000))
    {
      LOG0("\n*** Access Point Terminated.  Restarting...\n\n");
      STATUS_UPDATE(start(LED_ALERT), HS_AP_TERMINATED)
      homeSpan.controlButton->wait();
      homeSpan.reboot();
    }

    if (millis() > alarmTimeOut)
    {
      WiFi.softAPdisconnect(true); // terminate connections and shut down captive access point
      delay(100);
      if (apStatus == 1)
      {
        LOG0("\n*** Access Point: Exiting and Saving Settings\n\n");
        return;
      }
      else
      {
        if (apStatus == 0)
          LOG0("\n*** Access Point: Timed Out (%ld seconds).", lifetime / 1000);
        else
          LOG0("\n*** Access Point: Configuration Cancelled.");
        LOG0("  Restarting...\n\n");
        STATUS_UPDATE(start(LED_ALERT), HS_AP_TERMINATED)
        homeSpan.reboot();
      }
    }
    // wifiConfig.handleClient();
    if (is_config() == true)
    {
      while (true)
      {
        if (WiFi.status() != WL_CONNECTED)
        {
  // WiFi.begin(wifiData.ssid, wifiData.pwd);
          char Sean_ssid[MAX_SSID+1];
          char Sean_pass[MAX_SSID+1];
          strcpy(wifiData.ssid, SSID_S().toCharArray(Sean_ssid, MAX_SSID+1));
          // wifiData.ssid   = str.toCharArray(SSID_S(), MAX_SSID+1);
          strcpy(wifiData.pwd, PASS_S().toCharArray(Sean_pass, MAX_PWD+1));
          // wifiData.pwd   = str.toCharArray(PASS_S(), MAX_PWD+1);
          connectToWiFi();
        }
        else
        {
          homeSpan.reboot();
        }
      }
    }

    // SEANSEAN
    LOG2("\n------------ END BODY! ------------\n");

    LOG2("\n");

  } // process Client
}

// void Network::apConfigure(){

//   LOG0("*** Starting Access Point: %s / %s\n",apSSID,apPassword);

//   STATUS_UPDATE(start(LED_AP_STARTED),HS_AP_STARTED)

//   LOG0("\nScanning for Networks...\n\n");

//   scan();                   // scan for networks

//   for(int i=0;i<numSSID;i++)
//     LOG0("  %d) %s\n",i+1,ssidList[i]);

//   WiFiServer apServer(80);
//   client=0;

//   const byte DNS_PORT = 53;
//   DNSServer dnsServer;
//   IPAddress apIP(192, 168, 4, 1);

//   WiFi.mode(WIFI_AP);
//   WiFi.softAP(apSSID,apPassword);             // start access point
//   dnsServer.start(DNS_PORT, "*", apIP);       // start DNS server that resolves every request to the address of this device
//   apServer.begin();

//   alarmTimeOut=millis()+lifetime;            // Access Point will shut down when alarmTimeOut is reached
//   apStatus=0;                                // status will be "timed out" unless changed

//   LOG0("\nReady.\n");

//   while(1){                                  // loop until we get timed out (which will be accelerated if save/cancel selected)

//     if(homeSpan.controlButton && homeSpan.controlButton->triggered(9999,3000)){
//       LOG0("\n*** Access Point Terminated.  Restarting...\n\n");
//       STATUS_UPDATE(start(LED_ALERT),HS_AP_TERMINATED)
//       homeSpan.controlButton->wait();
//       homeSpan.reboot();
//     }

//     if(millis()>alarmTimeOut){
//       WiFi.softAPdisconnect(true);           // terminate connections and shut down captive access point
//       delay(100);
//       if(apStatus==1){
//         LOG0("\n*** Access Point: Exiting and Saving Settings\n\n");
//         return;
//       } else {
//         if(apStatus==0)
//           LOG0("\n*** Access Point: Timed Out (%ld seconds).",lifetime/1000);
//         else
//           LOG0("\n*** Access Point: Configuration Cancelled.");
//         LOG0("  Restarting...\n\n");
//         STATUS_UPDATE(start(LED_ALERT),HS_AP_TERMINATED)
//         homeSpan.reboot();
//       }
//     }

//     dnsServer.processNextRequest();

//     if(client=apServer.available()){                    // found a new HTTP client
//       LOG2("=======================================\n");
//       LOG1("** Access Point Client Connected: (");
//       LOG1(millis()/1000);
//       LOG1(" sec) ");
//       LOG1(client.remoteIP());
//       LOG1("\n");
//       LOG2("\n");
//       delay(50);                                        // pause to allow data buffer to begin to populate
//     }

//     if(client && client.available()){                   // if connection exists and data is available

//       LOG2("<<<<<<<<< ");
//       LOG2(client.remoteIP());
//       LOG2(" <<<<<<<<<\n");

//       int messageSize=client.available();

//       if(messageSize>MAX_HTTP){            // exceeded maximum number of bytes allowed
//         badRequestError();
//         LOG0("\n*** ERROR:  HTTP message of %d bytes exceeds maximum allowed (%d)\n\n",messageSize,MAX_HTTP);
//         continue;
//       }

//       TempBuffer<uint8_t> httpBuf(messageSize+1);      // leave room for null character added below

//       int nBytes=client.read(httpBuf,messageSize);       // read all available bytes up to maximum allowed+1

//       if(nBytes!=messageSize || client.available()!=0){
//         badRequestError();
//         LOG0("\n*** ERROR:  HTTP message not read correctly.  Expected %d bytes, read %d bytes, %d bytes remaining\n\n",messageSize,nBytes,client.available());
//         continue;
//       }

//       httpBuf[nBytes]='\0';                       // add null character to enable string functions
//       char *body=(char *)httpBuf.get();                 // char pointer to start of HTTP Body
//       char *p;                                          // char pointer used for searches

//       if(!(p=strstr((char *)httpBuf.get(),"\r\n\r\n"))){
//         badRequestError();
//         LOG0("\n*** ERROR:  Malformed HTTP request (can't find blank line indicating end of BODY)\n\n");
//         continue;
//       }

//       *p='\0';                                          // null-terminate end of HTTP Body to faciliate additional string processing
//       uint8_t *content=(uint8_t *)p+4;                  // byte pointer to start of optional HTTP Content
//       int cLen=0;                                       // length of optional HTTP Content

//       if((p=strstr(body,"Content-Length: ")))           // Content-Length is specified
//         cLen=atoi(p+16);
//       if(nBytes!=strlen(body)+4+cLen){
//         badRequestError();
//         LOG0("\n*** ERROR:  Malformed HTTP request (Content-Length plus Body Length does not equal total number of bytes read)\n\n");
//         continue;
//       }

//       LOG2(body);
//       LOG2("\n------------ END BODY! ------------\n");

//       content[cLen]='\0';                               // add a trailing null on end of any contents, which should always be text-based

//       processRequest(body, (char *)content);            // process request

//       LOG2("\n");

//     } // process Client

//   } // while 1

// }

///////////////////////////////

void Network::processRequest(char *body, char *formData)
{

  String responseHead = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n";

  String responseBody = "<html><meta charset=\"utf-8\"><head><style>"
                        "p{font-size:300%; margin:1em}"
                        "label{font-size:300%; margin:1em; color: black;}"
                        "input{font-size:250%; margin:1em; color: black;}"
                        "button{font-size:250%; margin:1em; color: black;}"
                        "</style></head>"
                        "<body style=\"background-color: white;\">"
                        "<center><p><b>HomeSpan Setup</b></p></center>";

  if (!strncmp(body, "POST /configure ", 16) && // POST CONFIGURE
      strstr(body, "Content-Type: application/x-www-form-urlencoded"))
  { // check that content is from a form

    LOG2(formData); // print form data
    LOG2("\n------------ END DATA! ------------\n");

    LOG1("In Post Configure...\n");

    getFormValue(formData, "network", wifiData.ssid, MAX_SSID);
    getFormValue(formData, "pwd", wifiData.pwd, MAX_PWD);

    STATUS_UPDATE(start(LED_WIFI_CONNECTING), HS_WIFI_CONNECTING)

    responseBody += "<meta http-equiv = \"refresh\" content = \"" + String(waitTime) + "; url = /wifi-status\" />"
                                                                                       "<p>Initiating WiFi connection to:</p><p><b>" +
                    String(wifiData.ssid) + "</p>";

    WiFi.begin(wifiData.ssid, wifiData.pwd);
  }
  else

      if (!strncmp(body, "POST /save ", 11))
  { // GET SAVE
    getFormValue(formData, "code", setupCode, 8);

    if (allowedCode(setupCode))
    {
      responseBody += "<p><b>Settings saved!</b></p><p>Restarting HomeSpan.</p><p>Closing window...</p>";
      alarmTimeOut = millis() + 2000;
      apStatus = 1;
    }
    else
    {
      responseBody += "<meta http-equiv = \"refresh\" content = \"4; url = /wifi-status\" />"
                      "<p><b>Disallowed Setup Code - too simple!</b></p><p>Returning to configuration page...</p>";
    }
  }
  else

      if (!strncmp(body, "GET /cancel ", 12))
  { // GET CANCEL
    responseBody += "<p><b>Configuration Canceled!</b></p><p>Restarting HomeSpan.</p><p>Closing window...</p>";
    alarmTimeOut = millis() + 2000;
    apStatus = -1;
  }
  else

      if (!strncmp(body, "GET /wifi-status ", 17))
  { // GET WIFI-STATUS

    LOG1("In Get WiFi Status...\n");

    if (WiFi.status() != WL_CONNECTED)
    {
      waitTime += 2;
      if (waitTime == 12)
        waitTime = 2;
      responseHead += "Refresh: " + String(waitTime) + "\r\n";
      responseBody += "<p>Re-initiating connection to:</p><p><b>" + String(wifiData.ssid) + "</b></p>";
      responseBody += "<p>(waiting " + String(waitTime) + " seconds to check for response)</p>";
      responseBody += "<p>Access Point termination in " + String((alarmTimeOut - millis()) / 1000) + " seconds.</p>";
      responseBody += "<center><button onclick=\"document.location='/hotspot-detect.html'\">Cancel</button></center>";
      WiFi.begin(wifiData.ssid, wifiData.pwd);
    }
    else
    {

      STATUS_UPDATE(start(LED_AP_CONNECTED), HS_AP_CONNECTED)

      responseBody += "<p>SUCCESS! Connected to:</p><p><b>" + String(wifiData.ssid) + "</b></p>";
      responseBody += "<p>You may enter new 8-digit Setup Code below, or leave blank to retain existing code.</p>";

      responseBody += "<form action=\"/save\" method=\"post\">"
                      "<label for=\"code\">Setup Code:</label>"
                      "<center><input size=\"32\" type=\"tel\" id=\"code\" name=\"code\" placeholder=\"12345678\" pattern=\"[0-9]{8}\" maxlength=8></center>"
                      "<center><input style=\"font-size:300%\" type=\"submit\" value=\"SAVE Settings\"></center>"
                      "</form>";

      responseBody += "<center><button style=\"font-size:300%\" onclick=\"document.location='/cancel'\">CANCEL Configuration</button></center>";
    }
  }
  else

      if (!strstr(body, "wispr") && !strncmp(body, "GET /hotspot-detect.html ", 25))
  { // GET LANDING-PAGE, but only if request does NOT contain "wispr" user agent

    LOG1("In Landing Page...\n");

    STATUS_UPDATE(start(LED_AP_CONNECTED), HS_AP_CONNECTED)
    waitTime = 2;

    responseBody += "<p>Welcome to HomeSpan! This page allows you to configure the above HomeSpan device to connect to your WiFi network.</p>"
                    "<p>The LED on this device should be <em>double-blinking</em> during this configuration.</p>"
                    "<form action=\"/configure\" method=\"post\">"
                    "<label for=\"ssid\">WiFi Network:</label>"
                    "<center><input size=\"32\" list=\"network\" name=\"network\" placeholder=\"Choose or Type\" required maxlength=" +
                    String(MAX_SSID) + "></center>"
                                       "<datalist id=\"network\">";

    for (int i = 0; i < numSSID; i++)
      responseBody += "<option value=\"" + String(ssidList[i]) + "\">" + String(ssidList[i]) + "</option>";

    responseBody += "</datalist><br><br>"
                    "<label for=\"pwd\">WiFi Password:</label>"
                    "<center><input size=\"32\" type=\"password\" id=\"pwd\" name=\"pwd\" required maxlength=" +
                    String(MAX_PWD) + "></center>"
                                      "<br><br>";

    responseBody += "<center><input style=\"font-size:300%\" type=\"submit\" value=\"SUBMIT\"></center>"
                    "</form>";

    responseBody += "<center><button style=\"font-size:300%\" onclick=\"document.location='/cancel'\">CANCEL Configuration</button></center>";
  }

  responseHead += "\r\n";           // add blank line between reponse header and body
  responseBody += "</body></html>"; // close out body and html tags

  LOG2("\n>>>>>>>>>> ");
  LOG2(client.remoteIP());
  LOG2(" >>>>>>>>>>\n");
  LOG2(responseHead);
  LOG2(responseBody);
  LOG2("\n");
  client.print(responseHead);
  client.print(responseBody);
  LOG2("------------ SENT! --------------\n");

} // processRequest

//////////////////////////////////////

int Network::getFormValue(char *formData, const char *tag, char *value, int maxSize)
{

  char *s = strstr(formData, tag); // find start of tag

  if (!s) // if not found, return -1
    return (-1);

  char *v = index(s, '='); // find '='

  if (!v) // if not found, return -1 (this should not happen)
    return (-1);

  v++;         // point to begining of value
  int len = 0; // track length of value

  while (*v != '\0' && *v != '&' && len < maxSize)
  { // copy the value until null, '&', or maxSize is reached
    if (*v == '%')
    { // this is an escaped character of form %XX
      v++;
      sscanf(v, "%2x", (unsigned int *)value++);
      v += 2;
    }
    else
    {
      *value++ = (*v == '+' ? ' ' : *v); // HTML Forms use '+' for spaces (and '+' signs are escaped)
      v++;
    }
    len++;
  }

  *value = '\0'; // add terminating null
  return (len);
}

//////////////////////////////////////

int Network::badRequestError()
{

  char s[] = "HTTP/1.1 400 Bad Request\r\n\r\n";
  LOG2("\n>>>>>>>>>> ");
  LOG2(client.remoteIP());
  LOG2(" >>>>>>>>>>\n");
  LOG2(s);
  client.print(s);
  LOG2("------------ SENT! --------------\n");

  delay(1);
  client.stop();

  return (-1);
}

//////////////////////////////////////
