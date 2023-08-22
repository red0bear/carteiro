#include "../../crypto/basicrypto.h"

int main()
{
  basicrypto CRYPTO;
  CRYPTO.createderivatedkeys();
  CRYPTO.encryption();
  CRYPTO.decryption();
  CRYPTO.debug();
  
  return 0;
}
