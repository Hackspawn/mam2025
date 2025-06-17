#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <WebSocketsClient.h>

#define RST_PIN 22
#define SS_PIN 21

const char* ssid = "TU_SSID"; //nombre de la Red_Wifi
const char* password = "TU_PASS"; //clave del a Red Wifi
const char* host = "192.168.1.100"; // IP de la ESP32 del servomotor
const uint16_t port = 81;

MFRC522 rfid(SS_PIN, RST_PIN);
WebSocketsClient webSocket;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  webSocket.begin(host, port, "/");
  webSocket.onEvent([](WStype_t type, uint8_t * payload, size_t length) {}, nullptr);
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop();

  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      uid += String(rfid.uid.uidByte[i], HEX);
    }
    webSocket.sendTXT(uid);
    delay(1000);
    rfid.PICC_HaltA();
  }
}
