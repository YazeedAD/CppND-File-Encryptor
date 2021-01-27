//
// Created by y on 1/27/21.
//

#ifndef UDACITYCAPSTONE_AES256_CLI_H
#define UDACITYCAPSTONE_AES256_CLI_H
#include<iostream>
#include <getopt.h>
#include <sys/stat.h>


#endif //UDACITYCAPSTONE_AES256_CLI_H

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */


enum MODE
{
    ENCRYPTION,
    DECRYPTION
};

void Usage();

void ArgsParser(int argc, char **argv, std::string &input_dir, std::string &output_dir, std::string &key_dir, MODE &mode);