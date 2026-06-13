#include "mpu.h"

void mpu6050_write_r(char reg_address, char data_value){
    i2c_start(1);
    i2c_address_w(1,0x68);
  i2c_data_w(1, reg_address);        
    i2c_data_w(1, data_value);       
    i2c_stop(1);
}










void mpu_init(){
    mpu6050_write_r(0x6B,0x00);
    mpu6050_write_r(0x1C, 0x00);
    mpu6050_write_r(0x1B,0x00);
   mpu6050_write_r(0x19, 0x07);
}


void mpu_ac_read(char i2c, int16_t *ax, int16_t *ay, int16_t* az){
    i2c_start(i2c);
    i2c_address_w(i2c, 0x68);
    i2c_data_w(i2c, 0x3B);      // ACCEL_XOUT_H register

    i2c_start(i2c);              // Repeated start
    i2c_address_r(i2c, 0x68);   // Switch to read mode

    char xh = i2c_data_r(i2c, 1);
    char xl = i2c_data_r(i2c, 1);
    char yh = i2c_data_r(i2c, 1);
    char yl = i2c_data_r(i2c, 1);
    char zh = i2c_data_r(i2c, 1);
    char zl = i2c_data_r(i2c, 0);  // NACK on last byte

    i2c_stop(i2c);

    *ax = (int16_t)((xh << 8) | xl);
    *ay = (int16_t)((yh << 8) | yl);
    *az = (int16_t)((zh << 8) | zl);
}

void mpu_gy_read(char i2c,int16_t *gx, int16_t *gy, int16_t* gz){
    char xh, xl, yh, yl, zh, zl;
    i2c_start(i2c);
    i2c_address_w(i2c, 0x68);       
    i2c_data_w(i2c, 0x43);

    i2c_start(i2c);
    i2c_address_r(i2c, 0x68);

xh = i2c_data_r(i2c, 1);          
    xl = i2c_data_r(i2c, 1);          
    yh = i2c_data_r(i2c, 1);          
    yl = i2c_data_r(i2c, 1);         
    zh = i2c_data_r(i2c, 1);          
    zl = i2c_data_r(i2c, 0);          

    i2c_stop(i2c);                    

    
    *gx = (int16_t)((xh << 8) | xl);
    *gy = (int16_t)((yh << 8) | yl);
    *gz = (int16_t)((zh << 8) | zl);

}