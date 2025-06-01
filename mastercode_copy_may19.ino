// transmitter code
// EStop_pressed is 1 when not pressed, 0 when pressed
#include <SoftwareSerial.h>
const byte rxPin = 2;
const byte txPin = 3;
SoftwareSerial BTSerial (rxPin, txPin);
int yAxis;
bool EStop_pressed = false;

void setup() {
  Serial.begin(9600); 
  //pinMode(rxPin, INPUT);
  //pinMode(txPin, OUTPUT);
  pinMode(5, INPUT_PULLUP);
  BTSerial.begin(9600);
}

void loop() {
  yAxis = analogRead(A0); 
//  Serial.print(yAxis / 4);
  EStop_pressed = digitalRead(5);
//  Serial.print(",");
//  Serial.println(EStop_pressed);
//  BTSerial.print(yAxis / 4);
//  BTSerial.print(",");
//  BTSerial.println(EStop_pressed);
//  delay(10);

  Serial.print("<");
  Serial.print(yAxis / 4);
  Serial.print(",");
  Serial.print(EStop_pressed);
  Serial.println(">");
 
  //Send to HC-05
  BTSerial.print("<");
  BTSerial.print(map(yAxis,0,1023,0,180));
  BTSerial.print(",");
  BTSerial.print(EStop_pressed);
  BTSerial.println(">");
  delay(10);

}
