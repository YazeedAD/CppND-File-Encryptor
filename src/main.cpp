#include <iostream>
#include "../include/AES256Mode.h"

int main(int argc, char **argv) {

    std::string input_dir;
    std::string output_dir;
    std::string key_dir;
    MODE mode;

    try {
        ArgsParser(argc, argv, input_dir, output_dir, key_dir, mode);
        if (mode == ENCRYPTION) {
            AES256Mode AESe(key_dir, input_dir, output_dir);
            AESe.EncCBC();
            std::cout << GREEN << "Encrypted file " << output_dir << " is ready " << RESET << std::endl;
        }

        if (mode == DECRYPTION) {
            AES256Mode AESd(key_dir, input_dir, output_dir);
            AESd.DecCBC();
//            std::cout << GREEN << "Decrypted file " << output_dir << " is ready " << RESET << std::endl;

        }


    }
    catch (const std::runtime_error &e) {
        std::cout << RED << e.what() << RESET << std::endl;
    }
    return 0;
}
