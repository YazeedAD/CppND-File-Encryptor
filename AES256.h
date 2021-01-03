//
// Created by y on 1/3/21.
//

#ifndef UDACITYCAPSTONE_AES256_AES256_H
#define UDACITYCAPSTONE_AES256_AES256_H

#include <vector>
#include<cstdint>
#include "sbox.h"
#endif //UDACITYCAPSTONE_AES256_AES256_H

#define BLOCK_SIZE 16

class AES256
{
    public:

    void SubByte (uint8_t sub_byte_in, uint8_t &sub_byte_out);
    void ShiftRows (uint8_t shift_rows_in, uint8_t &shift_rows_out);
    void MixColumns (uint8_t mix_columns_in, uint8_t &mix_columns_out);
    void AddRoundKey (uint8_t add_round_key_in, uint8_t &add_round_key_out);
    void Encrypt(uint8_t plain, uint8_t &cipher);
    void Decrypt(uint8_t cipher, uint8_t plain);

private:

    ByteAVector key[BLOCK_SIZE];

};