#include <iostream>
using std::cout;
using std::exit;

#include "string.h" // include definition of class String

string::string()
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
}

string::string( const size_type count, const char ch )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   // construct from count * ch
   mySize = count;
   if( count > 15 )
   {
      myRes = ( mySize / 16 ) * 16 + 15;
      bx.ptr = new value_type[ myRes + 1 ];
   }

   for( size_type i = 0; i < mySize; ++i )
      myPtr()[ i ] = ch;
   myPtr()[ mySize ] = value_type();
}

string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

const string::value_type* string::myPtr() const
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

// insert ch at where
string::iterator string::insert( const_iterator where, const char ch )
{
   if( where >= myPtr() && where <= myPtr() + mySize )
   {
      if( mySize == myRes )
      {

         size_type newMyRes;
         if( myRes == 15 || myRes == 31 )
            newMyRes = myRes + 16;
         else
            newMyRes = myRes * 3 / 2;
         
         if (newMyRes > 15) {

             value_type* tempPtr = new value_type[newMyRes]();
         
             for (size_type i = 0; i < where - myPtr(); i++) {

                 tempPtr[i] = myPtr()[i];
             }
             tempPtr[where - myPtr()] = ch;
             for (size_type i = where - myPtr() + 1; i < mySize + 1; i++) {

                 tempPtr[i] = myPtr()[i - 1];
             }
         
             myPtr()[mySize++] = value_type();
             bx.ptr = tempPtr;
             
             myRes = newMyRes;

             return myPtr() + (where - myPtr());
         }
         
         value_type buffer, tmp;
         tmp = ch;
         for (size_type i = where - myPtr(); i < mySize + 1; i++) {

             buffer = myPtr()[i];
             myPtr()[i] = tmp;
             tmp = buffer;
         }
         
         myPtr()[++mySize] = value_type();
         
         return myPtr() + (where - myPtr());
      }
      else
      {

          value_type buffer, tmp;
          tmp = ch;
          for (size_type i = where - myPtr(); i < mySize + 1; i++) {

              buffer = myPtr()[i];
              myPtr()[i] = tmp;
              tmp = buffer;
          }
          myPtr()[++mySize] = value_type();
          
          return myPtr() + (where - myPtr());
      }
   }
   else
      return iterator( nullptr );
}

void string::clear()
{
   mySize = 0;
   myPtr()[ 0 ] = value_type();
}

string::iterator string::begin()
{
   return myPtr();
}

string::const_iterator string::begin() const
{
   return const_iterator( myPtr() );
}

string::iterator string::end()
{
   return myPtr() + static_cast< difference_type >( mySize );
}

string::const_iterator string::end() const
{
   return const_iterator( myPtr() + static_cast< difference_type >( mySize ) );
}

string::reference string::operator[]( const size_type off )
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

string::const_reference string::operator[]( const size_type off ) const
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

string::size_type string::size() const
{
   return mySize;
}

string::size_type string::capacity() const
{
   return myRes;
}

bool string::empty() const
{
   return mySize == 0;
}