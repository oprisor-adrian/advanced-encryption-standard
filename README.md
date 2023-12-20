# aes256-cpp-implementation
C++ implementation of the 256-bits Rijndael block cipher (the Advanced Encryption Standard).

#### Usage
```
input = "00112233445566778899aabbccddeeff";
key = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
BlockCihper::AES aes(key);
output = aes256.Encrypt(input);
```

#### Doc
[Advanced Encryption Standard (AES)](https://doi.org/10.6028/NIST.FIPS.197-upd1)