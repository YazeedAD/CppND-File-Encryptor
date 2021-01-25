//
// Created by y on 1/24/21.
//

#include "../include/AES256Mode.h"

void AES256Mode::EncCBC() {
    ByteAVector iv(16,0);
    ByteAVector chaining_buffer(16,0);
    ByteAVector key_buffer(32, 0);
    ByteAVector plain_buffer;
    ByteAVector cipher_buffer;

    // IV




    ReadKeyFile("/home/y/UdacityCapstone_AES256/test/iv", iv);

    ReadKeyFile(key_dir_, key_buffer);
    file_in.Open();
    file_out.Create();

//    file_in.ReadBuffer(plain_buffer);
//    chaining_buffer = XorBuffers(iv,plain_buffer);
//    AES.Encrypt(chaining_buffer, key_buffer, cipher_buffer);
//    file_out.WriteBuffer(cipher_buffer);

    while(!file_in.ReadBuffer(plain_buffer)){
        if (plain_buffer.size() < 16)
        {
            Padding(plain_buffer);
            AES.Encrypt(plain_buffer, key_buffer, cipher_buffer);
            file_out.WriteBuffer(cipher_buffer);

            PaddingBlock(plain_buffer);
            AES.Encrypt(plain_buffer, key_buffer, cipher_buffer);
            file_out.WriteBuffer(cipher_buffer);

            break;
        }
        AES.Encrypt(plain_buffer, key_buffer, cipher_buffer);
        file_out.WriteBuffer(cipher_buffer);
    }
//    while(!file_in.ReadBuffer(plain_buffer)){
//        if (plain_buffer.size() < 16)
//        {
//            Padding(plain_buffer);
//            chaining_buffer = XorBuffers(cipher_buffer,plain_buffer);
//            AES.Encrypt(chaining_buffer, key_buffer, cipher_buffer);
//            file_out.WriteBuffer(cipher_buffer);
//
//            PaddingBlock(plain_buffer);
//            AES.Encrypt(chaining_buffer, key_buffer, cipher_buffer);
//            file_out.WriteBuffer(cipher_buffer);
//
//            break;
//        }
//        chaining_buffer = XorBuffers(cipher_buffer,plain_buffer);
//        AES.Encrypt(chaining_buffer, key_buffer, cipher_buffer);
//        file_out.WriteBuffer(cipher_buffer);
//    }

//    while(!file_in.ReadBuffer(plain_buffer)){
//
//        if (plain_buffer.size() != 16)
//            break;
//            //padding
//        AES.Encrypt(plain_buffer,key_buffer,cipher_buffer);
//        file_out.WriteBuffer(cipher_buffer);
//    }


// file close crashes every time
//    file_in->Close();


}

void AES256Mode::DecCBC() {

}
