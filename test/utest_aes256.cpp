//
// Created by y on 1/3/21.
//

#include <iostream>
#include "../include/AES256Mode.h"
//#include "../include/AES256.h"
//#include "../include/util.h"

int main() {

    // sbox test
    ByteAVector plain = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
    };
    ByteAVector cipher;
//
    ByteAVector cipher_in = {0x8e, 0xa2, 0xb7, 0xca, 0x51, 0x67, 0x45, 0xbf, 0xea, 0xfc, 0x49, 0x90, 0x4b, 0x49, 0x60,
                             0x89};
    ByteAVector plain_out;
//    ByteAVector cipher_in = {0x2b,0x60,0xbb,0x54,0x5d,0x88,0x10,0x26};

//    ByteAVector key_in = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
//                          0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

    ByteAVector key_in = {0x11, 0x22, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e,
                          0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d,
                          0x1e, 0x1f

    };

    std::string dir_k = "/home/y/UdacityCapstone_AES256/test/key";
    std::string dir_p = "/home/y/UdacityCapstone_AES256/test/plain";
    std::string dir_po = "/home/y/UdacityCapstone_AES256/test/plain_o";
    std::string dir_c = "/home/y/UdacityCapstone_AES256/test/cipher";

//    unsigned char out[4][4];
//    AES256 AES256AES;
//    ByteAVector key_i(32,0);
//    ReadKeyFile(dir,key_i);
//    AES256AES.Decrypt(cipher_in, key_i, plain_out);

////    ReadKeyFile(dir,key_in);
////    AES256AES.Encrypt(plain, key_in, cipher);
////    ReadInputFile(dir,plain_out);
//
//
//
////    CreateOutputFile(dir);
////    WriteOutputFile(dir,plain);
//
//
//OutputFile of(dir_c);
//of.Create();
//of.WriteBuffer(plain);
//of.WriteBuffer(plain);
//of.Close();

//InputFile i_f(dir_p);
//i_f.Open();
//i_f.ReadBuffer(plain_out);
//
    AES256Mode AESe(dir_k, dir_p,dir_c);
    AESe.EncCBC();

//    AES256Mode AESd(dir_k, dir_c, dir_po);
//    AESd.DecCBC();

    return 0;
}