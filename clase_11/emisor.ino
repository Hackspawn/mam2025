#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <WebSocketsClient.h>

#define RST_PIN 22
#define SS_PIN 21

const char* ssid = "TU_SSID";       // ← reemplaza con el nombre de tu red WiFi
const char* password = "TU_PASS";   // ← reemplaza con tu contraseña
const char* host = "192.168.1.100"; // ← IP de la ESP32 que mueve el servo
const uint16_t port = 81;

MFRC522 rfid(SS_PIN, RST_PIN);
WebSocketsClient webSocket;

void connectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(1000);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Conectado a WiFi");
    Serial.print("IP local: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ No se pudo conectar a WiFi");
  }
}

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  connectToWiFi();

  if (WiFi.status() == WL_CONNECTED) {
    webSocket.begin(host, port, "/");
    webSocket.onEvent([](WStype_t type, uint8_t * payload, size_t length) {
      switch (type) {
        case WStype_CONNECTED:
          Serial.println("✅ Conectado al servidor WebSocket");
          break;
        case WStype_DISCONNECTED:
          Serial.println("❌ Desconectado del servidor WebSocket");
          break;
        case WStype_TEXT:
          Serial.printf("Mensaje recibido: %s\n", payload);
          break;
        default:
          break;
      }
    });
    webSocket.setReconnectInterval(5000);
  }
}

void loop() {
  webSocket.loop();

  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      uid += String(rfid.uid.uidByte[i], HEX);
    }
    uid.toLowerCase();

    Serial.print("UID detectado: ");
    Serial.println(uid);

    if (webSocket.isConnected()) {
      webSocket.sendTXT(uid);
    } else {
      Serial.println("❗ WebSocket no conectado, no se envió UID.");
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1(); // ← línea corregida
    delay(1000);
  }
}
