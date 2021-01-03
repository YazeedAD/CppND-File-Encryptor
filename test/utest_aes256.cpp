//
// Created by y on 1/3/21.
//

#include <iostream>
#include "../src/AES256.h"
int main() {

    // sbox test
    ByteAVector data_in = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                           0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
    ByteAVector data_out(16,0);

    AES256 AES;

    AES.SubByte(data_in,data_out);

    for (int x : data_out)
        std::cout << "byte: " << std::hex << x << std::endl;
    return 0;
}