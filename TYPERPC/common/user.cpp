#include <iostream> 
#include <vector>
#include <cstring>
#include <string>

#include "user.h"

void user::setname(std::string value)
{
  if(!lock)
    name = value;
  else
    name = name;
}
  
std::string user::getname()
{
  return name;
}
 
void user::setphone(std::string value)
{
  if(!lock)
    phone = value;
  else
    phone = phone;
}
  
std::string user::getphone()
{
  return phone;
}
  
void user::setaddress(std::string value)
{
  if(!lock)
    address = value;  
}
  
std::string user::getaddress()
{
  return address;  
} 
  
void user::setemail(std::string value)  
{
  email = value;
} 
  
std::string user::getemail()
{
  return email;
}
  
void user::setuuid(std::string value)
{
  uuid = value;
} 
  
std::string user::getuuid()
{
  return uuid;
}
    
void user::setkey(std::string value)
{
  key.push_back(value);
}

void user::setiv(std::string value)
{
 iv.push_back(value);
}

void user::lockdown()
{
 lock = true;
}
