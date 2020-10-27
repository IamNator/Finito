#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> //For Handling Json diles

#include "ESPAsyncWebServer.h"

#define PASSWORD 45

  
const char* ssid = "Galaxy";
const char* password =  "hereNator";

AsyncWebServer server(80);

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

//typedef struct tokenChain{
//  TOKEN * tokenTree;   //an array of tokens
//}

 USER user;
 TOKEN transactionToken;
 
 


//String GenerateTransanctionToken(TOKEN *transactionToken){
//  // Use arduinojson.org/v6/assistant to compute the capacity.
//  StaticJsonDocument<300> doc;
//  doc["fname"] = transaction->User->fname;
//  doc["lname"] = transaction->User->lname;
//  doc["accountNumber"] = transaction->User->account_number;
//  doc["userID"] = transaction->User->id;
//  doc["amount"] = transaction->amount;
//  doc["balance"] = transaction->User->balance;
//  doc["time"] = transaction->transaction_time;
//  doc["password"] = transaction->User->password;
//
//  
//  String output;
//  
//  serializeJson(doc, output);
// // Serial.println(output);
//  
//  return output; 
//}

String GenerateTransanctionToken(TOKEN *transactionToken){
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<300> doc;
  doc["userID1"] = transactionToken->userID1;
  doc["userID2"] = transactionToken->userID2;
  doc["amount"] = transactionToken->amount;
  doc["password"] = PASSWORD;

  
  String output;
  
  serializeJson(doc, output);
 // Serial.println(output);
  
  return output; 
}

void UpdateUserDetails(USER * user){
  StaticJsonDocument<200> doc;

  DeserializationError error = deserializeJson(doc, json);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  user->fname = doc["fname"];
  user->lname = doc["lname"];
  user->userID = doc["userID"];
  user->balance = doc["balance"];
}

  
void setup() { 

  user.userID = "1";
  
  transactionToken.userID1 = user.userID;
  transactionToken.userID2 = "2";
  transactionToken.amount = "24500";

  
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
  
  WiFi.begin(ssid, password); 
  
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
  
}
  
void loop() {
  
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
   HTTPClient http;   
  
   http.begin("http://finito-cloud.herokuapp.com/api/send");  //Specify destination for HTTP request
   http.addHeader("Content-Type", "application/json");             //Specify content-type header
  
   String postData = String(GenerateTransanctionToken(&transactionToken));
   Serial.println(postData);
   delay(500);
   int httpResponseCode = http.POST(postData);   //Send the actual POST request
  
   if(httpResponseCode>0){
  
    String response = http.getString();                       //Get the response to the request
  
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
  
   }else{
  
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  
   }
  
   http.end();  //Free resources
  
 }else{
  
    Serial.println("Error in WiFi connection");   
  
 }
  
  delay(10000);  //Send a request every 10 seconds
  
}
