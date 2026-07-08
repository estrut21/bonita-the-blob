#include <EEPROM.h>

const int buzzer = 8;
const int trigPin = 9;
const int echoPin = 10;

int visits = 0;
bool handWasClose = false;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  visits = EEPROM.read(0);

  Serial.print("Bob remembers visits: ");
  Serial.println(visits);
}

void loop() {
  long distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Visits: ");
  Serial.println(visits);

  if (distance > 0 && distance < 15 && handWasClose == false) {
    visits++;
    EEPROM.write(0, visits);

    happyBeep();
    handWasClose = true;
  }

  if (distance >= 15) {
    handWasClose = false;
  }

  delay(200);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;

  return distance;
}

void happyBeep() {
  tone(buzzer, 1000, 100);
  delay(150);
  tone(buzzer, 1400, 100);
  delay(150);
  tone(buzzer, 1800, 150);
}

