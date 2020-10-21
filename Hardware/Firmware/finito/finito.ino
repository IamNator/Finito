#include "Wire.h"
#include "SSD1306.h"  //For display
#include <ArduinoJson.h> //For Handling Json diles
#include "BluetoothSerial.h" //For Bluetooth

/**********Bluetooth config***********/
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
/***********************/

SSD1306 display(0x3C, 5, 4); // display(I2C Address, SDA_Pin, SCL_Pin)
BluetoothSerial SerialBT; //For onboard esp32 bluetooth


//serial speed of both the SIM800L and the serial monitor
const int BAUD_RATE = 115200;
 

/********************************/

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
  USER *USE;
  String amount;
  String transactionID;
  String transaction_time;
  
} TRANSACTION;

 USER user;
 TRANSACTION transaction;
/*******************************/

/******Function Prototypes*******/
void DisplayFinito();
bool DisplayEnterPassword();
void DisplayUserDetails(USER);
void transanctionToken(TRANSACTION);



void setup(){

  user.fname= "Opeyemi";
  user.lname= "Oloruntegbe";
  user.account_number = "024435439";
  user.id = "343";
  user.balance = 500000;
  user.last_update_time = "4343554";
  user.password = "****";

  transaction.USE = &user;
  transaction.amount = 3435343;
  transaction.transactionID = "423";
  transaction.transaction_time = "4534";


  SerialBT.begin(user.id); //Starts onbaord serial bluetooth with name user_id
    
  Serial.begin(BAUD_RATE);
  Serial.println("(setup)...Starting ...");
  // starts and configures the SIM800L
  DisplayEnterPassword(&user); 
  while( user.password != user.password);
  DisplayFinito();

}

void loop(){
//  DisplayUserDetails(user);
//  transanctionToken(&transaction);
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(1000);
}

/****************************************/
//bool EnterPassword()



void DisplayFinito(){
  display.init();
  display.setFont(ArialMT_Plain_24);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.drawString(64, 20, "Finito");
  display.display();
  delay(3500);
  display.clear();
}

bool DisplayEnterPassword(USER * user){
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(10, 10, "Enter PIN:\n" + user->password );
  display.display();
  delay(5000);
  display.clear();
  
  return true;
}

void DisplayUserDetails(USER user){
  //Fetch stored user details
  //display it on the screen
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(10, 3, user.fname + "\n" + "\n" + user.lname + "\n" + user.account_number ); //Opeyemi \n 02344485"
  display.display();
  delay(5000);
  display.clear();
}

bool initBluetooth(){
   return false;
}

void transanctionToken(TRANSACTION *transaction){
    // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<300> doc;
  doc["fname"] = transaction->USE->fname;
  doc["lname"] = transaction->USE->lname;
  doc["account name"] = transaction->USE->account_number;
  doc["user id"] = transaction->USE->id;
  doc["amount"] = transaction->amount;
  doc["balance"] = transaction->USE->balance;
  doc["time"] = transaction->transaction_time;
  doc["password"] = transaction->USE->password;
  
  serializeJson(doc, Serial);
// return true when package is sent  
}
