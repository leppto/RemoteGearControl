// C++ code
//
#include "Arduino.h"
#include "Servo.h"
//Unkomment if Heartbeat is in use
/*#include <SoftwareSerial.h>
SoftwareSerial s = SoftwareSerial (7,8); // (Rx, Tx)
*/

// Global variables and defines
const int servoMDTargetNeutral   = 90;//1480; //Position when neutral
const int servoMDTargetForward = 0;//2200; //Position when forward
const int servoMDTargetBackward = 180;//750; //Position when backward
const int buttonPin1 = 4; //Gear to forward
const int buttonPin2 = 2; //Gear to backward
const int ledPin1 = 12; 
#define SERVOMD_PIN_SIG	6
Servo servoMD;
int pos;

int currentPos;
int buttonState1;
int buttonState2;

int showGearForward = 0;
int showGearBackward = 0;
int showGearNeutral = 0;

int servoDelay=50;

#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#endif

//Unkomment if Heartbeat is in use
/*
// Hearbeat
int availability =0;
int check_if_available(int );
*/

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  
  Serial.begin(9600);
  debugln("Start setup");
  servoMD.attach(SERVOMD_PIN_SIG);
  debugln("Testrun servo");
  debugln("Current position Forward:");
  servoMD.write(servoMDTargetForward);
  currentPos = servoMD.read();
  debugln(currentPos);
  delay(1000);

  debugln("Current position backward:");
  servoMD.write(servoMDTargetBackward);
  currentPos = servoMD.read();
  debugln(currentPos);
  delay(1000);

  debugln("Current position neutral:");
  servoMD.write(servoMDTargetNeutral);
  currentPos = servoMD.read();
  debugln(currentPos);
  delay(1000);

  servoMD.detach();
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);

  debugln("Led on");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);

  debugln("Led off");
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  debugln("Setup ready");
  
  //Unkomment if Heartbeat is in use
  /*
  s.begin(9600);
  delay(1000);
  
  if(s.available()>0)
  {
    debugln("1 is available");
  }else{
    debugln("1 is not available"); 
  }

  // Heartbeat
  check_if_available(10);
  
  */
}

void loop()
{
 //Unkomment if Heartbeat is in use
 // check_if_available(10); 
  
  
  
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1); //Gear to forward
  buttonState2 = digitalRead(buttonPin2); //Gear to backward
   
  if(DEBUG == 1){
      
      if (buttonState1 == HIGH) { 
            digitalWrite(LED_BUILTIN, HIGH);
            servoMD.attach(SERVOMD_PIN_SIG);

            if (showGearForward == 0){
              debug(F("Button 1, Gear forward: ")); debugln(buttonState1);
              servoMD.write(servoMDTargetForward);
              delay(1000);
              currentPos = servoMD.read();
              debug(F("Servo curren pos: ")); debugln(currentPos);
              showGearNeutral=0;
              showGearBackward=0;
            }
            showGearForward++;
            servoMD.detach();
      }

      else if (buttonState2 == HIGH) { 
          digitalWrite(LED_BUILTIN, HIGH);
          servoMD.attach(SERVOMD_PIN_SIG);

           if (showGearBackward == 0){
            debug(F("Button 2, Gear backward: ")); debugln(buttonState2);
            servoMD.write(servoMDTargetBackward);
            delay(1000);
            currentPos = servoMD.read();
            
            debug(F("Servo curren pos: ")); debugln(currentPos);
            showGearNeutral=0;
            showGearForward=0;
          }
          showGearBackward++;
          servoMD.detach();
      }
      else
      {
          digitalWrite(LED_BUILTIN, LOW);
          servoMD.attach(SERVOMD_PIN_SIG);
        
          if (showGearNeutral == 0){
             debug(F("No buttons, Gear neutral: "));
            servoMD.write(servoMDTargetNeutral);
            delay(1000);
            currentPos = servoMD.read();
            debug(F("Servo curren pos: ")); debugln(currentPos);
            showGearForward=0;
            showGearBackward=0;
          }
          showGearNeutral++;

          delay(1000);
          servoMD.detach();
      }
  }
  else
  {
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH: Gear to forward
  if (buttonState1 == HIGH) { 
    // turn LED on:
    digitalWrite(LED_BUILTIN, HIGH);
    servoMD.attach(SERVOMD_PIN_SIG);  // 1. attach the servo to correct pin to control it.
    
    
    // 2. turns servo to target position. Modify target position by modifying the 'ServoTargetPosition' definition above.
    if(currentPos!=280){
      for(pos=currentPos;pos<=280;pos++){
        servoMD.write(pos);
        debugln(servoMD.read());
        delay(servoDelay);
      }
    }
	  // release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
    servoMD.detach();  
    currentPos = servoMD.read();
    if (showGearForward == 0){
      debug(F("Button 1, Gear forward: ")); debugln(buttonState1);
      debug(F("Servo curren pos: ")); debugln(currentPos);
      showGearNeutral=0;
      showGearBackward=0;
    }
    showGearForward++;
   
  }
   // check if the pushbutton is pressed. If it is, the buttonState is HIGH: Gear to backward
  else if(buttonState2 == HIGH){
    // turn LED on:
    digitalWrite(LED_BUILTIN, HIGH);
    servoMD.attach(SERVOMD_PIN_SIG);  
  	
   
  	// 2. turns servo to target position. Modify target position by modifying the 'ServoTargetPosition' definition above.
    if(currentPos!=0){
      for(pos=currentPos;pos>=0;pos--){
        servoMD.write(pos);
        debugln(servoMD.read());
        delay(servoDelay);
      }
    }
    delay(100);
    // release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
  	servoMD.detach();
    currentPos = servoMD.read();

    if (showGearBackward == 0){
      debug(F("Button 2, Gear backward: ")); debugln(buttonState2);
      debug(F("Servo curren pos: ")); debugln(currentPos);
      showGearNeutral=0;
      showGearForward=0;
    }
    showGearBackward++;
  }
  else {
    // turn LED off:
    
   	digitalWrite(LED_BUILTIN, LOW);
    servoMD.attach(SERVOMD_PIN_SIG);  
  	currentPos = servoMD.read();

  	// 3. turns servo back to rest position. Modify initial position by modifying the 'ServoRestPosition' definition above.
    if(currentPos > 90 ){
      for(pos=currentPos;pos>=90;pos--){
          servoMD.write(pos);
          debugln(servoMD.read());
          delay(servoDelay);
      }
    }
    else if(currentPos < 90 ){
      for(pos=currentPos;pos<=90;pos++){
          servoMD.write(pos);
          debugln(servoMD.read());
          delay(servoDelay);
      }
    }
      
      // release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
      servoMD.detach();
      currentPos = servoMD.read();
      
      if (showGearNeutral == 0){
        debug(F("No buttons, Gear neutral: "));
        debug(F("Servo curren pos: ")); debugln(currentPos);
        showGearForward=0;
        showGearBackward=0;
      }
      showGearNeutral++;
  }
  
  
  
  } // End debug
  digitalWrite(ledPin1, LOW);
 
  delay(1000);
}

//Unkomment if Heartbeat is in use
/*
// Heartbeat
int check_if_available(int a)
{
  s.write(a); //Hello
  delay(10);


  if(s.available()>0) //check if there is incoming data
  {
    int data = s.read();

    if(data==11) //Hello back
    {
        debugln("Hello back 1");
        debugln("Data Received, Uno 1 is master");
      	digitalWrite(ledPin1, HIGH);
        return 1;
    }
  }
  else
  {
        debugln("No data received, Uno 2 must take over");
        return 0;
  }
}

*/
