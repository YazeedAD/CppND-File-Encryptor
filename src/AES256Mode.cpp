//
// Created by y on 1/24/21.
//

#include "../include/AES256Mode.h"

void AES256Mode::EncCBC() {
    ByteAVector iv(16, 0);
    ByteAVector chaining_buffer(16, 0);
    ByteAVector key_buffer(32, 0);
    ByteAVector plain_buffer;
    ByteAVector cipher_buffer;
    bool is_padded = false;
    // IV




    ReadKeyFile("/home/y/UdacityCapstone_AES256/test/iv", iv);

    ReadKeyFile(key_dir_, key_buffer);
    file_in.Open();
    file_out.Create();

    file_out.WriteBuffer(iv);

    file_in.ReadBuffer(plain_buffer);
    chaining_buffer = XorBuffers(iv, plain_buffer);
    AES.Encrypt(chaining_buffer, key_buffer, cipher_buffer);
    file_out.WriteBuffer(cipher_buffer);


    while (!file_in.ReadBuffer(plain_buffer)) {
        if (plain_buffer.size() < 16) {
            Padding(plain_buffer);
            chaining_buffer = XorBuffers(cipher_buffer, plain_buffer);
            AES.Encrypt(chaining_buffer, key_buffer, cipher_buffer);
            file_out.WriteBuffer(cipher_buffer);

            PaddingBlock(plain_buffer);
            chaining_buffer = XorBuffers(cipher_buffer, plain_buffer);
            AES.Encrypt(chaining_buffer, key_buffer, cipher_buffer);
            file_out.WriteBuffer(cipher_buffer);
            is_padded = true;
            break;
        }
        chaining_buffer = XorBuffers(cipher_buffer, plain_buffer);
        AES.Encrypt(chaining_buffer, key_buffer, cipher_buffer);
        file_out.WriteBuffer(cipher_buffer);
    }

    if (!is_padded) {
        // pad zeroization
        plain_buffer.clear();
        for (int i = 0; i < 16; i++)
            plain_buffer.push_back(0x0);

        PaddingBlock(plain_buffer);
        chaining_buffer = XorBuffers(cipher_buffer, plain_buffer);
        AES.Encrypt(chaining_buffer, key_buffer, cipher_buffer);
        file_out.WriteBuffer(cipher_buffer);
    }


}

void AES256Mode::DecCBC() {
    ByteAVector chaining_buffer(16, 0);
    ByteAVector key_buffer(32, 0);
    ByteAVector plain_buffer;
    ByteAVector cipher_buffer;
    ByteAVector cipher_chain;
    ByteAVector iv;
    ByteAVector last_block;
    ByteAVector padding_block;
    bool is_padded = false;
    int blocks =0;
    int pad_bytes =0;

    std::ifstream file( in_dir_, std::ios::binary | std::ios::ate);

    if(!file.is_open())
        throw std::runtime_error("Error opening cipher file");
    long int file_size = file.tellg();
    file.close();
    if (file_size < 48)
        throw std::runtime_error("Error file format");

    if (file_size%16 !=0)
        throw std::runtime_error("Error file format");


    ReadKeyFile(key_dir_, key_buffer);
    file_in.Open();
    file_out.Create();

    iv.clear();
    file_in.ReadBuffer(iv);
    if(iv.size() != 16)
        throw std::runtime_error("Error reading iv");

    AES.Decrypt(cipher_buffer, key_buffer, chaining_buffer);
    plain_buffer = XorBuffers(iv, chaining_buffer);
    file_out.WriteBuffer(plain_buffer);
    cipher_chain = cipher_buffer;
    blocks = file_size/16;

    while(!file_in.ReadBuffer(cipher_buffer) && blocks > 2) {

        AES.Decrypt(cipher_buffer, key_buffer, chaining_buffer);
        plain_buffer = XorBuffers(cipher_chain, chaining_buffer);
        file_out.WriteBuffer(plain_buffer);
        cipher_chain = cipher_buffer;
    }

    if (file_in.ReadBuffer(cipher_buffer))
        throw std::runtime_error("Error reading last_block");


    AES.Decrypt(cipher_buffer, key_buffer, chaining_buffer);
    last_block = XorBuffers(cipher_chain, chaining_buffer);
    cipher_chain = cipher_buffer;

    if (!file_in.ReadBuffer(cipher_buffer))
        throw std::runtime_error("Error reading padding_block");

    AES.Decrypt(cipher_buffer, key_buffer, chaining_buffer);
    padding_block = XorBuffers(cipher_chain, chaining_buffer);
    pad_bytes = int(padding_block[0]);

    for(int i = 0; i<16-pad_bytes; i++)
        plain_buffer[i] = last_block[i];


    file_out.WriteBuffer(plain_buffer);



}
