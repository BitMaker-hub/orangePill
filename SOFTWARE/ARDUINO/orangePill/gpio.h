/***************💊 EEPROM ***************/
void EEPROMsetup(void);
void saveMnemonic(String mnemonic);

/***************💊 NEOPIXELS ***************/

void LedSetup(void);
void Ledloop(void);
void showInitEffect(void);
void setLedsColor(int Led1, int Led2, int Led3);
void blinkAllLeds(uint32_t color);

/**************💊 ACCELEROMETER ***************/
// Accelerometer provides different Power modes by changing output bit resolution
void AccSetup();
void AccelerometerRead();

/**************💊 BUTTON ********************/
int checkButton (void);

