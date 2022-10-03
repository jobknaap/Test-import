#include <SPI.h>
#include <RFID.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


#define IN1  2
#define IN2  3
#define IN3  4
#define IN4  5
#define trigPin 6
#define echoPin 7
#define RST_PIN 9
#define SS_PIN 10


LiquidCrystal_I2C lcd(0x27, 16, 2);
RFID rfid(SS_PIN,RST_PIN);

int serNums[5];
String serNum;
String cards[] = {"237,131,63,89,8", "243,90,36,21,152", "145, 79, 114, 11, 167"};
const char* ssid = "Knaapjes";
const char* password = "Amsterdam1";
String serverName = "http://990ebedadf1e27.lhr.life//select_user.php";
int distance;
int bluePin = 2;    //IN1 on the ULN2003 Board, BLUE end of the Blue/Yellow motor coil
int pinkPin = 3;    //IN2 on the ULN2003 Board, PINK end of the Pink/Orange motor coil
int yellowPin = 4;  //IN3 on the ULN2003 Board, YELLOW end of the Blue/Yellow motor coil
int orangePin = 5;  
int currentStep = 0;

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

  pinMode(bluePin, OUTPUT);
  pinMode(pinkPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(orangePin,OUTPUT);
  
  lcd.begin();
  SPI.begin();
  rfid.init();

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

  lcd.backlight();
  setBeginScreen();
  
}

void loop() {  
  if (WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;

    for (int i=0; i<sizeof(serNums); i++){
        serNum = serNum + String(serNums[i]);
      }
      
    if(rfid.isCard()) {        
      if(rfid.readCardSerial()) {        
        if(serNum == cards[0]) {
          Serial.write(serNum);
          setWelcomeScreen("Job");
          delay(500);
          do {
            distance = getDistance();
          } while (distance > 25);

          turnGate();
          setBeginScreen();
          break;
          
        } else if(serNum == cards[1]) {
          Serial.write(serNum);
          setWelcomeScreen("Mats");
          delay(500);
          do {
            distance = getDistance();
          } while (distance > 25);

          turnGate();
          setBeginScreen();
          break;
          
        } else if(serNum == cards[2]) {
          Serial.write(serNum);
          setWelcomeScreen("OV");
          delay(500);
          do {
            distance = getDistance();
          } while (distance > 25);

          turnGate();
          setBeginScreen();
          break;
          
        } else {
          setTryScreen();
          delay(1500);
          setBeginScreen();
          break;
        }
      }
    }
    delay(500);
    rfid.halt();  
  } else {
    setErrorScreen();
  }
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

void turnGate(){
  digitalWrite(bluePin, LOW);
  digitalWrite(pinkPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(orangePin, LOW);

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
