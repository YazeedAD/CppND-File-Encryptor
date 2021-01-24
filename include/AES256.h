//
// Created by y on 1/3/21.
//

#ifndef UDACITYCAPSTONE_AES256_AES256_H
#define UDACITYCAPSTONE_AES256_AES256_H

#include <vector>
#include<cstdint>
#include "lookup_tables.h"

#endif //UDACITYCAPSTONE_AES256_AES256_H

#define KEY_SIZE 16
#define BLOCK_SIZE 16


class AES256 {

public:
    void State(const ByteAVector &input, unsigned char out[4][4]);

    void KeyState(int round);

    void SubBytes();

    void ShiftRows();

    void MixColumns();

    void MixMul(unsigned char state_column[4][1], int column);

    void AddRoundKey();

    void Encrypt(const ByteAVector &plain, const ByteAVector &key_in, ByteAVector &cipher);

    void InvSubBytes();

    void InvShiftRows();

    void InvMixColumns();

    void InvMixMul(unsigned char state_column[4][1], int column);


    void Decrypt(const ByteAVector &cipher, const ByteAVector &key_in, ByteAVector &plain);

    void KeyExpansion(const ByteAVector &key_in);

    void WordKeyExpansion(unsigned char temp_word[4], int round);

    void RotWord(unsigned char temp_word[4], int round);

    void SubWord(unsigned char temp_word[4], int round);

    void Rcon(unsigned char temp_word[4], int round);

    void PrintState();


private:
    unsigned char state[4][4];
    unsigned char key[4][4];
    unsigned char round_key[14][16];

};

