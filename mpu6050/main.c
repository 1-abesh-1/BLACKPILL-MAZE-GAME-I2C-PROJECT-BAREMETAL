#include "gpio.h"
#include "stm32f411xe.h"
#include <stdint.h>
#include <stdio.h>  // Required for sprintf string formatting
#include "i2c.h"
#include "oled.h"
#include "mpu.h"

#define OLED_ADDR  0x78

// Containers for raw sensor data
int16_t ax, ay, az;
int16_t gx, gy, gz;

// Reliable millisecond delay loop (for default 16MHz internal clock)
void delay_ms(uint32_t ms_count) {
    for (volatile uint32_t ms = 0; ms < ms_count; ms++) {
        for (volatile uint32_t count = 0; count < 1600; count++) {
            __asm__("nop");
        }
    }
}

int main(void) {
    // ----------------------------------------------------------------
    // 1. ENABLE CLOCKS & CONFIG DIAGNOSTIC LED (PC13)
    // ----------------------------------------------------------------
    RCC->AHB1ENR |= (1 << 1);  // Enable GPIOB clock (for I2C1)
    RCC->AHB1ENR |= (1 << 2);  // Enable GPIOC clock (for LED)

    GPIOC->MODER &= ~(3 << 26);
    GPIOC->MODER |=  (1 << 26); // Set PC13 as Output

    // ----------------------------------------------------------------
    // 2. CONFIGURE I2C1 PINS (PB6 = SCL, PB7 = SDA)
    // ----------------------------------------------------------------
    GPIOB->MODER &= ~((3 << 12) | (3 << 14));
    GPIOB->MODER |=  ((2 << 12) | (2 << 14)); // Alternate Function Mode

    GPIOB->OTYPER |= ((1 << 6) | (1 << 7));   // Open-Drain Configuration

    GPIOB->OSPEEDR &= ~((3 << 12) | (3 << 14));
    GPIOB->OSPEEDR |=  ((2 << 12) | (2 << 14)); // High Speed

    GPIOB->PUPDR &= ~((3 << 12) | (3 << 14));
    GPIOB->PUPDR |=  ((1 << 12) | (1 << 14)); // Internal Pull-ups

    GPIOB->AFR[0] &= ~((0xF << 24) | (0xF << 28));
    GPIOB->AFR[0] |=  ((4   << 24) | (4   << 28)); // Map to AF4 (I2C1)

    // ----------------------------------------------------------------
    // 3. HARDWARE INITIALIZATION ENGINE
    // ----------------------------------------------------------------
    i2c_init(1); 
    delay_ms(100); // Let the I2C bus settle down
    // Move OLED first!
oled_init(1);
oled_blank(1);
oled_print(1, "OLED Started!");

delay_ms(1000); 

// Put MPU second
// Blink 3 times = "about to call mpu_init"
for(int i = 0; i < 3; i++){
    GPIOC->ODR ^= (1 << 13);
    delay_ms(200);
}
mpu_init();
// Blink 5 times = "mpu_init returned successfully"  
for(int i = 0; i < 5; i++){
    GPIOC->ODR ^= (1 << 13);
    delay_ms(200);
}

    // Temporary string buffers for text formatting
    char buf1[64]; 
    char buf2[64]; 

    // ----------------------------------------------------------------
    // 4. TELEMETRY STREAM LOOP
    // ----------------------------------------------------------------
while(1) {
    GPIOC->ODR ^= (1 << 13);

    mpu_ac_read(1, &ax, &ay, &az);
    sprintf(buf1, "A:X=%d Y=%d Z=%d", ax, ay, az);

    mpu_gy_read(1, &gx, &gy, &gz);
    sprintf(buf2, "G:X=%d Y=%d Z=%d", gx, gy, gz);

    oled_clear_row(1, 0);    // clear first, then write
    oled_pos(1, 0, 0);
    oled_print(1, buf1);

    oled_clear_row(1, 2);    // clear first, then write
    oled_pos(1, 2, 0);
    oled_print(1, buf2);

    delay_ms(80);
}
}