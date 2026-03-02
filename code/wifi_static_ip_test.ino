// Stage 1 - WiFi Connection and Static IP Configuration

#include <WiFi.h>

// WiFi bilgileri
const char* ssid = "WIFI_ADIN";
const char* password = "SIFREN";

// Statik IP ayarları
IPAddress local_IP(192, 168, 1, 200);   // İstediğin IP
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);

  // Statik IP yapılandırma
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Static IP configuration failed!");
  }

  // WiFi bağlantısı başlat
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("Assigned IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Sürekli bir işlem yok
}
