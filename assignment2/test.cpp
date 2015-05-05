/*
 *Filename: doubleNum
 *Auther: Brian Labrum
 *Last Modified:1/14/15  
 *Version
 */

#include <string>
#include "huge_number.h"
#include <iostream>
using namespace std;

/*
 * method for testing huge_number class
 */
int main ()
{
  //test constructors 
  huge_number a;
  string s = "1234567890";
  huge_number aa("1");
  huge_number b(s);
  huge_number c(b); 
  huge_number d("1234567890123456789012345678901234567890123456789055461489716843516736871540258916582357816571547413573718607576389046035314");

  //print values
  cout << "test constructors: " << endl;
  cout << "test default " << a.get_value() << endl;
  cout << "test string constructor " << b.get_value() << endl;
  cout << "test string constructor 2 " << d.get_value() << endl;
  cout<<"test copy constructor " << c.get_value() << endl;

  //test equals constructor
  a = b;
  cout << endl << "test equals " << a.get_value() << endl;
  
  //test add
  cout << endl;
  huge_number e(b+c);
  cout<<"test add " << e.get_value() <<endl;
  cout<<"test add l: " << b.get_value() <<endl;
  cout<<"test add r: " << c.get_value() <<endl;
  e = a+aa;
  cout<<"test add " << e.get_value() <<endl;
  e = aa+a;
  cout<<"test add " << e.get_value() <<endl;

  //test subtract
  cout<<endl;
  e = b-c;
  cout<<"test sub " << e.get_value() <<endl;
  cout<<"test sub l: " << b.get_value() <<endl;
  cout<<"test sub r: " << c.get_value() <<endl;
  e = a - aa;
  cout<<"test sub " << e.get_value() <<endl;
  e = aa-a;
  cout<<"test sub " << e.get_value() <<endl;
  
  //test muliply 
  cout<<endl;
  e = b*c;
  cout<<"test mult " << e.get_value() <<endl;
  cout<<"test mult l: " << b.get_value() <<endl;
  cout<<"test mult r: " << c.get_value() <<endl;
  e = a * aa;
  cout<<"test mult " << e.get_value() <<endl;
  e = aa*a;
  cout<<"test mult " << e.get_value() <<endl;

  //test divide  
  huge_number f("1");
  huge_number g("2");
  huge_number h("4");
  huge_number i("50"); 
  huge_number j("100000000000000000000000000000");
  e = g/f;
  cout << endl << "2/1: " << e.get_value() << endl;
  e = f/g;
  cout  << "1/2: " << e.get_value()  << endl;
  e = h/g;
  cout  << "4/2: " << e.get_value()  << endl;
  e = i/h;
  cout  << "50/4: " << e.get_value()  << endl;
  e = j/g;
  cout  << "100000000000000000000000000000/2: " << e.get_value()   << endl;
  //test modulus
  e = g%f;
  cout << endl << "2/1: " << e.get_value() << endl;
  e = f%g;
  cout  << "1%2: " << e.get_value()  << endl;
  e = h%g;
  cout  << "4%2: " << e.get_value()  << endl;
  e = i%h;
  cout  << "50%4: " << e.get_value()  << endl;
  e = j%g;
  cout  << "100000000000000000000000000000%2: " << e.get_value()   << endl;
}
