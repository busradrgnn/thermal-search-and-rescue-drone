// I2C Scanner - Used to detect connected I2C devices (e.g., AMG8833)
#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Serial.println("I2C Tarayıcı başlatıldı.");
}

void loop() {
  byte error, address;
  int nDevices = 0;

  Serial.println("I2C cihazlarını tarıyor...");

  for (address = 1; address < 127; address++) {
    // I2C cihazına bağlanmayı dene
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Cihaz bulundu: 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println();
      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Hata: 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("Cihaz bulunamadı.");
  } else {
    Serial.println("Tarama tamamlandı.");
  }
  delay(5000);  // 5 saniye bekleyip tekrar tara
}
