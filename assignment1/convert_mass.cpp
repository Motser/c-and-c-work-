#include <iostream>

using namespace std;

int main()
{
  float kilo;//wieght in kilograms
  float pounds;//wieght in pounds
  cout<<"input weight in kilograms" << endl;
  cin >> kilo;
  //convert kg to lbs
  pounds = kilo * 2.2046;
  cout << kilo << " kg is equal to " << pounds << " lbs" << endl;

}
