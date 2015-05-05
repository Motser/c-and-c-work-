#include<iostream>
#include<fstream>
#include<map>
#include<set>
#include "FoodItem.h"
#include "warehouse.h"
#include "boost/date_time/gregorian/gregorian.hpp"

void end(std::map<std::string,inventory::FoodItem>& foodList, std::set<inventory::Warehouse>& warehouses);

  int main(int argc, char** argv)
  {
    if (argc != 2)
    {
      std::cout << "Only one command line parameter can be accepted. Aborting program." << std::endl;
      return 0;
    }
    /*std::string fileName = argv[1];*/
    std::ifstream fileStream(argv[1], std::ifstream::in);
    std::map<std::string, inventory::FoodItem> foodList;
    std::map<std::string, inventory::Warehouse> warehouseList;
    if (!fileStream.is_open())
    {
      std::cout << "Error reading file. Aborting program." << std::endl; 
      return 0;
    }
    std::string current_words;
    fileStream >> current_words;
    while(!fileStream.eof() && current_words != "Start")
    {
      if (current_words == "FoodItem")
      {
std::cout << "food item" << std::endl;
        for (int i = 0; i < 4; i++)
        {
          fileStream >> current_words;
        }
        std::string const newUpc(current_words);
        for (int i = 0; i < 3; i++)
        {
          fileStream >> current_words;
        }
        int const newShelfLife = atoi(current_words.c_str());
        //fileStream >> newShelfLife;
        fileStream >> current_words;
        std::getline(fileStream, current_words);
        std::string const newFoodName(current_words);
        boost::gregorian::date const default_date(2015, 1, 1);
        int const& defaultQuantity = 0;
        inventory::FoodItem newFoodItem(newUpc, newFoodName, defaultQuantity, newShelfLife, default_date);
        foodList[newUpc] = newFoodItem;
      }
      else
      {
std::cout << "warehouse" << std::endl;
        fileStream >> current_words;
        std::getline(fileStream, current_words);
        inventory::Warehouse newWarehouse(current_words);
        warehouseList[current_words] = newWarehouse;
      }
      fileStream >> current_words;
    }
    for (int i = 0; i < 2; i++)
    {
      fileStream >> current_words;
    }
    std::string date_month = current_words.substr(0,2);
    std::string date_day = current_words.substr(3, 2);
    std::string date_year = current_words.substr(6,4);
    boost::gregorian::date current_date(atoi(date_year.c_str()), atoi(date_month.c_str()), atoi(date_day.c_str()));
    boost::gregorian::date_duration day_increment(1);
    fileStream >> current_words;
for (std::map<std::string, inventory::Warehouse>::iterator it = warehouseList.begin(); it != warehouseList.end(); ++ it)
{
std::cout<<it->first<<std::endl;
}
    while(!fileStream.eof() && current_words != "End")
    {
std::cout << current_words << std::endl;

      if (current_words == "Request:")
      {
std::cout << "request" << std::endl;
        std::string requestUpc;
        fileStream >> requestUpc;
        int requestQuantity;
        fileStream >> requestQuantity;
        std::getline(fileStream, current_words);
        inventory::Warehouse currentWarehouse = warehouseList[current_words];
        currentWarehouse.RequestItem(requestUpc, requestQuantity);
      }
      else if (current_words == "Receive:")
      {
std::cout << "receive" << std::endl;
        std::string receiveUpc;
        fileStream >> receiveUpc;
        inventory::FoodItem receiveFoodItem = foodList[receiveUpc];
        int receiveQuantity;
        fileStream >> receiveQuantity;
        std::getline(fileStream, current_words);
        inventory::Warehouse &currentWarehouse = warehouseList[current_words];
        currentWarehouse.ReceiveItem(receiveFoodItem, receiveQuantity, current_date);
std::cout<<currentWarehouse.GetName()<<std::endl;
std::cout<<warehouseList[current_words].GetName()<<std::endl;
//        warehouseList[current_words].ReceiveItem(receiveFoodItem, receiveQuantity, current_date);
//std::set<std::string> inv = currentWarehouse.GetItemsStocked();
std::set<std::string> inv = warehouseList[current_words].GetItemsStocked();
std::set<std::string> inv2 = currentWarehouse.GetItemsStocked();
      }
      else
      {
std::cout << "next day" << std::endl;
        fileStream >> current_words;
        fileStream >> current_words;
        current_date = current_date + day_increment;
        for (std::map<std::string, inventory::Warehouse>::iterator it = warehouseList.begin(); it != warehouseList.end(); ++it)
        {
          it->second.AdvanceDate(current_date);
        }
      }
      fileStream >> current_words;
    }
    fileStream.close();
    std::set<inventory::Warehouse> warehouses;
    for (std::map<std::string, inventory::Warehouse>::iterator it = warehouseList.begin(); it != warehouseList.end(); ++ it)
    {
      warehouses.insert(it->second);
    }
    
std::cout << "end" << std::endl;
    end(foodList, warehouses);
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
void end(std::map<std::string,inventory::FoodItem>& foodList, std::set<inventory::Warehouse>& warehouses)
{

  //loop through warehouses and get inventory count
  for(std::set<inventory::Warehouse>::iterator it = warehouses.begin(); it != warehouses.end(); ++it)
  {
std::cout << "loop1" << std::endl;
    
    inventory:: Warehouse temp = *it;
    std::cout << temp.GetName() << std::endl;
    std::set<std::string> inv = temp.GetItemsStocked();
    for(std::set<std::string>::iterator it2 = inv.begin() ; it2 != inv.end() ; ++it2)//loop through warehouse inventory
    {
std::cout << "loop2" << std::endl;
std::cout << (*it2) << std::endl;
      foodList[*it2].updateQuantity(1);//increase the quantity by 1 
    }

  }

  //print out names followed by a blank line
  std::cout << "Report by Brian Labrum, Benjamin Skeen " << std::endl << std::endl;
  
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
