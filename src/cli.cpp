//
// Created by y on 1/27/21.
//

#include "../include/cli.h"


using namespace std;

void ArgsParser(int argc, char **argv, string &input_dir, string &output_dir, string &key_dir, MODE &mode) {

    int opt=0;
    bool flag_e = false;
    bool flag_d = false;
    bool flag_i = false;
    bool flag_o = false;
    bool flag_k = false;


    while ((opt = getopt(argc, argv, ":i:o:k:edh")) != -1)
        switch (opt) {
            case 'i':
                if (!boost::filesystem::exists(optarg))
                    throw std::runtime_error("Error opening input file");
                cout << "Input path: " << optarg << endl;
                input_dir = optarg;
                flag_i = true;
                break;
            case 'o':
                cout << "Output path: " << optarg << endl;
                output_dir = optarg;
                flag_o = true;
                break;
            case 'k':
                if (!boost::filesystem::exists(optarg))
                    throw std::runtime_error("Error opening key file");
                cout << "Key path: " << optarg << endl;
                key_dir = optarg;
                flag_k = true;

                break;
            case 'e':
                mode = ENCRYPTION;
                flag_e = true;
                break;
            case 'd':
                mode = DECRYPTION;
                flag_d = true;
                break;
            case 'h':
                Help();
                break;
            case '?':
                printf("Unknown option: %c\n", optopt);
                Usage();
                break;
            case ':':
                printf("Missing arg for %c\n", optopt);
                Usage();
                break;
            default:
                Usage();
        }

    if (flag_e == flag_d)
        throw std::runtime_error("Either -e or -d can be chosen");
    // Redundant flag_e , flag_d condition
    if (!(flag_i && flag_o && flag_k && (flag_e != flag_d))) {
        Usage();
    }

    if (flag_e) {
        cout << "Encryption with CBC-Mode" << endl;
    } else
        cout << "Decryption with CBC-Mode" << endl;
}

void Usage() {
    cout << "Usage: ./FileEncryptor [options]" << endl;
    cout << "Options: " << endl <<
         "-h | --help           Path of the output file" << endl <<
         "-i | --input          Path of the input file" << endl <<
         "-o | --output         Path of the output file" << endl <<
         "-k | --key            Path of the key file" << endl <<
         "                      Key should be a hex text with 16 Bytes length" << endl <<
         "-e | --encryption     Run as an encrypting tool" << endl <<
         "-d | --decryption     Run as a decrypting tool" << endl;

    throw std::runtime_error("Error: usage");

}

void Help() {
    cout << "--------------------------- " << endl;
    cout << "Files Encryptor " << endl;
    cout << "--------------------------- " << endl;
    cout << "A tool used for encrypting/decrypting files using AES-256-CBC " << endl;
    cout << "The IV is randomly generated,the key should be provided by the user " << endl;
    cout << "Usage: ./FileEncryptor [options]" << endl;
    cout << "Options: " << endl <<
         "-h | --help           Path of the output file" << endl <<
         "-i | --input          Path of the input file" << endl <<
         "-o | --output         Path of the output file" << endl <<
         "-k | --key            Path of the key file" << endl <<
         "                      Key should be a hex text with 16 Bytes length" << endl <<
         "-e | --encryption     Run as an encrypting tool" << endl <<
         "-d | --decryption     Run as a decrypting tool" << endl;
    cout << endl << "Note: Verbose mode is not activated" << endl << endl;

    throw std::runtime_error("");
}

// To be used in future
inline bool exists(boost::filesystem::file_status &f) {
    return f.type() != boost::filesystem::status_unknown && f.type() != boost::filesystem::file_not_found;
}
