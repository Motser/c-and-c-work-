/*
 *Filename: FoodItem.cpp
 *Auther: Brian Labrum, Benjamin Skeen
 *last modified: 2/5/2015
 *version: 1
 *
 */
#include"FoodItem.h"

/*
 *default constructor
 */
namespace inventory
{
  /*
   *defailt constructor creates food item with empty name, UPC, zero in quantity and shelf life
   *and the default DATE object
   */
  FoodItem::FoodItem()
  {
  
   this->UPC = "";
   this->Name = "";
   this->Quantity = 0;
   this->ShelfLife = 0;
  
  }

  FoodItem::FoodItem(std::string upc, std::string name, int quantity, int shelflife, boost::gregorian::date date)
  {
   this->UPC = upc;
   this->Name = name;
   this->Quantity = quantity;
   this->ShelfLife = shelflife;
   this->ExpirationDate = date + boost::gregorian::date_duration(this->ShelfLife);
  }
  /*copy constructor copies all values from old except the experation date
   * which is calculated using the new date
   */ 
  FoodItem::FoodItem(const FoodItem & old, boost::gregorian::date date)
  {
   this->UPC = old.UPC;
   this->Name = old.Name;
   this->Quantity = old.Quantity;
   this->ShelfLife = old.ShelfLife;
   this->ExpirationDate = date + boost::gregorian::date_duration(this->ShelfLife);
  }
  //get methods
  std::string FoodItem::getUPC()
  {
    return this->UPC;
  }
  std::string FoodItem::getName()
  {
    return this->Name;
  }
  int FoodItem::getQuantity()
  {
    return this->Quantity;
  }
  boost::gregorian::date FoodItem::getExpirationDate()
  {
    return this->ExpirationDate;
  }
  /*update the quantity of items in the object 
   * changes quantity by amount
   * if the Quantity falls below 0 sets it to 0
   * */
  int FoodItem::updateQuantity(int amount)
  {
    this->Quantity += amount;
    //check if Quantity < 0
//    if(this->Quantity < 0)
//      this->Quantity = 0;
    return this->Quantity;
  }
  
  /*
   *Returns a std::string for the value of the object
   *std::string is in the form of UPC Name
   */
  std::string FoodItem::toString()
  {
    return this->UPC + " " + this->Name;
  }
}
