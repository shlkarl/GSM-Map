#include "keys.h"

KEY::KEY(){
  pinMode(36, INPUT);
  pinMode(39, INPUT);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
}


void KEY::state(int key){
  int tmp = 0;
  while(analogRead(key) > 4050){
    delay(1);
    tmp++;
    }
  
    if(tmp > 40 && tmp <= 600){
      pressed = true;
      held = false;}
    else if(tmp > 600){
      pressed = false;
      held = true;}
    else{ 
      pressed = false;
      held = false;}
}

void KEY::check(){
  if(analogRead(ONE) > 4050){
    key = ONE;
    state(key);}
  else if(analogRead(TWO) > 4050){
    key = TWO;
    state(key);}
  else if(analogRead(FREE) > 4050){
    key = FREE;
    state(key);}
  else if(analogRead(FOUR) > 4050){
    key = FOUR;
    state(key);}
  else{
    pressed = false;
      held = false;}
  }

bool KEY::getPressed(){
  return pressed;
}
bool KEY::getHeld(){
  return held;
}
int KEY::getKey(){
  return key;
}
