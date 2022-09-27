#include <SPI.h>
#include <RFID.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9

LiquidCrystal_I2C lcd(0x27, 16, 2);
RFID rfid(SS_PIN,RST_PIN);

int serNum[5];
int cards[][5] = {{237,131,63,89,8}, {243,90,36,21,152}, {145, 79, 114, 11, 167}};

void setup() {
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
      for(int i = 0; i < sizeof(rfid.serNum); i++ ) {
        if(rfid.serNum[i] == cards[0][i]) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Hi! job");
          lcd.setCursor(0,1);
          lcd.print("enjoy work today");

          delay(1500);
          setBeginScreen();
          break;
        } else if(rfid.serNum[i] == cards[1][i]) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Hi! mats");
          lcd.setCursor(0,1);
          lcd.print("enjoy work today");

          delay(1500);
          setBeginScreen();
          break;
        } else if(rfid.serNum[i] == cards[2][i]) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Hi! OV");
          lcd.setCursor(0,1);
          lcd.print("enjoy work today");

          delay(1500);
          setBeginScreen();
          break;
        } else {
          setErrorScreen();
          delay(1500);
          setBeginScreen();
          break;
        }
      }
    }
  }
  delay(500);
  rfid.halt();  
}

void setBeginScreen(){
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Welcome!");
  lcd.setCursor(0,1);
  lcd.print("To digital works");
}

void setErrorScreen(){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Please try");
  lcd.setCursor(5,1);
  lcd.print("again!");
}
