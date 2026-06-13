#include "oled.h"

void oled_cmd(char i2c, char cmd){
    i2c_start(i2c);
    i2c_address_w(i2c, 0x3C);
    i2c_data_w(i2c, 0x00); // 0x00 = Command mode
    i2c_data_w(i2c, cmd);
    i2c_stop(i2c);
}

// --- ADD THIS MISSING FUNCTION ---
void oled_data(char i2c, char data){
    i2c_start(i2c);
    i2c_address_w(i2c, 0x3C);
    i2c_data_w(i2c, 0x40); // 0x40 = Data mode (PIXELS!)
    i2c_data_w(i2c, data);
    i2c_stop(i2c);
}

void oled_init(char i2c){
    const unsigned char sequence[]={
       0xA8, 0x3F,
       0xD3, 0x00,
       0x40,
       0xA1,
       0xC8,
       0xDA, 0x02,
       0x81, 0x7F,
       0xA4,
       0xA6,
       0xD5, 0x80,
       0x8D, 0x14
    };

    uint32_t len = sizeof(sequence) / sizeof(sequence[0]);
    for(int i = 0; i < len; i++){
        oled_cmd(i2c, sequence[i]);
    }

  
    oled_cmd(i2c, 0xAF); // Display On
}


void oled_pos(char i2c, char Ypos, char Xpos){
oled_cmd(i2c, 0x00+(0x0F & Xpos));
oled_cmd(i2c, 0x10+(0x0F & (Xpos>>4)));
oled_cmd(i2c, 0xB0+(0x0F & Ypos));

}

void oled_blank(char i2c){
int i,j;

for(i=0;i<8;i++){
    oled_pos(i2c,i,0);
    for(j=0;j<128;j++){
oled_data(i2c,0x00);
    }
}
oled_pos(i2c,0,0);
}


void oled_print(char i2c,char str[]){
int i,j;
i=0;
while(str[i]){
    for(j=0;j<5;j++){
oled_data(i2c,FONT[str[i]-32][j]);
    }
  oled_data(i2c,0x00);
    i++;
}
}

void oled_clear_row(char i2c, uint8_t row) {
    oled_pos(i2c, row, 0);
    i2c_start(i2c);
    i2c_address_w(i2c, 0x3C);
    i2c_data_w(i2c, 0x40);        // data mode, then stream all 128 bytes
    for (int i = 0; i < 128; i++) {
        i2c_data_w(i2c, 0x00);
    }
    i2c_stop(i2c);
}

