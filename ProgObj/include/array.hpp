#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <cstdlib>


template <class array_type> class array
{
private:
  int size, capacity;
  array_type *table;

  /* Note: table contains the values, size counts the number of used elements in table, and capacity is the maximum number of entries allocated in table */


  /* Quick reference - functions contained below

   array()
   array(const int& cap_init)
   array(const array& clone) - copie par constructeur
   ~array()
   void add(const array_type& newval) - ajoute
   void remove(const int& i_remove) - supprime
   void remove_ordered(const int& i_remove) - supprime ( garder l'ordre )
   int getSize();
   int getCap();
   void resize(const int& newsize) - retaille
   void reserve(const int& newcap) - reserve
   array operator=(const array& equal) - copie par operateur
   array_type operator[](const int&) - acces
   void show() const
   */



public:
  //=================
 //  Constructors
//=================
  /* No arguments: initialize with 0 size/1 capacity */
  array() {
    size = 0;
    capacity = 1;
    table = new array_type[1];
  }

  /* Initializing with a capacity */
  array(const int& cap_init) {
    size = 0;
    capacity = cap_init;
    table = new array_type[cap_init];
  }

  /* Clone constructor */
  array(const array& clone) {
    // Copy size, capacity, and allocate a same sized table
    size = clone.getSize();
    capacity = clone.getCap();    
    table = new array_type[capacity];
    
    // Copy all values of table
    for (int i = 0 ; i < size ; i++ ) {
      table[i] = clone.table[i];
    } 
  }

/* Destructor */
  ~array() {
    //std::cout << "Destructor: Array\n";
    delete[] table;
  }


  //=============
 //   Methods
//===============
/* Add a new element to table */
  void add(const array_type& newval) {
    // Make sure table is large enough to contain a new value
    if ( size == capacity ) {
      reserve(2*size);
    }
    // Add entry, then update size
    table[size] = newval;
    size++;
  }

/* Remove an element from table */
  void remove(const int& i_remove) {
    // Make sure we don't try to remove an entry that doesn't exist
    if ( i_remove >= size ) {
      std::cout << "Error: Attempt to remove nonexistant value" << std::endl;
    }
    else{
      table[i_remove] = table[size-1]; // Easiest to just replace entry's contents
      size--; // Update size
    }
  }

  void remove_ordered(const int& i_remove) {
    // Make sure we don't try to remove an entry that doesn't exist
    if ( i_remove >= size ) {
      std::cout << "Error: Attempt to remove nonexistant value" << std::endl;
    }
    else{
      // Set each element's value equal to that of the element after it
      // starting from the element to be removed: this value will be lost
      for ( int i = i_remove ; i < size ; i++ ) {
	table[i] = table[i+1];
      }
      size--; // Update size
    }
  }

/* Return size value */
  int getSize() const {
    return size;
  }

  int getCap() const {
    return capacity;
  }

/* Make the effective size bigger/smaller
     Note: if bigger, the new entries will be set to 0 */
  void resize(const int& newsize) {
    if ( newsize < size ) {/*do not shrink table*/}

    else {
    // Update capacity if needed
      if ( newsize > capacity ) {
	reserve(2*capacity);
      }
      size = newsize; // Update size
      capacity = 2*capacity; // update capacity value
    }
  }


/* Make the total/maximum size bigger/smaller
     Note: if bigger, new entries set to 0
           if smaller, values will be lost     */
  void reserve(const int& newcap) {
    // Assign new table of desired size, initialize to 0
    array_type *tmp;
    tmp = new array_type[newcap];

    // Copy values to new table, making sure not to leave the array's memory space
    int max;
    if ( newcap < size ) { max = newcap; }
    else { max = size; }
    for ( int i = 0 ; i < max ; i++ ) {
      tmp[i] = table[i];
    }

    // Update capacity, delete old table, swap pointers
    capacity = newcap;
    delete[] table;
    table = tmp;
  }


/* Obtain pointer to the i'th element of table
     -allows both reading and writing of table[i] */

  array_type& operator[](const int& place) const {
    // Make sure the desired element exists
    if ( place >= size || place < 0 ) {
      std::cout << "Error: Attempt to access nonexistant entry: " << place << std::endl;
      return table[capacity-1]; // probably 0
    }
    // Print element value
    else {
      //array_type *tmp;
      //tmp = table+place;
      return table[place];
    }
  }

  /* Set one table equal to another */
  array operator=(const array& equal) {
    // Resize if necessary
    if ( capacity < equal.size ) {
      reserve(equal.size);
    }
    // Copy values
    for ( int i = 0 ; i < equal.size ; i++ ) {
      table[i] = equal.table[i];
    }
    size = equal.size;
  }

  /* Display entire table */
  void show() const {
    for ( int i = 0 ; i < size ; i++ ) {
      std::cout << table[i] << "  ";
    }
    std::cout << std::endl;
  }
};


#endif
