//check the used library and your sensor for this settings (1k vs 22k resistor)
//#define RLOAD 2000
// This value needs to be captured first
#define RZERO 200
 
#include "MQ135.h" 
MQ135 gasSensor = MQ135(A0); 
int val; 
int sensorPin = A0; 
int digitalPin = 3;
int sensorValue = 0;
int buzzer = 12;
float xyz;
 
void setup() { 
  Serial.begin(115200);
  //mySerial.begin(115200);
  pinMode(sensorPin, INPUT); 
  pinMode(digitalPin, INPUT); 
  pinMode(buzzer,OUTPUT);
} 
  
void loop() { 
  val = analogRead(A0);  
  Serial.println(val);
  //String str = Serial.readString();
  //Serial.println(str);
  if(val>150){
    digitalWrite(buzzer,HIGH);
    delay(500);
    digitalWrite(buzzer,LOW);
    delay(2000);
  } 
  else if(val>300){
    digitalWrite(buzzer,HIGH);
    delay(500);
    digitalWrite(buzzer,LOW);
    delay(500);
    digitalWrite(buzzer,HIGH);
    delay(500);
    digitalWrite(buzzer,LOW);
    delay(500);
  } 
  delay(1000); 
} 
