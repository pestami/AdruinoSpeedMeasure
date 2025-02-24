/*

https://github.com/johnrickman/LiquidCrystal_I2C
https://docs.arduino.cc/language-reference/en/functions/external-interrupts/attachInterrupt/

Micro, Leonardo	0, 1, 2, 3, 7

*/

//========================================================================================
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

unsigned long startTime;
unsigned long elapsedTime;

unsigned long interuptStartTime;
unsigned long interuptStopTime;
unsigned long speed;

const int Button_7 = 7; 
int Button_State_7 = 0;

const int Button_1 = 1; 
int Button_State_1 = 0;
//========================================================================================
void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();  
  pinMode(Button_7, INPUT);             // initialize t:  
  pinMode(Button_1, INPUT);             // initialize t:  

   attachInterrupt(digitalPinToInterrupt(Button_7), measurestart, CHANGE);
   attachInterrupt(digitalPinToInterrupt(Button_1), measurestop, CHANGE);

                                            
  Serial.begin(9600);  //Initiate Serial communication.

}
   void measurestart() {

      interuptStartTime= millis();

    }

   void measurestop() {

      interuptStopTime= millis();

    }

//========================================================================================
void loop()
{
   Serial.print("\n========SPEAD============\n");
  
     
      Serial.print("\n-interuptstartTime: \n");
      Serial.print(interuptStartTime);
      Serial.print("\n-interupStopTime: \n");
      Serial.print(interuptStopTime);

      if  (interuptStopTime > interuptStartTime)
      {
        elapsedTime=interuptStopTime-interuptStartTime;
        Serial.print("\nELASPEED TIME: \n");
        Serial.print(elapsedTime);

        lcd.setCursor(0, 0);         // move cursor to   (2, 1)   
        lcd.print("Elapsed Time:");    
      
        lcd.setCursor(0, 1);         // move cursor to   (2, 1)  
        lcd.print("_______________");     
        lcd.setCursor(0, 1);         // move cursor to   (2, 1)  
        lcd.print(elapsedTime);   

        lcd.setCursor(5, 1);         // move cursor to   (2, 1)  
        lcd.print("ms");   

        lcd.setCursor(8, 1);         // move cursor to   (2, 1)  
        speed=85000;
        speed=speed/elapsedTime;
        speed=speed/1000;

        lcd.print(speed); 
        lcd.setCursor(13, 1);         // move cursor to   (2, 1) 
        lcd.print("m/s"); 
      }
     

 delay(200);               // display the above for two seconds

}
//========================================================================================
