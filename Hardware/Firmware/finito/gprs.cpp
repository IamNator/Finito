//#include <SPI.h> // SPI communication library
//#define TINY_GSM_MODEM_SIM800 // definition of the modem used (SIM800L)
//#include <TinyGsmClient.h> // library with GSM commands
//
//
//
//
//SIM800L serial communication object
//HardwareSerial SerialGSM(1);
//library object with GSM functions
//TinyGsm modemGSM(SerialGSM);
//
//
//RX / TX where the SIM800L will be connected
//#define RX_PIN 15
//#define TX_PIN 13
//
//*****Configuration for gprs connection******/
// Access point name airtel
//const char * APN = "gloflat";
// User, if it doesn't exist, leave it empty
//const char * USER = "flat";
// Password, if it doesn't exist, leave it empty
//const char * PASSWORD = "flat";
//
//void setupGSM();
//String sendAT(String);
//
//
//void setup(){
//setupGSM();
// 
//}
//
//
////Send AT command and wait until a response is obtained 
//String sendAT(String command)
//{
//  String response = "";
//  SerialGSM.println (command);
//  // we wait until there is a response from the SIM800L
//  while (! SerialGSM.available ());
// 
//  response = SerialGSM.readString ();
// 
//  return response;
//}
//
//SerialGSM.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN, false);
//  delay(1000);
