#include <ESP8266WiFi.h>
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
const char* serverAddress = "yourserver.com"; 
const int ldrPin = A0; 
void setup() {
 Serial.begin(115200);
 delay(10);
 
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, password);
 
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
Serial.print(".");
 }
 
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
}
void loop() {
 
 int ldrValue = analogRead(ldrPin);
 
 if (WiFi.status() == WL_CONNECTED) {
 WiFiClient client;
 if (client.connect(serverAddress, 80)) {
 String url = "/api/ldr-data?value=" + String(ldrValue);
 client.println("GET " + url + " HTTP/1.1");
 client.println("Host: " + String(serverAddress));
 client.println("Connection: close");
 client.println();
 client.stop();
 }
 }
 delay(1000); 
}
