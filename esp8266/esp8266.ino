#include <ESP8266WiFi.h>
#include <ThingsBoard.h> // Include the Wi-Fi library

const char* ssid     = "IOT";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "178!";     // The password of the Wi-Fi network
int lastSend = 0;
#define TOKEN ""
int value = -20;

char thingsboardServer[] = "demo.thingsboard.io";
int status = 0;
WiFiClient espClient;
ThingsBoard tb(espClient);


void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

void loop() { 
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    while ( status != WL_CONNECTED) {
      Serial.print("Attempting to connect to WPA SSID: ");
      Serial.println(WIFI_AP);
      status =  WiFi.begin(ssid, password); ;
      delay(500);
    }
    Serial.println("Connected to AP");
  }
  delay(1000);
   if ( !tb.connected() ) {
    reconnect();
  }

  if ( millis() - lastSend > 1000 ) { // Update and send only after 1 seconds
    getValue();
    lastSend = millis();
  }
  delay(2000);
  tb.loop();
 }

void reconnect(){
   while (!tb.connected()) {
    Serial.print("Connecting to ThingsBoard node ...");
    // Attempt to connect (clientId, username, password)
    if ( tb.connect(thingsboardServer, TOKEN) ) {
      Serial.println( "[DONE]" );
    } else {
      Serial.print( "[FAILED]" );
      Serial.println( " : retrying in 5 seconds" );
      // Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
}
void getValue()
{
  Serial.println("Collecting pollution data.");
  value = Serial.parseInt();
  Serial.println("Sending data to ThingsBoard:"); 
  Serial.print("PPM value: ");
  Serial.println(value);
  if (value>0){
  tb.sendAttributeFloat("shjvalue", value);}
}
