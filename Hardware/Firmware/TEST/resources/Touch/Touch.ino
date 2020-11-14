/*
This is un example howto use Touch Intrrerupts
The bigger the threshold, the more sensible is the touch
*/
#include "Wire.h"
#include "SSD1306.h"  //For display
SSD1306 display(0x3C, 5, 4); // display(I2C Address, SDA_Pin, SCL_Pin)

volatile int userInputNumber = 0;
int threshold = 55; //The Bigger the threshold, the more sensible is the touch
volatile bool userPressedEnter = false;
volatile bool userPressedCancel = false;

volatile int touchNumber = 0;


void FalseAll(){
 userPressedEnter = false;
 userPressedCancel = false;
}


void gotTouch2(){
 touchNumber = 2;
}

void gotTouch3(){
 touchNumber = 3;
}
//
void gotTouch4(){
 touchNumber = 4;
}

void gotTouch6(){
 touchNumber = 6;
}

void getUserInput(){
  switch(touchNumber){
    case 2:
      userInputNumber +=10;
      break;
    case 3: 
      if (userInputNumber <= 0){
        userInputNumber = 0;
      } else{
        userInputNumber -=10; 
      }
      break;
    case 6:
      userPressedCancel = true;
      break;
    case 4:
      userPressedEnter = true;
      break;
  }
      touchNumber = 0;
}

void DisplayNumberEntered(){
    display.init();
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.setColor(WHITE);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(16, 32,String(userInputNumber) );
    display.display();
}

int getInputFromUser(){

  while (!userPressedEnter){
    delay(350);
    getUserInput();
    
    if (userPressedCancel){
      userInputNumber = 0;
    }
    
    DisplayNumberEntered();
  }
 
  FalseAll();
  return userInputNumber;
}


void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Interrupt Test");

  touchAttachInterrupt(T2, gotTouch2, threshold);
  touchAttachInterrupt(T3, gotTouch3, threshold);
  touchAttachInterrupt(T4, gotTouch4, threshold);

  touchAttachInterrupt(T6, gotTouch6, threshold);

  Serial.println("End of interrupts");
  DisplayNumberEntered();
  delay(3000);
}

void loop(){
  getInputFromUser();
}
