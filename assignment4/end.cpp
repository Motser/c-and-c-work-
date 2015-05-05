/*
 *Filename: tester.cpp
 *Auther: Brian Labrum, Benjamin Skeen
 *last modified: 2/5/2015
 *version: 2
 *
 */
#include <iostream>
#include "FoodItem.h"
#include "warehouse.h"
#include <map>
#include <set>

int main()
{
//here to make it compile
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
