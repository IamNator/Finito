
#include "Wire.h"
#include "SSD1306.h"  //For display

SSD1306 display(0x3C, 5, 4); // display(I2C Address, SDA_Pin, SCL_Pin)


volatile int userInputNumber = 0;
int threshold = 50; //The Bigger the threshold, the more sensible is the touch
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

void gotTouch4(){
 touchNumber = 4;
}

void gotTouch6(){
 touchNumber = 6;
}

void getUserInput(){
  switch(touchNumber){
    case 0:
      userInputNumber = 0;
      break;
    case 1:
      userInputNumber = 1;
      break;
    case 2:
      userInputNumber = 2;
      break;
    case 3: 
      userInputNumber = 3;
      break;
    case 4:
      userInputNumber = 4;
      break;
    case 5:
      userPressedEnter = true;
      userInputNumber = 5;
      break;
    case 6:
      userPressedCancel = true;
      userInputNumber = 6;
      break;
    default :
      Serial.println("Key not included");
      break;
  }
      touchNumber = 0;
}

void DisplayNumberEntered(){
    display.init();
    display.flipScreenVertically();
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


void DisplayFinito(){
    display.init();
    display.flipScreenVertically();
    display.clear();
    display.setFont(ArialMT_Plain_24);
    display.setColor(WHITE);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    //transactionToken
    display.drawString(16, 8, "Finito" );
    display.display();
}


void setup() { 

  touchAttachInterrupt(T0, gotTouch2, threshold); //Number 0
  touchAttachInterrupt(T1, gotTouch2, threshold); //Number 1
  touchAttachInterrupt(T2, gotTouch2, threshold); //Number 2
  touchAttachInterrupt(T3, gotTouch3, threshold); //Number 3
  touchAttachInterrupt(T4, gotTouch4, threshold); //Number 4
  touchAttachInterrupt(T6, gotTouch6, threshold); //  Cancel
  
  display.init();//Initiate onbaord OLED Display

  DisplayFinito();
  user.userID = "2";
  
  transactionToken.userID1 = user.userID;
  transactionToken.userID2 = "1";
  transactionToken.amount = "";

  
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
  
  
  Serial.println(F("Connected to the WiFi network"));  

  
}

  
void loop() {
  
  if (MAKEPAYMENT == 10){ //Make Payment
    transactionToken.amount = getAmountFromUser();
    makePayment();
    UpdateUserDetails(&user, httpgetUserDetails(user.userID));
    UpdateUserDetails(&userDeptor, httpgetUserDetails(transactionToken.userID2));
    DisplayTransactionDone(&transactionToken);
    delay(5000);
  } else if (MAKEPAYMENT == 20){ //Receive Payment
    UpdateUserDetails(&user, httpgetUserDetails(user.userID));
    UpdateUserDetails(&userDeptor, httpgetUserDetails(transactionToken.userID2));
    DisplayUserDetails(&user);
    delay(5000);  //Send a request every 10 seconds
    //DisplayAmountReceived();
  }

  DisplayFinito();
  delay(5000);
  while(1){
    UpdateUserDetails(&user, httpgetUserDetails(user.userID));
    DisplayUserBalance(&user);
    delay(3000);
  }
  
  
}
