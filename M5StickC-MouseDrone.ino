#include <M5StickC.h>
#include <BleMouse.h>

BleMouse bleMouse("Standard Mouse");

const int button = 37;

int interval_max = 32000;
int interval = interval_max;
int btnState = 0;

void setup() {
  M5.begin();
  
  M5.Axp.ScreenBreath(9);
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(2);

  pinMode(M5_LED, OUTPUT);
  pinMode(button, INPUT);
  attachInterrupt(button,pressed,FALLING);
  btnState=0; 
  bleMouse.begin();
  delay(5000);

}

void pressed() {
  if (btnState==0) {
    btnState=1;
  } else {
    btnState=0;
  }

  interval = interval_max;

}
 
void loop() {
  if (btnState==0) {
    interval++;
    M5.Lcd.fillRect(0, 60, interval / 200, 8, ORANGE);
  }
  
  if ( interval >= interval_max ) { 
  
    interval=0;
    
    if (bleMouse.isConnected()) {
    
      M5.Lcd.fillScreen(BLACK); 
      
      M5.Lcd.setTextColor(CYAN, DARKCYAN);
      M5.Lcd.setCursor(2, 20);
      M5.Lcd.println("BT CONNECTED.");
      
      if (btnState==0) {
        M5.Lcd.setTextColor(CYAN, DARKCYAN);
        M5.Lcd.setCursor(2, 40);
        M5.Lcd.println("RUNNING.");
        
        digitalWrite(M5_LED, LOW);
        bleMouse.move(1, 1);
        delay(10);
        digitalWrite(M5_LED, HIGH);
        bleMouse.move(-1, -1);
        
      } else {
        M5.Lcd.setTextColor(RED, MAROON);
        M5.Lcd.setCursor(2, 40);
        M5.Lcd.println("STOPPED.");
      }
      
    } else {
      M5.Lcd.setTextColor(RED, MAROON);
      M5.Lcd.setCursor(2, 20);
      M5.Lcd.println("DISCONNECTED.");
    }
    
  }
   
   delay(1);
   
}
