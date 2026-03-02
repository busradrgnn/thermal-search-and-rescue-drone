// Thermal JSON API
// Connects to router and sends AMG8833 data as JSON

#include <Wire.h>
#include <Adafruit_AMG88xx.h>
#include <WiFi.h>
#include <WebServer.h>

Adafruit_AMG88xx amg;
WebServer server(80);

const char* ssid = "DSMART_0AF326";
const char* password = "AichYqz4";

void setup() {
  Serial.begin(115200);

  // WiFi bağlantısı
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // AMG başlat
  if (!amg.begin()) {
    Serial.println("AMG8833 not found!");
    while (1);
  }

  // Root endpoint JSON dönecek
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  float pixels[64];
  amg.readPixels(pixels);

  String json = "{ \"pixels\": [";
  for (int i = 0; i < 64; i++) {
    json += String(pixels[i]);
    if (i < 63) json += ",";
  }
  json += "] }";

  server.send(200, "application/json", json);
}
