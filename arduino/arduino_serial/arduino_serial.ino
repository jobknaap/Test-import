#include <SPI.h>
#include <RFID.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9

LiquidCrystal_I2C lcd(0x27, 16, 2);
RFID rfid(SS_PIN,RST_PIN);

int serNum[5];
int cards[][5] = {{237,131,63,89,8}, 243,90,36,21,152};

void setup() {
  Serial.begin(9600);
  lcd.begin();
  SPI.begin();
  rfid.init();

  lcd.backlight();
  
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,4);
  lcd.print("Welcome!");

  lcd.setCursor(1,0);
  lcd.print("To digital works");
  
  if(rfid.isCard()) {        
    if(rfid.readCardSerial()) {       
      for(int i = 0; i < sizeof(rfid.serNum); i++ ) {
        if(rfid.serNum[i] == cards[0][i]) {
          access = true;
          lcd.setCursor(0,0);
          lcd.print("Hi! job enjoy your work day");
          break;
        } else if(rfid.serNum[i] == cards[1][i]) {
            access = true;
            lcd.setCursor(0,0);
            lcd.print("Hi! mats enjoy your work day");
            break;
        } else {
            lcd.setCursor(0,0);
            lcd.print("Please try again!");
        }
      }
    }
    delay(1500);
  }
  rfid.halt();  
}
