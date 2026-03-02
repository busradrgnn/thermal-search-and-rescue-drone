// Thermal Web Interface - Hotspot Mode
// ESP32 creates its own WiFi and serves live thermal visualization

#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_AMG88xx.h>

const char* ssid = "ESP32_Hotspot";
const char* password = "123456789";

WebServer server(80);
Adafruit_AMG88xx amg;
float pixels[64];

void setup() {
  Serial.begin(115200);

  // Hotspot oluştur
  WiFi.softAP(ssid, password);
  Serial.println("Hotspot created!");
  Serial.print("Hotspot IP: ");
  Serial.println(WiFi.softAPIP());

  if (!amg.begin()) {
    Serial.println("AMG8833 not found!");
    while (1);
  }

  server.on("/", handleRoot);
  server.on("/update", handleUpdate);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><head><meta charset='UTF-8'><script>";
  html += "setInterval(function(){ fetch('/update').then(r=>r.json()).then(data=>{";
  html += "document.getElementById('grid').innerHTML='';";
  html += "data.pixels.forEach((t,i)=>{";
  html += "var c=getColor(t);";
  html += "var d=document.createElement('div');";
  html += "d.style.width='40px';d.style.height='40px';";
  html += "d.style.display='inline-block';";
  html += "d.style.backgroundColor='#'+c;";
  html += "document.getElementById('grid').appendChild(d);";
  html += "});});},1000);";

  html += "function getColor(temp){";
  html += "let min=18,max=35;";
  html += "let n=(temp-min)/(max-min);";
  html += "n=Math.min(Math.max(n,0),1);";
  html += "let r=Math.floor(255*n);";
  html += "let b=255-r;";
  html += "return ((r<<16)|(0<<8)|b).toString(16).padStart(6,'0');}";
  html += "</script></head><body>";
  html += "<h2>Thermal Visualization</h2>";
  html += "<div id='grid'></div>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleUpdate() {
  amg.readPixels(pixels);

  String json = "{ \"pixels\": [";
  for (int i = 0; i < 64; i++) {
    json += String(pixels[i]);
    if (i < 63) json += ",";
  }
  json += "] }";

  server.send(200, "application/json", json);
}
