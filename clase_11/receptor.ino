#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ESP32Servo.h>

const char* ssid = "TU_SSID";       // ← reemplaza con tu red
const char* password = "TU_PASS";   // ← reemplaza con tu clave

Servo myServo;
WebSocketsServer webSocket(81);

void handleUID(String uid) {
  int angle = 0;
  if (uid == "a1b2c3") angle = 30;
  else if (uid == "d4e5f6") angle = 90;
  else angle = 0;
  myServo.write(angle);
  Serial.print("Servo a: ");
  Serial.println(angle);
}

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    String uid = String((char*)payload);
    Serial.print("UID recibido: ");
    Serial.println(uid);
    handleUID(uid);
  }
}

void initWiFi() {
  WiFi.mode(WIFI_STA);              // ← esta línea es clave
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(1000);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Conectado!");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ No se pudo conectar.");
  }
}

void setup() {
  Serial.begin(115200);
  myServo.setPeriodHertz(50);
  myServo.attach(13);
  
  initWiFi();                      // ← usa el método comprobado
  if (WiFi.status() == WL_CONNECTED) {
    webSocket.begin();
    webSocket.onEvent(onWebSocketEvent);
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    webSocket.loop();
  }
}
