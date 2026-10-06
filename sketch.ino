// Jacob Kebbel - SAR 3: San Antonio Internet Weather Display
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);
const int BUTTON = 18;
const unsigned long PERIOD = 60000, MIN_REQUEST = 10000;
const char* API = "http://api.open-meteo.com/v1/forecast?latitude=29.4241&longitude=-98.4936&current=temperature_2m,relative_humidity_2m&temperature_unit=fahrenheit&timezone=America%2FChicago";
unsigned long lastRequest = 0, changedAt = 0;
bool lastRaw = HIGH, stable = HIGH, firstRequest = true, displayReady = false;

void message(const char* text) {
  Serial.println(text);
  if (!displayReady) return;
  oled.clearDisplay(); oled.setCursor(0, 0);
  oled.println("San Antonio Weather"); oled.println(text); oled.display();
}

bool connectWiFi() {
  if (WiFi.status() == WL_CONNECTED) return true;
  message("Connecting WiFi...");
  WiFi.begin("Wokwi-GUEST", "", 6);
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) delay(100);
  if (WiFi.status() != WL_CONNECTED) { message("WiFi timeout"); return false; }
  Serial.print("WiFi connected. IP: "); Serial.println(WiFi.localIP());
  return true;
}

void fetchWeather() {
  lastRequest = millis(); firstRequest = false;
  if (!connectWiFi()) return;
  message("Requesting weather...");
  HTTPClient http;
  http.setTimeout(10000);
  // HTTP is permitted by the assignment; no credentials are transmitted.
  if (!http.begin(API)) { message("HTTP begin failed"); return; }
  int status = http.GET();
  Serial.printf("HTTP status: %d\n", status);
  if (status != HTTP_CODE_OK) { http.end(); message("API request failed"); return; }
  String body = http.getString(); http.end();
  Serial.println("JSON response:"); Serial.println(body);
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, body);
  if (error) { message("Invalid JSON"); return; }
  JsonVariant t = doc["current"]["temperature_2m"];
  JsonVariant h = doc["current"]["relative_humidity_2m"];
  const char* time = doc["current"]["time"] | "";
  if (!t.is<float>() || !h.is<float>() || !time[0]) {
    message("Missing API fields"); return;
  }
  float temperature = t.as<float>(), humidity = h.as<float>();
  Serial.printf("Temperature: %.1f F | Humidity: %.0f %% | Time: %s\n", temperature, humidity, time);
  if (displayReady) {
    oled.clearDisplay(); oled.setCursor(0, 0);
    oled.println("San Antonio Weather"); oled.println();
    oled.printf("Temp: %.1f F\n", temperature);
    oled.printf("Humidity: %.0f %%\n", humidity);
    oled.println(time); oled.println("Button: refresh"); oled.display();
  }
}

void setup() {
  Serial.begin(115200); pinMode(BUTTON, INPUT_PULLUP);
  Wire.begin(21, 22);
  displayReady = oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  if (displayReady) { oled.setTextSize(1); oled.setTextColor(SSD1306_WHITE); }
  else Serial.println("OLED initialization failed; Serial output remains available.");
  WiFi.mode(WIFI_STA);
  fetchWeather();
}

void loop() {
  unsigned long now = millis();
  bool raw = digitalRead(BUTTON);
  if (raw != lastRaw) { lastRaw = raw; changedAt = now; }
  if (now - changedAt >= 40 && raw != stable) {
    stable = raw;
    if (stable == LOW) {
      if (now - lastRequest >= MIN_REQUEST) fetchWeather();
      else Serial.println("Refresh limited: wait 10 seconds between requests.");
    }
  }
  if (firstRequest || millis() - lastRequest >= PERIOD) fetchWeather();
  delay(5);
}
