# File Encryptor Project
This is a capstone project for [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). 
It's is a file encryption tool based on [Advanced Encryption Standard (AES)](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard) algorithm, it takes an input file and encrypt/decrypt it with a provided key by the user.


## Overview
The tool is using [AES-256](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard) with [CBC](https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Cipher_block_chaining_(CBC)) mode of operation to encrypt/decrypt input files. 
The implementation of AES is based on [FIPS-197](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf) provided by [NIST](https://www.nist.gov/).

The key length is 256-bit provided by the user as a text file with 32 hex characters in string form. 
The [IV](https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Initialization_vector_(IV)) for the [CBC](https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Cipher_block_chaining_(CBC)) is randomly generated during encryption and written as header at the output file. 
Padding is preformed for the input file with [PKCS#7](https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS#5_and_PKCS#7) as specified in [RFC 2315](https://www.ietf.org/rfc/rfc2315.txt).

The implementation was tested against teh test vectors provided by NIST at FIPS-197, and using [cryptool](https://www.cryptool.org/en/cto/highlights/aes-step-by-step) for more verification.
 

#### Disclaimer:
This project is intended for educational purpose only,  it doesn't guarantee the security or the reliability of the output files. 
Don't use it for any sensitive data or system, for that kind of usage it's recommended to use well tested libraries such as openssl or crpto++.
 


## Dependencies
The tool supports only Linux (for Mac it's not tested)
* cmake >= 3.16
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux)
  * Linux: make is installed by default on most Linux distros
* gcc/g++ >= 7.4.0
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same instructions as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
* boost >= 1.71.0
  * Linux: using apt   
``sudo apt-get install libboost-all-dev``


##Build Instructions
1- Clone this repo  
2- Build with cmake
````
$ cd FileEncryptor_cpp/
$ mkdir build
$ cd build/
$ cmake ../
$ make
````
3- Run the executable ```./FileEncryptor -h``` to know how to use 
##Usage
#### Encryption
````
./FileEncryptor -i [input] -o [output] -k [key] -e
````
#### Decryption
````
./FileEncryptor -i [input] -o [output] -k [key] -d
````
#### Parameters
````
         -i | --input          Path of the input file
         -o | --output         Path of the output file
         -k | --key            Path of the key file
         -e | --encryption     Run as an encrypting tool
         -d | --decryption     Run as a decrypting tool
         -h | --help           Help message
````
#### Example
````
./FileEncryptor -i ../test/plain -o ../test/cipher -k ../test/key -e
````
## Project Structure
The program encrypts any file regardless of its type or extension and create an output file which contains the cipher output and the used IV.
The user should provide the the input file path, the output file path, the key path and the argument for either encryption or decryption mode.  
The key format should be 32 byte hex-written string as in the provided key file at ``FileEncryptor_cpp/test/key``.

### Block Diagram


##  Rubric Points
| Criteria | Note | Location |
|---|---|---|
| TThe project demonstrates an understanding of C++ functions and control structures. |Achieved throughout many places in the source code  |All|
| The project reads data from a file and process the data, or the program writes data to a file. | The project preforms reading/writing and data processing on files. ``util.cpp`` provides ``InputFile`` and ``OutputFile`` and other methods like ``ReadKeyFile`` that implement file operations. Data processing is done in``EncCBC`` at ``AES256MODE.cpp``  | ``util.cpp``   ``AES256MODE.cpp`` |
|The project accepts user input and processes the input.|4 arguments are accepted as a user input to the program, and then processed in ``ArgsParser``|``cli.cpp``|
| The project uses Object Oriented Programming techniques | Classes ``AES256``, ``AES256Mode``, ``InputFile`` and ``OutputFile`` are implemented in the design   | ``AES256.h``  ``AES256MODE.h``  ``util.h``
| Classes use appropriate access specifiers for class members | Achieved all over the classes |``AES256.h``  ``AES256MODE.h``  ``util.h``|
|Class constructors utilize member initialization lists.| A constructor is used whenever needed e.g. ``AES256Mode``, ``InputFile`` and ``OutputFile`` |``AES256MODE.h``  ``util.h``|
| Classes abstract implementation details from their interfaces |   Achieved all over the classes |``AES256.h``  ``AES256MODE.h``  ``util.h``|
|Classes encapsulate behavior| Private variables and functions are used in all classes |``AES256.h``  ``AES256MODE.h``  ``util.h``|                                                              
|The project makes use of references in function declarations.|All over the code, e.g. ``AES256::Encrypt``|All|


## Future Work
- Support more modes (CTR,CFB,GCM)
- Provide authentication and integrity 