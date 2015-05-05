/*
 *Filename: tester.cpp
 *Auther: Brian Labrum, Benjamin Skeen
 *last modified: 2/4/2015
 *version: 2
 *
 */
#include"FoodItem.h"
#include"warehouse.h"
#include<iostream>
#include "boost/date_time/gregorian/gregorian.hpp"//class for dates
#include<iterator>
#include<set>

#define DATE boost::gregorian:: 
#define ADVANCE(a) DATE date_duration(a)


using namespace inventory; //namespace for Warhouse and FoodItem
/*
 *function for testing the FoodItem and Warehouse classes
 */
int main()
{
  bool testsPassed = true;//set to false if a test fails
 

  //block for tests of FoodItem 
  {
    //used to construct FoodItems
    std:: string upc = "1234567890";
    std:: string testName = "item1";
    int quantity = 1;
    int shelfLife = 3;
    //used for checking dates
    DATE date currentDate(DATE from_string("2001-4-23"));
    DATE date experationDate = currentDate + ADVANCE(shelfLife);
    DATE date experationDate2 = experationDate + ADVANCE(shelfLife);

    //defualt constructor
    FoodItem::FoodItem test1(upc, testName, quantity, shelfLife, currentDate );
    
    //copy constructor
    FoodItem::FoodItem test2(test1, experationDate );
   
    //test1
    std::cout << std::endl << "Test default constructor" << std::endl;
    //test get methods
    if(test1.getUPC() != upc)
    {
      std::cout  << "Test faild upc is: " << test1.getUPC() << " should be: " << upc << std::endl;
      testsPassed=false;
    }
    if(test1.getName() != testName)
    {
      std::cout  << "Test faild name is: " << test1.getName() << " should be: " << testName << std::endl;
      testsPassed=false;
    }
    if(test1.getQuantity() != quantity)
    {
      std::cout  << "Test faild quantity is: " << test1.getQuantity() << " should be: " << quantity << std::endl;
      testsPassed=false;
    }
    if(test1.getExpirationDate() != experationDate)
    {
      std::cout  << "Test faild date is: " << test1.getExpirationDate() << " should be: " << experationDate << std::endl;
      testsPassed=false;
    }
    //test change quantity
    test1.updateQuantity(1); 
    if(test1.getQuantity() != quantity + 1)
    {
      std::cout  << "Test change quantity1 failed is: " << test1.getQuantity() << " should be: " << (quantity+1) << std::endl;
      testsPassed=false;
    }
    test1.updateQuantity(-(quantity +1)); 
    if(test1.getQuantity() != 0 )
    {
      std::cout  << "Test change quantity1 failed is: " << test1.getQuantity() << " should be: " << 0 << std::endl;
      testsPassed=false;
    }
      



    //test2
    std::cout << std::endl << "Test copy constructor" << std::endl;
    //test get methods
    if(test2.getUPC() != upc)
    {
      std::cout  << "Test faild upc is: " << test1.getUPC() << " should be: " << upc << std::endl;
      testsPassed=false;
    }
    if(test2.getName() != testName)
    {
      std::cout  << "Test faild name is: " << test1.getName() << " should be: " << testName << std::endl;
      testsPassed=false;
    }
    if(test2.getQuantity() != quantity)
    {
      std::cout  << "Test faild quantity is: " << test1.getQuantity() << " should be: " << quantity << std::endl;
      testsPassed=false;
    }
    if(test2.getExpirationDate() != experationDate2)
    {
      std::cout  << "Test faild date is: " << test1.getExpirationDate() << " should be: " << experationDate2 << std::endl;
      testsPassed=false;
    }
    //test change quantity
    test2.updateQuantity(-10); 
    if(test1.getQuantity() != 0)
    {
      std::cout  << "Test change quantity1 failed is: " << test1.getQuantity() << " should be: " << 0 << std::endl;
      testsPassed=false;
    }
    test1.updateQuantity((quantity +10)); 
    if(test1.getQuantity() != (quantity+10) )
    {
      std::cout  << "Test change quantity1 failed is: " << test1.getQuantity() << " should be: " << (quantity+10) << std::endl;
      testsPassed=false;
    }
     

  }




  //block for warhouse tests
  {
    //UPC values for test items
    std::string upc1 = "1";
    std::string upc2 = "2";
    std::string upc3 = "3";
    std::string upc4 = "4";
    
    //shelf lifes for test items
    int shelf1 = 2;
    int shelf2 = 4; 
    int shelf3 = 10; 
    int shelf4 = 1; 
    
    //names for test items
    std::string name1 = "apple";
    std::string name2 = "bannana";
    std::string name3 = "carrot";
    std::string name4 = "grape";

    //date for tests
    DATE date currentDate(DATE from_string("2001-5-15"));    

    //food items for test
    FoodItem::FoodItem item1(upc1, name1, 1, shelf1, currentDate);
    FoodItem::FoodItem item2(upc2, name2, 1, shelf2, currentDate);
    FoodItem::FoodItem item3(upc3, name3, 1, shelf3, currentDate);
    FoodItem::FoodItem item4(upc4, name4, 1, shelf4, currentDate);
    
    //test warehouse
    Warehouse::Warehouse test("utah");
    
    //test empty warehouse
    {
      std::cout << std::endl << "Test empty warehouse" << std::endl;
      std::set<std::string> inv = test.GetItemsStocked();
      //check if inventory is empty
      for(std::set<std::string>::iterator it = inv.begin(); it != inv.end(); it++ )
      {
        //should only reach here if warehouse isn't empty
        std::cout << "Test empty warehouse failed " << *it <<" should not be in invintory" << std::endl;
        testsPassed = false;
      }
      //check get name
      if(test.GetName() != "utah")
      {
        std::cout << "Test empty warehouse failed get name returned " << test.GetName() << " when it should have been utah" <<std::endl;
        testsPassed = false;
      }

    }


    //test warehouse with one item
    {
      std::cout << std::endl << "Test warehouse with one item" << std::endl;
      test.ReceiveItem(item1, 1, currentDate);//add item1
      std::set<std::string> inv = test.GetItemsStocked();
      for(std::set<std::string>::iterator it = inv.begin(); it != inv.end(); it++ )
      {
        //should only reach here once
        if(*it != upc1)
        {  
          std::cout << "Test one item failed " << *it << " should not be in invintory" << std::endl;
          testsPassed = false;
        }
      }
    }

    //test warehouse with four items
    {
      std::cout << std::endl << "Test warehouse with four items" << std::endl;
      test.ReceiveItem(item2, 1, currentDate);//add item2
      test.ReceiveItem(item3, 1, currentDate);//add item3
      test.ReceiveItem(item4, 1, currentDate);//add item4
      std::set<std::string> inv = test.GetItemsStocked();
      for(std::set<std::string>::iterator it = inv.begin(); it != inv.end(); it++ )
      {
        //should reach here four times
        if(*it != upc1 && *it != upc2 && *it != upc3 && *it != upc4)
        {  
          std::cout << "Test four items failed " << *it << " should not be in invintory" << std::endl;
          testsPassed = false;
        }
      }
    }


    //test remove two items
    {
      std::cout << std::endl << "Test warehouse remove 2 items" << std::endl;
      test.RequestItem(item1.getUPC(), 1);//remove item 1
      test.RequestItem(item2.getUPC(), 1);//remove item 2
      std::set<std::string> inv = test.GetItemsStocked();
      for(std::set<std::string>::iterator it = inv.begin(); it != inv.end(); it++ )
      {
        //should only reach here twice
        if(*it != upc3 && *it != upc4)
        {  
          std::cout << "Test four items failed " << *it << " should not be in invintory" << std::endl;
          testsPassed = false;
        }
      }
    }


    //test advance date
    {
      std::cout << std::endl << "Test advance date items" << std::endl;
      test.AdvanceDate(currentDate + ADVANCE(1));//advance date 1 day
      std::set<std::string> inv = test.GetItemsStocked();
      for(std::set<std::string>::iterator it = inv.begin(); it != inv.end(); it++ )
      {
        //should only reach here once
        if(*it != upc3)
        {  
          std::cout << "Test advance1 failed " << *it << " should not be in invintory" << std::endl;
          testsPassed = false;
        }
      }
    
      //test advance part 2
      test.AdvanceDate(currentDate+ADVANCE(10));
      inv = test.GetItemsStocked();
      //check if inventory is empty
      if(std::distance(inv.begin(),inv.end()) != 0)
      {
        //should only reach here if it's failed
        std::cout << "Test advance2 failed inventory not empty" <<  std::endl;
        testsPassed = false;
      }
    }
  }

  if(testsPassed)
    std::cout << std::endl << "tests passed" << std::endl;
  else
    std::cout << std::endl << "tests failed" << std::endl;

return 0;
}


