#include <SoftwareSerial.h>// import the serial library

int tempo = 250;

int motor1[2] = {2, 3};
int motor2[2] = {4, 5};
int motor3[2] = {6, 7};
int motor4[2] = {8, 9};

//variaveis para o bluetooth

SoftwareSerial Genotronex(0, 1);
int ledpin=13; // led on D13 will show blink on / off
int BluetoothData;

void para() {
    for (int i = 0; i < 2; i++) {
    digitalWrite(motor1[i], LOW); 
    digitalWrite(motor2[i], LOW); 
  }
}

void setup() {
  for (int i = 0; i < 2; i++) {
    pinMode(motor1[i], OUTPUT);
    pinMode(motor2[i], OUTPUT);
  }
    // put your setup code here, to run once:
  Genotronex.begin(9600);
  Genotronex.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin,OUTPUT);
  Serial.begin(9600);
  para();
}



void paraFrente() {
   digitalWrite(motor1[0], HIGH);
   digitalWrite(motor2[0], HIGH);
   digitalWrite(motor1[1], LOW);
   digitalWrite(motor2[1], LOW);
}

void paraTras() {
   digitalWrite(motor1[0], LOW);
   digitalWrite(motor2[0], LOW);
   digitalWrite(motor1[1], HIGH);
   digitalWrite(motor2[1], HIGH);
}

void paraEsquerda() {
   digitalWrite(motor1[0], HIGH);
   digitalWrite(motor2[0], LOW);
   digitalWrite(motor1[1], LOW);
   digitalWrite(motor2[1], LOW);
}

void paraDireita() {
   digitalWrite(motor1[0], LOW);
   digitalWrite(motor2[0], HIGH);
   digitalWrite(motor1[1], LOW);
   digitalWrite(motor2[1], LOW);
}

void loop() {
  char k = 0;
    // put your main code here, to run repeatedly:
   if (Genotronex.available()){
      BluetoothData=Genotronex.read();
      k = BluetoothData;
      Serial.println(k);
  }
  switch (k) {
    case '1':
      paraFrente();
      delay(tempo);
      para();
      break;
    case '2':
      paraTras();
      delay(tempo);
      para();
      break;
    case '3':
      paraEsquerda();
      delay(tempo);
      para();
      break;
    case '4':
      paraDireita();
      delay(tempo);
      para();
      break;
  }
  delay(100);
}
