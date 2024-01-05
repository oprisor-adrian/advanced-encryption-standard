![Linux Compatible](https://img.shields.io/badge/Linux-Compatible-brightgreen.svg)
![GitHub License](https://img.shields.io/github/license/oprisor-adrian/advanced-encryption-standard)
![GitHub tag (with filter)](https://img.shields.io/github/v/tag/oprisor-adrian/advanced-encryption-standard)

## Advanced Encryption Standard
C++ implementation of the Rijndael block cipher.

## Disclaimer
This approach isn't meant for production use. Be aware of bugs and security risks.

## Usage
The AES block cipher implementation uses the `ByteUtils` library which is required to build and use the cipher. Please refer to the [byte-utilities repository](https://github.com/oprisor-adrian/byte-utilities.git) for more information about the library installation steps.
```c++
plain_text = "00112233445566778899aabbccddeeff";
key = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
Cryptography::AES aes;
cipher_text = aes.Encrypt(plain_test, key);
```

## Acknowledgments
This project utilizes the Google Test (GTest) framework for testing purposes. Please refer to the [GTest documentation](https://google.github.io/googletest/) for more information on its usage and licensing terms.

[ Documentation ]\
[Advanced Encryption Standard (AES)](https://doi.org/10.6028/NIST.FIPS.197-upd1)