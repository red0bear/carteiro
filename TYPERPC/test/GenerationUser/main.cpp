#include "../../common/usergenerate.h"
#include <time.h>

int main()
{
  time_t timer;

  usergenerate USERGENERATION;

  USERGENERATION.generatenewuser();
  USERGENERATION.getjsongenerateduser("test_1","00000000000",std::to_string(time(&timer)));
  return 0;
  
}
