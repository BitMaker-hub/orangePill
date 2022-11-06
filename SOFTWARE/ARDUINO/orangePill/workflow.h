#include <Arduino.h>

/**********💊 USB KEYBOARD ********/
void initUSBKeyboard(void);

/**********💊 WORKFLOW FUNCTIONS ****************/
void doVirginState(int keyState);
void doSeedingState(int keyState);
void doLockedState(int keyState);
void doOpenPill(int keyState);
void doUnlockedState(int keyState);
bool doShakeEffect(uint32_t mainColor);
  

/**********💊 WORKFLOW MESSAGES *****************/
/* --------------- 💊 VIRGIN STATE MESSAGES ---------------------*/
static const char *VIRGIN_SINGLECLICK_M = "\nHi! You got an Orange Pill\n" 
                                          "Your pill still need a seed, please hydrate it.\n" 
                                          "Options>\n"
                                          "*1( SingleClick> to repeat this message.\n"
                                          "*2( DoubleClick> to see device PGP key.\n"
                                          "*3( Hold&Shake>  until you see a BLUE light to get a new seed.\n";
                                          

static const char *VIRGIN_DOUBLECLICK_M = "\nThis pill was used # times.\n" 
                                          "PGP unique signed message> \n" 
                                          "PGP pubkey is> \n\n";

/* --------------- 💊 LOCKED STATE MESSAGES ---------------------*/
static const char *LOCKED_SINGLECLICK_M = "\nHi! You got an Orange Pill\n" 
                                          "Your pill has a seed, but you can't see it.\n"
                                          "This is the pill *xpub( address> sjsdjfsdfscsdcsdcksc"
                                          "You are able to open the pill when you need it.\n" 
                                          "Options>\n"
                                          "*1( SingleClick> to repeat this message.\n"
                                          "*2( DoubleClick> to see device PGP key.\n"
                                          "*3( Hold&Shake>  until you see a RED light to open the pill.\n";


static const char *LOCKED_DOUBLECLICK_M = "\nThis pill was used # times.\n" 
                                          "PGP unique signed message> \n"  
                                          "PGP pubkey is> \n\n";

/* --------------- 💊 UNLOCKED STATE MESSAGES ---------------------*/
static const char *UNLOCKED_SINGLECLICK_M = "\nHi! You got an Orange Pill\n" 
                                          "Your pill has a seed, but you can't see it.\n"
                                          "This is the pill *xpub( address> sjsdjfsdfscsdcsdcksc"
                                          "This has the *xpriv( address> sjsdjfsdfscsdcsdcksc"
                                          "Options>\n"
                                          "*1( SingleClick> to repeat this message.\n"
                                          "*2( DoubleClick> to see device PGP key.\n"
                                          "*3( Hold&Shake>  until you see a GREEN light to reboot the pill.\n";


static const char *UNLOCKED_DOUBLECLICK_M = "\nThis pill was used # times.\n" 
                                            "PGP unique signed message> \n"  
                                            "PGP pubkey is> \n\n";


