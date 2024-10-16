#include "vector.h" // include definition of class vector 

// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
   : myFirst(),
     myLast(),
     myEnd()
{
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector( const size_type count )
   : myFirst( count == 0 ? nullptr : new value_type[ count ]() ),
     myLast( count == 0 ? nullptr : myFirst + count ),
     myEnd( count == 0 ? nullptr : myLast )
{
}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
}

// Resizes the container so that it contains "newSize" elements.
// If "newSize" is smaller than the current container size,
// the content is reduced to its first "newSize" elements, removing those beyond.
// If "newSize" is greater than the current container size,
// the content is expanded by inserting at the end as many elements as needed
// to reach a size of "newSize".
// The new elements are initialized as 0.
// If "newSize" is also greater than the current container capacity,
// an automatic reallocation of the allocated storage space takes place.
void vector::resize( const size_type newSize )
{
   size_type originalSize = size();
   if (newSize > originalSize)
   {
      if (newSize > capacity())
      {
         size_type newCapacity = capacity() * 3 / 2;
         if (newCapacity < newSize)
            newCapacity = newSize;

         value_type* temp = new value_type[newCapacity + 1]();     // modify

         for (size_t i = 0; i < size(); i++) {
            temp[i] = myFirst[i];
         }
         delete[] myFirst;
         myFirst = temp;
         
         myEnd = myFirst + newCapacity;
         
      //   for (size_t i = size(); i < newSize; i++) {
      //       myFirst[i] = value_type();
      //   }   delete
      }

      myLast = myFirst + newSize;
   }
   else { 
      // add start
      for (size_type i = originalSize; i < newSize; i++) {

         myFirst[i] = value_type();
      }

      myLast = myFirst + newSize;
      // add end
   }
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear() // erase all
{
   myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::iterator vector::begin()
{
   return myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::const_iterator vector::begin() const
{
   return const_iterator( myFirst );
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::iterator vector::end()
{
   return myLast;
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::const_iterator vector::end() const
{
   return const_iterator( myLast );
}

// Returns whether the vector is empty (i.e. whether its size is 0).
bool vector::empty() const
{
   return myFirst == myLast;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size() const
{
   return static_cast< size_type >( myLast - myFirst );
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity() const
{
   return static_cast< size_type >( myEnd - myFirst );
}

// Returns a reference to the element at position "pos" in the vector container.
vector::reference vector::operator[]( const size_type pos )
{
   return myFirst[ pos ];
}

// Returns a reference to the element at position "pos" in the vector container.
vector::const_reference vector::operator[]( const size_type pos ) const
{
   return myFirst[ pos ];
}