//SoftwareSerial mySerial(3, 2);
#include "Wire.h"
#include "SSD1306.h"  //For display

SSD1306 display(0x3C, 5, 4); // display(I2C Address, SDA_Pin, SCL_Pin)

void DisplayResponse(String strings){
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(16, 8, "here" + strings );
  display.display();
}

void setup()
{

  char *c = "";
  display.init();
   Serial.begin(9600);
  delay(1000);
  Serial.println("AT");
  while(Serial.available()){
    c += Serial.read();
  }
  delay(1000);
  DisplayResponse(String(c));
  delay(500);
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.println("AT+CMGS=\"+2349045057268\"\r");
  delay(500);
  Serial.print("Hello World from Dev Craze!");
  delay(500);
  Serial.write(26);
}
 
void loop()
{
  while(Serial.available()){
    Serial.println(char(Serial.read()));
  }
}