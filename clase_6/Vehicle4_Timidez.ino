#define trigPin 9
#define echoPin 8

int motorRightPWM = 5;
int motorRightDir = 4;
int motorLeftPWM = 6;
int motorLeftDir = 7;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorRightPWM, OUTPUT);
  pinMode(motorRightDir, OUTPUT);
  pinMode(motorLeftPWM, OUTPUT);
  pinMode(motorLeftDir, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  int speed = map(constrain(distance, 5, 50), 5, 50, 255, 0);

  digitalWrite(motorRightDir, LOW);
  digitalWrite(motorLeftDir, LOW);
  analogWrite(motorRightPWM, speed);
  analogWrite(motorLeftPWM, speed);

  delay(50);
}