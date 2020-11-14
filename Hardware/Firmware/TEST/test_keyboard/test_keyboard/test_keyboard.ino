
#include "Wire.h"
#include "SSD1306.h"  //For display


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

int getUserPassword(){

    display.init();
    //display.flipScreenVertically();  
    while (!userPressedEnter){
      delay(300);
      getUserInput();
      
      if (userPressedCancel){
        userInputNumber = 0;
      }
      
      
      display.flipScreenVertically(); 
      display.setFont(ArialMT_Plain_16);
      display.setColor(WHITE);
      display.setTextAlignment(TEXT_ALIGN_LEFT);
      display.drawString(16, 4, "Enter Password\n" + String(userInputNumber) );
      display.display();
      display.clear();
  }
 
  FalseAll();
  return userInputNumber;
}

int CheckPassword(int password){
  if (password == PASSWORD){
    return 1;
  } else {
    return 0;
  }
}

int getTransactionType(){
  display.init();
  display.flipScreenVertically();  
    userInputNumber = 0;
    while (!userPressedEnter){
      delay(300);
      getUserInput();
     
      if (userPressedCancel){
        userInputNumber = 0;
      }
      
      
      display.clear();
      display.setFont(ArialMT_Plain_16);
      display.setColor(WHITE);
      display.setTextAlignment(TEXT_ALIGN_LEFT);
      display.drawString(16, 4, "Payment Type\n" + String(userInputNumber) );
      display.display();
  }
 
  FalseAll();
  return userInputNumber;
}

int getAmountFromUser(){
     display.init();
     display.flipScreenVertically(); 
     userInputNumber = 0;  
     userPressedEnter = false;
     int no_user_pressed_enter = 0;
     
    while (no_user_pressed_enter<2){
      
      if(userPressedEnter){
        no_user_pressed_enter +=1;
      }
      
      delay(300);
      getUserInput();
      
      if (userPressedCancel){
        userInputNumber = 0;
      }
      
      
      display.clear();
      display.setFont(ArialMT_Plain_16);
      display.setColor(WHITE);
      display.setTextAlignment(TEXT_ALIGN_LEFT);
      display.drawString(16, 4, "Enter Amount\n" + String(userInputNumber) );
      display.display();
    }

    FalseAll();
    return userInputNumber;
}

void DisplayUserBalance(USER *user){
    display.init();
    display.flipScreenVertically();
    display.clear();
    display.setFont(ArialMT_Plain_24);
    display.setColor(WHITE);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    //transactionToken
    display.drawString(16, 8, "Balance \n" + String(user->balance) );
    display.display();
    Serial.println(user->balance);
}

void setup() { 

  touchAttachInterrupt(T2, gotTouch2, threshold);
  touchAttachInterrupt(T3, gotTouch3, threshold);
  touchAttachInterrupt(T4, gotTouch4, threshold);
  touchAttachInterrupt(T6, gotTouch6, threshold);
  
  display.init();//Initiate onbaord OLED Display

  DisplayFinito();
  user.userID = "2";
  
  transactionToken.userID1 = user.userID;
  transactionToken.userID2 = "1";
  transactionToken.amount = "";

  
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
  
  WiFi.begin(ssid, password); 
  
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println(F("Connecting to WiFi.."));
  }
  
  Serial.println(F("Connected to the WiFi network"));  

  int user_password = 0;

  
  
  while(!CheckPassword(user_password)){
     user_password = getUserPassword();
     delay(1000);
  }



  MAKEPAYMENT = 0;
  while( (MAKEPAYMENT != 10) && (MAKEPAYMENT != 20)  ){
     MAKEPAYMENT = getTransactionType();
     delay(1000);
  }
  
  
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
