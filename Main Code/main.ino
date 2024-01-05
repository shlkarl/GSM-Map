#include "keys.h"
#include "screen.h"
#include "touch.h"
#include "sdcard.h"
#include "SIM800.h"




  bool type = 1, back = false, tmp;
  int scale = 0, part = 0;
  float LON[10], LAT[10];
  int lvl[20]={0};
  int size;

  
  TOUCH Touch;
  SDCARD SDcard;
  KEY Key;
  SIM800 Sim;
  
/*void TaskTouch(void *pvParameters){  // This is a task.
  (void) pvParameters;
  for (;;){ // A Task shall never return or exit.
    Screen.charge(Sim.charge());
    vTaskDelay(100);  // one tick delay (15ms) in between reads for stability
  }
}*/
void setup() {
  Serial.begin(115200);

          
 /* xTaskCreatePinnedToCore(
    TaskTouch
    ,  "TaskBlink"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL
    ,  0);*/
}


void loop() {
  SCREEN Screen(type,scale,part);
  while(1){
      Key.check();
      if(type){
          if (Key.getKey() == ONE && Key.getPressed()){
            Screen.loading();
            Sim.coord();
            Screen.loading();
            Screen.setCoord();}
          else if (Key.getKey() == ONE && Key.getHeld())
            Screen.dropCoord();
          else if (Key.getKey() == TWO && Key.getPressed())
            Screen.setGuide();
          else if (Key.getKey() == TWO && Key.getHeld())
            Screen.dropGuide(); 
          else if(Key.getKey() == FREE && Key.getPressed())
            Screen.setButtons();
          else if(Key.getKey() == FREE && Key.getHeld())
            Screen.dropButtons();
          else if(Key.getKey() == FOUR && Key.getPressed()){
            Screen.active(); type = 0;}
      }
       
      else{
         Touch.touch();
         if(Touch.getButton() == 1){
            part = 1;type = 1;
            SCREEN Screen(type,scale,part);}

         else if(Touch.getButton() == 2){ 
            part = 2;type = 1;
            SCREEN Screen(type,scale,part);}
            
         else if(Touch.getButton() == 3){
            part = 3;type = 1;
            SCREEN Screen(type,scale,part);}
            
         else if(Touch.getButton() == 4){
            part = 4;type = 1;
            SCREEN Screen(type,scale,part);}
            
         else if(Touch.getButton() == 0){
            SCREEN Screen(type,scale,part);
            while(!type){
                   Key.check();
                   if (Key.getKey() == ONE &&  Key.getPressed()){
                       Sim.select(1);Screen.change(1);} 
                       
                    else if (Key.getKey() == TWO && Key.getPressed()){
                       Sim.select(-1);Screen.change(0);} 
                       
                    else if(Key.getKey() == FREE && Key.getPressed()){
                        Sim.request();Screen.drawResponse(Sim.response());}
                        
                    else if(Key.getKey() == FOUR && Key.getHeld()){
                        type = 1, scale = 0, part = 0, X = 0, Y = 0, back = false;
                        SCREEN Screen(type,scale,part);break;}
               } 
            }  
            else if(Key.getKey() == FOUR && Key.getPressed() && back){
            type = 1, tmp = true;
            SCREEN Screen(type,scale,part);
            tmp = false;
            }
            
            else if(Key.getKey() == FOUR && Key.getHeld())
            ESP.restart();
      }
       /* while (Serial.available())
              Serial2.write(Serial.read());
          while (Serial2.available()) 
              Serial.write(Serial2.read());*/
  }
}
