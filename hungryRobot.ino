#define TrigPin 6
#define EchoPin 7

#include <Servo.h>

#define SERVO 4

#define LED1 PIN_LED2
#define LED2 PIN_LED3
#define LED3 PIN_LED

Servo myServo;

double speedSound = 331.5 + 0.61 * 20;

void setup() {
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  int pulse_min = 544;
  int pulse_max = 2400;
  myServo.attach(SERVO, pulse_min, pulse_max);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
}


void loop() {
  while (1) {
    double distance = measureDistance();
    Serial.println(distance);

    delay(100);

    if (distance < 10) {
      break;
    }
  }

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);

  while (1) {
    double distance = measureDistance();
    Serial.println(distance);

    delay(100);

    if (distance > 15) {
      break;
    }
  }

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  delay(1500);
  
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  myServo.write(0);
  delay(230);
  myServo.write(90);
  
  delay(500);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
}

void trigger() {
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
}

double measureDistance() {
  double dist = 0.0;
  trigger();

  double t = pulseIn(EchoPin, HIGH);
  if (t > 0) {
    t = t / 2;
    dist = t * speedSound * 100 / 1000000;
  }

  return dist;
}
