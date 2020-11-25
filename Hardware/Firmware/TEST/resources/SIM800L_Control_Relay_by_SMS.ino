#include "Adafruit_FONA.h"
#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

char replybuffer[255];

#include <SoftwareSerial.h>
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

#define RELAY_PIN 9
#define BUTTON_PIN 8

short sButton_Read = 0;
String smsString = "";
unsigned short gusIsSend_Bef = 0;

void setup() 
{
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  
  pinMode(BUTTON_PIN, INPUT);

  Serial.begin(115200);
  Serial.println(F("FONA SMS caller ID test"));
  Serial.println(F("Initializing....(May take 3 seconds)"));

  // make it slow so its easy to read!
  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial))
  {
    Serial.println(F("Couldn't find FONA"));
    while(1);
  }
  Serial.println(F("FONA is OK"));

  // Print SIM card IMEI number.
  char imei[16] = {0}; // MUST use a 16 character buffer for IMEI!
  uint8_t imeiLen = fona.getIMEI(imei);
  if (imeiLen > 0) 
  {
    Serial.print("SIM card IMEI: "); Serial.println(imei);
  }
  
  fonaSerial->print("AT+CNMI=2,1\r\n");  //set up the FONA to send a +CMTI notification when an SMS is received
  Serial.println("FONA Ready");
}

char fonaNotificationBuffer[64];          //for notifications from the FONA
char smsBuffer[250];

void loop() 
{
  char number, message;
  
  char* bufPtr = fonaNotificationBuffer;    //handy buffer pointer
  
  sButton_Read = sRead_Button();

  if(sButton_Read == 1)
  {
    if(gusIsSend_Bef == 0)
    {
      if(!fona.sendSMS("+601111721576", "Button is pressed!"))
      {
        Serial.println(F("Failed"));
      } 
      else 
      {
        Serial.println(F("Sent!"));
      }
      gusIsSend_Bef = 1;
    }
  }
  else
  {
    gusIsSend_Bef = 0;
  }
  
  if (fona.available())      //any data available from the FONA?
  {
    int slot = 0;            //this will be the slot number of the SMS
    int charCount = 0;
    //Read the notification into fonaInBuffer
    do
    {
      *bufPtr = fona.read();
      Serial.write(*bufPtr);
      delay(1);
    } while ((*bufPtr++ != '\n') && (fona.available()) && (++charCount < (sizeof(fonaNotificationBuffer)-1)));

    //Add a terminal NULL to the notification string
    *bufPtr = 0;

    //Scan the notification string for an SMS received notification.
    //  If it's an SMS message, we'll get the slot number in 'slot'
      if (1 == sscanf(fonaNotificationBuffer, "+CMTI: " FONA_PREF_SMS_STORAGE ",%d", &slot)) 
      {
        Serial.print("slot: "); Serial.println(slot);

        char callerIDbuffer[32];  //we'll store the SMS sender number in here

        // Retrieve SMS sender address/phone number.
          if (! fona.getSMSSender(slot, callerIDbuffer, 31)) 
          {
            Serial.println("Didn't find SMS message in slot!");
          }
          Serial.print(F("FROM: ")); Serial.println(callerIDbuffer);

          // Retrieve SMS value.
          uint16_t smslen;
            if (fona.readSMS(slot, smsBuffer, 250, &smslen)) // pass in buffer and max len!
            { 
              smsString = String(smsBuffer);
              Serial.println(smsString);
            }
              if (smsString == "RELAY_ON")
              {
                Serial.println("Relay is activated.");
                digitalWrite(RELAY_PIN, LOW);
                delay(100);

                if(!fona.sendSMS(callerIDbuffer,"Relay is activated." ))
                {
                  Serial.println(F("Failed"));
                } 
                else 
                {
                  Serial.println(F("Sent!"));
                }
              }
              else if(smsString == "RELAY_OFF")
              {
                Serial.println("Relay is deactivated.");
                digitalWrite(RELAY_PIN, HIGH);
                delay(100);

                if(!fona.sendSMS(callerIDbuffer, "Relay is deactivated."))
                {
                  Serial.println(F("Failed"));
                }
                else
                {
                  Serial.println(F("Sent!"));
                }
              }
               
              while(1)
              {
                if(fona.deleteSMS(slot))
                {
                  Serial.println(F("OK!"));
                  break;
                }
                else
                {
                  Serial.print(F("Couldn't delete SMS in slot ")); Serial.println(slot);
                  fona.print(F("AT+CMGD=?\r\n"));
                }
              }
            }  
          }
}

short sRead_Button()
{
  short sButton_Value = 0;
  sButton_Value = digitalRead(BUTTON_PIN);
  return sButton_Value;
}
