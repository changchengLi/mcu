/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.0
        Device            :  PIC16F1704
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.35	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set POWER_KEY aliases
#define POWER_KEY_TRIS                 TRISAbits.TRISA0
#define POWER_KEY_LAT                  LATAbits.LATA0
#define POWER_KEY_PORT                 PORTAbits.RA0
#define POWER_KEY_WPU                  WPUAbits.WPUA0
#define POWER_KEY_OD                   ODCONAbits.ODA0
#define POWER_KEY_ANS                  ANSELAbits.ANSA0
#define POWER_KEY_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define POWER_KEY_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define POWER_KEY_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define POWER_KEY_GetValue()           PORTAbits.RA0
#define POWER_KEY_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define POWER_KEY_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define POWER_KEY_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define POWER_KEY_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define POWER_KEY_SetPushPull()        do { ODCONAbits.ODA0 = 0; } while(0)
#define POWER_KEY_SetOpenDrain()       do { ODCONAbits.ODA0 = 1; } while(0)
#define POWER_KEY_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define POWER_KEY_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set RESET_KEY aliases
#define RESET_KEY_TRIS                 TRISAbits.TRISA2
#define RESET_KEY_LAT                  LATAbits.LATA2
#define RESET_KEY_PORT                 PORTAbits.RA2
#define RESET_KEY_WPU                  WPUAbits.WPUA2
#define RESET_KEY_OD                   ODCONAbits.ODA2
#define RESET_KEY_ANS                  ANSELAbits.ANSA2
#define RESET_KEY_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define RESET_KEY_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define RESET_KEY_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define RESET_KEY_GetValue()           PORTAbits.RA2
#define RESET_KEY_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define RESET_KEY_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define RESET_KEY_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define RESET_KEY_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define RESET_KEY_SetPushPull()        do { ODCONAbits.ODA2 = 0; } while(0)
#define RESET_KEY_SetOpenDrain()       do { ODCONAbits.ODA2 = 1; } while(0)
#define RESET_KEY_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define RESET_KEY_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set THERMAL_LED aliases
#define THERMAL_LED_TRIS                 TRISAbits.TRISA4
#define THERMAL_LED_LAT                  LATAbits.LATA4
#define THERMAL_LED_PORT                 PORTAbits.RA4
#define THERMAL_LED_WPU                  WPUAbits.WPUA4
#define THERMAL_LED_OD                   ODCONAbits.ODA4
#define THERMAL_LED_ANS                  ANSELAbits.ANSA4
#define THERMAL_LED_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define THERMAL_LED_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define THERMAL_LED_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define THERMAL_LED_GetValue()           PORTAbits.RA4
#define THERMAL_LED_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define THERMAL_LED_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define THERMAL_LED_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define THERMAL_LED_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define THERMAL_LED_SetPushPull()        do { ODCONAbits.ODA4 = 0; } while(0)
#define THERMAL_LED_SetOpenDrain()       do { ODCONAbits.ODA4 = 1; } while(0)
#define THERMAL_LED_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define THERMAL_LED_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set SMBALERT aliases
#define SMBALERT_TRIS                 TRISAbits.TRISA5
#define SMBALERT_LAT                  LATAbits.LATA5
#define SMBALERT_PORT                 PORTAbits.RA5
#define SMBALERT_WPU                  WPUAbits.WPUA5
#define SMBALERT_OD                   ODCONAbits.ODA5
#define SMBALERT_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define SMBALERT_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define SMBALERT_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define SMBALERT_GetValue()           PORTAbits.RA5
#define SMBALERT_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define SMBALERT_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define SMBALERT_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define SMBALERT_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define SMBALERT_SetPushPull()        do { ODCONAbits.ODA5 = 0; } while(0)
#define SMBALERT_SetOpenDrain()       do { ODCONAbits.ODA5 = 1; } while(0)

// get/set RC0 procedures
#define RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define RC0_GetValue()              PORTCbits.RC0
#define RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define RC0_SetPullup()             do { WPUCbits.WPUC0 = 1; } while(0)
#define RC0_ResetPullup()           do { WPUCbits.WPUC0 = 0; } while(0)
#define RC0_SetAnalogMode()         do { ANSELCbits.ANSC0 = 1; } while(0)
#define RC0_SetDigitalMode()        do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set RC1 procedures
#define RC1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define RC1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define RC1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RC1_GetValue()              PORTCbits.RC1
#define RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define RC1_SetPullup()             do { WPUCbits.WPUC1 = 1; } while(0)
#define RC1_ResetPullup()           do { WPUCbits.WPUC1 = 0; } while(0)
#define RC1_SetAnalogMode()         do { ANSELCbits.ANSC1 = 1; } while(0)
#define RC1_SetDigitalMode()        do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set POWER aliases
#define POWER_TRIS                 TRISCbits.TRISC2
#define POWER_LAT                  LATCbits.LATC2
#define POWER_PORT                 PORTCbits.RC2
#define POWER_WPU                  WPUCbits.WPUC2
#define POWER_OD                   ODCONCbits.ODC2
#define POWER_ANS                  ANSELCbits.ANSC2
#define POWER_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define POWER_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define POWER_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define POWER_GetValue()           PORTCbits.RC2
#define POWER_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define POWER_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define POWER_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define POWER_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define POWER_SetPushPull()        do { ODCONCbits.ODC2 = 0; } while(0)
#define POWER_SetOpenDrain()       do { ODCONCbits.ODC2 = 1; } while(0)
#define POWER_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define POWER_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set UNDER_TEMP aliases
#define UNDER_TEMP_TRIS                 TRISCbits.TRISC3
#define UNDER_TEMP_LAT                  LATCbits.LATC3
#define UNDER_TEMP_PORT                 PORTCbits.RC3
#define UNDER_TEMP_WPU                  WPUCbits.WPUC3
#define UNDER_TEMP_OD                   ODCONCbits.ODC3
#define UNDER_TEMP_ANS                  ANSELCbits.ANSC3
#define UNDER_TEMP_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define UNDER_TEMP_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define UNDER_TEMP_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define UNDER_TEMP_GetValue()           PORTCbits.RC3
#define UNDER_TEMP_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define UNDER_TEMP_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define UNDER_TEMP_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define UNDER_TEMP_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define UNDER_TEMP_SetPushPull()        do { ODCONCbits.ODC3 = 0; } while(0)
#define UNDER_TEMP_SetOpenDrain()       do { ODCONCbits.ODC3 = 1; } while(0)
#define UNDER_TEMP_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define UNDER_TEMP_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set HEATER aliases
#define HEATER_TRIS                 TRISCbits.TRISC4
#define HEATER_LAT                  LATCbits.LATC4
#define HEATER_PORT                 PORTCbits.RC4
#define HEATER_WPU                  WPUCbits.WPUC4
#define HEATER_OD                   ODCONCbits.ODC4
#define HEATER_ANS                  ANSELCbits.ANSC4
#define HEATER_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define HEATER_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define HEATER_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define HEATER_GetValue()           PORTCbits.RC4
#define HEATER_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define HEATER_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define HEATER_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define HEATER_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define HEATER_SetPushPull()        do { ODCONCbits.ODC4 = 0; } while(0)
#define HEATER_SetOpenDrain()       do { ODCONCbits.ODC4 = 1; } while(0)
#define HEATER_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define HEATER_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set POWER_LED aliases
#define POWER_LED_TRIS                 TRISCbits.TRISC5
#define POWER_LED_LAT                  LATCbits.LATC5
#define POWER_LED_PORT                 PORTCbits.RC5
#define POWER_LED_WPU                  WPUCbits.WPUC5
#define POWER_LED_OD                   ODCONCbits.ODC5
#define POWER_LED_ANS                  ANSELCbits.ANSC5
#define POWER_LED_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define POWER_LED_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define POWER_LED_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define POWER_LED_GetValue()           PORTCbits.RC5
#define POWER_LED_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define POWER_LED_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define POWER_LED_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define POWER_LED_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define POWER_LED_SetPushPull()        do { ODCONCbits.ODC5 = 0; } while(0)
#define POWER_LED_SetOpenDrain()       do { ODCONCbits.ODC5 = 1; } while(0)
#define POWER_LED_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define POWER_LED_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/