/*
 * Functions
 *  Created on: 08/04/2020
 *      Author: Roger Colet
 */
#include <Arduino.h>
#include "GlobalVARS.h"
#include "funcs.h"


/************** VARS *************************************************/
extern sPILL OrangePill;



/********************************************************************/
bool isValidNumber(String str){
   bool idDigit = true;
   for(byte i=0;i<str.length();i++)
   {
      if(!isDigit(str.charAt(i))) idDigit = false;
   }
   return idDigit;
} 

/********************************************************************
* Usefool BLE data characteristics functions section
* getCharParams:     -> Devuelve los parámetros leídos de una característica
*                       que ha sido modificada. Sólo los computa si siguen nuestra 
*                       estructura: STX PARAM1 , PARAM2 , PARAM3 ETX               
* publishRandomKey   -> Graba una nueva clave en la característica de claves
* setBLETXPowerLevel -> Setea la poténcia de transmisión del módulo BLE
* decryptBLEchar     -> Desencripta el valor de una característica y lo imprime en pantalla
*********************************************************************/
bool getCharParams(std::string rxValue, String &allData, String &param1, String &param2, String &param3, String &param4){
  bool isSTX, isETX=false;
  uint8_t x=0;  

  isSTX = rxValue[0]==STX;
  
  allData+=rxValue[0];
  for (int i = 1; i < rxValue.length(); i++) {
    allData+=rxValue[i]; 
    if(isSTX&&(rxValue[i]!=SEP)&&(rxValue[i]!=ETX)){
      if(x==0) param1+=rxValue[i];
      if(x==1) param2+=rxValue[i];
      if(x==2) param3+=rxValue[i];
      if(x==3) param4+=rxValue[i];
    }
    if(rxValue[i]==SEP) x++;
    else if(rxValue[i]==ETX) { isETX=true; break;} 
  }
  if(isSTX&&isETX) return true;
  else return false;
}
/********************************************************************/
void publishNewRandomKey(void){
  uint8_t key[16], i;
  
  for(i=0; i<16; i++) key[i]= random(0xFF);

  uint8_t x = getNewClient();
  
  /* --- STORE NEXT ENCRIPTION KEY --- */
  for(i=0; i<4; i++) {
    BLEClients.cli[x].eKey[i]=STATIC_KEY1[i];
    BLEClients.cli[x].eKey[i+4]=key[i+4];
    BLEClients.cli[x].eKey[i+8]=STATIC_KEY2[i];
    BLEClients.cli[x].eKey[i+12]=key[i+12];
  }
  Serial.print(">> Current eKEY: "); SerialPrintArray(BLEClients.cli[x].eKey,16); Serial.println();
  BLEChar_comm -> setValue(key, 16);
}
/********************************************************************/

/*************************************************************/
std::string decryptBLEchar(std::string rxValue, String strLog){
  uint8_t rxData[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  return rxData;
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


