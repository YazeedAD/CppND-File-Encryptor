//
// Created by y on 1/3/21.
//

#ifndef UDACITYCAPSTONE_AES256_AES256_H
#define UDACITYCAPSTONE_AES256_AES256_H

#include <vector>
#include<cstdint>
#include "sbox.h"
#endif //UDACITYCAPSTONE_AES256_AES256_H

#define KEY_SIZE 16
#define BLOCK_SIZE 16

class AES256
{
    public:

    void SubByte (const ByteAVector& sub_byte_in, ByteAVector &sub_byte_out);
    void ShiftRows (const ByteAVector& shift_rows_in, ByteAVector &shift_rows_out);
    void MixColumns (const ByteAVector& mix_columns_in, ByteAVector &mix_columns_out);
    void AddRoundKey (const ByteAVector& add_round_key_in, ByteAVector &add_round_key_out);
    void Encrypt(const ByteAVector& plain, ByteAVector &cipher);
    void Decrypt(const ByteAVector& cipher, ByteAVector &plain);

private:

    ByteAVector key[KEY_SIZE];

};