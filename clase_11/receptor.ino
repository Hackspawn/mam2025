#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ESP32Servo.h>

const char* ssid = "TU_SSID";
const char* password = "TU_PASS";

Servo myServo;
WebSocketsServer webSocket(81);

void handleUID(String uid) {
  int angle = 0;
  if (uid == "a1b2c3") angle = 30;
  else if (uid == "d4e5f6") angle = 90;
  else angle = 0;
  myServo.write(angle);
}

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    String uid = String((char*)payload);
    handleUID(uid);
  }
}

void setup() {
  Serial.begin(115200);
  myServo.setPeriodHertz(50);  // 👈 necesario para ESP32
  myServo.attach(13);

  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Conectado a WiFi.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
}

void loop() {
  webSocket.loop();
}
