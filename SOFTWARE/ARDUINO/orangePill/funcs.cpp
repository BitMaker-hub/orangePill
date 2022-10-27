#include <Arduino.h>
#include "GlobalVARS.h"
#include "funcs.h"


/************** VARS *************************************************/




/********************************************************************/
bool isValidNumber(String str){
   bool idDigit = true;
   for(byte i=0;i<str.length();i++)
   {
      if(!isDigit(str.charAt(i))) idDigit = false;
   }
   return idDigit;
} 

/*******************************************************************
 * PRINT DATA DEBUG FUNCS
 * 
 *******************************************************************/
void SerialPrintHex ( byte Data ) 
{
  //Serial.print(' ');
  if (Data < 0x10) Serial.print('0');
  Serial.print(Data, HEX);  
}
void SerialPrintArray (byte Source[], byte LEN)
{
  for (int Idx = 0; Idx < LEN; Idx++)  SerialPrintHex (Source[Idx]);
}
void printExact(String s, uint8_t nChars){
  uint8_t rest=0;
  if(s.length()<nChars) rest= nChars - s.length();
  Serial.print(s);
  for(int i=0;i<rest;i++) Serial.print(" ");
  Serial.print(" | "); 
}
void printClientsTable(void){
  /*Serial.println("-------------------------------------------------------------------------------");
    Serial.print("  Total Clients: "); Serial.println(BLEClients.total); 
  Serial.println("| idx |  idUser  | AWS | cmd | typ | Cfg(s) | Ret(s) | Timeout | eKey");
  for(int i=0;i<MAX_CLIENTS; i++){
    Serial.print("| ");printExact(String(i),3);
    printExact(String(BLEClients.cli[i].id),8);
    printExact(String(BLEClients.cli[i].isPendingAWS),3);
    printExact(String(BLEClients.cli[i].lastCmd),3);
    printExact(String(BLEClients.cli[i].accessType),3);
    printExact(String(BLEClients.cli[i].CfgSession),6);
    printExact(String(BLEClients.cli[i].retainTime),6);
    printExact(String(BLEClients.cli[i].timeoutAWS),7);Serial.print("0x");
    SerialPrintArray(BLEClients.cli[i].eKey,16);
    Serial.println();
  }
  Serial.println("-------------------------------------------------------------------------------");
  Serial.flush();*/
}


