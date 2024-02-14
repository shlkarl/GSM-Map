#include "sim800.h"


SIM800::SIM800() {
   Serial2.begin(9600, SERIAL_8N1, 16, 17);
}

char* SIM800::response() {
  Serial2.flush();
       while(Serial2.available()){
          str = Serial2.readString();
          Serial.println(str);delay(50);}
          if(tmp != 5)strcpy(buf,str.c_str());
          else{
          int size = strlen(str.c_str());
           for (int i = 0, tmp = 0, j = 0, l = 0; i < size; i++) {
             if (str[i] == ':') tmp++;
              if (tmp == 3) {
                 tmp++, i++;
                 if (str[i] == '0')
                      i++;
                  while (str[i] != ',') {
                      buf[j] = str[i];
                      j++, i++;}
                      buf[j] = str[i];
                      j++, i++;}
                  if (tmp == 5) {
                    tmp++, i++;
                    String tmp = "";
                     while (str[i] != ',') {
                      tmp+= str[i];
                       i++;}
                    lvl[l] = tmp.toInt();
                    l++;}
                  if (tmp == 7) {
                    tmp++, i++;
                     while (str[i] != ','){
                      buf[j] = str[i];
                      j++, i++;}
                      buf[j] = str[i];
                      j++, i++;}
                  if (tmp == 10) {
                    tmp++, i++;
                    while (str[i] != ',') {
                      buf[j] = str[i];
                      j++, i++;
                    }buf[j] = str[i];
                      j++, i++;
                  }
                  if (tmp == 12) {
                   buf[j] = '\n'; j++;
                    tmp = 0;
                  }
              }
          }
    
      
      Serial.println(buf);
      for(int i = 0; i < 10; i++)
        Serial.println(lvl[i]);
       return buf;
    
}
void SIM800::coord(){
  char arr[80] = {0};
  int j = 0, c = 0;
  String Lat, Lon;
        File Coords;
        Coords = SD.open("/little_list.txt", FILE_READ);
        while(Coords.available()){
              for(int i = 0; i < 80; i++){
                arr[i] = Coords.read();
                if(arr[i] == '\n')
                  break;}
              int l = 0;
              for(int i = 0, j = 0; buf[j] != 0; j++,i++){
                  if(buf[j] == '\n'){
                    if(arr[i] != '*')
                      i = -1;
                    else {
                      for(i = i+1; arr[i] != ','; i++)
                        Lat+=arr[i];
                      for(i = i+1; arr[i] != ','; i++)
                        Lon+=arr[i];
                      LON[c] = Lon.toDouble();LAT[c] = Lat.toDouble();
                      lvl[c]=lvl[l];
                      c++;
                      Lon = "";Lat = "";}
                      l++;}
                  else if(arr[i] != buf[j]){
                    i = -1;
                    l++;
                    while(buf[j] != '\n')
                      j++;}
                 }
            }
            Coords.close();
            
         for(int i = 0; i < c; i++)
          LON[i] = (LON[i]-minLon)/(maxLon-minLon)*240, LAT[i] = (LAT[i]-minLat)/(maxLat-minLat)*320;
          
          size = c;
          if(size > 1){
            float MaxLat = LAT[0], MinLat = LAT[0], MaxLon = LON[0], MinLon = LON[0];
    
            for (int i = 0; i < size; i++){
                if(MaxLat < LAT[i]) MaxLat = LAT[i];
                if(MinLat > LAT[i]) MinLat = LAT[i];
                if(MaxLon < LON[i]) MaxLon = LON[i];
                if(MinLon > LON[i]) MinLon = LON[i];}
                
            LON[size] = (MinLon + MaxLon)/2;
            LAT[size] = (MinLat + MaxLat)/2;}
        
        for(int i = 0; i < 10; i++){
        Serial.print(LON[i]*100000);
        Serial.print(',');
        Serial.println(LAT[i]*100000);}
}


void SIM800::request() {
      req = list[tmp];
      if(tmp == 5)
        Serial2.println("AT+CNETSCAN=1"); 
      Serial2.println(req);
}

void SIM800::select(int change){
       if(tmp == -1) 
           tmp+=1;
       else if(tmp == listSize) 
           tmp-=1;
       tmp += change;
} 

/*float SIM800::charge(){
  float a,b,c;
  Serial2.println("AT+CBC");
  for(int i = 0;Serial2.available();i++)
      buf[i] = Serial2.read();
  int i = 0, t = 0;
  while(t<2){
    i++;
    if(buf[i] == ',')
      t++;  
  }
  a=buf[i+1]-'0';
  b=buf[i+2]-'0';
  c=buf[i+3]-'0';
  return a+b/10+c/100;
}*/
