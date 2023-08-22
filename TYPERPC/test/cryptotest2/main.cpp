#include "../../common/basiccryptoaesgcmgeneric.h"

int main()
{

  basiccryptoaesgcmfilter CRYPTO;
  
 // CRYPTO.initializeCamellia();
  
  CRYPTO.setkey("640DAE21561AD94512E747F6011DF838");
  CRYPTO.setiv("E2D22C4AEC4EBDD452F9229C57655378");
  
  CRYPTO.setdatatoencrypted("container-image_bullseye-amd64-d399cc882768.tar.gz");  
  
  CRYPTO.debugenc();
  
  CRYPTO.aesgcmencryption();
  
  CRYPTO.debugafter();
  
  CRYPTO.aesgcmdecryption();
  
  return 0;
  
}
