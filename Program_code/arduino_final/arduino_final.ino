/*
  @author: Job van der Knaap
  @license: Permissive
  Goal: The arduino uno is used to be the brains of the project by activating
  the sensors and actuators, but also send important data to the wemos to
  send to the database.
*/

// Libraries
#include <SPI.h>
#include <RFID.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Pins for the stepmotor with the uln2003 module
#define IN1  2
#define IN2  3
#define IN3  4
#define IN4  5

// pins for the ultrasonic sensor
#define ECHO_PIN 6 
#define TRIG_PIN 7

// pins for the RFID scanner
#define RST_PIN 9
#define SS_PIN 10

// Constant variables
#define THRESHOLD_DISTANCE_ULTRSONIC 25
#define SPEED_OF_SOUND_WAVE 0.034


LiquidCrystal_I2C lcd(0x27, 16, 2); // Construct LCD screen on the I2C protocol with correct address
RFID rfid(SS_PIN,RST_PIN); // Construct RFID

//Global variables
String cards[] = {"237,131,63,89,8", "243,90,36,21,152", "145,79,114,11,167"}; // Active cards
String serNum;
int distance;


// One step for the stepper motor
int step [4][4] =
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

void setup() {
  // Pin setup
  pinMode(TRIG_PIN, OUTPUT); // Sends out ultrasonic waves
  pinMode(echoPin, INPUT); // Recieves ultrasonic waves

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4,OUTPUT);

  // Start funtcions
  Serial.begin(9600);
  lcd.begin();
  SPI.begin();
  
  rfid.init();
  lcd.backlight(); // Set backlight of LCD on
  setBeginScreen();
  
}

void loop() {        
  if(rfid.isCard()) { // Checks if there is any card detected
            
    if(rfid.readCardSerial()) { // Checks and reads card ID
      serNum = convertRfid(rfid.serNum); // Convert int array to string for the database

      // Checks if the card that is presented is a valid card.
      if(serNum == cards[0]) {
        setWelcomeScreen("Job");
        do {
          distance = getDistance(); // Gets the distance between ultrasonic sensor and person
          delay(10);
        } while (distance > THRESHOLD_DISTANCE_ULTRASONIC);
        Serial.print(serNum);
        turnGate(step);
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
  // Reset screen and display "welcome! To digital works"
  lcd.clear();
  lcd.setCursor(4,0); // Sets the cursor on the first(0) row and fifth(4) column to center the word welcome
  lcd.print("Welcome!");
  lcd.setCursor(0,1); // Sets cursor to second(1) row and first(0) column to add more text
  lcd.print("To digital works");
}

void setTryScreen(){
  // Reset screen and display "Please try again!"
  lcd.clear();
  lcd.setCursor(3,0); // Sets the cursor on the first(0) row and fourth(3) column to center text
  lcd.print("Please try");
  lcd.setCursor(5,1); // Sets cursor to second(1) row and sixth(5) column to center text
  lcd.print("again!");
}

void setWelcomeScreen(String name){
  // Reset screen and display "Hi! *name of checked in user* enjoy work today"
  lcd.clear();
  lcd.setCursor(0,0); // Sets the cursor on the first(0) row and first(0) column to ensure full name is displayed
  lcd.print("Hi! " + name);
  lcd.setCursor(0,1); // Sets cursor to second(1) row and first(0) column to add more text
  lcd.print("enjoy work today");
}

void setErrorScreen(){
  // Reset screen and display "No wifi conn... get assistance!"
  lcd.clear();
  lcd.setCursor(0,0); // Sets the cursor on the first(0) row and first(0) column to ensure all text is displayed
  lcd.print("No wifi conn...");
  lcd.setCursor(0,1); // Sets the cursor on the second(1) row and first(0) column to ensure all text is displayed
  lcd.print("get assistance!");
}

int getDistance(){
  digitalWrite(TRIG_PIN, LOW); // Reset pin
  delayMicroseconds(2);
  // Sets the TRIG_PIN HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(ECHO_PIN, HIGH);
  // Calculating the distance
  int distance = duration * SPEED_OF_SOUND_WAVE / 2; // Speed of sound wave divided by 2 (go and back)
  return distance;
}

void turnGate(int step[4][4]){
  delay(500);
  // Set all pins LOW for reset.
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  // Variables to calculate for the stepper motor to turn
  unsigned long starttime = millis();
  unsigned long endtime = starttime;
  
  while((endtime - starttime) <=1500) // do this loop for up to 1.5S
  {
    for (int i = 0; i < 4; i++)
    {
      // One step in the stepper motor every 2250 micro seconds
      digitalWrite(IN1, step[i][0]);
      digitalWrite(IN2, step[i][1]);
      digitalWrite(IN3, step[i][2]);
      digitalWrite(IN4, step[i][3]);
      delayMicroseconds(2250); // Delay needed for bugging stepper motor
    }
    endtime = millis();
  }
}

String convertRfid(unsigned char *serNums){
  String serNum;
  // Loops through serial number and convert them into 1 string with sepperating character
  for (int i=0; i<5; i++){
    serNum = serNum + String(serNums[i]) + ",";
  }
  // Gets the size of the string and removes last character
  int strSize = serNum.length();
  serNum.remove(strSize -1);
  
  return serNum;
}
