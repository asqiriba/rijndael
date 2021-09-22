# A C++ Implementation of the Rijndael Encryption/Decryption

Rijndael (pronounced *rain-dahl*) is the block cipher algorithm that has been selected by the U.S. National Institute of Standards and Technology (NIST) as the candidate for the Advanced Encryption Standard (AES). It was selected by contest from a list of five finalists, that were themselves selected from an original list of more than 15 submissions. Rijndael will begin to supplant the Data Encryption Standard (DES) - and later Triple DES - over the next few years in many cryptography applications. The algorithm was designed by two Belgian cryptologists, Vincent Rijmen and Joan Daemen, whose surnames are reflected in the cipher's name. Rijndael has its origins in Square, an earlier collaboration between the two cryptologists.

The cipher has a variable block length and key length. The authors currently specify how to use keys with a length of 128, 192 or 256 bits, to encrypt blocks with a length of 128, 192 or 256 bits (all nine combinations of key length and block length are possible). Both block length and key length can be extended very easily to multiples of 32 bits. Documentation and complete specification of the method (as required by NIST) can be found here.

Rijndael can be implemented very efficiently on a wide range of processors and in hardware. This C++ implementation presented here is based on the Java implementation used with the Cryptix toolkit found on the Internet here (Java code authors are Raif S. Naffah and Paulo S.L.M. Barreto). This implementation was tested against KAT test published by the authors of the method and the results were identical.

||
|---|
|The public user interface of the `CRijndael.cpp` class|
|The `MakeKey()` function is used to expand a user-supplied key material into a session key and to initialize the chain block. The `keylength` and `blockSize` can be any combination of 16, 24 or 32 bytes sizes with `DEFAULT_BLOCK_SIZE` being 16. This function has to be called after construction before any other functions.|
|The `EncryptBlock()` function is used to encrypt a block of the specified size using the specified key.|
|The `DecryptBlock()` function is the reverse of the `EncryptBlock()` function and is used to decrypt a block of the specified size using the specified key.|
|The `Encrypt()` function is used to encrypt larger blocks of data. The block size has to be a multiple of the method's block size. This function can operate in the following modes: `ECB`, `CBC` or `CFB`. `ECB` mode is not using chaining. If the same block is encrypted twice with the same key, the resulting ciphertext blocks are the same. In `CBC` mode, a ciphertext block is obtained by first XORing the plaintext block with the previous ciphertext block, and encrypting the resulting value. In `CFB` mode, a ciphertext block is obtained by encrypting the previous ciphertext block and XORing the resulting value with the plaintext. The operation mode is specified in the iMode parameter with `ECB` being the default value.|
|The `Decrypt()` function is the reverse of the `Encrypt()` function.|
||

## Use Examples
The use of `CRijndael` class is very easy. In the first code snippet example, a block and key size of 16 bytes are applied to a 16 bytes block. The initial chain block is a null block. The block "`aaaaaaaabbbbbbbb`" is encrypted and then decrypted back.

```cpp
try
{
  char szHex[33];

  //Initialization
  CRijndael oRijndael;
  oRijndael.MakeKey("abcdefghabcdefgh", CRijndael::sm_chain0, 16, 16);

  char szDataIn[] = "aaaaaaaabbbbbbbb";
  char szDataOut[17] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

  //Encryption
  oRijndael.EncryptBlock(szDataIn, szDataOut);

  CharStr2HexStr((unsigned char*)szDataIn, szHex, 16);
  cout << szHex << endl;
  CharStr2HexStr((unsigned char*)szDataOut, szHex, 16);
  cout << szHex << endl;
  memset(szDataIn, 0, 16);

  //Decryption
  oRijndael.DecryptBlock(szDataOut, szDataIn);

  CharStr2HexStr((unsigned char*)szDataIn, szHex, 16);
  cout << szHex << endl;
}
catch(exception& roException)
{
  cout << roException.what() << endl;
}
```

In the next code snippet example, a block and key size of 16 bytes are applied to a larger block of data of size 48 bytes (the block of data size should be a multiple of the block size). The initial chain block is a null block. The block "`ababababccccccccababababccccccccababababcccccccc`" is encrypted and then decrypted back in all the operation modes (`ECB`, `CBC` and `CFB`).

```cpp
try
{
  CRijndael oRijndael;
  oRijndael.MakeKey("1234567890123456", CRijndael::sm_chain0, 16, 16);
  char szDataIn1[49] = "ababababccccccccababababccccccccababababcccccccc";
  char szDataIn[49];
  char szDataOut[49];
  memset(szDataIn, 0, 49);
  memset(szDataOut, 0, 49);

  //Test ECB
  strcpy(szDataIn, szDataIn1);
  memset(szDataOut, 0, 49);
  oRijndael.Encrypt(szDataIn, szDataOut, 48, CRijndael::ECB);
  memset(szDataIn, 0, 49);
  oRijndael.Decrypt(szDataOut, szDataIn, 48, CRijndael::ECB);

  //Test CBC
  oRijndael.ResetChain();
  strcpy(szDataIn, szDataIn1);
  memset(szDataOut, 0, 49);
  oRijndael.Encrypt(szDataIn, szDataOut, 48, CRijndael::CBC);
  memset(szDataIn, 0, 49);
  oRijndael.ResetChain();
  oRijndael.Decrypt(szDataOut, szDataIn, 48, CRijndael::CBC);

  //Test CFB
  oRijndael.ResetChain();
  strcpy(szDataIn, szDataIn1);
  memset(szDataOut, 0, 49);
  oRijndael.Encrypt(szDataIn, szDataOut, 48, CRijndael::CFB);
  memset(szDataIn, 0, 49);
  oRijndael.ResetChain();
  oRijndael.Decrypt(szDataOut, szDataIn, 48, CRijndael::CFB);
}
catch(exception& roException)
{
  cout << "Exception: " << roException.what() << endl;
}
```

## License
This article, along with any associated source code and files, is licensed under **The Microsoft Public License (Ms-PL)**.
#### <div style="text-align: right"> Credits: George Anescu </div>