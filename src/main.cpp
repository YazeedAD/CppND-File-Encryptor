#include <iostream>
#include "../include/AES256.h"

int main(int argc, char **argv) {

    std::string input_dir;
    std::string output_dir;
    std::string key_dir;
    MODE mode;

    try {
    ArgsParser(argc, argv,input_dir,output_dir,key_dir,mode);

    }
    catch(const std::runtime_error& e) {
        std::cout << RED << e.what() << RESET<< std::endl;
    }
    return 0;
}
