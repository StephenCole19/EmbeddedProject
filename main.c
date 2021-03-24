// DSPIC33CK256MP506 Configuration Bit Settings

// 'C' source line config statements

// FSEC
#pragma config BWRP = OFF               // Boot Segment Write-Protect bit (Boot Segment may be written)
#pragma config BSS = DISABLED           // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSEN = OFF               // Boot Segment Control bit (No Boot Segment)
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = DISABLED           // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP = OFF               // Configuration Segment Write-Protect bit (Configuration Segment may be written)
#pragma config CSS = DISABLED           // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = OFF            // Alternate Interrupt Vector Table bit (Disabled AIVT)

// FBSLIM
#pragma config BSLIM = 0x1FFF           // Boot Segment Flash Page Address Limit bits (Enter Hexadecimal value)

// FSIGN

// FOSCSEL
#pragma config FNOSC = FRCDIVN          // Oscillator Source Selection (Internal Fast RC (FRC) Oscillator with postscaler)
#pragma config IESO = OFF                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)
#pragma config PLLKEN = ON              // PLL Lock Status Control (PLL lock signal will be used to disable PLL clock output if lock is lost)
#pragma config XTCFG = G3               // XT Config (24-32 MHz crystals)
#pragma config XTBST = ENABLE           // XT Boost (Boost the kick-start)

// FWDT
// RWDTPS = No Setting
#pragma config RCLKSEL = LPRC           // Watchdog Timer Clock Select bits (Always use LPRC)
#pragma config WINDIS = ON              // Watchdog Timer Window Enable bit (Watchdog Timer operates in Non-Window mode)
#pragma config WDTWIN = WIN25           // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
// SWDTPS = No Setting
#pragma config FWDTEN = ON              // Watchdog Timer Enable bit (WDT enabled in hardware)

// FPOR
#pragma config BISTDIS = DISABLED       // Memory BIST Feature Disable (mBIST on reset feature disabled)

// FICD
#pragma config ICS = PGD2               // ICD Communication Channel Select bits (Communicate on PGC1 and PGD1)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)
#pragma config NOBTSWP = DISABLED       // BOOTSWP instruction disable bit (BOOTSWP instruction is disabled)

// FDMTIVTL
#pragma config DMTIVTL = 0xFFFF         // Dead Man Timer Interval low word (Enter Hexadecimal value)

// FDMTIVTH
#pragma config DMTIVTH = 0xFFFF         // Dead Man Timer Interval high word (Enter Hexadecimal value)

// FDMTCNTL
#pragma config DMTCNTL = 0xFFFF         // Lower 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)

// FDMTCNTH
#pragma config DMTCNTH = 0xFFFF         // Upper 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)

// FDMT
#pragma config DMTDIS = OFF             // Dead Man Timer Disable bit (Dead Man Timer is Disabled and can be enabled by software)

// FDEVOPT
#pragma config ALTI2C1 = OFF            // Alternate I2C1 Pin bit (I2C1 mapped to SDA1/SCL1 pins)
#pragma config ALTI2C2 = OFF            // Alternate I2C2 Pin bit (I2C2 mapped to SDA2/SCL2 pins)
#pragma config ALTI2C3 = OFF            // Alternate I2C3 Pin bit (I2C3 mapped to SDA3/SCL3 pins)
#pragma config SMBEN = SMBUS            // SM Bus Enable (SMBus input threshold is enabled)
#pragma config SPI2PIN = PPS            // SPI2 Pin Select bit (SPI2 uses I/O remap (PPS) pins)

// FALTREG
#pragma config CTXT1 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits (Not Assigned)
#pragma config CTXT2 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits (Not Assigned)
#pragma config CTXT3 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 3 bits (Not Assigned)
#pragma config CTXT4 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 4 bits (Not Assigned)

// FBTSEQ
#pragma config BSEQ = 0xFFF             // Relative value defining which partition will be active after device Reset; the partition containing a lower boot number will be active (Enter Hexadecimal value)
#pragma config IBSEQ = 0xFFF            // The one's complement of BSEQ; must be calculated by the user and written during device programming. (Enter Hexadecimal value)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include "xc.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#define FCY 2000000UL
#define FOSC 4000000UL // FRC divided by 2 from 8MHz to 4MHz

/*
clock stuff
T1CON = 0x0;
T1CONbits.TECS = 3;
T1CONbits.TCKPS = 3;
T1CONbits.TCS = 0;
TMR1 = 0x0;
PR1 = 0xFFFF;
IEC0bits.T1IE = 1;
IFS0bits.T1IF = 0;
T1CONbits.TON = 1;
*/

//Green LED     CS_1
//Red LED       CS_2
//Push Button   INT_1
//Analog Stick  INT_2


int currentEvent  = -1;
int score = 0;
int level = 1;


int main(void) 
{
    CLKDIVbits.FRCDIV = 1; // Divide FRC by 2
    
    TRISCbits.TRISC0 = 1;  //C0 is input (on/off switch)
    
    while (1) 
    {
        if (PORTCbits.RC0 == 0) 
        {     
            //if switch is on
            //put all code in here
            
            humanInteractionListener();
            currentActionUpdater();
        }
        else {
            scoreHandler(0);        //reset score
            level = 1;              //reset level
            //turn off all outputs
            LATBbits.LATB2 = 0;     //Turn off green LED
            LATCbits.LATC3 = 0;     //Turn off red LED
            //turn off 7 seg
            
        }
    }
    return 0;
}

/*
 * Return 1 if the userEvent == currentEvent,
 * else return 0
 */
int checkEventType(int userEvent)
{
    int ret;
    if(userEvent == currentEvent)
        ret = 1;
    else
        ret = 0;
    
    return ret;
}

void humanInteractionListener()
{
    int listening = 1; 
    int eventType = 0; 
    int result = 0; // 1 == pass, 0 == fail
    
    while(listening){
        if(PORTCbits.RC14 == 0)
        { //push button has been clicked
            listening = 0; //stop listening
            result = checkEventType(1);
        }
        if(PORTBbits.RB14 == 0)
        {
            listening = 0; //stop listening 
            result = checkEventType(2);
        }
        if(0) /* mic has been detected??*/
        {
            listening = 0; 
            result = checkEventType(3); 
        }
    }
}

// updates the global variable currentEvent when called
// generates a random number and assigns it to the variable
// 1 = push button
// 2 = analog stick
// 3 = mic

void currentActionUpdater()
{
//    time_t t;
//    srand((unsigned) time(&t));
    currentEvent = rand() % 3;
}

void successHandler()
{
    currentActionUpdater();
    scoreHandler(1);
}

void failureHandler()
{
    scoreHandler(0);
}

void scoreHandler(int result)
{
    if(result == 1)
    {
        score++;
        if(score % 5 == 0)
        {
            level++;
        }
        //Increment and keep going
        //Every 5 levels speedup
    }
    else if(result == 0)
    {
        score = 0;
        //Reset score and tell game to stop
    }
}
// Timer1 Interrupt
void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void)
{
    T1CONbits.TON = 0;
    IFS0bits.T1IF = 0;
}