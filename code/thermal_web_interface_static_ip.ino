// Thermal Web Interface with Static IP Configuration
// ESP32 + AMG8833 basic temperature table display
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_AMG88xx.h>

// WiFi bilgileri
const char* ssid = "DSMART_0AF326"; // Buraya kendi WiFi adınızı yazın
const char* password = "AichYqz4"; // Buraya kendi WiFi şifrenizi yazın

// Statik IP adresi ayarları
IPAddress local_IP(192, 168, 1, 100); // Atamak istediğiniz IP adresi
IPAddress gateway(192, 168, 1, 1);     // Ağ geçidi (genellikle router IP'si)
IPAddress subnet(255, 255, 255, 0);    // Alt ağ maskesi

WebServer server(80); // HTTP sunucusu için port 80

Adafruit_AMG88xx amg;
float pixels[64];  // 8x8 piksel verileri

void setup() {
  Serial.begin(115200);
  
  // Statik IP adresini ayarla
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Statik IP ayarı yapılamadı!");
  }

  // WiFi bağlantısını başlat
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi'ye bağlanılıyor...");
  }
  Serial.println("WiFi bağlantısı sağlandı!");
  Serial.print("ESP32 IP adresi: ");
  Serial.println(WiFi.localIP()); // Atanan IP adresini yazdır

  // AMG8833'ü başlat
  if (!amg.begin()) {
    Serial.println("AMG8833 bulunamadı. Bağlantıları kontrol edin.");
    while (1);
  }
  Serial.println("AMG8833 başlatıldı!");

  // Ana sayfa için bir işlemci oluştur
  server.on("/", handleRoot);
  server.begin(); // Sunucuyu başlat
}

void loop() {
  server.handleClient(); // İstemci isteklerini dinle
}

// Ana sayfa işlemi
void handleRoot() {
  // Termal verileri oku
  amg.readPixels(pixels);

  // HTML formatında verileri gönder
  String html = "<html><body><h1>Termal Görüntüleme</h1><table border='1'>";
  for (int i = 0; i < 8; i++) {
    html += "<tr>";
    for (int j = 0; j < 8; j++) {
      html += "<td>" + String(pixels[i * 8 + j], 1) + " °C</td>";
    }
    html += "</tr>";
  }
  html += "</table></body></html>";

  server.send(200, "text/html", html); // İstemciye HTML verisi gönder
}
