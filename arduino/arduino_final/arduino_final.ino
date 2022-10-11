/*
  @author: Job van der Knaap
  @license: Permissive
  Goal: The goal of this code is to Read
*/
#include <SPI.h>
#include <RFID.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Pins for the stepmotor with u;m
#define IN1  2
#define IN2  3
#define IN3  4
#define IN4  5

#define echoPin 6
#define trigPin 7

#define RST_PIN 9
#define SS_PIN 10

LiquidCrystal_I2C lcd(0x27, 16, 2);
RFID rfid(SS_PIN,RST_PIN);

String cards[] = {"237,131,63,89,8", "243,90,36,21,152", "145,79,114,11,167"};
String serNum;
int distance;

int paso [4][4] =
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4,OUTPUT);

  Serial.begin(9600);
  lcd.begin();
  SPI.begin();
  
  rfid.init();
  lcd.backlight();
  setBeginScreen();
  
}

void loop() {        
  if(rfid.isCard()) {
            
    if(rfid.readCardSerial()) {       
      serNum = convertRfid(rfid.serNum);

      // Checks if the card that is presented is a valid card.
      if(serNum == cards[0]) {
        setWelcomeScreen("Job");
        do {
          distance = getDistance();
          delay(10);
        } while (distance > 25);
        Serial.print(serNum);
        turnGate(paso);
        setBeginScreen();
      } else {
        setTryScreen();
        delay(1500);
        setBeginScreen();
      }
    }
    delay(500);  
  }
  rfid.halt();
}
  

void setBeginScreen(){
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Welcome!");
  lcd.setCursor(0,1);
  lcd.print("To digital works");
}

void setTryScreen(){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Please try");
  lcd.setCursor(5,1);
  lcd.print("again!");
}

void setWelcomeScreen(String name){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hi! " + name);
  lcd.setCursor(0,1);
  lcd.print("enjoy work today");
}

void setErrorScreen(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("No wifi conn...");
  lcd.setCursor(0,1);
  lcd.print("get assistance!");
}

int getDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  return distance;
}

void turnGate(int settings[4][4]){
  delay(500);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  unsigned long starttime = millis();
  unsigned long endtime = starttime;
  
  while((endtime - starttime) <=1500) // do this loop for up to 1000mS
  {
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso[i][0]);
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delayMicroseconds(2250);
    }
    endtime = millis();
  }
}

String convertRfid(unsigned char *serNums){
  String serNum;
  for (int i=0; i<5; i++){
    serNum = serNum + String(serNums[i]) + ",";
  }
  int strSize = serNum.length();
  serNum.remove(strSize -1);
  return serNum;
}
