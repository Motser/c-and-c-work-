/*
 *Filename: huge_number.h 
 *Auther: Brian Labrum
 *Last Modified:1/23/15  
 *Version 1
 */

#include <string>


/*
 *class that represents non-negitive integers of an 
 *arbitrary number of digits 
 */
class huge_number
{
  public:
    //default constructor initalizes to zero
    huge_number();

    //initializes a huge number using a string that contains only digits
    //behavior for strings that contain things other than digits is undefined
    huge_number( std::string s); 
    
    huge_number(const huge_number &other); //copy constructor
    
    std:: string get_value(); //returns string representation of the number
    
    //overloads for operators =. +. -, *, /, and % the operators should 
    //behave how you would expect for numbers only guaranteed to work 
    //with two huge_number objects
    huge_number& operator= (const huge_number & rhs); 
    huge_number operator+ (const huge_number & rhs) const; 
    huge_number operator- (const huge_number & rhs) const; 
    huge_number operator* (const huge_number & rhs) const; 
    huge_number operator/ (const huge_number & rhs) const; 
    huge_number operator% (const huge_number & rhs) const; 

  private:  
    std:: string number;//number represented by class 
};
