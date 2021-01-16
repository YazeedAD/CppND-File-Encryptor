//
// Created by y on 1/3/21.
//

#include <iostream>
#include "../src/AES256.h"

int main() {

    // sbox test
    ByteAVector data_in = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d,
                           0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};

//    ByteAVector key_in = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
//                          0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

    ByteAVector key_in =  {0x60, 0x3d , 0xeb , 0x10 , 0x15 , 0xca , 0x71 , 0xbe , 0x2b , 0x73 , 0xae , 0xf0 , 0x85 , 0x7d , 0x77 , 0x81 , 0x1f , 0x35 , 0x2c , 0x07 , 0x3b , 0x61 , 0x08 , 0xd7 , 0x2d , 0x98 , 0x10 , 0xa3 , 0x09 , 0x14 , 0xdf , 0xf4};
    unsigned char out[4][4];
    AES256 AES256AES;

    AES256AES.Encrypt(data_in, key_in, data_in);



    return 0;
}