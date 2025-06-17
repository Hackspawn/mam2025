#include <WiFi.h>
#include <WebSocketsServer.h>
#include <Servo.h>

const char* ssid = "TU_SSID"; //nombre Red Wifi
const char* password = "TU_PASS"; //clave Red Wifi

Servo myServo;
WebSocketsServer webSocket(81);

void handleUID(String uid) {
  int angle = 0;
  if (uid == "a1b2c3") angle = 30;
  else if (uid == "d4e5f6") angle = 90;
  else angle = 0; // default
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
  myServo.attach(13);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
}

void loop() {
  webSocket.loop();
}
