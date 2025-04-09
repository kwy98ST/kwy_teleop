#include <Encoder.h>
#include "tb6612_motor.h"

float x = 0.0;
float y = 0.0;
int speed = 0;

SPDMotor *motorRB = new SPDMotor(19, 38, true, 8, 36, 37);
SPDMotor *motorRF = new SPDMotor(19, 38, true, 8, 37, 36);
SPDMotor *motorLB = new SPDMotor( 3, 49, true, 6, 43, 42);
SPDMotor *motorLF = new SPDMotor( 3, 49, true, 6, 42, 43);

void setup() {
  Serial2.begin(9600);
}

void loop() {
  
    
    
    if (Serial2.available() > 0) {
      String input = Serial2.readStringUntil('\n');
      //input.trim();
      

      // \uac12\uc774 "x y speed" \ud615\uc2dd\uc774\ub77c\uace0 \uac00\uc815 (\uc608: "0.5 0.0 50.0")
    int firstSpace = input.indexOf(' ');
    int secondSpace = input.indexOf(' ', firstSpace + 1);

    if (firstSpace > 0 && secondSpace > firstSpace) {
      String xStr = input.substring(0, firstSpace);
      String yStr = input.substring(firstSpace + 1, secondSpace);
      String speedStr = input.substring(secondSpace + 1);

      x = xStr.toFloat();
      y = yStr.toFloat();
      speed = speedStr.toInt();
      

      if(x == 0.5 && y == 0.0){
        
        motorRB->hardStop();
      motorLB->hardStop();
      motorLF->speed(speed);
      motorRF->speed(speed);
    }else if(x == -0.5 && y == 0.0){
      motorRF->hardStop();
        motorLF->hardStop();
        motorLB->speed(speed);
        motorRB->speed(speed);
    }else if(x == 0.0 && y == 0.5){
      motorRF->hardStop();
      motorLB->hardStop();
      motorLF->speed(speed);
      motorRB->speed(speed);
    }else if(x == 0.0 && y == -0.5){
      motorRB->hardStop();
      motorLF->hardStop();
      motorLB->speed(speed);
      motorRF->speed(speed);
    }    else if(x == 0.0 && y == 0.0){
      motorRF->hardStop();
      motorRB->hardStop();
      motorLF->hardStop();
      motorLB->hardStop();
    }
      }
    
  }
}
