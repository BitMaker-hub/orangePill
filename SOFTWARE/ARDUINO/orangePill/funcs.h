#include <Arduino.h>



/********** DATA TREATMENT FUNCTIONS *****/
bool isValidNumber(String str);

/********** BLE FUNCTIONS ****************/
void publishNewRandomKey();
bool getCharParams(std::string rxValue, String &allData, String &param1, String &param2, String &param3, String &param4);
std::string decryptBLEchar(std::string rxValue, String strLog);


/********** PRINT DEBUG FUNCTIONS *******/
 void SerialPrintHex (byte Data);
 void SerialPrintArray (byte Source[], byte LEN);
 void printClientsTable(void);
 
