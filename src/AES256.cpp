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
        MixMul(temp, i);

    }

    for (auto &i : state) {
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
    for (auto &i : state) {
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
    KeyExpansion(key_in);
    State(plain, state);
    KeyState(0);

    // Pre-round
    AddRoundKey();

    // Rounds iteration
    for (int i = 1; i < 14; i++) {
        KeyState(i);
        SubBytes();
        ShiftRows();
        MixColumns();
        AddRoundKey();

    }
    // Last round (no mix column)
    KeyState(14);
    SubBytes();
    ShiftRows();
    AddRoundKey();

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
        }
    }
}

void AES256::KeyState(int round) {

    std::cout << "Round :  "<< round <<"\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            key[i][j] = round_key[round][i + j * 4];
        }
    }
}

void AES256::KeyExpansion(const ByteAVector &key_in) {

    unsigned char temp_word[4];

    // Initial round key
    for (int i = 0; i < 16; i++) {
        round_key[0][i] = key_in[i];
        std::cout << std::hex << static_cast<int>(round_key[0][i]) << ",";

    }
    std::cout << std::endl;

    for (int i = 0; i < 16; i++) {
        round_key[1][i] = key_in[16 + i];
        std::cout << std::hex << static_cast<int>(round_key[1][i]) << ",";


    }
    std::cout << std::endl;


    for (int i = 2; i < 15; i++) {
        WordKeyExpansion(temp_word, i);
        std::cout << "Key: " << i << std::endl;

        for (int j = 0; j < 16; j++) {
            if (j < 4)
                round_key[i][j] = round_key[i - 2][j] ^ temp_word[j % 4];
            else
                round_key[i][j] = round_key[i - 2][j] ^ round_key[i][j - 4];

            std::cout << std::hex << static_cast<int>(round_key[i][j]) << ",";

        }
        std::cout << std::endl;

    }

}

void AES256::WordKeyExpansion(unsigned char temp_word[4], int round) {

    if (round % 2 == 0) {
        RotWord(temp_word, round);
        for (int i = 0; i < 4; i++)
            std::cout << std::hex << static_cast<int>(temp_word[i]) << ",";
        std::cout << std::endl;
        SubWord(temp_word, round);
        for (int i = 0; i < 4; i++)
            std::cout << std::hex << static_cast<int>(temp_word[i]) << ",";
        std::cout << std::endl;

        Rcon(temp_word, round);
    } else {
        for (int i = 0; i < 4; i++) {
            temp_word[i] = round_key[round - 1][12 + i];
        }
        for (int i = 0; i < 4; i++)
            std::cout << std::hex << static_cast<int>(temp_word[i]) << ",";
        std::cout << std::endl;

        SubWord(temp_word, round);
    }
}


void AES256::RotWord(unsigned char *temp_word, int round) {
    int k;
    for (int i = 0; i < 4; i++) {
        if (i < 3)
            k = (i + 13);
        else
            k = 12;
        temp_word[i] = round_key[round - 1][k];
    }
}

void AES256::SubWord(unsigned char *temp_word, int round) {
    for (int i = 0; i < 4; i++) {
        temp_word[i] = s_box[temp_word[i]];
    }
}

void AES256::Rcon(unsigned char *temp_word, int round) {
    temp_word[0] ^= rcon[round / 2];
}





