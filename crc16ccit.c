/*
 * Shortened C/C++ implementation of CRC16-CCIT calculating function
 * from the following website: https://srecord.sourceforge.net/crc16-ccitt.html
 *
 * test string “123456789” should be crc = 0xE5CC.
 */

#include <stdio.h>
#include <stdint.h>

#define poly 0x1021 /* crc-ccitt mask */

uint16_t crc16ccit(uint8_t* data, uint16_t data_len){
    uint16_t crc = 0xFFFF;
    uint16_t byte = 0;
    // uint16_t i = 0;
    uint16_t v = 0x80;
    uint16_t xor_flag = 0;
    // while((byte=text[i])!=0)
    for (uint16_t k = 0; k < data_len; k++){
        byte = data[k];
        for (uint16_t i=0; i<8; i++)
        {
            if (crc & 0x8000){
                xor_flag= 1;
            }else{
                xor_flag= 0;
            }
            crc <<= 1;
            if (byte & v){
                crc= crc + 1;
            }
            if (xor_flag){
                crc = crc ^ poly;
            }
            v >>= 1;
        }
        v = 0x80;
    }
    // augment if data is zero length
    xor_flag = 0;
    for (uint16_t i = 0; i < 16; i++){
        if (crc & 0x8000){
            xor_flag= 1;
        }
        else{
            xor_flag= 0;
        }
        crc = crc << 1;
        if (xor_flag){
            crc = crc ^ poly;
        }
    }
    return crc;
}

int main(void){
    printf(
        "Calculated CRC = [%04X], for text = [%s]\r\n",
        crc16ccit(
            (uint8_t*)"123456789",
            sizeof("123456789")-1
        ),
        "123456789"
    );
    return 0;
}
