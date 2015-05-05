/*
 *Filename: FoodItem.h
 *Auther: Brian Labrum, Benjamin Skeen
 *last modified: 2/4/2015
 *version: 1
 *
 */

#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>
#include "boost/date_time/gregorian/gregorian.hpp"//class for dates
namespace inventory
{
  class FoodItem
  {
    private: 
      std::string UPC;//contains the upc of the item
      std::string Name;//contains the name of the item
      int ShelfLife;//contains how many days untill the item expires
      int Quantity; //number of items
      boost::gregorian::date ExpirationDate;//the date the item will expire
    public:
      //constrictors
      FoodItem();
      FoodItem(std::string UPC, std::string name, int quantity, int ShelfLife, boost::gregorian::date Date);//basic constructor for a food item
      FoodItem(const FoodItem & old, boost::gregorian::date Date);//copies old food item and makes a new one with different date
      //get methods
      std::string getUPC();
      std::string getName();
      int getQuantity();
      boost::gregorian::date getExpirationDate();
      /*update the quantity of items in the object 
       * changes quantity by amount
       * if the Quantity falls below 0 sets it to 0
       * */
      int updateQuantity(int amount);
      /*
       *Returns a std::string for the value of the object
       *std::string is in the form of UPC Name
       */
      std::string toString();
  
   
  
  };
};

#endif
