//
// Created by y on 1/3/21.
//


#include "../include/AES256.h"


void AES256::SubBytes() {
    for (auto &i : state) {
        for (unsigned char &j : i) {
            j = s_box[j];
        }
    }

}

void AES256::ShiftRows() {
    auto temp = new unsigned char STATE_SIZE;
    auto *ptr = state;
    int x=0;

    // TODO: To be changed (Legacy Function)
    memcpy(temp, ptr, sizeof(state));

    for (int i = 0; i < STATE_ROW_SIZE; i++) {
        for (int j = 0; j < STATE_COLUMN_SIZE; j++) {
            x = (j + i) % STATE_COLUMN_SIZE;
            state[i][j] = temp[i][x];
        }

    }
    delete[] temp;
}

void AES256::MixColumns() {
    unsigned char temp[WORD_SIZE][1];

    for (int i = 0; i < STATE_COLUMN_SIZE; i++) {
        for (int j = 0; j < STATE_ROW_SIZE; j++) {
            temp[j][0] = state[j][i];
        }
        MixMul(temp, i);

    }


}

void AES256::MixMul(unsigned char state_column[WORD_SIZE][1], int column) {
    unsigned char tmp[WORD_SIZE];

    tmp[0] = gf_mul2[state_column[0][0]] ^ gf_mul3[state_column[1][0]] ^ state_column[2][0] ^ state_column[3][0];
    tmp[1] = state_column[0][0] ^ gf_mul2[state_column[1][0]] ^ gf_mul3[state_column[2][0]] ^ state_column[3][0];
    tmp[2] = state_column[0][0] ^ state_column[1][0] ^ gf_mul2[state_column[2][0]] ^ gf_mul3[state_column[3][0]];
    tmp[3] = gf_mul3[state_column[0][0]] ^ state_column[1][0] ^ state_column[2][0] ^ gf_mul2[state_column[3][0]];

    for (int i = 0; i < STATE_ROW_SIZE; i++) {
        state[i][column] = tmp[i];
    }

}

void AES256::AddRoundKey() {
    for (int i = 0; i < STATE_ROW_SIZE; i++) {
        for (int j = 0; j < STATE_COLUMN_SIZE; j++) {
            state[i][j] = state[i][j] ^ key[i][j];
        }
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
    for (int i = 1; i < NUMBER_OF_ROUNDS; i++) {
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

    State2Block(cipher);
}


void AES256::InvSubBytes() {
    for (auto &i : state) {
        for (unsigned char &j : i) {
            j = s_box_inv[j];
        }
    }
}

void AES256::InvShiftRows() {
    auto temp = new unsigned char STATE_SIZE;
    auto *ptr = state;
    int x=0;

    memcpy(temp, ptr, sizeof(state));

    for (int i = 0; i < STATE_ROW_SIZE; i++) {
        for (int j = 0; j < STATE_COLUMN_SIZE; j++) {
            x = ((4 - i + j) % 4);
            state[i][j] = temp[i][x];
        }
    }
    delete[] temp;
}

void AES256::InvMixColumns() {
    unsigned char temp[WORD_SIZE][1];

    for (int i = 0; i < STATE_COLUMN_SIZE; i++) {
        for (int j = 0; j < STATE_ROW_SIZE; j++) {
            temp[j][0] = state[j][i];
        }
        InvMixMul(temp, i);
    }
}

void AES256::InvMixMul(unsigned char state_column[WORD_SIZE][1], int column) {
    unsigned char tmp[4];

    tmp[0] = gf_mul14[state_column[0][0]] ^ gf_mul11[state_column[1][0]] ^ gf_mul13[state_column[2][0]] ^ gf_mul9[state_column[3][0]];
    tmp[1] = gf_mul9[state_column[0][0]] ^ gf_mul14[state_column[1][0]] ^ gf_mul11[state_column[2][0]] ^ gf_mul13[state_column[3][0]];
    tmp[2] = gf_mul13[state_column[0][0]] ^ gf_mul9[state_column[1][0]] ^ gf_mul14[state_column[2][0]] ^ gf_mul11[state_column[3][0]];
    tmp[3] = gf_mul11[state_column[0][0]] ^ gf_mul13[state_column[1][0]] ^ gf_mul9[state_column[2][0]] ^ gf_mul14[state_column[3][0]];
    for (int i = 0; i < STATE_ROW_SIZE; i++) {
        state[i][column] = tmp[i];
    }

}


void AES256::Decrypt(const ByteAVector &cipher, const ByteAVector &key_in, ByteAVector &plain) {
    if (cipher.size() != BLOCK_SIZE) {
        throw std::runtime_error("Decrypt input size error");
    }
    KeyExpansion(key_in);
    State(cipher, state);

    KeyState(14);
    // Pre-round
    AddRoundKey();

    // Rounds iteration
    for (int i = 1; i < NUMBER_OF_ROUNDS; i++) {

        KeyState(NUMBER_OF_ROUNDS - i);
        InvShiftRows();
        InvSubBytes();
        AddRoundKey();
        InvMixColumns();
    }
    // Last round (no mix column)
    KeyState(0);
    InvShiftRows();
    InvSubBytes();
    AddRoundKey();
    State2Block(plain);
}


void AES256::State(const ByteAVector &input, unsigned char out STATE_SIZE) {
    for (int i = 0; i < STATE_ROW_SIZE; i++) {
        for (int j = 0; j < STATE_COLUMN_SIZE; j++) {
            out[i][j] = input[i + j * WORD_SIZE];
        }
    }
}

void AES256::KeyState(int round) {
    for (int i = 0; i < STATE_ROW_SIZE; i++) {
        for (int j = 0; j < STATE_COLUMN_SIZE; j++) {
            key[i][j] = round_key[round][i + j * WORD_SIZE];
        }
    }
}

void AES256::KeyExpansion(const ByteAVector &key_in) {
    unsigned char temp_word[WORD_SIZE];

    // Initial round key
    for (int i = 0; i < BLOCK_SIZE; i++) {
        round_key[0][i] = key_in[i];
    }

    for (int i = 0; i < BLOCK_SIZE; i++) {
        round_key[1][i] = key_in[BLOCK_SIZE + i];
    }

    for (int i = 2; i < NUMBER_OF_ROUNDS_KEYS; i++) {
        WordKeyExpansion(temp_word, i);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (j < WORD_SIZE)
                round_key[i][j] = round_key[i - 2][j] ^ temp_word[j % WORD_SIZE];
            else
                round_key[i][j] = round_key[i - 2][j] ^ round_key[i][j - WORD_SIZE];
        }
    }
}

void AES256::WordKeyExpansion(unsigned char temp_word[WORD_SIZE], int round) {
    // Check even or odd round
    if (round % 2 == 0) {
        RotWord(temp_word, round);
        SubWord(temp_word, round);
        Rcon(temp_word, round);
    } else {
        for (int i = 0; i < WORD_SIZE; i++) {
            temp_word[i] = round_key[round - 1][12 + i];
        }
        SubWord(temp_word, round);
    }
}


void AES256::RotWord(unsigned char *temp_word, int round) {
    int k=0;

    for (int i = 0; i < 4; i++) {
        if (i < 3)
            k = (i + 13);
        else
            k = 12;
        temp_word[i] = round_key[round - 1][k];
    }
}

void AES256::SubWord(unsigned char *temp_word, int round) {
    for (int i = 0; i < WORD_SIZE; i++) {
        temp_word[i] = s_box[temp_word[i]];
    }
}

void AES256::Rcon(unsigned char *temp_word, int round) {
    temp_word[0] ^= rcon[round / 2];
}

void AES256::PrintState() {
    for (int i = 0; i < STATE_ROW_SIZE; i++) {
        for (int j = 0; j < STATE_COLUMN_SIZE; j++) {
            std::cout << std::hex << static_cast<int>(state[j][i]) << ",";
        }
    }
    std::cout << std::endl;

}

void AES256::State2Block(ByteAVector &block) {
    int k=0;
    block.clear();
    for (int i=0; i < STATE_ROW_SIZE; i++) {
        for (int j = 0; j < STATE_COLUMN_SIZE; j++){
            block.push_back(state[j][i]);
        }
    }
}







