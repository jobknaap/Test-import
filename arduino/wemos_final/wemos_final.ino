#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "iotroam";
const char* password = "goQYjjfhMu";
String serverName = "http://60a8524b02f5a6.lhr.life/select_user.php?rfid=";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  // Stopping 
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  WiFiClient client;
  HTTPClient http;
  if(Serial.available()>0){ 
    String rfid = Serial.readString(); //"237,131,63,89,8";   // It will read the incoming or arriving data byte  
    
    String serverPath = serverName + rfid;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverPath.c_str());
        
    http.end();
  }
  delay(10);
}
