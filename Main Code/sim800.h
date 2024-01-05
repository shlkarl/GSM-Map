#pragma once ////WTF???
class SIM800{
   String req = "";
   char buf[128] ={0};
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
