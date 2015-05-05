#include <iostream>//used for cout 
#include <boost/lexical_cast.hpp>
using namespace std;

/*
 * called with a single command argv 
 * check for user errors
 * parse int if prime print prime
 * otherwise print composite
 */
int main(int argc, char* argv[])
{
  int test;// the value to check

  //test the number of arguments
  if(argc > 2)
  {
    cout << "To many arguments" << endl;
    return 0;
  } 

  if(argc <=1)
  {
    cout<<"Not enough arguments" << endl;
    return 0;
  }

  //try to parse int
  try {
    test = boost::lexical_cast<int>( argv[1] );
  } catch( boost::bad_lexical_cast const& ) {
    std::cout << "composite" << std::endl;
  }
  
  //check if prime
  if(test <= 1)//1, 0, and negative numbers can't be prim
  {
    cout << "composite" << endl;
    return 0;
  }

  if(test % 2 == 0)//check for even numbers
  {
    if(test == 2)//only even number thats prime
    {
      cout << "prime" << endl;
      return 0;
    } else {// not prime
      cout << "composite" << endl;
      return 0;
    }
  }

  //check every smaller odd number execpt 1
  //we don't need to check even since that 
  //would make the number even
  for(int i = test - 2; i > 1; i-=2)
  {
    if(test % i == 0)//check if multiple
    {
      cout << "composite" << endl;
      return 0;
    }
  }
  //if we exit the loop then it's a prime number
  cout << "prime" << endl;
}
