#include"boost/date_time/gregorian/gregorian.hpp"
#include<iostream>
#include<string>
using namespace boost::gregorian;
int main()
{
  std::string s1 = "2003-07-28";
  date d(from_string(s1));
  date ds( 2001,Aug,10);  
  date_duration dd(1);
  date d2 = ds + dd;
  std::cout << d2 << std::endl;
  std::cout << d << std::endl;
}
