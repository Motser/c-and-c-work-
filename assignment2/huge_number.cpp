/*
 *  *Filename: huge_number.h 
 *   *Auther: Brian Labrum
 *    *Last Modified:1/23/15  
 *     *Version 1
 *      */

#include <string>
#include "huge_number.h"
#include <iostream>

std:: string multiply(const std::string left, const std::string right);
std:: string add(const std::string left, const std::string right);
std:: string subtract(const std::string left, const std::string right);
std:: string divide(const std::string left, const std::string right);
std:: string mod(const std::string left, const std::string right);

/*
 *functions for class that represents non-negitive integers of an 
 *arbitrary number of digits
 */

/*
 * default constructor initalizes number to zero
 */
huge_number::huge_number()
{
  this->number = "0";
}

/*
 *initializes a huge number using a string that contains only digits
 *behavior for strings that contain things other than digits is undefined
 */
huge_number::huge_number( std::string s)
{
  this->number = s;
}

/*
 * copy constructor
 */
huge_number::huge_number(const huge_number &other)
{
  this->number = other.number;
}

/*
 *returns string representation of the number
 */
std::string huge_number::get_value()
{
  return this->number;
}    

/*
 *overload the = operator set the value of this to that of rhs
 */
huge_number& huge_number::operator= (const huge_number & rhs)
{
  this->number = rhs.number;
  return *this;
}

/*
 *overload the + operator add the values of this and rhs
 */
huge_number huge_number::operator+ (const huge_number & rhs) const
{
  std::string left = this->number;
  std::string right = rhs.number;
  std::string temp = add(left,right);
  huge_number result(temp);
  return result;
} 


/*
 *overload the - operator subtract the values of this and rhs if this results in a
 * negitive number sets value to 0
 */
huge_number huge_number::operator- (const huge_number & rhs) const
{
  huge_number result(subtract(this->number, rhs.number));
  return result;
} 


/*
 *overload the * operator multiply the values of this and rhs
 *use long mulitplication starting with the significant digit 
 *of the multiplier
 */
huge_number huge_number::operator* (const huge_number & rhs) const
{

  std::string left = this->number;
  std::string right = rhs.number;
  std::string temp = multiply(left,right);
  huge_number result(temp);
  return result;
}

/*
 *overload the / operator divide the values of this and rhs
 */
huge_number huge_number::operator/ (const huge_number & rhs) const
{
  huge_number result(divide(this->number,rhs.number));
  return result;
} 


/*
 *overload the % operator get the remader of the values of this and rhs
 */
huge_number huge_number::operator% (const huge_number & rhs) const
{ 
  huge_number result(mod(this->number, rhs.number));
  return result;
}

/*
 * Adds two numbers stored in strings, building a string result.
 */
std:: string add(const std::string left, const std::string right)
{
  // Build up a string to contain the result.
   
  std::string result = "";

  // Work right to left.

  int left_pos  = left.length()  - 1;
  int right_pos = right.length() - 1;
 
  int carry = 0;

  // Loop, adding columns until no more digits remain.

  while (left_pos >= 0 || right_pos >= 0 || carry > 0)
  {
    // Get the digit from each string, or 0 if none.

    int left_digit  = left_pos  >= 0 ? left[left_pos--]   - '0' : 0;
    int right_digit = right_pos >= 0 ? right[right_pos--] - '0' : 0;

    // Calcuate the sum of the digits.

    int sum = left_digit + right_digit + carry;
    carry = sum / 10;
    sum   = sum % 10 + '0';

    // Put the sum into the new string (at the left side)

    result.insert (0, 1, static_cast<char>(sum) );

  }

  // Strip out any leading 0's from our result.  (Might not be needed)

  while (result.length() > 0 && result[0] == '0')
    result.erase(0, 1);

  // If the string is empty, it's a 0.  Put one back.

  if (result.length() == 0)
    result = "0";

  return result;
}

/*
 *subtraction method for two strings 
 *works right to left keeping track of 
 *the carry.
 *
 * if the result is less then 0 return 0
 */
std:: string subtract(const std::string left, const std::string right)
{
  //new value
  std::string value;
  //start from the right
  int left_pos = left.length() -1;
  int right_pos = right.length() -1;
  //carry value
  int carry = 0;


  //loop through strings
  while(left_pos >= 0 || right_pos >= 0)
  {
     //get digits by checking if position is greater than zero
     //then removing the asscii bias by - '0'
     int left_digit = left_pos >= 0 ? left[left_pos--] - '0' : 0;
     int right_digit = right_pos >= 0 ? right[right_pos--] - '0' : 0;
      
     //subtract the digits
     
     int sum = left_digit - right_digit - carry;
     //check for carry
     if (sum < 0)
     {
       //if sum is less then 0 then carry is 1 and sum is sum +10
       carry = 1;
       sum +=10;// remove carry
       
     }
     else 
     {
       carry = 0;
     }
     //add asscii bias
     sum += '0';
     value.insert(0,1, static_cast<char>(sum));//cast the sum into a char and insert it to the front
  } 

  //if their is a carry value is negative and results in zero
  if(carry > 0)
    value = "0";

  //remove leading zeros
  while(value.length()>0 && value[0] == '0')
    value.erase(0,1);

  //if string is empty set to zero
  if(value.length() == 0)
    value = "0";

  return value;
}
/*
* Multiplies two numbers stored in strings, building a string result.
* The algorithm is long multiplication, starting with the most significant
* digit of the multiplier.
*/
std:: string multiply(const std::string left, const std::string right)
{
  std::string result = "0";

  int right_pos = 0;

  while (right_pos < right.length())
  {
    result.append("0");  // Multiply the product by 10.

    int right_digit = right[right_pos++] - '0';

    for (int i = 0; i < right_digit; i++)
      result = add(result, left);
  }

  // Strip out any leading 0's from our result.  (Might not be needed)

  while (result.length() > 0 && result[0] == '0')
    result.erase(0, 1);

  // If the string is empty, it's a 0.  Put one back.

  if (result.length() == 0)
    result = "0";

  return result;
}
/*
 *divide left/right by counting how many times right goes into left
 */
std:: string divide(const std::string left, const std::string right)
{
  std::string count ("0");//number of subtractions
  std::string dividend = left; 
  std::string divisor;
  //used for large numbers
  while(dividend.length()!=right.length())
  {
     divisor = right;
     //difference between the two lengths
     int offset = dividend.length() - right.length();
     //amount to increase count by
     std:: string offset2 = "1";
     //incease divisor and offset 2 by a factor of 10
     for(int i =0; i<offset-1; i++)
     {
       divisor.append("0");
       offset2.append("0");
     }
     //take the dividend from the divisor untill the offset needs to change
     while(dividend.length()-right.length() == offset)
     {
       dividend = subtract(dividend, divisor);
       count = add(count, offset2);
     }
  
  }

  //if they have the same number of digits 
  while(subtract(dividend, right) != "0")
  {
    dividend = subtract(dividend,right);
    count = add(count,"1");
  }
  if(dividend == right)
    count = add(count, "1");
  return count;
}

std:: string mod(const std::string left, const std::string right)
{
  std::string result;
  std::string temp = divide(left,right);
  result = subtract(left, multiply(right, temp));
  return result;
}
