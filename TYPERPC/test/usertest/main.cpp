#include <iostream> 
#include <vector>
#include <cstring>
#include <string>

#include "../../common/user.h"


int main()
{

  user USER;
  
  USER.setname("My super name goes here");
  USER.setphone("00 00 00000000");
  USER.setaddress("Some Avenue and some address");
  USER.setemail("email@mustendthis.com");
  USER.setuuid("0aa8ddufhi-90d908f99f-juuwhuwcc99-u9c");
  
  USER.setkey("00112233445566778899AABBCCDDEEFF");
  USER.setkey("00001111222233334444555566667777");
  USER.setkey("00000000000000000000000000000000");
  USER.setkey("11111111111111111111111111111111");
  USER.setkey("22222222222222222222222222222222");
  
  USER.setiv("00112233445566778899AABBCCDDEEFF");
  USER.setiv("00001111222233334444555566667777");
  USER.setiv("00000000000000000000000000000000");
  USER.setiv("11111111111111111111111111111111");
  USER.setiv("22222222222222222222222222222222");

  return 0;
}
