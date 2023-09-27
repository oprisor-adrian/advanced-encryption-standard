# aes256-cpp-implementation
C++ implementation of the 256-bits Rijndael block cipher (the Advanced Encryption Standard).

#### Usage
```
input = "00112233445566778899aabbccddeeff";
key = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
BlockCihper::AES256 aes256(input, key);
output = aes256.Encrypt();
```

#### Doc
[Advanced Encryption Standard (AES)](extension://efaidnbmnnnibpcajpcglclefindmkaj/https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197-upd1.pdf)