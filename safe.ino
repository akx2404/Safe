#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
#include <Servo.h>


int red_light_pin=11 ;
int green_light_pin = 12;



int i=0;
char pass[4];
char *p1="AB25";
char k;
char *lock="####";
Servo s;

int const buzz=13;

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  s.attach(10);
  pinMode(buzz,OUTPUT);
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
}
  
void loop(){
  char k = customKeypad.getKey();
  
  
  
  if (k){
    pass[i++]=k;
    lcd.print(k);
  }

  if(i==4){
    delay(200);
    for(int j=0;j<4;j++){
      if(strncmp(pass, p1,4)==0){
        lcd.clear();
        lcd.print("pass Accepted");
        digitalWrite(green_light_pin,HIGH);
        delay(1000);
        digitalWrite(green_light_pin,LOW);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Opened---");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0,0);
        i=0;
        s.write(90);
        
      }

      else if(strncmp(pass, lock,4)==0){
        lcd.clear();
        lcd.print("Locking ---");
        s.write(180);
        digitalWrite(buzz,HIGH);
        delay(500);
        digitalWrite(buzz,LOW);
        lcd.clear();
        lcd.setCursor(0,0);
        i=0;
        
      }
  
    else{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.println("Wrong password !");
      digitalWrite(buzz,HIGH);
      digitalWrite(red_light_pin,HIGH);
      delay(1000);
      digitalWrite(buzz,LOW);
      digitalWrite(red_light_pin,LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Try Again :( ");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0);
      i=0;
      s.write(180);
      
    }

    
  }}





  
}
