#pragma once ////WTF???
class SIM800{
   float maxLat = 60.05927, minLat = 59.83023, maxLon = 30.514334, minLon = 30.1662;
   String req = "";
   char buf[255] ={0};
   String str;
   int tmp = 0;
   static const int listSize = 7;
   String list[listSize] = {"AT+GMM","AT+COPS?","AT+CPAS","AT+CREG?","AT+CSQ","AT+CNETSCAN","AT+CBC"};
 public:
    SIM800() ;
    void request() ;
    char* response() ;
    void select(int change);
    //float charge();
    void coord();
};
