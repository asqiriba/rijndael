class CRijndael
{
public:
  //Operation Modes
  enum { ECB=0, CBC=1, CFB=2 };

  //CONSTRUCTOR
  CRijndael();

  //DESTRUCTOR
  virtual ~CRijndael();

  //Expand a user-supplied key material into a session key.
  void MakeKey(char const* key, char const* chain, 
    int keylength=DEFAULT_BLOCK_SIZE, 
    int blockSize=DEFAULT_BLOCK_SIZE);

  //Encrypt exactly one block of plaintext.
  void EncryptBlock(char const* in, char* result);

  //Decrypt exactly one block of ciphertext.
  void DecryptBlock(char const* in, char* result);

  //Encrypt a larger block of data
  void Encrypt(char const* in, char* result, size_t n, int iMode=ECB);

  //Decrypt a larger block of data
  void Decrypt(char const* in, char* result, size_t n, int iMode=ECB);

  //Get Key Length
  int GetKeyLength();

  //Block Size
  int GetBlockSize();

  //Number of Rounds
  int GetRounds();

  //Resets chain block to initial chain block.
  void ResetChain();

  //Null chain block
  static char const* sm_chain0;
};