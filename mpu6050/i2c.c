#include "i2c.h"

void i2c_init(char i2c){

  RCC->APB1ENR |=(0b1<<(20+i2c));

   for(volatile int i = 0; i < 100; i++);
    if(i2c==1){
  I2C1->CR1 |= (1 << 15); 
I2C1->CR1 &= ~(1 << 15);


    I2C1->CR1 &= ~(0b1);
    I2C1->CR2 &=~(0b111111);
    I2C1->CR2 |=(0b010000);
    I2C1->CCR &=~(0b1<<15);
    I2C1->CCR &=~(0b111111111111);
    I2C1->CCR |= (0b1<<4)|(0b1<<6);
    I2C1->TRISE=(0b10001);
    I2C1->CR1 |= (0b1);
}else if(i2c==2){
  I2C2->CR1 |= (1 << 15); 
I2C2->CR1 &= ~(1 << 15);


    I2C2->CR1 &= ~(0b1);
    I2C2->CR2 &=~(0b111111);
    I2C2->CR2 |=(0b010000);
    I2C2->CCR &=~(0b1<<15);
    I2C2->CCR &=~(0b111111111111);
    I2C2->CCR |= (0b1<<4)|(0b1<<6);
    I2C2->TRISE=(0b10001);
    I2C2->CR1 |= (0b1);
}else if(i2c==3){
  
    I2C3->CR1 |= (1 << 15); 
I2C3->CR1 &= ~(1 << 15);


    I2C3->CR1 &= ~(0b1);
    I2C3->CR2 &=~(0b111111);
    I2C3->CR2 |=(0b010000);
    I2C3->CCR &=~(0b1<<15);
    I2C3->CCR &=~(0b111111111111);
    I2C3->CCR |= (0b1<<4)|(0b1<<6);
    I2C3->TRISE=(0b10001);
    I2C3->CR1 |= (0b1);
}
}






void i2c_start(char i2c){ 
    if(i2c==1){
        I2C1->CR1 |=(0b1<<8);
        
        
    while (!(I2C1->SR1 & (1 << 0)));
    }else if(i2c==2){
 
        I2C2->CR1 |=(0b1<<8);
        
        
    while (!(I2C2->SR1 & (1 << 0)));
    
    }else if(i2c==3){
        
        I2C3->CR1 |=(0b1<<8);
        
        
    while (!(I2C3->SR1 & (1 << 0)));

    }
}


void i2c_address_w(char i2c,char adr){
if(i2c==1){
I2C1->DR =(adr<<1);

while(!(I2C1->SR1 & (1<<1))){};
uint32_t temp = I2C1->SR1;
temp=I2C1->SR2;
(void)temp;

}else if(i2c==2){
I2C2->DR =(adr<<1);

while(!(I2C2->SR1 & (1<<1))){};
uint32_t temp = I2C2->SR1;
temp=I2C2->SR2;
(void)temp;

}else if(i2c==3){
I2C3->DR =(adr<<1);

while(!(I2C3->SR1 & (1<<1))){};
uint32_t temp = I2C3->SR1;
temp=I2C3->SR2;
(void)temp;

}
}


void i2c_data_w(char i2c, char data){
    if(i2c==1){
        I2C1->DR =data;
        while(!(I2C1->SR1 & (0b1<<7))){};
    }else  if(i2c==2){
        I2C2->DR =data;
        while(!(I2C2->SR1 & (0b1<<7))){};
    }else  if(i2c==3){
        I2C3->DR =data;
        while(!(I2C3->SR1 & (0b1<<7))){};
    }
}

void i2c_stop(char i2c){
    if(i2c==1){
        I2C1->CR1 |= (1<<9);          // issue STOP immediately
        while(I2C1->CR1 & (1<<9));    // wait until hardware clears it
    }else if(i2c==2){
        I2C2->CR1 |= (1<<9);
        while(I2C2->CR1 & (1<<9));
    }else if(i2c==3){
        I2C3->CR1 |= (1<<9);
        while(I2C3->CR1 & (1<<9));
    }
}



void i2c_address_r(char i2c, char address) {
    I2C1->DR = (address << 1) | 1;
    while(!(I2C1->SR1 & (1<<1)));
    
    // SET ACK before clearing ADDR so first byte is handled correctly
    I2C1->CR1 |= (1 << 10);
    
    uint32_t temp = I2C1->SR1;
    temp = I2C1->SR2;   // This clears ADDR and starts the first byte clocking in
    (void)temp;
}



int8_t i2c_data_r(char i2c, char ack_option) {
    if (ack_option == 0) {
        I2C1->CR1 &= ~(1 << 10);  // NACK — signal end after this byte
    }
    while (!(I2C1->SR1 & (1 << 6)));
    return (int8_t)I2C1->DR;
}