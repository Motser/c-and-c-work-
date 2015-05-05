/*
 *Filename: doubleNum
 *Auther: Brian Labrum
 *Last Modified:1/14/15  
 *Version
 */

/*
 
 */
#include <iostream>

using namespace std;
/*
 * get number num from user and output num * 2
 */
int main()
{
  int num;
  //ask for and get num
  cout<<"Input number\n";
  cin >> num;
  //print num * 2
  num*=2;
  cout<<"\nThe new value is: " << num << "\n";
 /* 
  if(num > 5)
    cout<<"num is greater than 5";
  else
    cout<<"num is less than 5";
  */
  for(int i=1; i<10; i+=2)
  {
     cout<<i<<"\n";
  }
}
