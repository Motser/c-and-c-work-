/*
 *Filename: FoodItem.cpp
 *Auther: Brian Labrum, Benjamin Skeen
 *last modified: 2/5/2015
 *version: 1
 *
 */
#include"FoodItem.h"
#include"warehouse.h"
#include<map>
#include<set>
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<boost/algorithm/string/split.hpp>
#include<boost/algorithm/string/classification.hpp>
#include<vector>
#include<cmath>
//macros
#define BOOST_AL boost::algorithm::
#define INV inventory::
#define DATE boost::gregorian:: 
#define ADVANCE DATE date_duration(1)

//declair functions
void end(std::map<std::string,inventory::FoodItem> foodList, std::set<inventory::Warehouse> warehouses);


using namespace std;
int main(int argc, char* argv[])
{
  //check for correct number of inputs
  if(argc != 2)
  {
    cout << "Incorect number of arguments" << endl;
    return 0;
  }
  //make variables to track FoodItems and Warehouses
  map<string, INV Warehouse> warehouses; //holds warehouses
  map<string, INV FoodItem> foodList; //holds list of zero quantity food items   
  DATE date currentDate;

  //open the file
  string line; //holds the line
  ifstream infile(argv[1]);//reads the file

  //read each line of the file
  while(getline(infile,line))
  {
    //split into tokens
    vector<string> tokens;//holds string tokens
    BOOST_AL split(tokens, line, BOOST_AL is_any_of(" "));//split the string 
    //if FoodItem
    if(tokens[0] == "FoodItem")
    {
cout<<"food" << endl;
      //get name
      string name;
      for(int i = 9; i < tokens.size(); i++)
      {
        if (tokens[i]!="Name")
          name = name+ " " + tokens[i];
      }
cout << name << endl;
      foodList[tokens[4]] = INV FoodItem(tokens[4], name, 0, atoi(tokens[7].c_str()), currentDate);//new FoodItem with quantity 0
      

    }
   
    //if Warehouse
    else if(tokens[0] == "Warehouse")
    {
cout<<"warehouse" << endl;
      cout << tokens[2] << endl;
      INV Warehouse newWarehouse(tokens[2]);
      warehouses[tokens[2]] = newWarehouse;
    }

    //if Start Date
    else if(tokens[0] == "Start")
    {
cout<<"start" << endl;
      string current_words = tokens[2];   
      string date_month = current_words.substr(0,2);
      string date_day = current_words.substr(3, 2);
      string date_year = current_words.substr(6,4);
      currentDate =  DATE date(atoi(date_year.c_str()), atoi(date_month.c_str()), atoi(date_day.c_str()));
    }

    //if Receive
    else if(tokens[0] == "Receive:")
    {
cout<<"receive" << endl;
        warehouses[tokens[3]].ReceiveItem(foodList[tokens[1]], atoi(tokens[2].c_str()), currentDate);
    }

    //if Request
    else if(tokens[0] == "Request:")
    {
cout<<"request" << endl;
        warehouses[tokens[3]].RequestItem(tokens[1], atoi(tokens[2].c_str()));
    }

    //if Next Day
    else if(tokens[0] == "Next")
    {
cout<<"next" << endl;
      currentDate = currentDate + ADVANCE;
      for(map<string, INV Warehouse>::iterator it = warehouses.begin(); it != warehouses.end(); ++it)
      {
        it->second.AdvanceDate(currentDate);
      }
    }

    //if End
    else //if(tokens[0] == "End")
    {
cout<<"end start" << endl;
      std::set<inventory::Warehouse> wares;
      for (std::map<std::string, inventory::Warehouse>::iterator it = warehouses.begin(); it != warehouses.end(); ++ it)
      {
        wares.insert(it->second);
      }
      end(foodList, wares);
    }

  }

  infile.close();// close file
  return 0;
}


/*
 * Generates the end report takes in a <string,FoodItem> map
 * and a set of warehouses to check
 * where the FoodItems in the map have a quantity set to zero 
 * and the are mapped using their upc as the key
 *
 * the function loops through the set of warehouses checking their 
 * inventory and increaseing the quantity of FoodItem in the map 
 * it then uses this quantity to determine what items are unstocked
 * and well stocked
 */
void end(std::map<std::string,inventory::FoodItem> foodList, std::set<inventory::Warehouse> warehouses)
{
  //loop through warehouses and get inventory count
  for(std::set<inventory::Warehouse>::iterator it = warehouses.begin(); it != warehouses.end(); ++it)
  {
    inventory:: Warehouse temp = *it;
    std::set<std::string> inv = temp.GetItemsStocked();
    for(std::set<std::string>::iterator it2 = inv.begin() ; it2 != inv.end() ; ++it2)//loop through warehouse inventory
    {
      foodList[*it2].updateQuantity(1);//increase the quantity by 1 
    }

  }

  //print out names followed by a blank line
  std::cout << "Report by Brian Labrum, BEnjamin Skeen " << std::endl << std::endl;
  
  //print out unstocked products
  std::cout << "Unstocked Products" << std::endl;
  //loop through and find unstocked products
  for(std::map<std::string, inventory::FoodItem>::iterator it = foodList.begin(); it != foodList.end(); ++it)
  {
    if(it->second.getQuantity() == 0)//check count
    {
      std::cout << it->second.toString() << std::endl;
    }
  }

  //print out blank line
  std::cout << std:: endl;

  //print out well stocked
  std::cout << "Well-Stocked Products" << std::endl;
  //loop through and find well stocked items 
  for(std::map<std::string, inventory::FoodItem>::iterator it = foodList.begin(); it != foodList.end(); ++it)
  {
    if(it->second.getQuantity() > 1)//check count
    {
      std::cout << it->second.toString() << std::endl;
    }
  }
  //print a blank line
  std::cout << std::endl;

}
