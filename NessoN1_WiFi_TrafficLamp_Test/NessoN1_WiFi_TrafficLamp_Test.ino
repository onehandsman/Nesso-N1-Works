// Nesso N1 minimal Wi-Fi LCD color test

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <M5Unified.h>
#include "secrets.h"

const char* wifiName = "Nesso-N1-Lamp";
const char* wifiPassword = NESSO_AP_PASSWORD;

WebServer server(80);

const char page[] PROGMEM = R"HTML(
<!doctype html>
<html lang="ja">
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Nesso N1</title>
<style>
body{font-family:sans-serif;text-align:center;background:#222;color:white}
a{display:block;margin:16px;padding:22px;font-size:28px;color:white;text-decoration:none;border-radius:12px}
</style>
<h2>Nesso N1 液晶</h2>
<a href="/red" style="background:red">赤</a>
<a href="/yellow" style="background:#e0b000;color:black">黄</a>
<a href="/blue" style="background:blue">青</a>
<a href="/off" style="background:black;border:1px solid white">消灯</a>
</html>
)HTML";

void showPage() {
  server.send_P(200, "text/html; charset=utf-8", page);
}

void showColor(uint16_t color) {
  M5.Display.fillScreen(color);
  showPage();
}

void setup() {
  Serial.begin(115200);

  auto config = M5.config();
  M5.begin(config);
  M5.Display.fillScreen(0x0000);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(wifiName, wifiPassword);

  server.on("/", showPage);
  server.on("/red", []() { showColor(0xF800); });
  server.on("/yellow", []() { showColor(0xFFE0); });
  server.on("/blue", []() { showColor(0x001F); });
  server.on("/off", []() { showColor(0x0000); });
  server.begin();

  Serial.println("Wi-Fi: Nesso-N1-Lamp");
  Serial.println("Password: see secrets.h");
  Serial.println("Open: http://192.168.4.1");
}

void loop() {
  server.handleClient();
}
