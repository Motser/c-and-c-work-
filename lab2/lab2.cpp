#include <iostream>

using namespace std;

void swap(int &x, int &y)
{
  int temp; 
  temp = x;
  x = y;
  y = temp;
}

int main()
{
   int x,y;
   x = 5;
   y = 10;

   cout << "Before\n";
   cout << "x = " << x << "\ny = " << y << endl;
 
   swap(x,y);

   cout << "After\n";
   cout << "x = " << x << "\ny = " << y << endl;
}
