#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> //For Handling Json diles

  
const char* ssid = "Opeyemi";
const char* password =  "peaceunity";

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


String GenerateTransanctionToken(TRANSACTION *transaction){
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<300> doc;
  doc["fname"] = transaction->User->fname;
  doc["lname"] = transaction->User->lname;
  doc["accountNumber"] = transaction->User->account_number;
  doc["userID"] = transaction->User->id;
  doc["amount"] = transaction->amount;
  doc["balance"] = transaction->User->balance;
  doc["time"] = transaction->transaction_time;
  doc["password"] = transaction->User->password;

  
  String output;
  
  serializeJson(doc, output);
 // Serial.println(output);
  
  return output; 
}

  
void setup() { 

  user.fname= "Opeyemi";
  user.lname= "Oloruntegbe";
  user.account_number = "024435439";
  user.id = "1";
  user.last_update_time = "43:43:554";
  user.password = "****";

  transaction.User = &user;
  transaction.amount = "350000";
  transaction.transactionID = "1";
  transaction.transaction_time = "45:53:523";

  
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
  
   String postData = String(GenerateTransanctionToken(&transaction));
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
