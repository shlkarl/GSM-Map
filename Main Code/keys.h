#pragma once 


//keyboard
#define ONE 34  
#define TWO 35 
#define FREE 36   
#define FOUR 39


class KEY{
  int key;
  bool pressed = false;
  bool held = false;
  void state(int key);
  public:
  KEY();
  void check();
  bool getHeld();
  bool getPressed();
  int getKey();
};
