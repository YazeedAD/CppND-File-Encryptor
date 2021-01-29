//
// Created by y on 1/3/21.
//

#ifndef UDACITYCAPSTONE_AES256_AES256_H
#define UDACITYCAPSTONE_AES256_AES256_H
#include <vector>
#include<cstdint>
#include "lookup_tables.h"
#include "cli.h"
#include <memory>
#define KEY_SIZE 32
#define BLOCK_SIZE 16
#define NUMBER_OF_ROUNDS 14
#define STATE_SIZE [4][4]
#define STATE_ROW_SIZE 4
#define STATE_COLUMN_SIZE 4
#define WORD_SIZE 4
#define NUMBER_OF_ROUNDS_KEYS 15
#endif //UDACITYCAPSTONE_AES256_AES256_H


class AES256 {

public:

    void Encrypt(const ByteAVector &plain, const ByteAVector &key_in, ByteAVector &cipher);
    void Decrypt(const ByteAVector &cipher, const ByteAVector &key_in, ByteAVector &plain);

private:
    unsigned char state STATE_SIZE;
    unsigned char key STATE_SIZE;
    unsigned char round_key[NUMBER_OF_ROUNDS_KEYS][BLOCK_SIZE];

    void State(const ByteAVector &input, unsigned char out STATE_SIZE);
    void KeyState(int round);

    void SubBytes();
    void ShiftRows();
    void MixColumns();
    void MixMul(unsigned char state_column[WORD_SIZE][1], int column);

    void AddRoundKey();

    void InvSubBytes();
    void InvShiftRows();
    void InvMixColumns();
    void InvMixMul(unsigned char state_column[WORD_SIZE][1], int column);

    void KeyExpansion(const ByteAVector &key_in);
    void WordKeyExpansion(unsigned char temp_word[WORD_SIZE], int round);
    void RotWord(unsigned char temp_word[WORD_SIZE], int round);
    void SubWord(unsigned char temp_word[WORD_SIZE], int round);
    void Rcon(unsigned char temp_word[WORD_SIZE], int round);

    void PrintState();
    void State2Block(ByteAVector &block);

};

