/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F57Q43
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include <math.h>

#define T               (128)
#define W               (0.049f)
#define AMPLITUDE       (2047)
#define OFFSET_VALUE    (2047)

/* variables to be used
 */
uint8_t u8temp = 0;
uint8_t u8count = 0;
uint16_t u8value = 0;
uint16_t sins[128];
uint8_t i;
uint16_t test = 0;

void dac(uint16_t value) {

    CS_SetLow();
    /*Send High Byte*/
    u8temp = (value >> 8)&0x0F; // Store bits 8:11 to temp
    u8temp |= 0x30; // Define DAC setting (choose 1x gain)
    SPI1_ExchangeByte(u8temp); // Send high byte via SPI

    /*Send Low Byte*/
    u8temp = value; // Store bits 0:7 to temp
    SPI1_ExchangeByte(u8temp); // Send low byte via SPI
    CS_SetHigh();

}

void updateDac(void) {
    u8value = (uint16_t) sins[u8count++];
    dac(u8value);
    if (u8count > 127) u8count = 0;
}


/*
                         Main application
 */
void main(void) {
    // Initialize the device
    SYSTEM_Initialize();
    LED0_SetHigh();

    SPI1_Open(0);

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    LED0_SetLow();
    for (i = 0; i < 128; i++) {
        sins[i] = OFFSET_VALUE + AMPLITUDE * sin(W * i);
    }
    LED0_SetHigh();
 
    TMR2_SetInterruptHandler(updateDac);
    while (1) {
        // Add your application code
    }
}
/**
 End of File
 */