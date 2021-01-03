//
// Created by y on 1/3/21.
//

#include <stdexcept>
#include "AES256.h"


void AES256::SubByte(const ByteAVector& sub_byte_in, ByteAVector &sub_byte_out) {
    if (sub_byte_in.size() != BLOCK_SIZE)
    {
        throw std::runtime_error("SubByte input size error");
    }
    for(int i =0 ; i< sub_byte_in.size() ; i++)
    {
        sub_byte_out[i] = s_box[sub_byte_in[i]];
    }
}

void AES256::ShiftRows(const ByteAVector& shift_rows_in, ByteAVector &shift_rows_out) {
    if (shift_rows_in.size() != BLOCK_SIZE)
    {
        throw std::runtime_error("ShiftRows input size error");
    }
}

void AES256::MixColumns(const ByteAVector& mix_columns_in, ByteAVector &mix_columns_out) {
    if (mix_columns_in.size() != BLOCK_SIZE)
    {
        throw std::runtime_error("MixColumns input size error");
    }
}

void AES256::AddRoundKey(const ByteAVector& add_round_key_in, ByteAVector &add_round_key_out) {
    if (add_round_key_in.size() != BLOCK_SIZE)
    {
        throw std::runtime_error("AddRoundKey input size error");
    }
}

void AES256::Encrypt(const ByteAVector& plain, ByteAVector &cipher) {
    if (plain.size() != BLOCK_SIZE)
    {
        throw std::runtime_error("Encrypt input size error");
    }
}

void AES256::Decrypt(const ByteAVector& cipher, ByteAVector &plain) {
    if (cipher.size() != BLOCK_SIZE)
    {
        throw std::runtime_error("Decrypt input size error");
    }
}



