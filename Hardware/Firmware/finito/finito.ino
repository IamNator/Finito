#include "SSD1306.h"

SSD1306 display(0x3C, 5, 4);

void setup(){
  display.init();
  display.setFont(ArialMT_Plain_24);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 20, "Finito");

  display.display();
}

void loop(){

   display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 20, "Finito");

  display.display();
  delay(5000);
  //
}
