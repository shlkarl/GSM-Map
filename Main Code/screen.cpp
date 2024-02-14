#include "screen.h"

SCREEN::SCREEN(bool type, int scale, int part) {
  tft.init();
  if(type){
    setImg();
    setCoord();
    setButtons();
  }
   else{
      tft.fillScreen(TFT_BLACK);
      tft.setRotation(2);
      tft.setTextColor(TFT_RED);
      tft.drawString("SIM800L",108,5,2);
      tft.drawFastHLine(0, 20, sizeWeight, TFT_RED) ;
      tft.drawString("REQUST:                RESPONSE:",5,25,2);
      tft.drawRect(5,y,60,15,TFT_RED);
      tft.drawString("Check",7,40,2);
      tft.drawString("Provider",7,55,2);
      tft.drawString("State",7,70,2);
      tft.drawString("Info",7,85,2);
      tft.drawString("Signal",7,100,2);
      tft.drawString("Location",7,115,2);
      tft.drawString("Charge",7,130,2);
      tft.setRotation(0);
  } 
}
 
void SCREEN::setImg(){
     if(back && tmp && scale > 1){
          scale-=1;
          X = oldX, Y = oldY;
          back = false;}
      else if(scale >= 0 && scale < 7){
          scale+=1;
          oldX = X, oldY = Y;
          X *= 2, Y *= 2;
          if(part == 2) X += 1;
          else if(part == 3) Y += 1;
          else if(part == 4) X += 1, Y += 1;
          back = true;}
        File Pic;
        Pic = SD.open("/bmp24bit"+String(scale)+"/map"+String(scale)+ "_"+String(Y)+"_"+String(X)+".bmp", FILE_READ);
        Pic.seek(70);
        while (Pic.available()) {
          for (int i = 0; i <= sizeLen; i++){
            for (int j = 0; j <= sizeWeight ; j++){
              uint16_t color;
              uint8_t x1 = Pic.read();
              uint8_t x2 = Pic.read();
              color = (x1 << 8) | x2;
              tft.drawPixel(sizeWeight-j, i, color);}
          }
        }
        Pic.close();  
  }
  
void SCREEN::setCoord() {
      tft.setTextColor(TFT_BLACK);
      int r, col;
      switch(scale){
          case(1): r = 1;
          break;
          case(2): r = 2;
          break;
          case(3): r = 3;
          break;
          case(4): r = 4;
          break;
          case(5): r = 5;
          break;
          case(6): r = 6;
          break;
          case(7): r = 6;
          break;
      }

      for(int i = 0; i < size+1; i++){
        if(i == size) col = TFT_RED;
        else col = TFT_BLACK;

        
         if(!back){
          LON[i] = oldLON[i], LAT[i] = oldLAT[i];
          tft.drawCircle(240 - LON[i], LAT[i], r, col);}
          
          oldLON[i] = LON[i], oldLAT[i] = LAT[i]; 
          
        if(back){
          if(part == 0) tft.drawCircle(240 - LON[i], LAT[i], r, col);
           
          else if(part == 1 && !end){
           LON[i]*=2, LAT[i] = LAT[i]*2 - 320;
           tft.drawCircle(240 - LON[i], LAT[i], r, col);
           if(scale == 7 && i != size){
             end = true;
             tft.setRotation(2); 
             tft.drawString(String(lvl[i]),LON[i], 320 - LAT[i], 2);
             tft.setRotation(0);}
           }
           
          else if(part == 2 && !end){
            LON[i] = LON[i]*2-240, LAT[i] = LAT[i]*2 - 320;
            tft.drawCircle(240 - LON[i], LAT[i], r, col);
            if(scale == 7 && i != size){
              end = true;
              tft.setRotation(2);
              tft.drawString(String(lvl[i]),LON[i], 320 - LAT[i], 2);
              tft.setRotation(0);}
            }
            
          else if(part == 3 && !end){
           LON[i] *= 2, LAT[i]*=2;
           tft.drawCircle(240 - LON[i], LAT[i], r, col);
           if(scale == 7 && i != size){
             end = true;
             tft.setRotation(2); 
             tft.drawString(String(lvl[i]),LON[i], 320 - LAT[i], 2);
             tft.setRotation(0);}
          }
           
          else if(part == 4 && !end){ 
           LON[i] = LON[i]*2 - 240, LAT[i]*=2;
           tft.drawCircle(240 - LON[i], LAT[i], r, col);
           if(scale == 7 && i != size){ 
            end = true;
            tft.setRotation(2);
            tft.drawString(String(lvl[i]),LON[i], 320 - LAT[i], 2);
            tft.setRotation(0);}
          }
          if(end){
            tft.drawCircle(240 - LON[i], LAT[i], r, col);
            if(i != size){
              tft.setRotation(2);
              tft.drawString(String(lvl[i]),LON[i], 320 - LAT[i], 2);
              tft.setRotation(0);}
          }
      }
          
      }
      if(scale < 7){
      tft.drawFastVLine(sizeWeight/2, 50,sizeLen, TFT_BLACK);
      tft.drawFastHLine(0, sizeLen/2, sizeWeight, TFT_BLACK);
      tft.setRotation(2);
      tft.drawString("1  2",108,145,2);
      tft.drawString("3  4",108,165,2);
      tft.setRotation(0);}
}

void SCREEN::dropCoord(){
        File Pic;
         Pic = SD.open("/bmp24bit"+String(scale)+"/map"+String(scale)+ "_"+String(Y)+"_"+String(X)+".bmp", FILE_READ);
        Pic.seek(70);
        while (Pic.available()) {
          for (int i = 0; i <= sizeLen; i++){
            for (int j = 0; j <= sizeWeight ; j++){
              uint16_t color;
              uint8_t x1 = Pic.read();
              uint8_t x2 = Pic.read();
              color = (x1 << 8) | x2;
              tft.drawPixel(sizeWeight-j, i, color);}
          }
        }
        Pic.close();  
}

void SCREEN::setGuide(){
  tft.setRotation(2);
  tft.setTextColor(TFT_RED);
  tft.drawString("HELP:",5,5,2);
  tft.drawString("1 - LOCATION",5,20,2);
  tft.drawString("2 - HELP",5,35,2);
  tft.drawString("3 - BUTTONS",5,50,2);
  tft.drawString("4 - CHOISE",5,65,2);
  tft.setRotation(0);
}

void SCREEN::dropGuide(){
        File Pic;
        Pic = SD.open("/bmp24bit"+String(scale)+"/map"+String(scale)+ "_"+String(Y)+"_"+String(X)+".bmp", FILE_READ);
        Pic.seek(70);
          for (int i = 0; i <= sizeLen; i++){
            for (int j = 0; j <= sizeWeight ; j++){
              uint16_t color;
              uint8_t x1 = Pic.read();
              uint8_t x2 = Pic.read();
              color = (x1 << 8) | x2;
              if(i > 190 && j < 100)
              tft.drawPixel(sizeWeight-j, i, color);}
          }
        Pic.close();  
}

void SCREEN::setButtons(){
   tft.setRotation(2);
   for(int i = 5; i< 240; i+=50)
      tft.drawRect(i,285,30,30,TFT_BLUE);
   tft.setTextColor(TFT_BLUE);
   tft.drawString("  1       2",5,290,2);
   tft.fillCircle(120,300,8,TFT_BLUE);
   tft.drawString("     3      4",140,290,2);
   tft.setRotation(0);
}

void SCREEN::dropButtons(){
        File Pic;
         Pic = SD.open("/bmp24bit"+String(scale)+"/map"+String(scale)+ "_"+String(Y)+"_"+String(X)+".bmp", FILE_READ);
        Pic.seek(70);
          for (int i = 0; i <= 50; i++){
            for (int j = 0; j <= sizeWeight ; j++){
              uint16_t color;
              uint8_t x1 = Pic.read();
              uint8_t x2 = Pic.read();
              color = (x1 << 8) | x2;
              tft.drawPixel(sizeWeight-j, i, color);}
          }
        Pic.close(); 
}


void SCREEN::active(){
  tft.setRotation(2);
  tft.setTextColor(TFT_BLUE);
  tft.drawString("SELECT BUTTON:",5,240,2);
  tft.setRotation(0);
  setButtons();
}


void SCREEN::drawResponse(char* res){
  tft.setRotation(2);
  tft.fillRect(100,40,140,320,TFT_BLACK);
  tft.setTextColor(TFT_RED);
  for(int i = 0, x = 0, y = 0; i < 500; i++, x++){
    if(x == 16)y += 15, x = 0;
    else if(res[i] == '\n') y += 15, x = 0;
    tft.drawChar(res[i],100+x*8,40+y,2);}
  tft.setRotation(0);
} 

void SCREEN::change(bool tmp){
 tft.setRotation(2);
 if(tmp){
    tft.drawRect(5,y,60,15,TFT_BLACK);
    if(y < 116) y+=15;
    tft.drawRect(5,y,60,15,TFT_RED);}
 else{
    tft.drawRect(5,y,60,15,TFT_BLACK);
    if(y > 40) y-=15;
    tft.drawRect(5,y,60,15,TFT_RED);}
 tft.setRotation(0);
}

void SCREEN::loading(){
  if(scale == 1){
      if(load){
        tft.setRotation(2);
        tft.setTextColor(TFT_BLUE);
        tft.drawString("LOADING...",150,5,2);
        tft.setRotation(0);
        load = false;}
      else{
        File Pic;
        Pic = SD.open("/bmp24bit1/map1_0_0.bmp", FILE_READ);
        Pic.seek(138310);
          for (int i = 287; i <= sizeLen; i++){
            for (int j = 0; j <= sizeWeight ; j++){
              uint16_t color;
              uint8_t x1 = Pic.read();
              uint8_t x2 = Pic.read();
              color = (x1 << 8) | x2;
              if(j>130)
              tft.drawPixel(sizeWeight-j, i, color);}
          }
        Pic.close();
        load = true;}
  }
}
