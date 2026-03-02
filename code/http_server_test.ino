// Basic wifi server test
#include <WiFi.h> 
#include <WebServer.h>

const char* ssid = "DSMART_0AF326";
const char* password = "AichYqz4";

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "ESP32 Calisiyor!");
}

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  
  server.on("/", handleRoot);  // Ana sayfaya bir yanıt ekle
  server.begin();
}

void loop() {
  server.handleClient();  // HTTP isteklerini işle
}
