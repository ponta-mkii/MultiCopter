//This program is a quote
//URL:https://www.dropbox.com/s/cgqzhisb2gbgjjc/basic_t.ino?dl=0

/* ENSA-M QUADROTOR */

/*
AUTHOR: Scientific Club- ENSA of Marrakech
UCAM University, Marrakech, Morocco
*/

/*
Motors won't turn if you don't ARM them;
First, send the 'A' command to arm the motors;
Then, send speed commands fitting the pattern: $tyyyy
Example:
$10040 will the send the 40 command to the motor number 1
*/

#include <Servo.h>

Servo mymotor1;
Servo mymotor2;
Servo mymotor3;
Servo mymotor4;

//First run
void setup()
{
  //serial start conect
  Serial.begin(115200);

  mymotor1.attach(3);
  mymotor2.attach(5);
  mymotor3.attach(6);
  mymotor4.attach(9);
  
  mymotor1.write(0);
  mymotor2.write(0);
  mymotor3.write(0);
  mymotor4.write(0);

  //serial monitor display "ENSA-M Quadrotor"
  Serial.println("ENSA-M Quadrotor");
}

//Main Loop
void loop() 
{
    if (Serial.available()>0) { // Pattern form: $tyyyy
        
        char mode=Serial.read();
        
        if (mode=='$') {
              while (Serial.available()<5) ;
              int target=Serial.read()-'0'; // t
              int a4=Serial.read()-'0';
              int a3=Serial.read()-'0';
              int a2=Serial.read()-'0';
              int a1=Serial.read()-'0';
              int val_speed = a1 + a2*10 + a3*100 + a4*1000;
                        
              if (target==1) mymotor1.write(val_speed);
              if (target==2) mymotor2.write(val_speed);
              if (target==3) mymotor3.write(val_speed);
              if (target==4) mymotor4.write(val_speed);
	      // use the function "writeMicroseconds" instead of "write" for more precision
              
              Serial.print("sent value = ");
              Serial.print(val_speed);
              Serial.print(" to target ");
              Serial.println(target);
        }
        
        if (mode=='A') { // ARM
              mymotor1.write(10);
              mymotor2.write(10);
              mymotor3.write(10);
              mymotor4.write(10);
              // the "10" value may need to be changed as it depends on the used ESC (see datasheet for appropriate command to arm)
      
              Serial.println("armed motors");
        }
        
    }   
}
