int sharpSensor = A0;

int motorRightPWM = 5;
int motorRightDir = 4;
int motorLeftPWM = 6;
int motorLeftDir = 7;

void setup() {
  pinMode(sharpSensor, INPUT);
  pinMode(motorRightPWM, OUTPUT);
  pinMode(motorRightDir, OUTPUT);
  pinMode(motorLeftPWM, OUTPUT);
  pinMode(motorLeftDir, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(sharpSensor);
  int distance = map(value, 500, 50, 10, 80); // Aproximación

  if (distance < 15) {
    digitalWrite(motorLeftDir, HIGH);
    analogWrite(motorLeftPWM, 200);
    digitalWrite(motorRightDir, LOW);
    analogWrite(motorRightPWM, 200);
  } else {
    int speed = map(constrain(distance, 10, 80), 10, 80, 50, 200);
    digitalWrite(motorLeftDir, HIGH);
    digitalWrite(motorRightDir, HIGH);
    analogWrite(motorLeftPWM, speed);
    analogWrite(motorRightPWM, speed);
  }

  delay(100);
}