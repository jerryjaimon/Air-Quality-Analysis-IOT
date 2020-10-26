int sensorPin = A6; 
// variable to store the value coming from the sensor.
int val = 0; 
 
void setup() {
  Serial.begin(9600);
}
void loop() {
  // read the value from the sensor
  val = analogRead(sensorPin);
  Serial.println (val);
  delay(1000);
}
