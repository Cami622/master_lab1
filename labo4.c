////////////////////////////////////////LABORATORY 4////////////////////////////////


//EXCERCISE 1
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"

volatile uint32_t blinkPeriod = 5;  
uint32_t systemClock;  
void Timer0IntHandler(void) {
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);  

    uint8_t ledState = GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, ledState ^ GPIO_PIN_1);

    TimerLoadSet(TIMER0_BASE, TIMER_A, (systemClock * blinkPeriod) - 1);
}

int main(void) {
    systemClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                      SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {}  

    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1); 

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)) {}  

    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, (systemClock * blinkPeriod) - 1);

    // Habilitar interrupciones del Timer
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();

    // Registrar y activar la interrupción del Timer
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);
    TimerEnable(TIMER0_BASE, TIMER_A);

    while (1) {
    }
}

//EXCERCISE 2
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"

const uint32_t blinkPeriod = 1;  
uint32_t systemClock;
uint8_t step = 0;

void Timer0IntHandler(void) {
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0, 0);

    switch (step) {
        case 0: GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1); break;  
        case 1: GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1); 
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0); break;
        case 2: GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1); 
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4); break;
        case 3: GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0); 
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0); break;
    }

    // Cambiar al siguiente paso
    step = (step + 1) % 4;

    // Recargar el temporizador
    TimerLoadSet(TIMER0_BASE, TIMER_A, (systemClock * blinkPeriod) - 1);
}

int main(void) {
    systemClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                      SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {} 
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}  

    // Configurar PN3, PN2, PN1 y PN0 como salida
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0);
    
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)) {}  

    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, (systemClock * blinkPeriod) - 1);

    // Habilitar interrupciones del Timer
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();

    // Registrar y activar la interrupción del Timer
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);
    TimerEnable(TIMER0_BASE, TIMER_A);

    while (1) {
    }
}


//EXCERCISE 3
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"

// Definiciones de pines
#define LED_PORT_N GPIO_PORTN_BASE
#define LED_PORT_F GPIO_PORTF_BASE
#define LED_PIN_1 GPIO_PIN_1  // PN_1
#define LED_PIN_2 GPIO_PIN_0  // PN_0
#define LED_PIN_3 GPIO_PIN_4  // PF_4
#define LED_PIN_4 GPIO_PIN_0  // PF_0
#define BUTTON_PORT GPIO_PORTJ_BASE
#define BUTTON_PIN GPIO_PIN_1 // PJ_1

#define TIMER_DELAY_2S 240000000  
#define TIMER_DELAY_1S 120000000  // 1s
#define TIMER_DELAY_05S 60000000 

volatile uint8_t led_state = 0;
volatile uint32_t current_delay = TIMER_DELAY_2S;
volatile bool button_pressed = false;
volatile uint8_t press_count = 0;

void Timer0IntHandler(void) {
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // off the leds
    GPIOPinWrite(LED_PORT_N, LED_PIN_1 | LED_PIN_2, 0);
    GPIOPinWrite(LED_PORT_F, LED_PIN_3 | LED_PIN_4, 0);

    switch (led_state) {
        case 0:
            GPIOPinWrite(LED_PORT_N, LED_PIN_1, LED_PIN_1);
            break;
        case 1:
            GPIOPinWrite(LED_PORT_N, LED_PIN_2, LED_PIN_2);
            break;
        case 2:
            GPIOPinWrite(LED_PORT_F, LED_PIN_3, LED_PIN_3);
            break;
        case 3:
            GPIOPinWrite(LED_PORT_F, LED_PIN_4, LED_PIN_4);
            break;
    }

    led_state = (led_state + 1) % 4;  //reset secuence

    //button adjust
    if (button_pressed) {
        button_pressed = false;
        press_count++;
        if (press_count == 1) {
            current_delay = TIMER_DELAY_1S;
        } else if (press_count == 2) {
            current_delay = TIMER_DELAY_05S;
        } else {
            current_delay = TIMER_DELAY_2S;
            press_count = 0;
        }
        TimerLoadSet(TIMER0_BASE, TIMER_A, current_delay);
    }
}

void ButtonIntHandler(void) {
    GPIOIntClear(BUTTON_PORT, BUTTON_PIN);
    if (GPIOPinRead(BUTTON_PORT, BUTTON_PIN) == 0) {
        button_pressed = true;
    }
}

int main(void) {
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                        SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000);

    // Habilitar puertos GPIO
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ));

    // Configurar pines de salida para LEDs
    GPIOPinTypeGPIOOutput(LED_PORT_N, LED_PIN_1 | LED_PIN_2);
    GPIOPinTypeGPIOOutput(LED_PORT_F, LED_PIN_3 | LED_PIN_4);

    // Configurar botón PJ_1
    GPIOPinTypeGPIOInput(BUTTON_PORT, BUTTON_PIN);
    GPIOPadConfigSet(BUTTON_PORT, BUTTON_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOIntRegister(BUTTON_PORT, ButtonIntHandler);
    GPIOIntTypeSet(BUTTON_PORT, BUTTON_PIN, GPIO_FALLING_EDGE);
    GPIOIntEnable(BUTTON_PORT, BUTTON_PIN);

    // Configurar Timer0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, current_delay);
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntEnable(INT_TIMER0A);
    IntMasterEnable();
    TimerEnable(TIMER0_BASE, TIMER_A);

    while (1) {
        // Todo ocurre por interrupciones
    }
}


//EXCERSICE 4
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"

const uint32_t blinkPeriod = 1;  
uint32_t systemClock;
uint8_t counter = 0;  // BINARY COUNTER

void Timer0IntHandler(void) {
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); 

    
    uint8_t pinValues = 0;
    if (counter & 0x01) pinValues |= GPIO_PIN_0;  // Bit 0 -> PF0
    if (counter & 0x02) pinValues |= GPIO_PIN_4;  // Bit 1 -> PF4
    if (counter & 0x04) pinValues |= GPIO_PIN_0;  // Bit 2 -> PN0
    if (counter & 0x08) pinValues |= GPIO_PIN_1;  // Bit 3 -> PN1

    // Escribir valores en los pines de cada puerto
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0, pinValues & (GPIO_PIN_4 | GPIO_PIN_0));
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, pinValues & (GPIO_PIN_1 | GPIO_PIN_0));

    counter = (counter + 1) % 16;

    // Recargar el temporizador
    TimerLoadSet(TIMER0_BASE, TIMER_A, (systemClock * blinkPeriod) - 1);
}

int main(void) {
    systemClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                      SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {}  
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}  

    // Configurar PN1, PN0, PF4 y PF0 como salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0);
    
    // Apagar todos los LEDs al inicio
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, 0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0, 0);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)) {}  

    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, (systemClock * blinkPeriod) - 1);

    // Habilitar interrupciones del Timer
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();

    // Registrar y activar la interrupción del Timer
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);
    TimerEnable(TIMER0_BASE, TIMER_A);

    while (1) {
    }
}