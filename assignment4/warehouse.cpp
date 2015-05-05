/*
 *Filename: warehouse.cpp
 *Auther: Brian Labrum, Benjamin Skeen
 *last modified: 2/8/2015
 *version: 3
 *
 */
/*
* The Warehouse class allows management of the inventory for a
* single warehouse,
*/

#include "warehouse.h"

namespace inventory
{
  /*******************************************************
    * Warehouse member function definitions
    ******************************************************/
  /*
  * Constructs a warehouse with the given name.
  **/
  Warehouse::Warehouse(const std::string name)
    : _name(name)
  {
  }
  
  Warehouse::Warehouse()
    :_name("")
  {
  }

  /*
  * Removes the given quantity of the FoodItem with the given UPC code from the warehouse.
  **/
  void Warehouse::RequestItem(std::string upc_code, int quantity)
  {
     int change = -quantity;
     while(change < 0 && !_inventory[upc_code].empty()) // Check to see if there are more left to remove from the inventory
     {
       change = _inventory[upc_code].front().updateQuantity(change); // If there are, then remove them from the next item in the list
       if(change <= 0) // If change is still negative, then there are more items that need to be removed, and the first item 
       {
         _inventory[upc_code].pop_front();//if quantity zero remove
       }
     }
  }

  
  /*
  * Adds the specified quantity of the FoodItem passed in to the warehouse, using the date argument
  * to calculate when the food item expires.
  **/
  void Warehouse::ReceiveItem(FoodItem food_received, int quantity, boost::gregorian::date current_date)
  {
    std::list<FoodItem> &food_list = _inventory[food_received.getUPC()]; // Get the list of food
    FoodItem newItem(food_received, current_date); // Construct a new food item
    newItem.updateQuantity(quantity); // Update the quantity of the new food item to be the input quantity
    food_list.push_back(newItem); // Add the food item to the end of the list
  }
  
  /*
  * Expires all items in the inventory that have an expiration date on or before the given date.
  **/
  void Warehouse::AdvanceDate(boost::gregorian::date current_date)
  {
    for (std::map<std::string, std::list<FoodItem> >::iterator it = _inventory.begin(); it != _inventory.end(); ++it)
    {
      std::list<FoodItem> food_list = it->second; // Get the next list of FoodItems
      while (food_list.front().getExpirationDate() <= current_date) // If the expiration date of the first FoodItem is before or on the current date
      {
        food_list.pop_front(); // Get rid of it
      }
      if (food_list.empty()) // If the current list is empty
      {
        _inventory.erase(it); // Get rid of it
      }

    }
  }
  /*
  * Returns a set of the UPC codes of the FoodItems currently in stock in the warehouse.
  **/
  std::set<std::string> Warehouse::GetItemsStocked()
  {
    std::set<std::string> result; // Declare a set to save the results in.
    for (std::map<std::string, std::list<FoodItem> >::iterator it = _inventory.begin(); it != _inventory.end(); ++it)
    {
      if(it->second.front().getQuantity() > 0) // If the first quantity in the current list is zero, the list is considered empty
        result.insert(it->first); // Add the UPC code to the set.
    }
    return result;
  }
  /*
  * Get the name of the warehouse.
  **/
  std::string Warehouse::GetName()
  {
    std::string result(_name);
    return result;
  }
  
  /*
  * This overridden < operator is used when adding the warehouse to a set.
  * In order to tell if the argument comes before the current warehouse, the
  * names of the warehouses are compared.
  **/
  bool Warehouse::operator< (const Warehouse & rhs) const
  {
    return _name < rhs._name;
  }
}