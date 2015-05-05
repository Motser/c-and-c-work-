/*
* The warehouse class is used to keep
* track of the name and inventory for
* one warehouse
*
* Ben Skeen and Brian Labrum
* February 3, 2015
*/

#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include<string>
#include<map>
#include<set>
#include<list>
#include<boost/date_time/gregorian/gregorian.hpp>
#include "FoodItem.h"

namespace inventory
{
  class Warehouse
  {
    public:
      Warehouse(std::string name);
      Warehouse();
      void RequestItem(std::string upc_code, int quantity);
      void ReceiveItem(inventory::FoodItem food_received, int quantity, boost::gregorian::date current_date);
      void AdvanceDate(boost::gregorian::date current_date);
      std::set<std::string> GetItemsStocked();
      std::string GetName();
      
      bool operator< (const Warehouse & rhs) const;


    private:
      std::string _name;
      std::map<std::string, std::list<inventory::FoodItem> > _inventory;
  };
  
}

#endif
