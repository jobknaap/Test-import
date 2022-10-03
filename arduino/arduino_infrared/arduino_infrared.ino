int pirPin = 8;                 // PIR Out pin 
int pirStat = 0;                // PIR status

void setup() {
 pinMode(LED_BUILTIN, OUTPUT);     
 pinMode(pirPin, INPUT);     
 Serial.begin(9600);
}
void loop(){
 pirStat = digitalRead(pirPin); 
 if (pirStat == HIGH) {            // if motion detected
   digitalWrite(LED_BUILTIN, HIGH);  // turn LED ON
   Serial.println("Hey I got you!!!");
   pirStat == LOW;
   delay(500);
 } 
 else {
   digitalWrite(LED_BUILTIN, LOW); // turn LED OFF if we have no motion
 }
 delay(100);
} 
