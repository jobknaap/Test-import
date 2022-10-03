#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

void setup() {
  WiFi.begin("iotroam", "goQYjjfhMu");

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // Making sure the LED is off!

  // Keep in while-loop while the device is not connected to your accesspoint.
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); // Waiting on connection...
  }
  String rfid = "243,90,36,21,152";
  WiFiClient client;
  HTTPClient httpClient;

  httpClient.begin(client, "https://9072283bcb1826.lhrtunnel.link/select_user.php?rfid=" + rfid);
  httpClient.GET();
}

void loop() {
  
}
