/*

https://github.com/johnrickman/LiquidCrystal_I2C
https://docs.arduino.cc/language-reference/en/functions/external-interrupts/attachInterrupt/

Micro, Leonardo	0, 1, 2, 3, 7

*/

//========================================================================================
// DECLARATIONS
//========================================================================================
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

unsigned long startTime;
unsigned long elapsedTime;

unsigned long interuptStartTime;
unsigned long interuptStopTime;
long int speed;

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
int intLen=0;

int MStatePre=1111;
int MState=1111;
//========================================================================================
// INTERUPT HANDLERS
//========================================================================================
      #include <TimerOne.h>
      int Timer_Loop=0; 
    void Timer1_ISR(void)
      {
        Timer_Loop=Timer_Loop + 1;
        if (Timer_Loop==11){ Timer_Loop=0;}   // timer counts one to 10
      }   
   void measurestart() 
      {
        interuptStartTime= millis();
        MStatePre=MState;
        MState=101;
        FlagMeasurementStop=0;
        FlagMeasurementStart=1;
      }
   void measurestop() 
      {
        if (FlagMeasurementStart==1)
        {
          interuptStopTime= millis();  //millis()   micros()
          MStatePre=MState;
          MState=110;
          FlagMeasurementStop=1;
          FlagMeasurementStart=0;
        }
      }
//========================================================================================
// PROCEDURES
//========================================================================================
void DebugPrint()
{
  Serial.print("\n=======MACHINE STATE=====");
  
  Serial.print("\nSCounter: " + String(measurementCounter) + "");
  Serial.print("\nStart Button:" + String(Button_Start) + "");
  Serial.print("\nStop Button:" + String(Button_Stop) + "");     
  Serial.print("\nStart Interupt:" + String(FlagMeasurementStart) + "");
  Serial.print("\nStop Interupt:" + String(FlagMeasurementStop) + "");  

  Serial.print("\n MachineState_now =:" + String(MState) + "");  
  Serial.print("\n nMachineState_Pre = :" + String(MStatePre) + "");  

  Serial.print("\n========SPEED============");   

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
  
  Serial.print("\n Speed=" + sSpeed + "");    
  Serial.print("\n=========================\n");

}
//========================================================================================
// SETUP
//========================================================================================
void setup()
        {
          lcd.init(); // initialize the lcd
          lcd.backlight();  
          pinMode(Button_7, INPUT);             // initialize t:  
          pinMode(Button_1, INPUT);             // initialize t:  

          attachInterrupt(digitalPinToInterrupt(Button_7), measurestart, RISING);
          attachInterrupt(digitalPinToInterrupt(Button_1), measurestop, FALLING);
          
            Timer1.initialize(100*1000); // Fire An Interrupt Every 100ms // Timer_Loop counts to 10 = 1 count per second
            Timer1.attachInterrupt(Timer1_ISR);
                                                    
          Serial.begin(9600);  //Initiate Serial communication.
        }
//========================================================================================
//MAIN LOOP
//========================================================================================
void loop()
{   if (Timer_Loop==0)   // every second buttons are read
      {
        Button_Start = digitalRead(Button_7);
        Button_Stop = digitalRead(Button_1);
      }    
    if (Button_Start==LOW && Button_Stop==HIGH)  //
      {
         MStatePre=101;
         MState=101;   // Device Ready Pre state reset

        interuptStartTime=0;
        interuptStopTime=0;

          if ((Timer_Loop % 3) ==0 )   // every 10/3 second buttons are read
            {
                lcd.setCursor(0, 0);         // move cursor to   (2, 1)   
                lcd.print("Device Ready    ");   
                lcd.setCursor(0, 1);         // move cursor to   (2, 1)   
                lcd.print("----------------");  
            }

          // delay(2000); 
      }

     // if  (interuptStopTime > interuptStartTime)
      if (FlagMeasurementStart==0 && FlagMeasurementStop==1)
      {
        elapsedTime=interuptStopTime-interuptStartTime;
        FlagMeasurementDone=1;
        //lcd.setCursor(0, 0);         // move cursor to   (2, 1)   
        //lcd.print("Elapsed Time:");    
      
        lcd.setCursor(0, 1);         // move cursor to   (2, 1)  
        lcd.print("           ");     
        //lcd.setCursor(0, 1);         // move cursor to   (2, 1)  
        //lcd.print(elapsedTime);   

       // lcd.setCursor(7, 1);         // move cursor to   (2, 1)  
       // lcd.print("ms");   

                 // move cursor to   (2, 1)  
        speed=85*1000*10;   //*1000*10 to avoid truncation of digits; // mm
        speed=speed/elapsedTime; // time is micro second

         
        sSpeed=String(speed);
        sSpeedUnformated=sSpeed; // variable for debug
        intLen=sSpeedUnformated.length();
        sSpeed=sSpeed.substring(0,3)+"."+ sSpeed.substring(3,0);  //string substr (size_t pos, size_t len) const;

        speed=speed/1000;
        sSpeedUnformated=String(speed);

        //long int v = 123456; 
        ///printf("%.1f\n", v / 10000.0);

	      //char output[10];
	      //sprintf(output, "%.1f m/s", speed/10.0/1000.0); //speed = long int
        //sSpeed=String(output);

        lcd.setCursor(0, 0);         // move cursor to   (2, 1)   
        lcd.print("              ");    
        lcd.setCursor(0, 0);         // move cursor to   (2, 1)   
        lcd.print("Measurement Done");  
        lcd.setCursor(0, 1);         // move cursor to   (2, 1)   
        lcd.print("                ");   
        lcd.setCursor(0, 1);
        //lcd.print(sSpeed); 
        lcd.print(sSpeedUnformated.substring(0,14));
        //lcd.setCursor(13, 1);         // move cursor to   (2, 1) 
        //lcd.print("m/s"); 

          measurementCounter+=1;

           DebugPrint()

      FlagMeasurementStop=0;
      FlagMeasurementStart=0;
         delay(4000);               // display the above for two seconds
      }



 //delay(2000);               // display the above for two seconds

}
//========================================================================================
