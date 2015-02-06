#include <Servo.h>

Servo motor;
int aux = 0;


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  motor.attach(3); 
}

void loop() {
  if (!aux) {
  for (int i = 0; i < 4; i++) {
    motor.write(20);
    delay(random(400, 450));
    motor.write(random(30, 60));
    delay(random(400, 450));
  }
    aux = 7;
  }
}
