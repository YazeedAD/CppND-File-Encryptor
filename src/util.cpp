//
// Created by y on 1/22/21.
//

#include "../include/util.h"
#include <cstring>

// TODO: Error handling with length
void ReadKeyFile(const std::string &dir, ByteAVector &key) {

    std::ifstream stream(dir);
    std::string line;
//    std::string key_in;

    if (stream.is_open()) {
        std::getline(stream, line);
//        key_in = line;
        stream.close();

//        auto *k = new unsigned char[16];
//        auto *k = &key[0];
//        std::istringstream key_h(key_in);

        StringToHex(line, &key[0]);

        for (int i = 0; i < 32; i++) {
            std::cout << std::hex << static_cast<int>(key[i]) << ",";

        }

    } else
        throw std::runtime_error("Couldn't open the file");


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