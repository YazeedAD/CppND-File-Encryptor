//
// Created by y on 1/24/21.
//

#include "../include/AES256Mode.h"


void AES256Mode::EncCBC() {
    ByteAVector iv(BLOCK_SIZE, 0);
    ByteAVector chaining_buffer(BLOCK_SIZE, 0);
    ByteAVector key_buffer(KEY_SIZE, 0);
    ByteAVector plain_buffer;
    ByteAVector cipher_buffer;
    bool is_padded = false;
    bool need_padding = false;
    int long file_size = 0;

    // Generate random number
    boost::random::random_device rng;
    for (int i=0 ; i<iv.size(); i++) {
        iv[i] = rng();
    }

    std::ifstream file(in_dir_, std::ios::binary | std::ios::ate);
    if (!file.is_open())
        throw std::runtime_error("Error opening cipher file");
    file_size = file.tellg();
    file.close();
    if (file_size <= 0)
        throw std::runtime_error("Error file size");

    if (file_size % BLOCK_SIZE != 0)
        need_padding = true;

    ReadKeyFile(key_dir_, key_buffer);
    file_in.Open();
    file_out.Create();

    file_out.WriteBuffer(iv);
    cipher_buffer = iv;

    while (!file_in.ReadBuffer(plain_buffer)) {
        chaining_buffer = XorBuffers(cipher_buffer, plain_buffer);
        AES.Encrypt(chaining_buffer, key_buffer, cipher_buffer);
        file_out.WriteBuffer(cipher_buffer);
    }

    if (plain_buffer.size() < 16 && need_padding) {
        Padding(plain_buffer);
        chaining_buffer = XorBuffers(cipher_buffer, plain_buffer);
        AES.Encrypt(chaining_buffer, key_buffer, cipher_buffer);
        file_out.WriteBuffer(cipher_buffer);
        is_padded = true;
    }
    if (!is_padded) {
        // pad zeroization
        plain_buffer.clear();
        for (int i = 0; i < BLOCK_SIZE; i++)
            plain_buffer.push_back(0x0);
    }
    PaddingBlock(plain_buffer);
    chaining_buffer = XorBuffers(cipher_buffer, plain_buffer);
    AES.Encrypt(chaining_buffer, key_buffer, cipher_buffer);
    file_out.WriteBuffer(cipher_buffer);

}

void AES256Mode::DecCBC() {
    ByteAVector chaining_buffer(BLOCK_SIZE, 0);
    ByteAVector key_buffer(KEY_SIZE, 0);
    ByteAVector plain_buffer;
    ByteAVector cipher_buffer;
    ByteAVector cipher_chain;
    ByteAVector iv;
    ByteAVector last_block;
    ByteAVector padding_block;
    bool is_padded = true;
    long int blocks = 0;
    int pad_bytes = 0;
    long int file_size = 0;
    bool eof = false;
    std::ifstream file(in_dir_, std::ios::binary | std::ios::ate);

    if (!file.is_open())
        throw std::runtime_error("Error opening cipher file");
    file_size = file.tellg();
    file.close();

    // Check if the file contains at least IV + last_block + padding_block
    if (file_size < (3*BLOCK_SIZE))
        throw std::runtime_error("Error file format");

    if (file_size % BLOCK_SIZE != 0)
        throw std::runtime_error("Error file format");

    ReadKeyFile(key_dir_, key_buffer);
    file_in.Open();
    file_out.Create();

    // read iv
    iv.clear();
    file_in.ReadBuffer(iv);
    if (iv.size() != BLOCK_SIZE)
        throw std::runtime_error("Error reading iv");

    cipher_chain = iv;

    blocks = file_size / BLOCK_SIZE - 1;

    // Read until last_block
    while (!eof && blocks > 2) {
        eof = file_in.ReadBuffer(cipher_buffer);
        AES.Decrypt(cipher_buffer, key_buffer, chaining_buffer);
        plain_buffer = XorBuffers(cipher_chain, chaining_buffer);
        file_out.WriteBuffer(plain_buffer);
        cipher_chain = cipher_buffer;
        blocks--;
    }

    if (eof)
        throw std::runtime_error("Error reading file");

    if (file_in.ReadBuffer(cipher_buffer))
        throw std::runtime_error("Error reading last_block");


    AES.Decrypt(cipher_buffer, key_buffer, chaining_buffer);
    last_block = XorBuffers(cipher_chain, chaining_buffer);
    cipher_chain = cipher_buffer;

    if (file_in.ReadBuffer(cipher_buffer))
        throw std::runtime_error("Error reading padding_block");

    AES.Decrypt(cipher_buffer, key_buffer, chaining_buffer);
    padding_block = XorBuffers(cipher_chain, chaining_buffer);

    if (padding_block[0] == 0) {
        // is_padded used for readability reason (avoiding if else)
        is_padded = false;
        plain_buffer = last_block;
    }

    if (is_padded) {
        if (padding_block[0] != last_block[15])
            throw std::runtime_error("file has been modified!");
        plain_buffer.clear();
        pad_bytes = int(padding_block[0]);
        for (int i = 0; i < (16 - pad_bytes); i++)
            plain_buffer.push_back(last_block[i]);
    }

    file_out.WriteBufferPad(plain_buffer);

}
