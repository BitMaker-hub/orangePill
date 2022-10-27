#include <stdint.h>
#include <Arduino.h>

#define byte uint8_t
/**********************************
 IO PINs
**********************************/
#define P_BUTTON			    45  		// Led apagat
#define P_NEOPIXEL        38      // Pin - leds neopixel
/**********************************
 GENERAL
**********************************/
#define SERIAL_BAUD       9600    // baudrate del port RS232/RS485
#define DEBUG_BAUD        115200  //115200  // baudrate del portdebug RS232

#define EEPROM_SIZE       10       // define the number of bytes you want to access

#define WORKMODE_UC       1
#define WORKMODE_ALONE    2

const int wdtTimeout = 3000;  //time in ms to trigger the watchdog

/**********************************
 TIMER VARS- DELAYS
**********************************/
#define DELAY_T           20                      // Delay global en ms
#define ONE_SEC_T         1000/DELAY_T            // Ciclos de program que deben pasar para llegar a 1 segundo de delay (    
#define CONFIG_TIME       ONE_SEC_T * 60 * 5      //Expresado en unidades de 5 minutos * 60 * 10 
#define RETAIN_TIME       ONE_SEC_T * 20         
#define TIMEOUT_AWS       ONE_SEC_T * 60          
#define T_ACTIVITY_LED    80/DELAY_T              //80 ms
/************** Definición de RS485 ************************************/

//Variables de control del RS485
typedef struct {
   uint8_t currentState;       //Modo en el que operamos [1- UC, 2- Stand_Alone]
}sNODE;

/*********************************************************************************
**                            End Of File
*********************************************************************************/


