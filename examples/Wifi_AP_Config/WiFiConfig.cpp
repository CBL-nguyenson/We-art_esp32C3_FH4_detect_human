#include "WiFiConfig.h"

WiFiConfig::WiFiConfig(const char* ap_ssid, const char* ap_password) 
  : ap_ssid(ap_ssid), ap_password(ap_password), server(80) {}

void WiFiConfig::begin() {
  Serial.begin(115200);

  // Khởi động WiFi ở chế độ AP
  WiFi.softAP(ap_ssid, ap_password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Thiết lập các route
  server.on("/", [this]() { handleRoot(); });
  server.on("/configure_wifi", HTTP_POST, [this]() { handleConfigure(); });
  server.on("/refresh", HTTP_GET, [this]() { handleRefresh(); });

  // Bắt đầu máy chủ web
  server.begin();

  Serial.println("Server started");
  Serial.println("Connect to AP 'ESP32_Config' and navigate to http://192.168.4.1");
}

void WiFiConfig::handleClient() {
  server.handleClient();
}

void WiFiConfig::handleRoot() {
  server.send(200, "text/html", generateHTML());
}

void WiFiConfig::handleConfigure() {
  String ssid = server.arg("ssid");
  String ssid_manual = server.arg("ssid_manual");
  String password = server.arg("password");

  if (ssid == "manual") {
    ssid = ssid_manual;
  }

  if (password.length() == 0) {
    // Kết nối WiFi không có mật khẩu
    WiFi.begin(ssid.c_str());
  } else {
    // Kết nối WiFi có mật khẩu
    WiFi.begin(ssid.c_str(), password.c_str());
  }

  server.send(200, "text/html", "Configuration Saved. Trying to connect to WiFi...");

  // Đợi và kiểm tra kết nối

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi!");
  } else {
    Serial.println("Failed to connect to WiFi.");
  }
}

void WiFiConfig::handleRefresh() {
  handleRoot();
}

String WiFiConfig::generateHTML() {
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
  if (n == 0) {
    htmlPage += "<option value=\"\">No networks found</option>";
  } else {
    for (int i = 0; i < n; ++i) {
      htmlPage += "<option value=\"" + String(WiFi.SSID(i)) + "\">" + String(WiFi.SSID(i)) + "</option>";
    }
  }

  htmlPage += htmlPageMiddle;

  return htmlPage;
}
