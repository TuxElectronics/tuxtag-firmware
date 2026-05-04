#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// --- ESP32 WiFi Network Settings ---
const char* ssid = "ESP32_Tag_Network";
const char* password = "password123"; // Must be at least 8 characters

// --- Hardware Pins ---
#define VIBRATOR_PIN 1
#define BUZZER_PIN 10

WebServer server(80);

// Function declarations
void setVibrator(bool state);
void setBuzzer(bool state);

// --- HTML Web Page UI ---
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial; text-align: center; margin: 50px auto; background-color: #f0f0f0;}
    .btn { display: inline-block; padding: 15px 25px; font-size: 24px; cursor: pointer; text-align: center; text-decoration: none; outline: none; color: #fff; background-color: #4CAF50; border: none; border-radius: 15px; margin: 10px; width: 80%; max-width: 300px; }
    .btn:active { background-color: #3e8e41; transform: translateY(4px); }
    .btn-off { background-color: #f44336; }
    .btn-off:active { background-color: #da190b; }
  </style>
</head>
<body>
  <h2>ESP32 AP Control</h2>
  <a href="/cmd?action=VIB_ON"><button class="btn">Vibrator ON</button></a><br>
  <a href="/cmd?action=VIB_OFF"><button class="btn btn-off">Vibrator OFF</button></a><br><br>
  <a href="/cmd?action=BUZ_ON"><button class="btn">Buzzer ON</button></a><br>
  <a href="/cmd?action=BUZ_OFF"><button class="btn btn-off">Buzzer OFF</button></a><br>
</body>
</html>
)rawliteral";

// --- Hardware Control Logic ---
void setVibrator(bool state) {
    if (state) {
        setBuzzer(false); // MUTUAL EXCLUSION
        digitalWrite(VIBRATOR_PIN, HIGH);
        Serial.println("=> Vibrator ON, Buzzer OFF");
    } else {
        digitalWrite(VIBRATOR_PIN, LOW);
        Serial.println("=> Vibrator OFF");
    }
}

void setBuzzer(bool state) {
    if (state) {
        setVibrator(false); // MUTUAL EXCLUSION
        tone(BUZZER_PIN, 1000); // 1000 Hz tone
        Serial.println("=> Buzzer ON, Vibrator OFF");
    } else {
        noTone(BUZZER_PIN);
        digitalWrite(BUZZER_PIN, LOW);
        Serial.println("=> Buzzer OFF");
    }
}

// --- Web Server Endpoints ---
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleCommand() {
  if (server.hasArg("action")) {
    String action = server.arg("action");

    if (action == "VIB_ON") setVibrator(true);
    else if (action == "VIB_OFF") setVibrator(false);
    else if (action == "BUZ_ON") setBuzzer(true);
    else if (action == "BUZ_OFF") setBuzzer(false);

    // Redirect back to the main page after command
    server.sendHeader("Location", "/");
    server.send(303);
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000); // Give the C3 time to initialize the USB Serial

  // Initialize Pins
  pinMode(VIBRATOR_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  setVibrator(false);
  setBuzzer(false);

  // START ESP32 AS A WIFI ACCESS POINT (ROUTER)
  Serial.println("\n--- Starting Access Point ---");
  WiFi.setTxPower(WIFI_POWER_11dBm);
  WiFi.softAP(ssid, password);

  // The default IP for the ESP32 in AP mode is almost always 192.168.4.1
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point started! Network Name: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(IP);

  // Setup Web Server Routes
  server.on("/", handleRoot);
  server.on("/cmd", handleCommand);

  server.begin();
  Serial.println("HTTP server started. Waiting for app commands...");
}

void loop() {
  server.handleClient(); // Listen for incoming web requests
  delay(2);
}