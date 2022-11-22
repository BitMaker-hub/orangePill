#include <Arduino.h>
#include <EEPROM.h>
#include "hidkeyboard.h"
#include "gpio.h"
#include "btc.h"
#include "GlobalVARS.h"
#include "workflow.h"

HIDkeyboard Keyboard;
extern sPILL myPill;

/**************💊 USB KEYBOARD INIT **********/
void initUSBKeyboard(){
  Keyboard.begin();                  // Init USB as keyboard
}

/**************💊 WORKSATES *********************
  💊💊💊💊💊💊💊💊💊💊💊💊💊💊💊💊💊💊💊💊💊💊💊💊💊💊
 ***********************************************/

/**************💊 SET NEWSTATE *******************/
void saveNewState(uint8_t newState){
  EEPROM.write(0, newState);
  EEPROM.commit();
  myPill.State = newState;
}

/**************💊 VIRGIN STATE *****************/
void doVirginState(int keyState){
  
  setLedsColor(COLOR_GREEN, COLOR_NONE, COLOR_NONE);
  
  switch(keyState){
    case SingleClick: Serial.print(Keyboard.sendString(VIRGIN_SINGLECLICK_M)?"OK":"FAIL");
                      break;
    case DoubleClick: Serial.print(Keyboard.sendString(VIRGIN_DOUBLECLICK_M)?"OK":"FAIL");
                      break;
    case LongClick:   myPill.State = STATE_SEEDING;
                      Keyboard.sendString("SHAKE the pill to generate a seed!\n");
                      blinkAllLeds(COLOR_GREEN);
                      break;
  }
}

/**************💊 SEEDING STATE *****************/
void doSeedingState(int keyState){
  
  //ReadAccelerometer
  AccelerometerRead();

  if(doShakeEffect(COLOR_GREEN)){
    blinkAllLeds(COLOR_GREEN);
    saveNewState(STATE_LOCKED);
    createSeed();
    saveMnemonic(myPill.mnemonic);
    showInitEffect();
  }
}

/**************💊 LOCKED STATE *****************/
void doLockedState(int keyState){
  
  setLedsColor(COLOR_NONE, COLOR_BLUE, COLOR_NONE);
  
  switch(keyState){
    case SingleClick: Serial.print(Keyboard.sendString(LOCKED_SINGLECLICK_M)?"OK":"FAIL");
                      break;
    case DoubleClick: Serial.print(Keyboard.sendString(LOCKED_DOUBLECLICK_M)?"OK":"FAIL");
                      break;
    case LongClick:   myPill.State = STATE_OPENPILL;
                      Keyboard.sendString("SHAKE the pill to open it and see the seed!\n");
                      blinkAllLeds(COLOR_BLUE);
                      break;
  }
}

/**************💊 OPEN PILL *****************/
void doOpenPill(int keyState){

  //ReadAccelerometer
  AccelerometerRead();
  
  if(doShakeEffect(COLOR_BLUE)){
    blinkAllLeds(COLOR_BLUE);
    saveNewState(STATE_UNLOCKED);
    showInitEffect();
  }
}
/**************💊 UNLOCKED STATE *****************/
void doUnlockedState(int keyState){
  setLedsColor(COLOR_NONE, COLOR_NONE, COLOR_RED);
  
  switch(keyState){
    case SingleClick: Serial.print(Keyboard.sendString(UNLOCKED_SINGLECLICK_M)?"OK":"FAIL");
                      break;
    case DoubleClick: Serial.print(Keyboard.sendString(UNLOCKED_DOUBLECLICK_M)?"OK":"FAIL");
                      break;
    case LongClick:   saveNewState(STATE_VIRGIN);
                      blinkAllLeds(COLOR_RED);
                      showInitEffect();
                      break;
  }
}

/************ SHAKE EFFECT ************/

bool doShakeEffect(uint32_t mainColor){
  
  static int brightness;
  static bool operand;
    
  //ReadAccelerometer
  //AccelerometerRead();

  //Led effect during seed generation
  brightness = brightness + ( operand ? 5 : -5 ) ;
  if(brightness >= 255) operand = false;
  if(brightness <= 0) operand = true;
  uint32_t color = (brightness << 16) + (brightness << 8)  + brightness; //Move color to one byte at left
  color = color & mainColor;
  
  if(myPill.shakeCounts < (SHAKE_TRIGGER_N/3)){
    setLedsColor(color, COLOR_NONE, COLOR_NONE);
  }
  else if(myPill.shakeCounts < (SHAKE_TRIGGER_N*2/3)){
    setLedsColor(mainColor, color, COLOR_NONE);
  }
  else if(myPill.shakeCounts < SHAKE_TRIGGER_N){
    setLedsColor(mainColor, mainColor, color);
  }
  else if(myPill.shakeCounts > SHAKE_TRIGGER_N){
    myPill.shakeCounts = 0;
    return true;
  } 

  return false;
}


