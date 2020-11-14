#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> //For Handling Json files

#include "Wire.h"
#include "SSD1306.h"  //For display


#define PASSWORD 20

  
const char* ssid = "Galaxy";
const char* password =  "hereNator";


typedef struct USER{
  String fname;
  String lname;
  String balance;
  String accountNumber;
  String userID;
  String lastUpdate;
} USER;

typedef struct TOKEN {
  String userID1; //Creditor/Sender
  String userID2; //Debitor/REceiver
  String amount; //amount to be transfered
} TOKEN;


//GLOBAL Variables
USER user;
USER userDeptor; //Money is sent ti this person
TOKEN transactionToken;
SSD1306 display(0x3C, 5, 4); // display(I2C Address, SDA_Pin, SCL_Pin)

volatile int MAKEPAYMENT = 0;


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



String GenerateTransanctionToken(TOKEN *transactionToken){
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<100> doc;
  doc["userID1"] = transactionToken->userID1;
  doc["userID2"] = transactionToken->userID2;
  doc["amount"] = transactionToken->amount;
  doc["password"] = PASSWORD;

  
  String output;
  
  serializeJson(doc, output);
 // Serial.println(output);
  
  return output; 
}

String httpgetUserDetails(String userID){

  String payload;
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin( ("http://finito-cloud.herokuapp.com/api/fetch/"+ userID) ); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
 
  delay(100);
  
  return payload;
}


void UpdateUserDetails(USER * user, String json){

  StaticJsonDocument<700> doc;

  DeserializationError error = deserializeJson(doc, json);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
     return;
  }

  user->fname=doc["name"].as<String>();
 // user->lname=doc["lname"].as<String>();
  user->userID=doc["id"].as<String>();
  user->balance=doc["wallet"].as<String>();

}

void makePayment(){
  
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

   HTTPClient http; 
   http.begin("http://finito-cloud.herokuapp.com/api/send");  //Specify destination for HTTP request
   http.addHeader("Content-Type", "application/json");             //Specify content-type header
  
   String postData = String(GenerateTransanctionToken(&transactionToken));
   Serial.println(postData);
   delay(100);
   int httpResponseCode = http.POST(postData);   //Send the actual POST request
  
   if(httpResponseCode>0){
   
   String response = http.getString();                       //Get the response to the request
   
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
   
   }else{
  
    Serial.print(F("Error on sending POST: "));
    Serial.println(httpResponseCode);
   
   }
  
   http.end();  //Free resources
  
 }else{
  
   Serial.println("Error in WiFi connection");   

 }
}


void DisplayTransactionDone(TOKEN * transactionToken){
  display.init();
  display.flipScreenVertically();
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(10, 3, transactionToken->amount + "\nsent to\n" +  userDeptor.fname ); //Opeyemi \n 02344485"
  display.display();
}

void DisplayUserDetails(USER *user){
  //Fetch stored user details
  //display it on the screen
  display.init();
  display.flipScreenVertically();
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(10, 3, user->fname + "\n" + user->userID ); //Opeyemi \n 02344485"
  display.display();
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
