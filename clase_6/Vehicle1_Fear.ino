int ldrLeft = A0;
int ldrRight = A1;

int motorRightPWM = 5;
int motorRightDir = 4;
int motorLeftPWM = 6;
int motorLeftDir = 7;

void setup() {
  pinMode(ldrLeft, INPUT);
  pinMode(ldrRight, INPUT);
  pinMode(motorRightPWM, OUTPUT);
  pinMode(motorRightDir, OUTPUT);
  pinMode(motorLeftPWM, OUTPUT);
  pinMode(motorLeftDir, OUTPUT);
}

void loop() {
  int lightLeft = analogRead(ldrLeft);
  int lightRight = analogRead(ldrRight);

  int speedLeft = map(lightLeft, 0, 1023, 255, 0);  // inhibitorio
  int speedRight = map(lightRight, 0, 1023, 255, 0);

  digitalWrite(motorLeftDir, HIGH);
  digitalWrite(motorRightDir, HIGH);
  analogWrite(motorLeftPWM, speedLeft);
  analogWrite(motorRightPWM, speedRight);
}