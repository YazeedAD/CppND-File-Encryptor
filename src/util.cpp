//
// Created by y on 1/22/21.
//

#include "../include/util.h"

void ReadKeyFile(const std::string &dir, ByteAVector &key) {
// key should be 32 size
    std::ifstream stream(dir);
    std::string line;

    if (!stream.is_open())
        throw std::runtime_error("Error opening file");

    std::getline(stream, line);
    stream.close();
    int k = key.size();
    int len = line.length();
    if (len != k * 2)
        throw std::invalid_argument("Error invalid input size");
    StringToHex(line, &key[0]);
}

void OutputFile::Create() {
    stream.open(dir, std::ios::trunc);
    if (!stream.is_open())
        throw std::runtime_error("Error creating file");
    stream.close();
}

void OutputFile::WriteBuffer(ByteAVector &input) {
    stream.open(dir, std::ios::app);
    if (!stream.is_open())
        throw std::runtime_error("Error writing file");
    if (input.size() != BLOCK_SIZE)
        throw std::runtime_error("Error WriteBuffer size");

    for (auto i: input)
        stream.write(reinterpret_cast<char *>(&i), sizeof(i));
    stream.close();
}

void OutputFile::WriteBufferPad(ByteAVector &input) {
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
    int i = 0;
    auto *temp = new unsigned char;

    input.clear();
    while (!stream.eof() && i < BLOCK_SIZE) {
        stream.read(reinterpret_cast<char *>(temp), 1);
        if (stream.eof())
            break;
        input.push_back(*temp);
        i++;
    }
    delete temp;
    return stream.eof();
}

void InputFile::Close() {
    if (stream.is_open())
        stream.close();
}

void StringToHex(const std::string &str, unsigned char *out) {
    int len = str.length();

    for (int i = 0; i < len; i += 2) {
        CharHexCheck(str[i]);
        // TODO: To be changed (Legacy Function)
        sscanf(str.c_str() + i, "%2hhx", out);
        out++;
    }
}

bool CharHexCheck(unsigned char input) {
    if (input >= '0' && input <= '9')
        return true;
    if (input >= 'A' && input <= 'F')
        return true;
    if (input >= 'a' && input <= 'f')
        return true;
    throw std::invalid_argument("Error invalid input string");

}

ByteAVector XorBuffers(ByteAVector &buffer_1, ByteAVector &buffer_2) {
    ByteAVector buffer_out;

    for (int i = 0; i < BLOCK_SIZE; i++) {
        buffer_out.push_back(buffer_1[i] ^ buffer_2[i]);
    }

    return buffer_out;
}

void Padding(ByteAVector &input) {
    int k = 0;
    if (input.size() > BLOCK_SIZE)
        throw std::runtime_error("Error Padding size");
    k = BLOCK_SIZE - input.size();

    while ((16 - input.size()) != 0) {
        input.push_back(k);

    }
}

void PaddingBlock(ByteAVector &input) {
    //  error handling if input is not 16 byte
    if (input.size() != BLOCK_SIZE)
        throw std::runtime_error("Error PaddingBlock size");
    for (int i = 0; i < (BLOCK_SIZE-1); i++)
        input[i] = input[(BLOCK_SIZE-1)];
}
