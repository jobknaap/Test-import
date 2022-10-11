/*
  @author: Job van der Knaap
  @license: Permissive
  Goal: The goal of this code is to receive data from the arduino and sent this to the http server
*/

// Libraries
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// Constant variables
#define SSID = "iotroam"
#define PASSWORD = "goQYjjfhMu"
#define SERVER_NAME = "http://60a8524b02f5a6.lhr.life/select_user.php?rfid="

void setup() {
  // Sarting serial and wifi
  Serial.begin(9600);
  WiFi.begin(SSID, PASSWORD);

  // Delaying code untill wifi is connected
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  // Constructing client and http
  WiFiClient client;
  HTTPClient http;

  // Checks if serial is sent from other device
  if(Serial.available()>0){ 
    
    String rfid = Serial.readString(); // It will read the incoming string sent from the wemos 
    String serverPath = serverName + rfid; // Creates the full server path for the http
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverPath.c_str());
        
    http.end();
  }
  delay(10);
}
