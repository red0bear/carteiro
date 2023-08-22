#include "../../crypto/basiccryptoaesgcm.h"

int main()
{

  basiccryptoaesgcm CRYPTO;
  
  CRYPTO.setadata("The sun will reveal all ponzi and scam");
  CRYPTO.setpdata("Trump and biden sux");
  
  CRYPTO.aesgcmencryption();
  
  
  return 0;
  
}
