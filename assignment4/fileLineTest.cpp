#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<boost/algorithm/string/split.hpp>
#include<boost/algorithm/string/classification.hpp>
#include<vector>
#define BOOST_AL boost::algorithm::
using namespace std;
int main()
{
  string line; //holds the line
  ifstream infile("data1.txt");//reads the file
  while(getline(infile,line))//loops through each line of the file
  {
    vector<string> tokens;//holds string tokens
    BOOST_AL split(tokens, line, BOOST_AL is_any_of(" "));//split the string 
    cout << tokens[0] << endl;
  }

  infile.close();
}
