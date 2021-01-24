//
// Created by y on 1/22/21.
//

#include "../include/util.h"
#include <cstring>

// TODO: Remove debugging and dead codes

void ReadKeyFile(const std::string &dir, ByteAVector &key) {

    std::ifstream stream(dir);
    std::string line;

    if (!stream.is_open())
        throw std::runtime_error("Error opening file");

    std::getline(stream, line);
    stream.close();
    StringToHex(line, &key[0]);

    for (int i = 0; i < 32; i++) {
        std::cout << std::hex << static_cast<int>(key[i]) << ",";
    }

}


void OutputFile::Create() {
    stream.open(dir);
    if (!stream.is_open())
        throw std::runtime_error("Error creating file");
    stream.close();
}

void OutputFile::WriteBuffer(ByteAVector &input) {
    stream.open(dir, std::ios::app);
    if (!stream.is_open())
        throw std::runtime_error("Error writing file");

    for (auto i: input)
        stream.write(reinterpret_cast<char *>(&i), sizeof(i));
    stream.close();
}
void OutputFile::Close() {

    stream.close();

}
void InputFile::Open() {
    stream.open(dir, std::ios::binary);
    if (!stream.is_open())
        throw std::runtime_error("Error opening file");

}

bool InputFile::ReadBuffer(ByteAVector &input) {

    int size;
    int i = 0;
    auto *temp = new unsigned char;
    bool eof;
    while (!stream.eof() && i < 32) {
        stream.read(reinterpret_cast<char *>(temp), 1);
        if (stream.eof())
            break;
        input.push_back(*temp);
        i++;
    }
    return stream.eof();
}

void InputFile::Close() {

    stream.close();

}

void StringToHex(const std::string &str, unsigned char *out) {

    int len = str.length();
    if (len != 64)
        throw std::invalid_argument("Invalid input size");

    for (int i = 0; i < len; i += 2) {
        CharHexCheck(str[i]);
        sscanf(str.c_str() + i, "%2hhx", out);
        std::cout << std::hex << static_cast<int>(*out) << ",";

        out++;
    }
    std::cout << std::endl;

}


bool CharHexCheck(unsigned char input) {
    if (input >= '0' && input <= '9')
        return true;
    if (input >= 'A' && input <= 'F')
        return true;
    if (input >= 'a' && input <= 'f')
        return true;
    throw std::invalid_argument("Invalid input string");

}


