/*
 *Filename: tester.cpp
 *Auther: Brian Labrum
 *last modified: 1/30/2015
 *version: 1
 *
 */


/*
 * This is a tester similar to the tester written in class.  It reads
 * words from a text file, then adds the words to two sets: A built-in
 * set class, and our wordset class.  After reading the file, it
 * prints out all the words stored in the STL set object.  At the end
 * of the test, it prints out the sizes of both sets to see that they
 * are the same.
 *
 * After the test completes, I make sure the local variabls are properly
 * cleaned up.
 *
 * If the comments wrap lines, widen your emacs window.
 *
 * Peter Jensen
 * January 22, 2015
 */


#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include "wordset.h"
#include "node.h"

using namespace std;

// Note:  Our classes were declared in a cs3505 namepsace.
//        Instead of 'using namespace cs3505', I qualify the class names below with cs3505::

int main ()
{
  
  bool tests_passed = true; //will be set to false if any of the tests fail

  // Open up another block.  This way, when the block ends,
  // variables local to the block will be destroyed, but main
  // will still be running.  (Did you know that you can open
  // up a block at any time to control local variable scope and
  // lifetime?)
  
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
  
    set<string>      stl_set_of_words;  // The built-in set class - no constructor parameters.

    cs3505::wordset  our_set_of_words(1000);  // Our set class, with a hashtable of 1000 slots.
  
    // Open the file stream for reading.  (We'll be able to use it just like
    //   the keyboard stream 'cin'.)

    ifstream in("Yankee.txt");

    // Loop for reading the file.  Note that it is controlled
    //   from within the loop (see the 'break').
    
    while (true)
    {
      // Read a word (don't worry about punctuation)
      
      string word;
      in >> word;

      // If the read failed, we're probably at end of file
      //   (or else the disk went bad).  Exit the loop.
      
      if (in.fail())
	break;

      // Word successfully read.  Add it to both sets.
      
      stl_set_of_words.insert(word);
      our_set_of_words.add(word);
    }

    // Close the file.

    in.close();

    // Print out the words found in the STL set.  I do this to show
    //   students how to get at the entries in an STL object.  For
    //   more examples, look up 'STL iterator examples'.
    // Notice that the iterator object 'it' acts like a pointer, but
    //   it is not a pointer.  (Bad, bad, bad design choice, but not mine!)
    // Feel free to comment this out.
/* 
    for (set<string>::iterator it = stl_set_of_words.begin(); it != stl_set_of_words.end(); it++)
    {
      string s = *it;
      cout << s << endl;
    }
*/
    //compare the number of words in each set 
    int our_size = our_set_of_words.size();
    int stl_size = stl_set_of_words.size();  
    cout << endl;
    cout << "STL set contains " << stl_size << " unique words.\n";
    cout << "Our set contains " <<  our_size << " unique words.\n";
    if(our_size != stl_size)//check they are the same size
    {
      cout<<"Failed size test. Size was: " << our_size << " should have been: " << stl_size << endl;
      tests_passed = false; 
    }
    cout << endl;
   
    //test contains
    cout << endl;
    cout << "Test contains" << endl;  
    for (set<string>::iterator it = stl_set_of_words.begin(); it != stl_set_of_words.end(); it++)
    {
      string s = *it; 
      if(!our_set_of_words.contains(s))
      {
        cout << "contains faild returned false when it should have been true for the word : "<< s <<endl;
        tests_passed = false;
      }
    }
    cout<<endl;
    


    //test = operator 
    cs3505::wordset our_equals_set;//make an empty set
    our_equals_set = our_set_of_words;
    cout << endl;
    cout << "Test = operator" << endl;
    int size1 = our_equals_set.size();
    int size2 = our_set_of_words.size();
    if(size1 != size2)//check size
    {
      cout << "= operator failed size is " << size1 << " should be " << size2 << endl;
      tests_passed = false;
    }
    for (set<string>::iterator it = stl_set_of_words.begin(); it != stl_set_of_words.end(); it++)
    {
      string s = *it; 
      if(!our_equals_set.contains(s))
      {
        cout << "contains faild returned false when it should have been true for the word : "<< s <<endl;
        tests_passed = false;
      }
    }
     
    //test copy constructor
    cs3505::wordset our_copy_set(our_set_of_words);
    cout << endl;
    cout << "Test Copy constructor" << endl;
    size1 = our_copy_set.size();
    size2 = our_set_of_words.size();
    if(size1 != size2)//check size
    {
      cout << "Copy constructor failed size is " << size1 << " should be " << size2 << endl;
      tests_passed = false;
    }
    for (set<string>::iterator it = stl_set_of_words.begin(); it != stl_set_of_words.end(); it++)
    {
      string s = *it; 
      if(!our_copy_set.contains(s))
      {
        cout << "contains faild returned false when it should have been true for the word : "<< s <<endl;
        tests_passed = false;
      }
    }


    //test get elements
    cout << endl <<"Test get elements" << endl;
    //test for getting all elements
    {

      int n = our_set_of_words.size();//set n 
      cs3505::wordset our_array_set(1000);          
      string array[n];//make new array
      our_set_of_words.get_elements(array,n);//get elements
      //check that elements are in set
      for(int i; i < n && array[i] != ""; i++)
        if(!our_set_of_words.contains(array[i]))
        {
          cout << "faild getting all elements array contains: "<< array[i] << " which is not in list "<<endl;
          tests_passed = false;
        }
      //fill new set with words from old set
      for(int i = 0; i < n && array[i] != ""; i++)
        our_array_set.add(array[i]);
      //check size
      if(our_array_set.size() != n) 
        {
          cout << "faild getting all elements array is size: "<< our_array_set.size() << " when it should be size: " << n << endl;
          tests_passed = false;
        }

    }
    //test for getting more than in the list 
    {

      int n = our_set_of_words.size() + 100;//set n 
      cs3505::wordset our_array_set(1000);          
      string array[n];//make new array
      our_set_of_words.get_elements(array,n);//get elements
      //check that elements are in set
      for(int i; i < n && array[i] != ""; i++)
        if(!our_set_of_words.contains(array[i]))
        {
          cout << "faild getting all elements array contains: "<< array[i] << " which is not in list "<<endl;
          tests_passed = false;
        }
      //fill new set with words from old set
      for(int i = 0; i < n && array[i] != ""; i++)
      {
        our_array_set.add(array[i]);
      }
      //check size
      if(our_array_set.size() != our_set_of_words.size()) 
        {
          cout << "faild getting more elements array is size: "<< our_array_set.size() << " when it should be size: " << our_set_of_words.size() << endl;
          tests_passed = false;
        }

    }
    //test for getting some elements
    {

      int n = our_set_of_words.size()-100;//set n 
      cs3505::wordset our_array_set(1000);          
      string array[n];//make new array
      our_set_of_words.get_elements(array,n);//get elements
      //check that elements are in set
      for(int i; i < n && array[i] != ""; i++)
        if(!our_set_of_words.contains(array[i]))
        {
          cout << "faild getting some elements array contains: "<< array[i] << " which is not in list "<<endl;
          tests_passed = false;
        }
      //fill new set with words from old set
      for(int i = 0; i < n && array[i] != ""; i++)
        our_array_set.add(array[i]);
      //check size
      if(our_array_set.size() != n) 
        {
          cout << "faild getting all elements array is size: "<< our_array_set.size() << " when it should be size: " << n << endl;
          tests_passed = false;
        }

    }

    //test remove
    cout << endl << "Test remove " << endl;
    our_set_of_words.remove("MARK"); //check for single removed   
    size1 = our_set_of_words.size();
    size2 = stl_set_of_words.size() -1;;//one item removed so list should be one less
    if(size1 != size2)//check if count changed
    {
      cout << "Remove failed size wrong size is " << size1 << " should be " << size2 << endl;
      tests_passed = false;
    }
    if(our_set_of_words.contains("MARK"))
    {
      cout << "Remove failed didn't remove word" << endl;
      tests_passed = false;
    }

    our_set_of_words.remove("ajlsdfhfjkaavbutkraadvf");//test remove of element not in set

    size1 = our_set_of_words.size();
    if(size1 != size2)//check if count changed
    {
      cout << "Remove failed size wrong size is " << size1 << " should be " << size2 << endl;
      tests_passed = false;
    }
    if(our_set_of_words.contains("ajlsdfhfjkaavbutkraadvf"))
    {
      cout << "Remove failed added word" << endl;
      tests_passed = false;
    }

    //remove all words
    for (set<string>::iterator it = stl_set_of_words.begin(); it != stl_set_of_words.end(); it++)
    {
      string s = *it;
      our_set_of_words.remove(s); 
      if(our_set_of_words.contains(s))
      {
        cout << "contains faild returned true when it should have been false for the word : "<< s <<endl;
        tests_passed = false;
      }
    }
      size1 = our_set_of_words.size();
      if(size1 != 0) //set sould be empty 
      {
        cout << "Remove failed size wrong size is " << size1 << " should be 0" << endl;
        tests_passed = false;
      }

    


    // Done.  Notice that this code block ends below.  Any local
    // variables declared within this block will be automatically
    // destroyed.  Local objects will have their destructors
    // called.

  }

  // Now that the objects have been destroyed, I will simply call my auditing
  // code to print out how many times constructors have been called, and
  // how many times destructors have been called.  They should exactly match.
  // If not, we have a memory problem.

  long long con_num_wordset = cs3505::wordset::constructor_count();//number of times wordset constructor called
  long long decon_num_wordset = cs3505::wordset::destructor_count();//number of times wordset deconstructor called
  cout << "Class cs3505::wordset:" << endl;
  cout << "    Objects created:  " << con_num_wordset << endl;
  cout << "    Objects deleted:  " << decon_num_wordset << endl;
  if(con_num_wordset != decon_num_wordset)
  {
    cout << "Wordset constructor and deconstructor not called the same number of times" <<endl;
    tests_passed = false;
  }
  cout << endl;

  long long con_num_node = cs3505::node::constructor_count();//number of times node constructor called
  long long decon_num_node = cs3505::node::destructor_count();//number of times node deconstructor called
  cout << "Class cs3505::node:" << endl;
  cout << "    Objects created:  " << con_num_node  << endl;
  cout << "    Objects deleted:  " <<  decon_num_node << endl;
  if(con_num_node != decon_num_node)
  {
    cout << "Node constructor and deconstructor not called the same number of times" <<endl;
    tests_passed = false;
  }
  cout << endl;
  
  //check if all the tests passed
  if (tests_passed)
  {
    cout << "Tests passed" << endl;
  }else //if tests failed
  {
    cout << "Tests failed" << endl;
  }
  // Now we're really done.  End main.
  
  return 0;
}
