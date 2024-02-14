#pragma once ////WTF???
#include "TouchScreen.h"

//touchscreen
#define YP 15  
#define XM 33 
#define YM 12   
#define XP 13  

  struct POINT{
        int X = -1, Y = -1;
    };
    
class TOUCH{
  TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);//300 Om - betwen X+ and X- 
  TSPoint point;
  int minPress = 11, maxPress = 500;
  int button;
  bool held;
  POINT Point;
public:
  void convertCoord(int *x, int *y);
  void touch();
  POINT getCoord();
  int getButton() ;
};
