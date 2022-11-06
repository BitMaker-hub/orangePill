#include <stdint.h>
#include <Arduino.h>

#define byte uint8_t
/**********************************
 💊 IO PINs
**********************************/
#define BUTTON_PIN			  45  		// Button pin
#define LED_PIN           38      // Pin - leds neopixel
#define LED_COUNT         3       // Neopixel number of leds
#define I2C_SDA           41      // SDA I2C pin
#define I2C_SCL           39      // SCL I2C pin
#define LOW_POWER                 // Accelerometer mode

/**********************************
 💊 DEFINITIONS
**********************************/
//💊 WORKING STATES
enum { None, SingleClick, DoubleClick, LongClick };

#define COLOR_RED         0xFF0000
#define COLOR_GREEN       0x00FF00
#define COLOR_BLUE        0x0000FF
#define COLOR_NONE        0x000000

/**********************************
 💊 GENERAL
**********************************/
#define SERIAL_BAUD       115200   // baudrate debug
#define EEPROM_SIZE       10       // define the number of bytes you want to access
#define SHAKE_TRIGGER_H   1.80     // high value to trigger a shake count on any axis
#define SHAKE_TRIGGER_L   -1.80    // low value to trigger a shake count on any axis
#define SHAKE_TRIGGER_N   300       // minimum shakes done to consider a good entropy seed

const int wdtTimeout = 3000;  //time in ms to trigger the watchdog

/********** 💊 STATES ************************/
#define STATE_VIRGIN      1
#define STATE_SEEDING     2
#define STATE_LOCKED      3
#define STATE_OPENPILL    4
#define STATE_UNLOCKED    5
/**********************************/

//💊 Global vars 
typedef struct {
   uint8_t State;           //Pill initStatus [Virgin, Locked, Unlocked]
   int shakeCounts;         //Detect s
}sPILL;

/*********************************************************************************
**                            End Of File
*********************************************************************************/


