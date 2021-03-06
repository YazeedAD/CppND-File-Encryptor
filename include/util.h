//
// Created by y on 1/22/21.
//

#ifndef UDACITYCAPSTONE_AES256_UTIL_H
#define UDACITYCAPSTONE_AES256_UTIL_H
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#define BLOCK_SIZE 16
#endif //UDACITYCAPSTONE_AES256_UTIL_H


typedef std::vector<unsigned char> ByteAVector;

class InputFile {

public:
     InputFile(const std::string &dir){
        this->dir = dir;
    }

    void Open();
    bool ReadBuffer(ByteAVector &input);
    void Close();

private:
    std::ifstream stream;
    std::string dir;

};


class OutputFile {

public:
     OutputFile(const std::string &dir){
        this->dir = dir;
    }

    void Create();
    void WriteBuffer(ByteAVector &input);
    void WriteBufferPad(ByteAVector &input);
    void Close();

private:
    std::ofstream stream;
    std::string dir;

};


void ReadKeyFile(const std::string &dir, ByteAVector &key);

void StringToHex(const std::string &inStr, unsigned char *outStr);

bool CharHexCheck(unsigned char input);

void Padding(ByteAVector &input);

void PaddingBlock(ByteAVector &input);

ByteAVector XorBuffers(ByteAVector &buffer_1, ByteAVector &buffer_2);



const ByteAVector HEX = //This is the ASCII table in number value form
        {   //0     1     2     3     4     5     6    7      8     9     A     B     C     D     E     F
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//0
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//1
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//2
                0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//3
                0x00, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//4
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//5
                0x00, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//6
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 //7
        };