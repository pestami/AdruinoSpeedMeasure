/*

https://github.com/johnrickman/LiquidCrystal_I2C

*/


#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
}

void loop()
{
  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("SPEAD MEASUREMENT 2025");        // print message at (0, 0)
  lcd.setCursor(2, 1);         // move cursor to   (2, 1)
  lcd.print("20 m/s "); // print message at (2, 1)
  delay(2000);                 // display the above for two seconds

 lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("SPEAD MEASUREMENT 2025");        // print message at (0, 0)
  lcd.setCursor(2, 1);         // move cursor to   (2, 1)
  lcd.print("20 m/s "); // print message at (2, 1)
  delay(2000);                  // display the above for two seconds
}
