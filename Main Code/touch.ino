#include "touch.h"

void TOUCH::convertCoord(int *x, int *y){
  int Y1 = 750, Y2 = 35;  
  int X1 = -2350, X2 = 600; 
  *y=(Y1-*y)/(715/72); 
  (*x-=X1)/=12.3;    
}

void TOUCH::touch(){
    point = ts.getPoint();
    if (point.z >= minPress && point.z <= maxPress) {
      Point.X = point.y, Point.Y = point.x;
      convertCoord(&Point.X, &Point.Y);
    }
    else
      Point.X = -1, Point.Y = -1;
}

int TOUCH::getButton(){
    if(Point.X < 48 && Point.X > 0)
         button = 1;
    else if(Point.X < 96 && Point.X > 48)
         button = 2;
    else if(Point.X < 144 && Point.X > 96)
         button = 0;
    else if(Point.X < 192 && Point.X > 144)
         button = 3;
    else if(Point.X < 240 && Point.X > 192)
         button = 4;
    else 
          button = -1;
    return button;
}
