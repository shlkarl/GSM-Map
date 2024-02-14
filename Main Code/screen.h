#pragma once
#include <TFT_eSPI.h>
#include "SPI.h"

  
  int X = 0, Y = 0, oldX, oldY;
  
class SCREEN{
  int sizeLen = 319, sizeWeight = 239;
  int y = 40;
  bool load = true;
  TFT_eSPI tft = TFT_eSPI();
 public:
  SCREEN(bool type, int scale, int part);
  void setImg();
  void setCoord();
  void dropCoord();
  void setGuide();
  void dropGuide();
  void setButtons();
  void dropButtons();
  void active();
  void drawResponse(char* res) ;
  void change(bool tmp);
  void loading();
};
