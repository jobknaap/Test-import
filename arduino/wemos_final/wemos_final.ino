#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Knaapjes";
const char* password = "Amsterdam1";
String serverName = "http://4096060a575b5b.lhr.life///select_user.php";

void setup() {
  Serial.begin(9600); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
//  WiFiClient client;
//  HTTPClient http;

  while(Serial.available()){
    delay(1);
    if (Serial.available() > 0){
      String rfid = Serial.readString(); //"237,131,63,89,8";   // It will read the incoming or arriving data byte  
      Serial.println(rfid);
    }
//    String serverPath = serverName + "?rfid=" + rfid;
//    
//    // Your Domain name with URL path or IP address with path
//    http.begin(client, serverPath.c_str());
//    int httpResponseCode = http.GET();
//    
//    if (httpResponseCode>0) {
//      Serial.print("HTTP Response code: ");
//      Serial.println(httpResponseCode);
//      String payload = http.getString();
//      Serial.println(payload);
//    }
//    else {
//      Serial.print("Error code: ");
//      Serial.println(httpResponseCode);
//    }
//    // Free resources
//    http.end();
  }
//  delay(20000);
}
