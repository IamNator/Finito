
#include "Wire.h"
#include "SSD1306.h"  //For onboard display

#include <WiFi.h>
#include <HTTPClient.h>  //onboard oled screen


const char* ssid = "Opeyemi";
const char* password = "peaceunity";

//Your IP address or domain name with URL path
const char* getTransactionToken  = "http://192.168.4.1/getTransactionToken";
SSD1306 display(0x3C, 5, 4); // display(I2C Address, SDA_Pin, SCL_Pin)


/*********Function Prototypes**************************/
void DisplayConnecting();
void DisplayDiscounted();
void DisplayConnected(String ip_address);
void DisplayTransactionDone(String *transactionToken);
String httpGETRequest(const char* serverName);

/****************Time***********************/
unsigned long previousMillis = 0;
const long interval = 5000;
int transactionTokenNotSent = 1;
String transactionToken;



void setup() {

  Serial.begin(115200); //For debuging through Serial monitor
  display.init();

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  
  while(WiFi.status() != WL_CONNECTED) { 
    DisplayConnecting();
    delay(500);
    Serial.println("Connecting...");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  DisplayConnected(String(WiFi.localIP()));
  
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


void DisplayConnecting(){
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(16, 8, "Connecting..." );
  display.display();
}

void DisplayDiscounted(){
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(16, 8, "Disconnected..." );
  display.display();
}

void DisplayConnected(String ip_address){
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "Connected to \n"+ip_address );
  display.display();
}

void DisplayTransactionDone(String *transactionToken){
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  //transactionToken
  display.drawString(16, 8, "Token Received" );
  display.display();
}