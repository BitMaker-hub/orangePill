#include <Arduino.h>
#include "btc.h"
#include "Bitcoin.h"
#include "GlobalVARS.h"
#include "workflow.h"

extern sPILL myPill;

String password="";

/**************💊 INIT WALLET *******************/
void initWallet(void){

  if(myPill.mnemonic.length() > 0){
    HDPrivateKey hd(myPill.mnemonic, password);
    HDPrivateKey account = hd.derive("m/84'/0'/0'/");
    
    myPill.xpub= account.xpub();
  }

}

void createSeed(void){

  // entropy bytes to mnemonic
  uint8_t arr[512] = {0};
  random_buffer(arr, 512);
  String mn = generateMnemonic(arr, sizeof(arr));
  Serial.println(mn);

  // Extract xpub from primary address
  HDPrivateKey hd(mn, password);
  HDPrivateKey account = hd.derive("m/84'/0'/0'/");
    
  myPill.xpub= account.xpub();
  myPill.mnemonic = mn;
}


