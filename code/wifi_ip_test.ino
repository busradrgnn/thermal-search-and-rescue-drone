//Find IP address
#include <WiFi.h>

// WiFi bilgileri
const char* ssid = "DSMART_0AF326";
const char* password = "AichYqz4";

void setup() {
  Serial.begin(115200);  // Seri haberleşme için
  WiFi.begin(ssid, password);  // WiFi başlat
  
  Serial.println("WiFi'ye bağlanıyor...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Bağlantı bekleniyor...");
  }
  
  Serial.println("WiFi'ye bağlandı!");
  Serial.println(WiFi.localIP());  // IP adresini yazdır
}

void loop() {
  // Döngüde başka işlemler yapılabilir
}
