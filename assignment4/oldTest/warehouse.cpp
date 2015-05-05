/*
 *Filename: warehouse.cpp
 *Auther: Brian Labrum, Benjamin Skeen
 *last modified: 2/8/2015
 *version: 3
 *
 */
/*
* The Warehouse class allows management of 
*/

#include "warehouse.h"
#include "FoodItem.h"
#include <string>
#include <iostream>
namespace inventory
{
  /*******************************************************
    * Warehouse member function definitions
    ******************************************************/
  Warehouse::Warehouse(const std::string name)
    : _name(name)
  {
  }
  
  Warehouse::Warehouse()
    :_name("")
  {
  }
  
  void Warehouse::RequestItem(std::string upc_code, int quantity)
  {
    std::map<std::string, std::list<FoodItem> >::iterator mit = _inventory.find(upc_code);
    if (mit != _inventory.end())
    {
      int quantityLeft = quantity * -1;
      std::list<FoodItem> food_list = mit->second;
      while (!food_list.empty() && quantityLeft < 0)
      {
        quantityLeft = food_list.front().updateQuantity(quantityLeft);
        if (quantityLeft <= 0)
        {
          food_list.pop_front();
        }
      }
      if (food_list.empty())
      {
        this->_inventory.erase(mit);
      }
    }
  }
  
  void Warehouse::ReceiveItem(FoodItem food_received, int quantity, boost::gregorian::date current_date)
  {
    std::map<std::string, std::list<FoodItem> >::iterator it = _inventory.find(food_received.getUPC());
    std::list<FoodItem> food_list;
    if (it != _inventory.end())
    {
      food_list = it->second;
    }
    else
    {
      food_list = _inventory[food_received.getUPC()];
    }
    FoodItem newItem(food_received, current_date);
    newItem.updateQuantity(quantity);
    food_list.push_back(newItem);
  }
  
  void Warehouse::AdvanceDate(boost::gregorian::date current_date)
  {
    for (std::map<std::string, std::list<FoodItem> >::iterator it = _inventory.begin(); it != _inventory.end(); ++it)
    {
      std::list<FoodItem> food_list = it->second;
      while (food_list.front().getExpirationDate() < current_date)
      {
        food_list.pop_front();
      }
      if (food_list.empty())
      {
        _inventory.erase(it);
      }
    }
  }
  
  std::set<std::string> Warehouse::GetItemsStocked()
  {
    std::set<std::string> result;
std::cout << "get items stocked start" << std::endl;
    for (std::map<std::string, std::list<FoodItem> >::iterator it = _inventory.begin(); it != _inventory.end(); ++it)
    {
      result.insert(it->first);
std::cout << it->first << std:: endl;
    }
    return result;
  }
  
  std::string Warehouse::GetName()
  {
    std::string result(_name);
    return result;
  }  
  
  bool Warehouse::operator< (const Warehouse & rhs) const
  {
    return _name < rhs._name;
  }
}
