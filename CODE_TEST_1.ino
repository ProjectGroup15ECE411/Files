#include <LiquidCrystal.h> // includes the LiquidCrystal Library
#include "RTClib.h"
#include <Wire.h>

RTC_DS1307 RTC;

LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 


//************Button*****************//
int P1=8; // Button SET Alarm MENU'
int P2=9; // Hour Button
int P3=10; // Minute Button 
//**************Alarm***************//
#define buzzer 12


/*
 * the following line is declaring the variable of unassigned 
 * to hold the alarm minute and hour
 */
uint8_t alarmHours = 0, alarmMinutes = 0;  // Holds the current alarm time


/*
 * Putting the pins as outputs 
 * Note Menu the variable counting the times the button is pushed
 * 
 */

   int menu=0;

void setup() {

  pinMode(P1,INPUT_PULLUP);
  pinMode(P2,INPUT_PULLUP);
  pinMode(P3,INPUT_PULLUP);
  pinMode(buzzer, OUTPUT); // Set buzzer as an output
  int menu=0;

 Wire.begin();
 RTC.begin();
 lcd.begin(16,2);// Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 


}


/*THE functions are below the loop function
 * timenn: is a function that display the time adn date on the LCD
 * Alarm: is the function that control compare the current time with the alarb time, then write wake up on the screen
 * SetHourAlarm is the function that contrls the hours of the alarm
 * SetMinuteAlarm is the function that contrls the minute of the alarm
 * Menu:
 * depends on how many times you click on menu will take you to a different case
 * 
 */

void loop() { 

  timenn();
  Alarm();
  
  if(digitalRead(P1)== LOW)
  {
   menu=menu+1;
  }

  if (menu == 1){

    lcd.clear();
    delay(1000);
      // menu=menu+1;

  }

  if(menu==2){

    SetHourAlarm();

  }

  if (menu == 3){
    SetMinuteAlarm();
    
    }


  if (menu == 4)
  {
    menu=0;
  }
   
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Alarm");
    lcd.setCursor(0,1);
    lcd.print(alarmHours, DEC);
    lcd.print(":");
    lcd.print(alarmMinutes, DEC);
    //delay(1000);
    //lcd.clear();
    
    

    
}




void timenn(){
  
    DateTime now = RTC.now();

    lcd.setCursor(7,0);
  
   
    //lcd.print("Date:"); 
    lcd.print(now.day(), DEC);
    lcd.print("/");
    lcd.print(now.month(), DEC);
    lcd.print("/");
    lcd.print(now.year(), DEC);

    lcd.setCursor(7, 1);
    
    if (now.hour()<10)
    lcd.print("0");
    lcd.print(now.hour(), DEC);
    lcd.print(":");
    if (now.minute()<10)
    lcd.print("0");
    lcd.print(now.minute(), DEC);
    lcd.print(":");
    if (now.second()<10)
    lcd.print("0");
    lcd.print(now.second(), DEC);
    lcd.setCursor(12, 0);
    delay(1000);

    if (now.hour() == 22 && now.minute() == 32 && now.second() == 20 ){
    lcd.clear();
    delay(3000);
}
  
  
  }



void SetHourAlarm()// Setting the alarm minutes
{
  while(digitalRead(P1)==HIGH) {
 
  if(digitalRead(P2) == LOW)
  {
   if(alarmHours==23)
    {
      alarmHours=0;
    }
    else
    {
      alarmHours=alarmHours+1;
    }
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set HOUR Alarm:");
  lcd.setCursor(0,1);
  lcd.print(alarmHours,DEC);
  delay(200);
  menu = 3;
}
 }



  
void SetMinuteAlarm()// Setting the alarm minutes
 {
  while(digitalRead(P1)==HIGH){ 

  lcd.clear();
  
  if(digitalRead(P3)==LOW)
  {
  
    if (alarmMinutes==59)
    {
      alarmMinutes=0;
    }
    else
    {
      alarmMinutes=alarmMinutes+1;
    }
  }
  
  lcd.setCursor(0,0);
  lcd.print("Set MIN. Alarm:");
  lcd.setCursor(0,1);
  lcd.print(alarmMinutes,DEC);
  delay(200);

 menu = 0;
 }
 }
 


void Alarm(){

     DateTime now = RTC.now();
     if ( now.hour() == alarmHours && now.minute() == alarmMinutes )
        {
          lcd.clear();
          lcd.print("WAKE UP YA B3'AL");
          delay(1000);
         DateTime now = RTC.now();
        }
        else {
          lcd.setCursor(0,0);
          lcd.print("Alarm");
          lcd.setCursor(0,1);
          lcd.print("OFF");
          }
}

 


