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

// The vector is extended by inserting a new element before the element
// at the specified position, effectively increasing the container size by one.
// This causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
// Relocates all the elements that were after "where" to their new positions.
vector::iterator vector::insert( const_iterator where, const value_type &val )
{
   if( where >= myFirst && where <= myLast )
   {
      size_type originalSize = size();
      size_type originalCapacity = capacity();
      if( originalSize == originalCapacity )
      {
         size_type newCapacity;
         if( originalCapacity <= 1 )
            newCapacity = originalCapacity + 1;
         else
            newCapacity = originalCapacity * 3 / 2;

         value_type* tempPtr = myFirst;
         myFirst = new value_type[newCapacity]();

         for (size_type i = 0; i < where - tempPtr; i++) {

             myFirst[i] = tempPtr[i];
         }
         myFirst[where - tempPtr] = val;
         for (size_type i = where - tempPtr+ 1; i < originalSize+ 1; i++) {

             myFirst[i] = tempPtr[i- 1];
         }
         myLast = myFirst + originalSize+ 1;
         myEnd = myFirst + newCapacity;

         return myFirst + (where - tempPtr);
      }
      else
      {
          value_type buffer, tmp;
          tmp = val;
          for (size_type i = where- myFirst; i< originalSize+ 1; i++) {

              buffer= myFirst[i];
              myFirst[i] = tmp;
              tmp = buffer;
          }
          myLast= myFirst+ originalSize+ 1;
          myEnd = myFirst + capacity();
          return myFirst + (where- myFirst);
      }
      
   }
   else
      return nullptr;
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