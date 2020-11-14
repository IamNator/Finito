
#include "Wire.h"
#include "SSD1306.h"  //For onboard display

#include <WiFi.h>
#include <HTTPClient.h>  //onboard oled screen

#include <ArduinoJson.h> 


const char* ssid = "Opeyemi";
const char* password = "peaceunity";

String fname = "Nator";
String lname = "Paul";

//Your IP address or domain name with URL path
const char* getTransactionToken  = "http://192.168.4.1/getTransactionToken";
SSD1306 display(0x3C, 5, 4); // display(I2C Address, SDA_Pin, SCL_Pin)


/*********Function Prototypes**************************/

String httpGETRequest(const char* serverName);

/****************Time***********************/
unsigned long previousMillis = 0;
const long interval = 5000;
int transactionTokenNotSent = 1;
String transactionToken;




String httpGETRequest(const char* serverName) {

  HTTPClient http;
  
  // Your IP address with path or Domain name with URL path 
  http.begin(serverName);

  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}


void DisplayUserDetails(){
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  String accountNumber = "50000000";
  display.drawString(16, 8, fname + " \n" + accountNumber );
  display.display();
}

void DisplayReadyToReceive(){
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(16, 8, "Ready \nTo \nReceive" );
  display.display();
}

void DisplayTransactionReceived(String *transactionToken){
    StaticJsonDocument<700> doc;
    DeserializationError error = deserializeJson(doc, *transactionToken);
    //Test if parsing succeeds.
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    // Most of the time, you can rely on the implicit casts.
    // In other case, you can do doc["time"].as<long>();
    String Amount = doc["amount"];
    String  fname = doc["fname"];
    String lname = doc["lname"];

    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.setColor(WHITE);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    //transactionToken
    display.drawString(16, 8, Amount + " received \nfrom "+fname +" " + lname );
    display.display();
}

void DisplayPressOneToContinue(){
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.setColor(WHITE);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(16, 8, "Press one \nTo \nContinue" );
    display.display();
}

void DisplayFinito(){
    display.clear();
    display.setFont(ArialMT_Plain_24);
    display.setColor(WHITE);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    //transactionToken
    display.drawString(16, 8, "Finito" );
    display.display();
}



void setup() {

  Serial.begin(115200); //For debuging through Serial monitor
  display.init();

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  
  while(WiFi.status() != WL_CONNECTED) { 
    DisplayConnecting();
    delay(500);
    Serial.println("Connecting...");
    DisplayUserDetails();
  }
  
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  DisplayReadyToReceive();
  
}

void loop() {

  unsigned long currentMillis = millis();
  
  
  if(currentMillis - previousMillis >= interval) {
     // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED ){ 
      if (transactionTokenNotSent){
          transactionToken = httpGETRequest(getTransactionToken);
          Serial.println(transactionToken);
          transactionTokenNotSent = 0;
      }

       //DisplayTransactionDone(&transactionToken);
       DisplayConnected(String(WiFi.localIP()));
       previousMillis = currentMillis;
    }
    else {
      Serial.println("Wifi Disconnected");
      DisplayDiscounted();
      }
    }
  
}
