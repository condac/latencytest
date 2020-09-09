#include "Mouse.h"

#define PIN  3
#define LED  15
#define ON 0
#define OFF 1
long counter;

bool keypress;

void setup() {
  pinMode(PIN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  // open the serial port:
  Serial.begin(9600);
  // initialize control over mouse:
  Mouse.begin();
  Serial.println("Arduino started");
  counter = millis();
  keypress = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  int state = digitalRead(PIN);
  digitalWrite(LED, state);

  
  if (Serial.available() > 0) {
    // get incoming byte:
    char inByte = Serial.read();
    if (inByte == '1') {
      long result = test();
      float res = result;
      res = res / 1000;
      Serial.print("result: ");
      Serial.print(res);
      Serial.println(" ms");
      
    }
    else if (inByte == '2') {
      delay(3000);
      long result = test();
      float res = result;
      res = res / 1000;
      Serial.print("result: ");
      Serial.print(res);
      Serial.println(" ms");
      
    }
    else if (inByte == '3') {
      Serial.println("Starting average burst test...");
      delay(3000);
      int nr = 5;
      long total = 0;
      for (int i = 0; i<5; i++) {
        long result = test();
        float res = result;
        res = res / 1000;
        Serial.print("result: ");
        Serial.print(res);
        Serial.println(" ms");
        total = total + result;
        delay(1000);
      }
      float res = total;
      res = res / 1000;
      res = res / nr;
      Serial.print("Average result: ");
      Serial.print(res);
      Serial.println(" ms");
      
    }
    else if (inByte == '4') {
      Serial.println("Starting mspaint test...");
      delay(3000);
      int nr = 10;
      long total = 0;
      for (int i = 0; i<nr; i++) {
        Mouse.press(MOUSE_LEFT);
        delay(100);
        Mouse.release(MOUSE_LEFT);
        delay(100);
        long result = testRight();
        float res = result;
        res = res / 1000;
        Serial.print("result: ");
        Serial.print(res);
        Serial.println(" ms");
        total = total + result;
        
      }
      float res = total;
      res = res / 1000;
      res = res / nr;
      Serial.print("Average result: ");
      Serial.print(res);
      Serial.println(" ms");
      
    }
    else {
      Serial.println("Type 1 for test, 2 delay start, 3 = 5 burst test, 4 = mspaint test");
    }

  }
  delay(100);
  

}

long test() {
  long result;
  long stoptime = 0;
  // wait for sensor to be HIGH
  while (!digitalRead(PIN) ) {
    digitalWrite(LED,ON);
  }
  digitalWrite(LED,OFF);
  delay(100);
  digitalWrite(LED,ON);
  long starttime = micros();
  Mouse.press(MOUSE_LEFT);
  while (digitalRead(PIN)) {
    
  }
  stoptime = micros();
  digitalWrite(LED,OFF);
  Mouse.release(MOUSE_LEFT);
  result = stoptime - starttime;
  return result;
}
long testRight() {
  long result;
  long stoptime = 0;
  // wait for sensor to be HIGH
  while (!digitalRead(PIN) ) {
    digitalWrite(LED,ON);
  }
  digitalWrite(LED,OFF);
  delay(100);
  digitalWrite(LED,ON);
  long starttime = micros();
  Mouse.press(MOUSE_RIGHT);
  while (digitalRead(PIN)) {
    
  }
  stoptime = micros();
  digitalWrite(LED,OFF);
  Mouse.release(MOUSE_RIGHT);
  result = stoptime - starttime;
  return result;
}
