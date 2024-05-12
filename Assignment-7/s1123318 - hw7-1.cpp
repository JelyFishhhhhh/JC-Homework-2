#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <iomanip>
using std::setw;
using std::setfill;

#include <string>
using std::string;

// vector standard header
#ifndef VECTOR_H
#define VECTOR_H

// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
   using value_type = ValueType;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   VectorVal()
      : myFirst(),
      myLast(),
      myEnd()
   {
   }

   pointer myFirst; // pointer to beginning of array
   pointer myLast;  // pointer to current end of sequence
   pointer myEnd;   // pointer to end of array
};


// CLASS TEMPLATE vector
template< typename Ty >
class vector // varying size array of values
{
public:
   using value_type = Ty;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = Ty &;
   using const_reference = const Ty &;
   using size_type = size_t;
   using difference_type = ptrdiff_t;

private:
   using ScaryVal = VectorVal< Ty >;

public:
   using iterator = value_type *;
   using const_iterator = const value_type *;

   vector()
      : myData()
   {
   }

   vector( const size_type count )
      : myData()
   {
      myData.myFirst= new value_type[count]();
      myData.myLast= myData.myFirst+ count;
      myData.myEnd= myData.myFirst+ count;
   }

   vector( const vector &right )
      : myData()
   {
      myData.myFirst= new value_type[right.capacity()]();
      for(size_type i= 0; i< right.size(); i++){

         myData.myFirst[i]= right.myData.myFirst[i];
      }
      myData.myLast= myData.myFirst+ right.size();
      myData.myEnd= myData.myFirst+ right.size();

   }

   ~vector()
   {
      if( myData.myFirst != nullptr )
         delete[] myData.myFirst;
   }

   void push_back( const Ty &val )
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

         value_type* newArr= new value_type[newCapacity]();
         for(size_type i= 0; i< originalSize; i++){

            newArr[i]= myData.myFirst[i];
         }
         newArr[originalSize]= val;
         delete[] myData.myFirst;
         myData.myFirst= newArr;
         myData.myLast= myData.myFirst+ originalSize+ 1;
         myData.myEnd= myData.myFirst+ newCapacity;
      }
      else{

         myData.myFirst[originalSize]= val;
         myData.myLast= myData.myFirst+ originalSize+ 1;
         myData.myEnd= myData.myFirst+ originalCapacity;
      }
   }

   vector& operator=( const vector &right )
   {
      if( this != &right ) // avoid self-assignment
      {
         size_type rightSize = right.size();
         if( rightSize > capacity() )
         {
            if( capacity() > 0 )
               delete[] myData.myFirst; // release space

            size_type newCapacity = capacity() * 3 / 2;
            if( newCapacity < rightSize )
               newCapacity = rightSize;

            myData.myFirst= new value_type[newCapacity];

            for(size_type i= 0; i< rightSize; i++){

               myData.myFirst[i]= right.myData.myFirst[i];
            }
            myData.myLast= myData.myFirst+ rightSize;
            myData.myEnd= myData.myFirst+ newCapacity;
         }
         else{

            for(size_type i= 0; i< rightSize; i++){

               myData.myFirst[i]= right.myData.myFirst[i];
            }
            myData.myLast= myData.myFirst+ rightSize;
         }
      }

      return *this; // enables x = y = z, for example
   }

   void resize( const size_type newSize )
   {
      size_type originalSize = size();
      if( newSize > originalSize )
      {
         if( newSize > capacity() )
         {
            size_type newCapacity = capacity() * 3 / 2;
            if( newCapacity < newSize )
               newCapacity = newSize;

            value_type* newArr= new value_type[newCapacity]();
            for(size_type i= 0; i< originalSize; i++){

               newArr[i]= myData.myFirst[i];
            }
            for(size_type i= originalSize; i< newCapacity; i++){

               newArr[i]= value_type();
            }
            delete[] myData.myFirst;
            myData.myFirst= newArr;
            myData.myLast= myData.myFirst+ newSize;
            myData.myEnd= myData.myFirst+ newCapacity;
         }
         else{
            for(size_type i= originalSize; i< newSize; i++){

               myData.myFirst[i]= value_type();
            }
            myData.myLast= myData.myFirst+ newSize;
         }

      }
      else{

         myData.myLast= myData.myFirst+ newSize;
      }

   }

   void pop_back()
   {
      if( size() > 0 )
         --myData.myLast;
   }

   void clear()
   {
      myData.myLast = myData.myFirst;
   }

   iterator begin()
   {
      return iterator( myData.myFirst );
   }

   iterator end()
   {
      return iterator( myData.myLast );
   }

   bool empty() const
   {
      return myData.myFirst == myData.myLast;
   }

   size_type size() const
   {
      return static_cast< size_type >( myData.myLast - myData.myFirst );
   }

   size_type capacity() const
   {
      return static_cast< size_type >( myData.myEnd - myData.myFirst );
   }

   value_type& front()
   {
      return *myData.myFirst;
   }

   const value_type& front() const
   {
      return *myData.myFirst;
   }

   value_type& back()
   {
      return myData.myLast[ -1 ];
   }

   const value_type& back() const
   {
      return myData.myLast[ -1 ];
   }

private:

   ScaryVal myData;
};

// determine if two vectors are equal and return true, otherwise return false
template< typename Ty >
bool operator==( vector< Ty > &left, vector< Ty > &right )
{
   if( left.size() != right.size() )
      return false; // vectors of different number of elements

   typename vector< Ty >::iterator it1 = left.begin();
   typename vector< Ty >::iterator it2 = right.begin();
   for( ; it1 != left.end(); ++it1, ++it2 )
      if( *it1 != *it2 )
         return false; // vector contents are not equal

   return true; // vector contents are equal
}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=( vector< Ty > &left, vector< Ty > &right )
{
   return !( left == right );
}

#endif // VECTOR_H


// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

template< typename T >
class HugeInteger
{
   template< typename U >
   friend ostream& operator<<( ostream &output, HugeInteger< U > hugeInteger );
public:
   using value_type = typename T::value_type;
   using size_type = typename T::size_type;

   HugeInteger( unsigned int n = 0 ); // constructor; construct a zero HugeInteger with size n

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   HugeInteger( string str );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   bool operator==( HugeInteger &right ); // less than or equal to

   bool operator<( HugeInteger &right );  // less than

   bool operator<=( HugeInteger &right ); // less than or equal to

   HugeInteger square( value_type powerTwo ); // the square of HugeInteger
   HugeInteger squareRoot( value_type powerTwo ); // the square root of HugeInteger

   bool isZero();           // return true if and only if all digits are zero
private:
   T integer;
}; // end class HugeInteger

#endif

// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : integer( ( n == 0 ) ? 1 : n )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
}

template< typename T >
HugeInteger< T >::HugeInteger( string str )
{
   value_type digits[ 1001 ] = {};
   size_type last = str.size() - 1;
   for( size_type i = 0; i <= last; ++i )
      digits[ i ] = static_cast< value_type >( str[ last - i ] ) - '0';

   size_type numDigits = sizeof( value_type ) - 1;
   for( size_type i = 0; i <= last; i += numDigits )
   {
      value_type bigDigit = digits[ i ] + digits[ i + 1 ] * 10 + digits[ i + 2 ] * 100;
      if( sizeof( value_type ) == 8 )
         bigDigit += digits[ i + 3 ] * 1000 +
         digits[ i + 4 ] * 10000 +
         digits[ i + 5 ] * 100000 +
         digits[ i + 6 ] * 1000000;

      integer.push_back( bigDigit );
   }
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( HugeInteger &right )
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger is less than another
template< typename T >
bool HugeInteger< T >::operator<( HugeInteger &right )
{

   if(integer.size()> right.integer.size()){

      return false;
   }
   else if(integer.size()< right.integer.size()){

      return true;
   }
   // else
   typename T::iterator it= integer.end()- 1;
   typename T::iterator it2= right.integer.end()- 1;
   for(; it!= integer.begin()- 1 && it2!= right.integer.begin()- 1; --it, --it2){

      if(*it< *it2){

         return true;
      }
      else if(*it> *it2){

         return false;
      }
   }
   return false;
} // end function operator<

// function that tests if one HugeInteger is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( HugeInteger &right )
{
   return ( *this == right || *this < right );
}

template< typename T >
HugeInteger< T > HugeInteger< T >::square( value_type powerTwo )
{
   HugeInteger zero;
   if( isZero() )
      return zero;

   size_t squareSize = 2 * integer.size();
   HugeInteger square( squareSize );
   
   typename T::iterator it= integer.begin();
   typename T::iterator it2= integer.begin();
   typename T::iterator result;

   for(size_type i= 0; i< integer.size(); ++i, ++it){

      it2= integer.begin();
      result= square.integer.begin()+ i;
      for(size_type j= 0; j< integer.size(); ++j, ++it2, ++result){

         *result+= (*it)* (*it2);

         if(*result>= powerTwo){

            typename T::iterator next= result;
            ++next;
            *next+= *result/ powerTwo;
            *result%= powerTwo;
         }
      }
   }
   while (square.integer.size() > 1 && square.integer.back() == 0) {
      square.integer.pop_back();
   }
   // cout << square<<'\n';
   return square;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::squareRoot( value_type powerTwo )
{
   HugeInteger zero;
   if( isZero() )
      return zero;

   size_type sqrtSize = ( integer.size() + 1 ) / 2;
   HugeInteger sqrt( sqrtSize );
   HugeInteger sq;

   typename T::iterator it= sqrt.integer.end()- 1;

   for(size_type i= 0; i< sqrtSize; i++, --it){

      value_type low= 0;
      value_type high= powerTwo- 1;
      value_type mid;

      while(low<= high){

         mid= (low+ high)/ 2;
         *it= mid;
         // cout << sqrt << '\n';
         sq= sqrt.square(powerTwo);
         // cout << "::" << sq << " " << *this << "::\n";
         if(sq== *this){

            high= mid;
            break;
         }
         else if(sq< *this){

            low= mid+ 1;
         }
         else{

            high= mid- 1;
         }
      }
      *it= high;
   }

   return sqrt;
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
   typename T::iterator it = integer.begin();
   for( ; it != integer.end(); ++it )
      if( *it != 0 )
         return false;

   return true;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename T::value_type numDigits = sizeof( typename T::value_type ) - 1;
   typename T::iterator it = hugeInteger.integer.end() - 1;
   output << *it;
   for( --it; it != hugeInteger.integer.begin() - 1; --it )
      output << setw( numDigits ) << setfill( '0' ) << *it;

   return output; // enables cout << x << y;
}


template< typename T >
void solution()
{
   T powerTwo = 1000;
   if( sizeof( T ) == 8 )
      powerTwo = 10000000;

   int numCases;
   cin >> numCases;
   for( int i = 1; i <= numCases; ++i )
   {
      string str;
      cin >> str;

      HugeInteger< vector< T > > hugeInteger( str );

      cout << hugeInteger.squareRoot( powerTwo ) << endl;

      if( i < numCases )
         cout << endl;
   }
}

int main()
{
   // execute the following 4 instructions one by one, each of them should get an AC
   solution< long int >();
//   solution< unsigned long int >();
//   solution< long long int >();
//   solution< unsigned long long int >();
}