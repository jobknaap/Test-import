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
}

void loop() {
  float temperature = 1.3;

  WiFiClient client;
  HTTPClient httpClient;

  httpClient.begin(client, "http://3a6ee7c462149d.lhrtunnel.link/api.php?temprature=" + String(temperature));
  
  httpClient.GET();

  String payload = httpClient.getString();

  temperature++;

  delay(5000);
}
