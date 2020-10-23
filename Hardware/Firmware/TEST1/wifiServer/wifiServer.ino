
// Import required libraries
#include "Wire.h"
#include "SSD1306.h"  //For display
#include <ArduinoJson.h> //For Handling Json objects

#include "WiFi.h"
#include "ESPAsyncWebServer.h"


// Set your access point network credentials
const char* ssid = "Opeyemi";
const char* password = "peaceunity";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String transactionToken = "---";
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

/******************************/
USER user;
TRANSACTION transaction;
/*******************************/

String GenerateTransanctionToken(TRANSACTION *transaction);
void DisplayTransactionDone(TRANSACTION * transaction);
void DisplayUserDetails(USER *user);


void setup(){

  user.fname= "Opeyemi";
  user.lname= "Oloruntegbe";
  user.account_number = "024435439";
  user.id = "34";
  user.balance = "500,000.00";
  user.last_update_time = "43:43:554";
  user.password = "****";

  transaction.User = &user;
  transaction.amount = "3,343.78";
  transaction.transactionID = "423";
  transaction.transaction_time = "45:53:523";


  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  display.init();

  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  //Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/getTransactionToken", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", transactionToken );
    DisplayTransactionDone(&transaction);
  });
  
  
  bool status;
  // Start server
  server.begin();
}
 
void loop(){
  void DisplayUserDetails(&Transaction->User);
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

void DisplayTransactionDone(TRANSACTION * transaction){
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(10, 3, transaction->amount + "\nsent to\n" +  transaction->User->lname ); //Opeyemi \n 02344485"
  display.display();
}

void DisplayUserDetails(USER *user){
  //Fetch stored user details
  //display it on the screen
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(10, 3, user->fname + "\n" + "\n" + user->lname + "\n" + user->account_number ); //Opeyemi \n 02344485"
  display.display();
}