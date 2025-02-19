/*

https://github.com/johnrickman/LiquidCrystal_I2C

*/

//========================================================================================
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

unsigned long startTime;
unsigned long elapsedTime;

unsigned long interuptstartTime;
unsigned long interuptstopTime;

const int Button_7 = 7; 
int Button_State_7 = 0;
//========================================================================================
void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();  
  pinMode(Button_7, INPUT);             // initialize t:  

   attachInterrupt(digitalPinToInterrupt(Button_7), measurestart, CHANGE);

  


                                          
  Serial.begin(9600);  //Initiate Serial communication.

}
   void measurestart() {

      interuptstartTime= millis();

    }


//========================================================================================
void loop()
{
   Serial.print("\n========SPEAD============\n");
  
     
      Serial.print("\n-interuptstartTime: \n");
      Serial.print(interuptstartTime);
      Serial.print(interuptstopTime);

      lcd.setCursor(1, 1);         // move cursor to   (2, 1)       
      lcd.print(interuptstartTime);
       lcd.setCursor(2, 1);         // move cursor to   (2, 1)       
      lcd.print(interuptstopTime);
     

 delay(200);               // display the above for two seconds

}
//========================================================================================
