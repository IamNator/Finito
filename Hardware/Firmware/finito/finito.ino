#include "Wire.h"
#include "SSD1306.h"  //For display
#include <ArduinoJson.h> //For Handling Json diles

#include "WiFi.h" 
#include "ESPAsyncWebServer.h"
#include <HTTPClient.h>

AsyncWebServer server(80); // Port 80 for wifi server 

//For control
#define SEND 0
#define RECEIVE 1
volatile int CHANGE_TRANSACTION_TYPE = 0;
String sendToken;


SSD1306 display(0x3C, 5, 4); // display(I2C Address, SDA_Pin, SCL_Pin)



//serial speed of both the SIM800L and the serial monitor
const int BAUD_RATE = 9600;
 

/******************************/

/******Variables**************/
typedef struct USER{
  String fname;
  String lname;
  String account_number;
  String id;
  String balance;
  String last_update_time;
  String password;
} USER;


typedef struct TRANSACTION{
  USER *User;
  String amount;
  String transactionID;
  String transaction_time;
  
} TRANSACTION;

 USER user;
 TRANSACTION transaction;
 bool trans_status = false;
/*******************************/

/******Function Prototypes*******/
void DisplayFinito();
void DisplayEnterPassword();
void DisplayUserDetails(USER *);
String GenerateTransanctionToken(TRANSACTION * transaction);
void DisplayTransactionDone(TRANSACTION * transaction);
void DisplayBalance(TRANSACTION * transaction);
void DisplayConnectingToPayer();

void MakePayment();
void ReceivePayment();




void setup(){

  user.fname= "Opeyemi";
  user.lname= "Oloruntegbe";
  user.account_number = "024435439";
  user.id = "343";
  user.balance = "500,000.00";
  user.last_update_time = "4343554";
  user.password = "****";

  transaction.User = &user;
  transaction.amount = "3,435,343.78";
  transaction.transactionID = "423";
  transaction.transaction_time = "4534";

  Serial.begin(BAUD_RATE);
  Serial.println("(setup)...Starting ...");
 
  DisplayEnterPassword(&user);
  delay(1500);
  while( user.password != user.password);
  DisplayFinito();
  delay(1500);

  GenerateTransanctionToken(&transaction);
  MakePayment(&transaction);//Testing

}

void loop(){
  //
}

/****************************************/


void DisplayFinito(){
  display.init();
  display.setFont(ArialMT_Plain_24);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.drawString(64, 20, "Finito");
  display.display();
  display.clear();
}

void DisplayEnterPassword(USER *user){
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(10, 10, "Enter PIN:\n" + user->password );
  display.display();
  display.clear();
  
}

void DisplayUserDetails(USER *user){
  //Fetch stored user details
  //display it on the screen
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(10, 3, user->fname + "\n" + "\n" + user->lname + "\n" + user->account_number ); //Opeyemi \n 02344485"
  display.display();
  display.clear();
}

String GenerateTransanctionToken(TRANSACTION *transaction){
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<300> doc;
  doc["fname"] = transaction->User->fname;
  doc["lname"] = transaction->User->lname;
  doc["account number"] = transaction->User->account_number;
  doc["user id"] = transaction->User->id;
  doc["amount"] = transaction->amount;
  doc["balance"] = transaction->User->balance;
  doc["time"] = transaction->transaction_time;
  doc["password"] = transaction->User->password;

  
  String output;
  
  serializeJson(doc, output);
  Serial.println(output);
  trans_status = true;
  
  return output; 
}

void DisplayTransactionDone(TRANSACTION * transaction, int type){
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  if(type){
    display.drawString(10, 3, transaction->amount + "\nreceived from\n" +  transaction->User->lname ); //Opeyemi \n 02344485"
  } else {
    display.drawString(10, 3, transaction->amount + "\nsent to\n" +  transaction->User->lname ); //Opeyemi \n 02344485"
  }
  
  display.display();
  display.clear();
  trans_status = false;
}

void DisplayBalance(TRANSACTION * transaction){
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(8, 3, "You have \nNGN" +  transaction->User->balance + "\nLeft" ); //Opeyemi \n 02344485"
  display.display();
  display.clear();
}

void DisplayConnectingToPayer(){
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(8, 3, "Connecting \nto\nPayer... " ); //Opeyemi \n 02344485"
  display.display();
  display.clear();
}


/******************************************************************/


// void MakePayment(TRANSACTION *trans){

//   // Set your access point network credentials
//   const char * ssid = "Opeyemi";
//   const char * password = "peaceunity";

//   WiFi.softAP(ssid, password);//sets up ssid and password for board
//   IPAddress IP = WiFi.softAPIP();
//   Serial.print("AP IP address: ");
//   Serial.println(IP);


//   server.on("/getTransactionToken", HTTP_GET, [](AsyncWebServerRequest *request){
//     request->send(200, "text/plain", sendToken );
//   });
    
//   server.begin(); //Start Server

//  // while(1){
//     DisplayUserDetails(trans->User);
//     if (trans_status){
//     DisplayTransactionDone(trans, SEND);
//     }
//     DisplayBalance(trans);

//     if(CHANGE_TRANSACTION_TYPE) return;
//  // }

// }



/******************************************************************/

void ReceivePayment(const char* serverName, TRANSACTION * transaction){

  const char* serverNameGetTransactionToken = "http://192.168.4.1/getTransactionToken";
 
  String transactionToken;
  HTTPClient http;
  
  
  

/***********CONNECT TO PAYER**********/
    // Set your access point network credentials
    const char * ssid = "Galaxy";
    const char * password = "hereNator";
  
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED){
      DisplayConnectingToPayer();
    }; //waits till connection is done
    if(WiFi.status() != WL_CONNECTED){
     transactionToken = httpGETRequest(serverNameGetTransactionToken); 
    }
    Serial.println(transactionToken);


    /*******SETTING UP HTTP SERVER***********/
  
    // Your IP address with path or Domain name with URL path 
    http.begin(serverName);
    
    // Send HTTP POST request
    int httpResponseCode = http.GET();
    
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      transactionToken = http.getString();
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();

 

  while(1){
  DisplayUserDetails(transaction->User);
  if (trans_status){
  DisplayTransactionDone(transaction, RECEIVE);
  }
  DisplayBalance(transaction);

  if(CHANGE_TRANSACTION_TYPE) return; 
  }
}
