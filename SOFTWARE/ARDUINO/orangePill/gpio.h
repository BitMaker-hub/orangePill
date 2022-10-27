
/********************** NEOPIXELS ***************/
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    38

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 3

void LedSetup(void);
void Ledloop(void);

void showInitEffect(int wait);
/************************************************/

/********************** ACCELEROMETER ***************/
// Accelerometer provides different Power modes by changing output bit resolution
#define LOW_POWER
//#define HIGH_RESOLUTION

#define I2C_SDA 41
#define I2C_SCL 39

void accSetup();
void AccelerometerLoop();
/************************************************/
