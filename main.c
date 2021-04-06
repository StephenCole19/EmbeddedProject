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
#include <stdbool.h>
#define FCY 2000000UL
#define FOSC 4000000UL // FRC divided by 2 from 8MHz to 4MHz
#define RAND_MAX 4

#include <libpic30.h>


//Green LED     CS_1
//Red LED       CS_2
//Push Button   INT_1
//ON OFF  INT_2 XXX
//Analog Stick MISO_2 RC1 AN13
//Analog Stick MOSI_2 RC2 AN14

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
int firstEvent = 1;
int dataAN0;
int dataAN13;
int dataAN14;
int timerCheck = 0;
int irIn = -1;


int main(void) 
{
    setup(); 
    
    highScore = 0; //initialize high score to 0
    
    while (1) 
    {
        if (PORTBbits.RB15 == 0)         //if switch is on
        {    
            fail = 0;       //initialize fail to 0;
            
            if(firstEvent)
            {
                currentActionUpdater();       // Generate event
                firstEvent = 0;
            }
            
            humanInteractionListener();     // listen for user input
        }
        else {                      //if switch is off
            scoreHandler(0);        //reset score
            level = 1;              //reset level
            firstEvent = 1;         //reset first event
            
            //turn off all outputs
            LATBbits.LATB2 = 0;     //Turn off green LED
            LATDbits.LATD11 = 0;     //Turn off red LED
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
    T1CON = 0x0;
    T1CONbits.TECS = 3;
    T1CONbits.TCKPS = 3;
    T1CONbits.TCS = 0;
    TMR1 = 0x0;
    PR1 = 0xFFFF - 1000*level;       // Load period register - decrease time per level
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
    T1CONbits.TON = 1;
}

void humanInteractionListener()
{
    listening = 1; 
    int result = 0; // 1 == pass, 0 == fail
    timerCheck = 0;
    int micLevel = 0;
    
    while(listening && PORTBbits.RB15 == 0){
        
        if(PORTCbits.RC14 == 0)
        { //push button has been clicked
            listening = 0; //stop listening
            result = checkEventType(1);
        }
        
        if(PORTBbits.RB14 == 0 || PORTBbits.RB13 == 0) // Analog Stick
        {
            listening = 0; //stop listening 
            result = checkEventType(2);
        }
        
        listenMic();
        if(micLevel == 0)
        {
            micLevel = dataAN0 + 20;
        }
        
        // if mic peeks above 800 and its looking for a mic event
        if(dataAN0 >= micLevel && currentEvent == 3 && micLevel != 0)
        {
            listening = 0; 
            result = checkEventType(3); 
        }
        
        if(getCurrentCommand() != -1)
        {
            listening = 0;
            irIn = -1;
            result = checkEventType(4);
        }
    }
    
    if (result == 1 && timerCheck == 0)
    {
        successHandler();
    }
    else
        failureHandler();
}

// updates the global variable currentEvent when called
// generates a random number and assigns it to the variable
// 1 = push button
// 2 = analog stick
// 3 = mic
void currentActionUpdater()
{
    currentEvent = (rand() % 4) + 1;
    beep(currentEvent);
    setClockBits();
}

void successHandler()
{
    T1CONbits.TON = 0; //reset clock
    scoreHandler(1);
    LATBbits.LATB2 = 1;     //Turn on green LED
    __delay_ms(10);
    LATBbits.LATB2 = 0;     //Turn off green LED
    currentActionUpdater();
}

void failureHandler()
{
    LATDbits.LATD11 = 1;     //Turn on red LED
    __delay_ms(500);
    LATDbits.LATD11 = 0;     //Turn off red LED
    firstEvent = 1;
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
        highScoreHandler(score);
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
            display1();
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
            __delay_ms(5);
            enableDP1();
            currentDigit = digit0;
            i++;
        }
        else if(i == 1)
        {
            if(digit1 != -1)
            {
                __delay_ms(5);
                enableDP2();
                currentDigit = digit1;
            }
            i++;
        }
        else if(i == 2)
        {
            if(digit2 != -1)
            {
                __delay_ms(5);
                enableDP3();
                currentDigit = digit2;
            }
            i++;
        }
        else
        {
            if(digit3 != -1)
            {
                __delay_ms(5);
                enableDP4();
                currentDigit = digit3;
            }
           i = 0;
        } 
    }
    setDPbits();
}

void beep(int numBeeps)
{
    int i = 0;
    for(i; i<numBeeps; i++)
    {
        LATDbits.LATD15 = 1;
        __delay_ms(150);
        LATDbits.LATD15 = 0;
    }
    
    __delay_ms(1500);
}

void checkIR()
{   
    if(irIn != -1)
        return;
    
    int i = 0;
    while(PORTCbits.RC3 && (i <= 90)) 
    { 
        i++; 
        __delay_us(50); 
    }
    if((i > 90) || (i < 40)) 
        return;
    
    int n;
    for(n = 0; n < 32; ++n)
    {
        i = 0;
        while(!PORTCbits.RC3 && (i <= 23))
        { 
            i++; 
            __delay_us(50); 
        }
        
        if((i > 22) || (i < 4)) 
            return;
        
        i = 0;
        while(PORTCbits.RC3 && (i <= 45))
        { 
            i++; 
            __delay_us(50); 
        }
        
        if((i > 44) || (i < 8)) 
            return;
        
        if(i > 21) 
            irIn |= 1ul << (31-n);
        else
            irIn &= ~(1ul << (31-n));
    }
}

// microphone read (analog)
void listenMic(void)
{
    ADCON3Lbits.SWCTRG = 1;
    __delay_ms(100)
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

void setup()
{
    CLKDIVbits.FRCDIV = 1; // Divide FRC by 2
 
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
    
    //inputs
    TRISBbits.TRISB15 = 1;  //AN_2 D10 is input (on/off switch)
    TRISCbits.TRISC14 = 1; //C14 is input (pushbutton)
    TRISBbits.TRISB14 = 1; //Analog Stick RB14 RX_2
    TRISBbits.TRISB13 = 1; //Analog Stick RB13 TX_2
    
    //outputs
    TRISBbits.TRISB2 = 0;   //B2 is output (green LED)
    TRISDbits.TRISD11 = 0;   //RST_2 D11 is output (red LED)
    TRISDbits.TRISD15 = 0; //D15 is output (Speaker)
    
    setupSpeaker();
    setupSevenSeg();
    setupMic();
    setupIR();
}

void setupSpeaker()
{
    //Speaker
    
    //Configure the source clock for the APLL
    ACLKCON1bits.FRCSEL = 1;
    // Configure the APLL prescalar, APLL feedback divider, and both APLL postscalars
    ACLKCON1bits.APLLPRE = 1; //N1 = 1
    APLLFBD1bits.APLLFBDIV = 125; // M = 125
    APLLDIV1bits.APOST1DIV = 2; // N2 = 2
    APLLDIV1bits.APOST2DIV = 1; // N3 = 1
    // Enable APLL
    ACLKCON1bits.APLLEN = 1;
    
    //DAC
    DACCTRL1Lbits.CLKSEL = 2;
    DACCTRL1Lbits.DACON = 1;
    DAC1CONLbits.DACEN = 1;
    DAC1CONLbits.DACOEN = 1;
    //Triangle Wave mode
    DAC1DATLbits.DACLOW = 0xCD; // Lower data value
    DAC1DATHbits.DACDAT = 0xF32; // Upper data value
    SLP1DATbits.SLPDAT = 0x1; // Slope rate, counts per step
    SLP1CONHbits.TWME = 1;
    SLP1CONHbits.SLOPEN = 1;
}

void setupSevenSeg()
{
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
}

void setupMic()
{
    //MIC
    ANSELAbits.ANSELA0 = 1;
    ANSELAbits.ANSELA1 = 1;
    ANSELAbits.ANSELA2 = 1;
    TRISAbits.TRISA0 = 1; // RA0 AN MIC_IN_ADC
    TRISAbits.TRISA1 = 1; // MIC-
    TRISAbits.TRISA2 = 1; // MIC+
    
    
    ADCON5Hbits.WARMTIME = 15;
    ADCON1Lbits.ADON = 1;  // enable
    ADCON5Lbits.C0PWR = 1;
    while(ADCON5Lbits.C0RDY == 0);
    ADCON3Hbits.C0EN = 1;
    
    ADCON3Hbits.CLKSEL = 1; // ADC Module clock source selection bits set to FOSC
    ADCON3Hbits.CLKDIV = 0; // no clock divider (1:1)
    
    ADCORE0Hbits.ADCS = 0; // clock divider (1:2)
    ADCORE1Hbits.ADCS = 0; // clock divider (1:2)
    
    ADCON3Lbits.REFSEL = 0;
    
    ADCON1Hbits.FORM = 0;   // fractional data output format bit set to integer
    ADMOD0Lbits.SIGN0 = 0;
    ADMOD0Lbits.DIFF0 = 0;
    ADIELbits.IE0 = 1;
    _ADCAN0IF = 0; // clear interrupt flag for AN0
    _ADCAN0IE = 1; // enable interrupt for AN0
    
    ADTRIG0Lbits.TRGSRC0 = 0b00001; // Select software trigger
}

int getCurrentCommand() 
{ 
    switch(irIn)
    {
        case 0x6897:
            return 0;
        case 0x30CF:
            return 1;
        case 0x18E7: 
            return 2;
        case 0x7A85: 
            return 3;
        default: 
            return -1;

    }
}

void setupIR()
{
    TRISCbits.TRISC3 = 1;
    ANSELCbits.ANSELC3 = 0;
    
    // use RC3 for IC1
    RPINR3bits.ICM1R = 51;
    
    CCP1CON1Lbits.T32 = 1; // capture 32 bits
    CCP1CON1Lbits.CCPMOD = 1; 
    CCP1CON1Lbits.CCPON = 1; // start capture
    CCP1CON1Lbits.CCSEL = 1; // Use input
    CCP1CON2Hbits.ICS = 0;   // I2C1
    CCP1CON2Hbits.AUXOUT = 3; // set event capture
    
    IEC0bits.CCP1IE = 1;
    IFS0bits.CCP1IF = 0;
    IPC1bits.CCP1IP = 7;
    irIn = -1;
}

// Timer1 Interrupt
void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void)
{

    display7SEG = false;
    listening = 0;
    timerCheck = 1;
    
    T1CONbits.TON = 0;      //turn timer off 
    IFS0bits.T1IF = 0;      
}

// ADC AN0 ISR
void __attribute__((interrupt, no_auto_psv)) _ADCAN0Interrupt(void)
{
    dataAN0 = ADCBUF0; // read conversion result
    _ADCAN0IF = 0; // clear interrupt flag
}

void __attribute__((interrupt, auto_psv)) _CCP1Interrupt(void)
{
    checkIR();
    IFS0bits.CCP1IF = 0;
}
