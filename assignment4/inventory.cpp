/*
 *Filename: inventory.cpp
 *Auther: Brian Labrum, Benjamin Skeen
 *last modified: 2/11/2015
 *version: 1
 *
 */
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include "FoodItem.h"
#include "warehouse.h"
#include "boost/date_time/gregorian/gregorian.hpp"
#include <string>

#include <queue>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <iterator>

void end(std::map<std::string,inventory::FoodItem> foodList, std::set<inventory::Warehouse> warehouses);

  int main(int argc, char** argv)
  {
    // Check to make sure the number of command line arguments is correct.
	if (argc != 2)
    {
      std::cout << "Only one command line parameter can be accepted. Aborting program." << std::endl;
      return 0;
    }
	// Open the file from the name given by the command line argument
    std::ifstream fileStream(argv[1], std::ifstream::in);
	
	// Declare collections to store the data from the file
    std::map<std::string, inventory::FoodItem> foodList;
    std::map<std::string, inventory::Warehouse> warehouseList;
	
	//make queues
     std::queue<std::string> receive;
     std::queue<std::string> request;

	// If the file is not open, then close the program.
    if (!fileStream.is_open())
    {
      std::cout << "Error reading file. Aborting program." << std::endl; 
      return 0;
    }
	
	// String to keep track of the current words received from the file.
    std::string current_words;
	// Retrieve the first word of the file
    fileStream >> current_words;
	
	// Continue this loop until the "Start Date" line is reached.
    while(!fileStream.eof() && current_words != "Start")
    {
      // If the current line starts with "FoodItem," then read the input as a new FoodItem
	  // and add it to the list of possible FoodItems
	  if (current_words == "FoodItem")
      {
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
        fileStream >> current_words;
        std::getline(fileStream, current_words);
		if (current_words[0] == ' ')
		{
		  current_words = current_words.substr(1, current_words.size() - 1);
		}
		if (current_words[current_words.length() - 1] == '\r')
		{
		  current_words = current_words.substr(0, current_words.size() -1);
		}
        std::string const newFoodName(current_words);
        boost::gregorian::date const default_date(2015, 1, 1);
        int const& defaultQuantity = 0;
        inventory::FoodItem newFoodItem(newUpc, newFoodName, defaultQuantity, newShelfLife, default_date);
        foodList[newUpc] = newFoodItem;
      }
	  // Otherwise, construct a warehouse from the current line
      else
      {
        fileStream >> current_words;
        std::getline(fileStream, current_words);
		if (current_words[0] == ' ')
		{
		  current_words = current_words.substr(1, current_words.size() - 1);
		}
		if (current_words[current_words.length() - 1] == '\r')
		{
		  current_words = current_words.substr(0, current_words.size() -1);
		}
        inventory::Warehouse newWarehouse(current_words);
        warehouseList[current_words] = newWarehouse;
      }
	  // Grab the next word
      fileStream >> current_words;
    }
	// Declare and parse the current start date
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
	// Continue attempting to parse the file until the word "End" is reached
    while(!fileStream.eof() && current_words != "End")
    {
	  // If the first word of the line is "Request:" then call the RequestItem method on the warehouse
      if (current_words == "Request:")
      {
        std::string requestUpc;
        fileStream >> requestUpc;
        int requestQuantity;
        fileStream >> requestQuantity;
        std::getline(fileStream, current_words);
		if (current_words[0] == ' ')
		{
		  current_words = current_words.substr(1, current_words.size() - 1);
		}
		if (current_words[current_words.length() - 1] == '\r')
		{
		  current_words = current_words.substr(0, current_words.size() -1);
		}
	request.push(current_words + " " + requestUpc + " " + std::to_string(static_cast<long long>(requestQuantity)));
//        warehouseList[current_words].RequestItem(requestUpc, requestQuantity);
      }
	  // If the first word of the line is "Receive:" then call the ReceiveItem method on the warehouse
      else if (current_words == "Receive:")
      {
        std::string receiveUpc;
        fileStream >> receiveUpc;
        inventory::FoodItem receiveFoodItem = foodList[receiveUpc];
        int receiveQuantity;
        fileStream >> receiveQuantity;
        std::getline(fileStream, current_words);
		if (current_words[0] == ' ')
		{
		  current_words = current_words.substr(1, current_words.size() - 1);
		}
		if (current_words[current_words.length() - 1] == '\r')
		{
		  current_words = current_words.substr(0, current_words.size() -1);
		}
	receive.push(current_words + " " + receiveUpc + " " + std::to_string(static_cast<long long>(receiveQuantity)));
//        inventory::Warehouse &currentWarehouse = warehouseList[current_words];
//        currentWarehouse.ReceiveItem(receiveFoodItem, receiveQuantity, current_date);
      }
	  // If the above conditions are not true, then increment the date.
      else
      {
        for (std::map<std::string, inventory::Warehouse>::iterator it = warehouseList.begin(); it != warehouseList.end(); ++it)
        {
	  while(!receive.empty())
	  {
		std::vector<std::string> command;
		boost::split(command, receive.front(), boost::is_any_of(" "));
    		int quant = std::atoi(command[2].c_str());

	        inventory::Warehouse &currentWarehouse = warehouseList[command[0]];
        	inventory::FoodItem receiveFoodItem = foodList[command[1]];

	        currentWarehouse.ReceiveItem(receiveFoodItem, quant, current_date);
		
		receive.pop();
	  }

	  while(!request.empty())
	  {
		std::vector<std::string> command;
		boost::split(command, request.front(), boost::is_any_of(" "));
    		int quant = std::atoi(command[2].c_str());

	        warehouseList[command[0]].RequestItem(command[1], quant);
		
		request.pop();
	  }
          current_date = current_date + boost::gregorian:: date_duration(1);
          it->second.AdvanceDate(current_date);
        }
        fileStream >> current_words;
      }
	  // Get the next word
      fileStream >> current_words;
    }
	// Close the file
    fileStream.close();
	// Add the warehouses to a set so that they can be processed by the report function.
    std::set<inventory::Warehouse> warehouses;
    for (std::map<std::string, inventory::Warehouse>::iterator it = warehouseList.begin(); it != warehouseList.end(); ++ it)
    {
      warehouses.insert(it->second);
    }
    // Call the report function.
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
