//
// Created by y on 1/24/21.
//

#include "../include/AES256Mode.h"

void AES256Mode::EncCBC() {

    ByteAVector key_buffer(32, 0);
    ByteAVector plain_buffer;
    ByteAVector cipher_buffer;

    ReadKeyFile(key_dir_, key_buffer);
    file_in.Open();
    file_out.Create();

    file_in.ReadBuffer(plain_buffer);
    AES.Encrypt(plain_buffer, key_buffer, cipher_buffer);
    file_out.WriteBuffer(cipher_buffer);


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
