String escaneado;

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80);

#include "data.h"
const uint32_t TiempoEsperaWifi = 5000;

void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando Server Web");

  wifiMulti.addAP(ssid_1, password_1);
  wifiMulti.addAP(ssid_2, password_2);

  WiFi.mode(WIFI_STA);
  Serial.print("Conectando a Wifi ..");
  while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println(".. Conectado");
  Serial.print("SSID: ");
  Serial.print(WiFi.SSID());
  Serial.print(" ID: ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin("elesp")) {
    Serial.println("Erro configurando mDNS!");
    while (1) {
      delay(1000);
    }
  }

  MDNS.addService("http", "tcp", 80);
  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
   MDNS.update();
   if (Serial.available() > 0)
  {
    scaneado = Serial.readStringUntil('\n');
    if (escaneado == "001589") {
      Serial.println(escaneado);
      server.send(200, "text/plain", scaneado);
    }
}
 //server.send(200, "text/plain", scaneado);
}
