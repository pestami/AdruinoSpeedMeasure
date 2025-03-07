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
long speed;

const int Button_7 = 7; 
int Button_State_7 = 0;
int Button_Start = 0;  // variable for reading the pushbutton status

const int Button_1 = 1; 
int Button_State_1 = 0;
int Button_Stop = 0; 

int FlagMeasurementDone=0;
int FlagMeasurementStart=0;
int FlagMeasurementStop=0;
int measurementCounter = 0; 

String sSpeed="";
String sSpeedUnformated="";
//========================================================================================
void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();  
  pinMode(Button_7, INPUT);             // initialize t:  
  pinMode(Button_1, INPUT);             // initialize t:  

   attachInterrupt(digitalPinToInterrupt(Button_7), measurestart, RISING);
   attachInterrupt(digitalPinToInterrupt(Button_1), measurestop, FALLING);

                                            
  Serial.begin(9600);  //Initiate Serial communication.

}
   void measurestart() {

      interuptStartTime= millis();
      FlagMeasurementStop=0;
      FlagMeasurementStart=1;

    }

   void measurestop() {

      interuptStopTime= millis();  //millis()   micros()
      FlagMeasurementStop=1;
      FlagMeasurementStart=0;

    }

//========================================================================================
void loop()
{


    Button_Start = digitalRead(Button_7);
    Button_Stop = digitalRead(Button_1);





     // if  (interuptStopTime > interuptStartTime)
      if (FlagMeasurementStart==0 && FlagMeasurementStop==1)
      {

        elapsedTime=interuptStopTime-interuptStartTime;
        FlagMeasurementDone=1;
        lcd.setCursor(0, 0);         // move cursor to   (2, 1)   
        lcd.print("Elapsed Time:");    
      
        lcd.setCursor(0, 1);         // move cursor to   (2, 1)  
        lcd.print("_______________");     
        lcd.setCursor(0, 1);         // move cursor to   (2, 1)  
        lcd.print(elapsedTime);   

        lcd.setCursor(7, 1);         // move cursor to   (2, 1)  
        lcd.print("ms");   

                 // move cursor to   (2, 1)  
        speed=85*1000*10;   //*1000; // mm
        speed=speed/elapsedTime; // micro second
        speed=speed;
        //speed=123;
        sSpeed=String(speed);
        sSpeedUnformated=sSpeed;
        sSpeed=sSpeed.substring(0,1)+"."+ sSpeed.substring(1,1);

        lcd.setCursor(10, 1);
        lcd.print(sSpeed); 
        lcd.setCursor(13, 1);         // move cursor to   (2, 1) 
        lcd.print("m/s"); 

          measurementCounter+=1;

            Serial.print("\n========SPEED============");
            
            Serial.print("\nSCounter: " + String(measurementCounter) + "");
            Serial.print("\nStart Button:" + String(Button_Start) + "");
            Serial.print("\nStop Button:" + String(Button_Stop) + "");     
            Serial.print("\nStart Interupt:" + String(FlagMeasurementStart) + "");
            Serial.print("\nStop Interupt:" + String(FlagMeasurementStop) + "");     
            Serial.print("\n-interuptstartTime: ");
            Serial.print(interuptStartTime);
            Serial.print("\n-interupStopTime: ");
            Serial.print(interuptStopTime);
            Serial.print("\nELASPEED TIME: ");
            Serial.print(elapsedTime);
            Serial.print("\n-Speed String: ");
           Serial.print(":" + sSpeedUnformated+ ":");
            Serial.print("\n-Speed String len: ");
           Serial.print(sSpeedUnformated.length());
            Serial.print("\n=========================\n");

      FlagMeasurementStop=0;
      FlagMeasurementStart=0;
      }

  if (Button_Start==LOW && Button_Stop==HIGH)
    {
      interuptStartTime=0;
      interuptStopTime=0;
        lcd.setCursor(0, 0);         // move cursor to   (2, 1)   
        lcd.print("Device Ready");   
        //lcd.setCursor(0, 1);         // move cursor to   (2, 1)   
        //lcd.print("----------------");   
        // FlagMeasurementDone=0;
        // FlagMeasurementStop=0;
        //FlagMeasurementStart=1;
            // Serial.print("\n========SPEED============");
            // Serial.print("\nReady to go !!! ");
            // Serial.print("\n=========================\n");
    }

 delay(2000);               // display the above for two seconds

}
//========================================================================================
