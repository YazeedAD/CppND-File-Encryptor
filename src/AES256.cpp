//
// Created by y on 1/3/21.
//

#include <stdexcept>
#include <cstring>
#include <iostream>
#include "AES256.h"
#include <memory>

void AES256::SubBytes() {
    std::cout << "SubBytes \n";

    for (auto &i : state) {
        for (unsigned char &j : i) {
            j = s_box[j];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << std::hex << static_cast<int>(state[i][j]) << ",";
        }
        // debug code
        std::cout << std::endl;
    }
}

void AES256::ShiftRows() {
    std::cout << "ShiftRows \n";

    auto temp = new unsigned char[4][4];
    auto *ptr = state;
    int x;
    memcpy(temp, ptr, sizeof(state));

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            x = (j + i) % 4;
            state[i][j] = temp[i][x];
            std::cout << std::hex << static_cast<int>(state[i][j]) << ",";
        }
        // debug code
        std::cout << std::endl;
    }
    delete[] temp;
}

void AES256::MixColumns() {
    std::cout << "MixColumns \n";

    unsigned char temp[4][1];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[j][0] = state[j][i];
        }
        MixMul(temp,i);

    }

    for (auto & i : state) {
        for (unsigned char j : i) {
            std::cout << std::hex << static_cast<int>(j) << ",";
        }
        // debug code
        std::cout << std::endl;
    }

}

void AES256::MixMul(unsigned char state_column[4][1], int column) {
    unsigned char tmp[4];
    tmp[0] = gf_mul2[state_column[0][0]] ^ gf_mul3[state_column[1][0]] ^ state_column[2][0] ^ state_column[3][0];
    tmp[1] = state_column[0][0] ^ gf_mul2[state_column[1][0]] ^ gf_mul3[state_column[2][0]] ^ state_column[3][0];
    tmp[2] = state_column[0][0] ^ state_column[1][0] ^ gf_mul2[state_column[2][0]] ^ gf_mul3[state_column[3][0]];
    tmp[3] = gf_mul3[state_column[0][0]] ^ state_column[1][0] ^ state_column[2][0] ^ gf_mul2[state_column[3][0]];

    for (int i = 0; i < 4; i++) {
        state[i][column] = tmp[i];
    }

}

void AES256::AddRoundKey() {
    std::cout << "AddRoundKey \n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] = state[i][j] ^ key[i][j];
        }
    }
    for (auto & i : state) {
        for (unsigned char j : i) {
            std::cout << std::hex << static_cast<int>(j) << ",";
        }
        // debug code
        std::cout << std::endl;
    }
}

void AES256::Encrypt(const ByteAVector &plain, const ByteAVector &key_in, ByteAVector &cipher) {
    if (plain.size() != BLOCK_SIZE) {
        throw std::runtime_error("Encrypt input size error");
    }
    State(plain, state);
    State(key_in, key);
    AddRoundKey();
    SubBytes();
    ShiftRows();
    MixColumns();
}

void AES256::Decrypt(const ByteAVector &cipher, ByteAVector &plain) {
    if (cipher.size() != BLOCK_SIZE) {
        throw std::runtime_error("Decrypt input size error");
    }
}


void AES256::State(const ByteAVector &input, unsigned char out[4][4]) {
    std::cout << "State \n";

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            out[i][j] = input[i + j * 4];
            // debug code
            std::cout << std::hex << static_cast<int>(out[i][j]) << ",";
        }
        // debug code
        std::cout << std::endl;
    }
    std::cout << std::endl;

}



