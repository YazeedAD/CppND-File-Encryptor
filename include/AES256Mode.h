//
// Created by y on 1/24/21.
//

#ifndef UDACITYCAPSTONE_AES256_AES256MODE_H
#define UDACITYCAPSTONE_AES256_AES256MODE_H
#include <memory>
#include "AES256.h"
#include "util.h"
#endif //UDACITYCAPSTONE_AES256_AES256MODE_H


class AES256Mode {

public:
    AES256Mode(const std::string &key_dir, const std::string &in_dir,const std::string &out_dir) :file_in(in_dir),file_out(out_dir) {
        this->key_dir_ = key_dir;
        this->in_dir_ = in_dir;
        this->out_dir_ = out_dir;
    }

    void EncCBC();
    void DecCBC();

private:
    std::string key_dir_;
    std::string in_dir_;
    std::string out_dir_;
    InputFile file_in;
    OutputFile file_out;
    AES256 AES;
};


