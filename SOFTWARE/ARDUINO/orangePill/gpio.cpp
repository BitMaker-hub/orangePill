#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#include "GlobalVARS.h"
#include "gpio.h"
#include "kxtj3-1057.h"
#include "Wire.h"

// Enable Serial debbug on Serial UART to see registers wrote
#define KXTJ3_DEBUG Serial

float   sampleRate = 6.25;  // HZ - Samples per second - 0.781, 1.563, 3.125, 6.25, 12.5, 25, 50, 100, 200, 400, 800, 1600Hz
uint8_t accelRange = 2;     // Accelerometer range = 2, 4, 8, 16g

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

KXTJ3 myACC(0x0E); // Address can be 0x0E or 0x0F

extern sPILL myPill;

/***********************💊 EEPROM DATA ******************************/

void EEPROMsetup(){
  
  EEPROM.begin(EEPROM_SIZE);
  
  /********💊 READ PILL STATE ************/
  myPill.State = EEPROM.read(0);
  if(myPill.State>STATE_UNLOCKED) myPill.State = STATE_VIRGIN;
  
  /********💊 READ MNMONIC ************/
  String mnemonic="";
  if(EEPROM.read(1) == STX){
    for(uint16_t i=2; i<400; i++){
      uint8_t nm = EEPROM.read(i);
      if(nm == ETX) break;
      mnemonic = mnemonic + char(nm);
    }
  }
  myPill.mnemonic = mnemonic;
  Serial.print("Current mnemonic: "); Serial.println(mnemonic);
  
}

void saveMnemonic(String mnemonic){

  uint16_t i;
  for(i=2; i<(mnemonic.length()+2); i++){
    EEPROM.write(i, mnemonic[i-2]);
  }
  EEPROM.write(i,3);
  EEPROM.write(1,STX);
  delay(10);
  EEPROM.commit();
}

/***********************💊 LED EFFECTS ******************************/
void LedSetup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(40); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
void colorWipeBack(uint32_t color, int wait) {
  for(int i=strip.numPixels(); i>0; i--) { // For each pixel in strip...
    strip.setPixelColor(i-1, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 1*65536; firstPixelHue += 256) {
    strip.rainbow(firstPixelHue);
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

//Init efect on leds
void showInitEffect(){
                            //RED-GREEN-BLUE
  //uint32_t color = strip.Color(0,   255,   0); //Green
  //rainbow(6); 
  setLedsColor(COLOR_NONE, COLOR_NONE, COLOR_NONE);
  delay(100);

  uint32_t color = COLOR_GREEN;
  switch(myPill.State){
     case STATE_VIRGIN:  color = COLOR_GREEN; break;
     case STATE_LOCKED: color = COLOR_BLUE; break;
     case STATE_UNLOCKED: color = COLOR_RED; break;
  }
  
  colorWipe(color, 100);
  delay(100);
  colorWipe(COLOR_NONE, 100);
  colorWipeBack(color, 100);
  delay(100);
  colorWipeBack(COLOR_NONE, 100);
}

void setLedsColor(int Led1, int Led2, int Led3) {
    strip.setPixelColor(0, Led1);
    strip.setPixelColor(1, Led2);
    strip.setPixelColor(2, Led3);
    strip.show();
}

//Blink all 3 leds 
void blinkAllLeds(uint32_t color){
  for(int i=0; i<4; i++){
    strip.setPixelColor(0, color);
    strip.setPixelColor(1, color);
    strip.setPixelColor(2, color);
    strip.show();
    delay(150);
    strip.setPixelColor(0, COLOR_NONE);
    strip.setPixelColor(1, COLOR_NONE);
    strip.setPixelColor(2, COLOR_NONE);
    strip.show();
    delay(150);
  }
  delay(500);
}


/*********************💊 ACCELEROMETER *****************/
void AccSetup(){
  Wire.begin(I2C_SDA, I2C_SCL); 
  
  if( myACC.begin(sampleRate, accelRange) != 0 )
  {
    Serial.print("Failed to initialize IMU.\n");
  }
  else
  {
    Serial.print("IMU initialized.\n");
  }
  
  // Detection threshold, movement duration and polarity
  myACC.intConf(123, 1, 10, HIGH);

  uint8_t readData = 0;

  // Get the ID:
  myACC.readRegister(&readData, KXTJ3_WHO_AM_I);
  Serial.print("Who am I? 0x");
  Serial.println(readData, HEX);
}

void AccelerometerRead(){
  myACC.standby( false );

  float acc_x = myACC.axisAccel( X );
  float acc_y = myACC.axisAccel( Y );
  float acc_z = myACC.axisAccel( Z );
  /*Serial.print(acc_x);Serial.print(",");
  Serial.print(acc_y);Serial.print(",");
  Serial.println(acc_z);*/

  if(( acc_x > SHAKE_TRIGGER_H) || ( acc_x < SHAKE_TRIGGER_L) || 
     ( acc_y > SHAKE_TRIGGER_H) || ( acc_y < SHAKE_TRIGGER_L) || 
     ( acc_z > SHAKE_TRIGGER_H) || ( acc_z < SHAKE_TRIGGER_L))
    myPill.shakeCounts++;
  
  myACC.standby( true );
}

/*****************💊 BUTTON DETECTION *********************/
byte butLst;

int checkButton (void)
{
    bool   butReleased = false;
    const  unsigned long ButTimeout    = 250;
    const  unsigned long ButLongClick  = 5000;
    static unsigned long msecLst;
           unsigned long msec = millis ();

    byte but = digitalRead (BUTTON_PIN);
    if (butLst != but)  {
        butLst = but;
        delay (10);           // **** debounce

        if (LOW == but)  {   // press
            if (msecLst)  { // 2nd press
                msecLst = 0; myPill.shakeCounts = 0;
                return DoubleClick;
            }
            else
                msecLst = 0 == msec ? 1 : msec;
        }
    }

    int elapsed = msec - msecLst;
    if (msecLst && (elapsed > ButTimeout) && (elapsed < ButLongClick))  {
        if(but != LOW) {
          msecLst = 0; myPill.shakeCounts = 0;
          return SingleClick;
        }
    }

    //LongClick + Shake detection
    if((but == butLst) && (but == LOW)) {
        if((elapsed > ButTimeout) && (elapsed < ButLongClick)){
          AccelerometerRead();
        }
        if(elapsed > ButLongClick) {
          Serial.print("Pill Shakes =");Serial.println(myPill.shakeCounts);
          
          msecLst = 0; myPill.shakeCounts = 0;
          return LongClick;
        }
    }
    
    return None;
}
// -----------------------------------------------------------------------------


