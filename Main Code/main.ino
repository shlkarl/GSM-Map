#include "keys.h"
#include "screen.h"
#include "touch.h"
#include "sdcard.h"
#include "SIM800.h"

  bool type = 1, back = false, tmp, end = false;
  int scale = 0, part = 0;
  float LON[10] = {0}, LAT[10] = {0};
  float oldLON[10] = {0}, oldLAT[10] = {0};
  int lvl[10]={0};
  int size;
  
  TOUCH Touch;
  SDCARD SDcard;
  KEY Key;
  SIM800 Sim;
  
void setup() {
  Serial.begin(115200);
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
                        type = 1, scale = 0, part = 0, X = 0, Y = 0, back = false; end = false;
                        SCREEN Screen(type,scale,part);break;}
               } 
            }  
            else if(Key.getKey() == FOUR && Key.getPressed() && back){
            type = 1, tmp = true; end = false;
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
