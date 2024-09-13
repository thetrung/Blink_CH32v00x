#include "ch32v00x.h"
// As using "none" seem better.

// Config PIN_0 :
#define LED_PIN GPIO_Pin_0
#define LED_PORT GPIOC

// custom-made sleep :
void sleep(uint32_t ms){
    while (ms--){}
}

void setup(){
     // Enable GPIO clock
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOC;

    // Set PC0 -> output && clear 4-bit for pin-0
    //
    // Explain : 
    //
    // ~(0xF << (4 * 0)) => 0x000
    //
    // Bitwise &= : execute AND(0x0000, 0x0000...0000) (32-bit of CFGLR registers)
    // in this case, that mean clearing last 4-bit.
    GPIOC->CFGLR &= ~(0xF << (4 * 0));


    // GPIO->CFGLR : Configuration Register for LOW-pin
    // Mode Selection : 0x3 - mode for GPIO push-pull
    // Pin Position : (4 * 0) - Pin position in Register [0..3]
    // bitwise OR |= : update config bits for PIN_0 while leaving othe pins unchanged.
    // (0x3 << (4 * 0)) => 0x3 or 0x0000 0011 
    // Then CFGLR will obtain last 2-bits (0x0011) into its value => 0x0000...0011
    GPIOC->CFGLR |= (0x3 << (4 * 0));
}

void loop(){
    while (1)
    {
        // Set PC0 -> HIGH
        GPIOC->BCR = LED_PIN;
        sleep(1000000);

        // Set PC0 -> LOW
        GPIOC->BSHR = LED_PIN;
        sleep(1000000);
    }
    
}

int main(void){
    setup();
    loop();
}
