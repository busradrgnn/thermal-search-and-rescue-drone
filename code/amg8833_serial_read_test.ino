// AMG8833 Thermal Data Serial Output Test
// Reads 8x8 temperature matrix and prints to Serial Monitor
#include <Wire.h>
#include <Adafruit_AMG88xx.h>
#include <WiFi.h>  // WiFi kütüphanesini ekledik

// I2C adresi
#define AMG88xx_ADDR 0x69 

Adafruit_AMG88xx amg; // AMG8833 nesnesini oluştur

float pixels[64];  // 8x8 piksel verileri

void setup() {
  Serial.begin(115200);
  
  // I2C'yi başlat
  Wire.begin();

  // AMG8833'ü başlat
  if (!amg.begin(AMG88xx_ADDR)) { // Adres parametre olarak veriliyor
    Serial.println("AMG8833 bulunamadı. Bağlantıları kontrol edin.");
    while (1); // Hatalı durumda sonsuz döngüye gir
  }
  Serial.println("AMG8833 başlatıldı!");

  // WiFi bağlantısını başlat
  const char* ssid = "DSMART_0AF326"; // Buraya kendi WiFi adınızı yazın
  const char* password = "AichYqz4"; // Buraya kendi WiFi şifrenizi yazın
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi'ye bağlanılıyor...");
  }
  Serial.println("WiFi bağlantısı sağlandı!");
  Serial.print("ESP32 IP adresi: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Termal verileri oku
  amg.readPixels(pixels);

  // Termal verileri seri monitörde yazdır
  for (int i = 0; i < 64; i++) {
    Serial.print(pixels[i]);
    Serial.print("\t");
    if ((i + 1) % 8 == 0) {
      Serial.println();
    }
  }
  delay(1000); // Her 1 saniyede bir okuma yap
}
