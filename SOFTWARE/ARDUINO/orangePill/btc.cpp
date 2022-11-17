#include <Arduino.h>
#include <btc.h>
#include "Bitcoin.h"
#include "GlobalVARS.h"
#include "workflow.h"

extern sPILL myPill;

string myWallet="arch volcano urge cradle turn labor skin secret squeeze denial jacket vintage fix glad lemon";
string password="";

/**************💊 INIT WALLET *******************/
void initWallet(void){

  HDPrivateKey hd(mnemonic, password);
  HDPrivateKey account = hd.derive("m/84'/0'/0'/");
  
  myPill.xpub= account.xpub();
  myPill.mnemonic = myWallet;
}



