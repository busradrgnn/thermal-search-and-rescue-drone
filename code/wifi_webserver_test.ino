//Stage 1 - Creating HTTP server
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "WiFi_ADI";
const char* password = "WiFi_SIFRESI";

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Termal veriler burada gösterilecek");
}

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}
