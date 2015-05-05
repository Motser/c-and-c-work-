/*
 *Filename: tester.cpp
 *Auther: Brian Labrum
 *last modified: 1/30/2015
 *version: 2
 *
 */
/* A 'word set' is defined as a set of strings stored
 * in a hashtable that uses chaining to resolve collisions.
 *
 * Peter Jensen
 * January 22, 2015
 */

#ifndef WORDSET_H
#define WORDSET_H

#include<string>

namespace cs3505
{
  class node;  // A forward declaration of the class.  We can now
               // create pointer variables involving the node class.
  
  class wordset
  {
  public:
    wordset(int capacity = 100);     // Constructor.  Notice the default parameter value.
    wordset(const wordset & other);  // Copy constructor
    ~wordset();                      // Destructor

    void add      (std::string element);  // Not const - modifies the object
    void remove   (std::string element);  // Not const - modifies the object
    bool contains (std::string element) const;  // const - does not change the object
    int  size     () const;               // Const - does not change object

    wordset & operator= (const wordset & rhs);  // Modifies this object

    /** This function populates an array of strings with elements from the set.
      * The caller passes an array (by pointer) and a count 'n' to the function.
      * The function copies n unique elements from the set into
      * the array.  (Order does not matter.)  If 'n' is smaller
      * than the number of elements in the set, only 'n' elements are
      * copied into the array in positions [0..n-1].  If 'n' is larger than the number
      * of elements in the set, all the elements in the set are
      * copied into the first positions of the array, and excess positions
      * in the array remain unchanged.
      *
      * It is assumed that the array reference is valid and that n is non-negative.
      */
    void get_elements(std::string *array, int n) const;
     
  private:
    int hash (std::string s) const;  // Const - does not change this object
    void clean ();                   // Not const - modifies the object
    
    int capacity;  // The size of the hashtable
    int count;     // The number of elements in the set
    node** table;  // The hashtable, a pointer to a node pointer
                   //   (which will really be an array of node pointers

    // Below are a few definitions that I use to make sure I am cleaning
    //   up memory properly.  (Notice that I can switch back to public / private
    //   as many times as I like.)  These are not part of a normal
    //   hashtable, but they are here because they help with debugging.
    // These functions and variables are declared static - they exist in the
    //   class, but not in any particular object.  (The objects can access
    //   them, of course.)
    
  public:
    static long long constructor_count ();  // A debugging function for Peter
    static long long destructor_count ();   // A debugging function for Peter

  private:
    static long long constructor_calls;  // A debugging variable for Peter
    static long long destructor_calls;   // A debugging variable for Peter
    
  };

 
}

#endif
