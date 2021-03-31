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
#include <stdbool.h>
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

/*
 * 7SEG 
 * 1st EN from left SDA_1 RD4 PIN 12
 * 2nd SCL_1 RD3 PIN 9
 * 3rd TX_1 RB12 PIN 8
 * 4th RX_1 RC15 PIN 6
 * A PWM_1 RC13 PIN 11
 * B AN_1 RC0 PIN 7
 * C RST_1 RC7 PIN 4
 * D SCK_1 RB7 PIN 2
 * E MISO_1 RB8 PIN 1
 * F MOSI_1 RB9 PIN 10
 * G SDA_2 RC8 PIN 5
 */



int currentEvent  = -1;
int highScore = 0;
int score = 0;
int level = 1;
int fail = 0;
int listening = 1; 
bool display7SEG = false;


int main(void) 
{
    CLKDIVbits.FRCDIV = 1; // Divide FRC by 2
 
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
    
    //inputs
    TRISCbits.TRISC0 = 1;  //C0 is input (on/off switch)
    TRISCbits.TRISC14 = 1; //C14 is input (pushbutton)
    TRISBbits.TRISB15 = 1; //B15 is input (analog stick)
    
    //outputs
    TRISBbits.TRISB2 = 0;   //B2 is output (green LED)
    TRISCbits.TRISC3 = 0;   //C3 is output (red LED)
    
    highScore = 0; //initialize high score to 0
    
    //7SEG
    // DP# EN bits
    TRISDbits.TRISD4 = 0; // 1st EN from left SDA_1 RD4
    TRISDbits.TRISD3 = 0; // 2nd SCL_1 RD3
    TRISBbits.TRISB12 = 0; // 3rd TX_1 RB12
    TRISCbits.TRISC15= 0; // 4th RX_1 RC15 PIN 6
    
    // A-G
    TRISCbits.TRISC13= 0; // A PWM_1 RC13 PIN 11
    TRISCbits.TRISC0= 0;//B AN_1 RC0 PIN 7
    TRISCbits.TRISC7= 0;//C RST_1 RC7 PIN 4
    TRISBbits.TRISB7= 0;//D SCK_1 RB7 PIN 2
    TRISBbits.TRISB8= 0;//E MISO_1 RB8 PIN 1
    TRISBbits.TRISB9= 0;//F MOSI_1 RB9 PIN 10
    TRISCbits.TRISC8= 0;//G SDA_2 RC8 PIN 5
    
    // ANALOG INPUTS (microphone)
    ADCON1Lbits.ADON = 1;  // enable
    ADCON1Hbits.FORM = 1;   // fractional data output format bit set to integer
    ADCON1Hbits.SHRRES = 11;   // shared ADC core resolution selection bits
    ADCON3Hbits.CLKSEL = 01; // ADC Module clock source selection bits set to FOSC
    ADCON3Lbits.CNVCHSEL = 1; // channel number selection for software individual channel conversion trigger bits
    ADCON3Lbits.SHRSAMP = 0;    // shared ADC core samples an analog input specified by CNVSCHSEL bits
    

    while (1) 
    {
        if (PORTCbits.RC0 == 0)         //if switch is on
        {    
            fail = 0;       //initialize fail to 0;
            
            //put all code in here
            PR1 = 0xFFFF - 10000*level;       // Load period register - decrease time per level
            
            currentActionUpdater();       // Generate event
            humanInteractionListener();     // listen for user input
        }
        else {                      //if switch is off
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

void setClockBits()
{
    T1CON = 0x0;        // Stop timer and clear control register,               
    T1CONbits.TECS = 3; // set prescaler at 1:1, internal clock source 
    T1CONbits.TCKPS = 3;
    T1CONbits.TCS = 0;
    TMR1 = 0x0;         // Clear timer register
}

void humanInteractionListener()
{
    listening = 1; 
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
        
        if(currentEvent == 3 && listenMic() > 70) /* mic has been detected??*/
        {
            listening = 0; 
            result = checkEventType(3); 
        }
    }
    if(result == 0 || fail == 1)
    {
        failureHandler();
    }
    else if (result == 1)
    {
        successHandler();
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
    T1CONbits.TON = 1; //starting timer
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
        highScoreHandler(score);
        //Increment and keep going
        //Every 5 levels speedup
    }
    else if(result == 0)
    {
        score = 0;
        //Reset score and tell game to stop
    }
}

void highScoreHandler(int score)
{
    if(score > highScore)
    {
        highScore = score;
        updateSevenSeg(highScore);
    }
}

// Call updateSevenSeg with new number to display on 7SEG
// Will display the number then turn off the 7SEG
void updateSevenSeg(int newScore)
{    
    T1CON = 0x0;
    T1CONbits.TECS = 3;
    T1CONbits.TCKPS = 3;
    T1CONbits.TCS = 0;
    TMR1 = 0x0;
    PR1 = 0xAAAA;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
    T1CONbits.TON = 1;
    
    int digit0 = newScore % 10;
    int digit1 = (newScore / 10) % 10;
    int digit2 = (newScore / 100) % 10;
    int digit3 = (newScore / 1000) % 10;
    
    if(digit3 == 0)
    {
        digit3  = -1;
        if(digit2 == 0)
        {
            digit2 = -1;
            if(digit1 == 0)
                digit1 = -1;
        }
    }
    
    int i = 0;
    
    display7SEG = true;
    int currentDigit;
    while(display7SEG)
    {
        
        
        if(currentDigit == 0)
            display0();
        else if(currentDigit == 1)
        {
            display1();
            //break;
        }
        else if(currentDigit == 2)
            display2();
        else if(currentDigit == 3)
            display3();
        else if(currentDigit == 4)
            display4();
        else if(currentDigit == 5)
            display5();
        else if(currentDigit == 6)
            display6();
        else if(currentDigit == 7)
            display7();
        else if(currentDigit == 8)
            display8();
        else if(currentDigit == 9)
            display9();
        
        if(i == 0)
        {
            __delay_ms(10);
            enableDP1();
            currentDigit = digit0;
            i++;
        }
        else if(i == 1)
        {
            if(digit1 != -1)
            {
                __delay_ms(10);
                enableDP2();
                currentDigit = digit1;
            }
            i++;
        }
        else if(i == 2)
        {
            if(digit2 != -1)
            {
                __delay_ms(10);
                enableDP3();
                currentDigit = digit2;
            }
            i++;
        }
        else
        {
            if(digit3 != -1)
            {
                __delay_ms(10);
                enableDP4();
                currentDigit = digit3;
            }
           i = 0;
        } 
    }
    setDPbits();
}


void enableDP1()
{
    LATDbits.LATD4 = 0; // DP4 EN 
    LATDbits.LATD3 = 0; // DP3 EN
    LATBbits.LATB12 = 0; // DP2 EN
    LATCbits.LATC15= 1; // DP1 EN
}

void enableDP2()
{
    LATDbits.LATD4 = 0; // DP4 EN 
    LATDbits.LATD3 = 0; // DP3 EN
    LATBbits.LATB12 = 1; // DP2 EN
    LATCbits.LATC15= 0; // DP1 EN
}

void enableDP3()
{
    LATDbits.LATD4 = 0; // DP4 EN 
    LATDbits.LATD3 = 1; // DP3 EN
    LATBbits.LATB12 = 0; // DP2 EN
    LATCbits.LATC15= 0; // DP1 EN
}

void enableDP4()
{
    LATDbits.LATD4 = 1; // DP4 EN 
    LATDbits.LATD3 = 0; // DP3 EN
    LATBbits.LATB12 = 0; // DP2 EN
    LATCbits.LATC15= 0; // DP1 EN
}

void setDPbits()
{
    LATDbits.LATD4 = 0; // DP4 EN 
    LATDbits.LATD3 = 0; // DP3 EN
    LATBbits.LATB12 = 0; // DP2 EN
    LATCbits.LATC15= 0; // DP1 EN
    
    LATCbits.LATC13= 1; // A on
    LATCbits.LATC0= 1;//B AN_1 RC0 PIN 7
    LATCbits.LATC7= 1;//C RST_1 RC7 PIN 4
    LATBbits.LATB7= 1;//D SCK_1 RB7 PIN 2
    LATBbits.LATB8= 1;//E MISO_1 RB8 PIN 1
    LATBbits.LATB9= 1;//F MOSI_1 RB9 PIN 10
    LATCbits.LATC8= 1;//G SDA_2 RC8 PIN 5
}

void display0()
{
    LATCbits.LATC13= 0; // A on
    LATCbits.LATC0= 0;//B AN_1 RC0 PIN 7
    LATCbits.LATC7= 0;//C RST_1 RC7 PIN 4
    LATBbits.LATB7= 0;//D SCK_1 RB7 PIN 2
    LATBbits.LATB8= 0;//E MISO_1 RB8 PIN 1
    LATBbits.LATB9= 0;//F MOSI_1 RB9 PIN 10
    LATCbits.LATC8= 1;//G SDA_2 RC8 PIN 5
}

void display1()
{
    LATCbits.LATC13= 1; // A on
    LATCbits.LATC0= 0;//B AN_1 RC0 PIN 7
    LATCbits.LATC7= 0;//C RST_1 RC7 PIN 4
    LATBbits.LATB7= 1;//D SCK_1 RB7 PIN 2
    LATBbits.LATB8= 1;//E MISO_1 RB8 PIN 1
    LATBbits.LATB9= 1;//F MOSI_1 RB9 PIN 10
    LATCbits.LATC8= 1;//G SDA_2 RC8 PIN 5
}

void display2()
{
    LATCbits.LATC13= 0; // A on
    LATCbits.LATC0= 0;//B AN_1 RC0 PIN 7
    LATCbits.LATC7= 1;//C RST_1 RC7 PIN 4
    LATBbits.LATB7= 0;//D SCK_1 RB7 PIN 2
    LATBbits.LATB8= 0;//E MISO_1 RB8 PIN 1
    LATBbits.LATB9= 1;//F MOSI_1 RB9 PIN 10
    LATCbits.LATC8= 0;//G SDA_2 RC8 PIN 5
}

void display3()
{
    LATCbits.LATC13= 0; // A on
    LATCbits.LATC0= 0;//B AN_1 RC0 PIN 7
    LATCbits.LATC7= 0;//C RST_1 RC7 PIN 4
    LATBbits.LATB7= 0;//D SCK_1 RB7 PIN 2
    LATBbits.LATB8= 1;//E MISO_1 RB8 PIN 1
    LATBbits.LATB9= 1;//F MOSI_1 RB9 PIN 10
    LATCbits.LATC8= 0;//G SDA_2 RC8 PIN 5
}

void display4()
{
    LATCbits.LATC13= 1; // A on
    LATCbits.LATC0= 0;//B AN_1 RC0 PIN 7
    LATCbits.LATC7= 0;//C RST_1 RC7 PIN 4
    LATBbits.LATB7= 1;//D SCK_1 RB7 PIN 2
    LATBbits.LATB8= 1;//E MISO_1 RB8 PIN 1
    LATBbits.LATB9= 0;//F MOSI_1 RB9 PIN 10
    LATCbits.LATC8= 0;//G SDA_2 RC8 PIN 5
}

void display5()
{
    LATCbits.LATC13= 0; // A on
    LATCbits.LATC0= 1;//B AN_1 RC0 PIN 7
    LATCbits.LATC7= 0;//C RST_1 RC7 PIN 4
    LATBbits.LATB7= 0;//D SCK_1 RB7 PIN 2
    LATBbits.LATB8= 1;//E MISO_1 RB8 PIN 1
    LATBbits.LATB9= 0;//F MOSI_1 RB9 PIN 10
    LATCbits.LATC8= 0;//G SDA_2 RC8 PIN 5
}

void display6()
{
    LATCbits.LATC13= 0; // A on
    LATCbits.LATC0= 1;//B AN_1 RC0 PIN 7
    LATCbits.LATC7= 0;//C RST_1 RC7 PIN 4
    LATBbits.LATB7= 0;//D SCK_1 RB7 PIN 2
    LATBbits.LATB8= 0;//E MISO_1 RB8 PIN 1
    LATBbits.LATB9= 0;//F MOSI_1 RB9 PIN 10
    LATCbits.LATC8= 0;//G SDA_2 RC8 PIN 5
}

void display7()
{
    LATCbits.LATC13= 0; // A on
    LATCbits.LATC0= 0;//B AN_1 RC0 PIN 7
    LATCbits.LATC7= 0;//C RST_1 RC7 PIN 4
    LATBbits.LATB7= 1;//D SCK_1 RB7 PIN 2
    LATBbits.LATB8= 1;//E MISO_1 RB8 PIN 1
    LATBbits.LATB9= 1;//F MOSI_1 RB9 PIN 10
    LATCbits.LATC8= 1;//G SDA_2 RC8 PIN 5
}

void display8()
{
    LATCbits.LATC13= 0; // A on
    LATCbits.LATC0= 0;//B AN_1 RC0 PIN 7
    LATCbits.LATC7= 0;//C RST_1 RC7 PIN 4
    LATBbits.LATB7= 0;//D SCK_1 RB7 PIN 2
    LATBbits.LATB8= 0;//E MISO_1 RB8 PIN 1
    LATBbits.LATB9= 0;//F MOSI_1 RB9 PIN 10
    LATCbits.LATC8= 0;//G SDA_2 RC8 PIN 5
}

void display9()
{
    LATCbits.LATC13= 0; // A on
    LATCbits.LATC0= 0;//B AN_1 RC0 PIN 7
    LATCbits.LATC7= 0;//C RST_1 RC7 PIN 4
    LATBbits.LATB7= 1;//D SCK_1 RB7 PIN 2
    LATBbits.LATB8= 1;//E MISO_1 RB8 PIN 1
    LATBbits.LATB9= 0;//F MOSI_1 RB9 PIN 10
    LATCbits.LATC8= 0;//G SDA_2 RC8 PIN 5
}

// microphone read (analog)
// not using function prototype since we want to call randomly
unsigned int listenMic(void){
    ADCON1bits.SAMP = 1;    // enable sampling
    __delay_ms(0xFFFF - 10000*level); // wait for user to make noise
    ADCON1bits.SAMP = 0;    // converting sample
    
    while(!ADCON1bits.DONE){
        return ADCBUF0;
    }
}

// Timer1 Interrupt
void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void)
{
    if(display7SEG)
    {
        display7SEG = false;
    }
    else
    {
        fail = 1;
        listening = 0;
    }

    T1CONbits.TON = 0;      //turn timer off 
    IFS0bits.T1IF = 0;      
}