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


void ReadInputFile(const std::string &dir, ByteAVector &input){
    std::ifstream stream(dir, std::ios::binary );
    int size;
    if (!stream.is_open())
        throw std::runtime_error("Error opening file");

    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(stream), {});
    stream.close();

    size = buffer.size();
    for (auto i : buffer)
        std::cout << std::hex << static_cast<int>(i) << ",";
    std::cout << std::endl;
    std::cout << std::dec << size;
}

void CreateOutputFile(const std::string &dir) {
    std::ofstream file;
    file.open(dir);
    if(!file.is_open())
        throw std::runtime_error("Error opening file");
    file.close();

    // TODO: Remove file after errors
}

void WriteOutputFile(const std::string &dir, ByteAVector &input){
    std::ifstream file(dir);
    if(!file.is_open())
        throw std::runtime_error("Error opening file");
    file.close();

    std::ofstream stream(dir,std::ios::app );

    for (auto i: input)
        stream.write(reinterpret_cast<char*>(&i), sizeof(i));
    stream.close();
}

void StringToHex(const std::string &str, unsigned char *out) {
    // dummy variable just to check char value
    bool is_hex;
    int len = str.length();
    if (len != 64)
        throw std::invalid_argument("Invalid input size");

    for (int i = 0; i < len; i += 2) {
        is_hex = CharHexCheck(str[i]);
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


