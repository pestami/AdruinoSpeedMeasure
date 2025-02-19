/*

https://github.com/johnrickman/LiquidCrystal_I2C

*/

//========================================================================================
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

unsigned long startTime;
unsigned long elapsedTime;

const int Button_9 = 9; 
int Button_State_9 = 0;
//========================================================================================
void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();  
  pinMode(Button_9, INPUT);             // initialize t:  
                                          
  Serial.begin(9600);  //Initiate Serial communication.

}
//========================================================================================
void loop()
{
   Serial.print("\n========SPEAD============\n");
  Button_State_9 = digitalRead(Button_9);
  if (Button_State_9 == LOW) 
        {
          lcd.clear();   
          lcd.print("SPEAD MEASUREMENT 2025"); 
          Serial.print("\n---LOW ");
           lcd.setCursor(2, 1);         // move cursor to   (2, 1)
            lcd.print("CLOSED--------");
            lcd.setCursor(2, 1);  
            lcd.print(elapsedTime);
            Serial.print(elapsedTime);
              
          startTime = millis(); // Start timing

        } else 
        {
          Serial.print("\n----HIGH ");
            lcd.setCursor(2, 1);         // move cursor to   (2, 1)
            lcd.print("OPEN-");
            elapsedTime = millis() - startTime;
            
            lcd.print(elapsedTime);
            Serial.print(elapsedTime);
        }
 delay(200); 
 // lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("SPEAD MEASUREMENT 2025");        // print message at (0, 0)
  lcd.setCursor(2, 1);         // move cursor to   (2, 1)
// lcd.print("20 m/s "); // print message at (2, 1)
 //  delay(200);                 // display the above for two seconds

// lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("SPEAD MEASUREMENT 2025");        // print message at (0, 0)
  lcd.setCursor(2, 1);         // move cursor to   (2, 1)
 //  lcd.print("40 m/s "); // print message at (2, 1)
 //  delay(200);                  // display the above for two seconds
}
//========================================================================================
