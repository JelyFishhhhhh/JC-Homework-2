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

         value_type* buffer = new value_type[newMyRes + 1];
         size_t num = where - myPtr();
         if (myRes <= 15)
         {
            for (size_t i = 0; i < num; i++)
            {
                buffer[i] = bx.buf[i];
            }
            buffer[num] = ch;
            for (size_t i = num; i < mySize; i++)
            {
                buffer[i+1] = bx.buf[i];
            }
            bx.ptr = new value_type[newMyRes + 1];
            for (size_t i = 0; i < mySize + 1; i++)
            {
                bx.ptr[i] = buffer[i];
            }
            bx.ptr[mySize + 1] = value_type();
            mySize = mySize + 1;
            myRes = newMyRes;
            return myPtr() + (where - myPtr());
         }
         else
         {
             for (size_t i = 0; i < num; i++)
             {
                 buffer[i] = bx.ptr[i];
             }
             buffer[num] = ch;
             for (size_t i = num; i < mySize; i++)
             {
                 buffer[i + 1] = bx.ptr[i];
             }
             buffer[mySize + 1] = value_type();
             //delete[] bx.ptr;
             bx.ptr = buffer;
             mySize = mySize + 1;
             myRes = newMyRes;
             return myPtr() + (where - myPtr());
         }
      }
      else
      {
          if (myRes <= 15)
          {
              value_type* buffer = new value_type[myRes + 1];
              size_t num = where - myPtr();
              for (size_t i = 0; i < num; i++)
              {
                  buffer[i] = bx.buf[i];
              }
              buffer[num] = ch;
              for (size_t i = num; i < mySize; i++)
              {
                  buffer[i + 1] = bx.buf[i];
              }
              for (size_t i = 0; i < mySize + 1; i++)
              {
                  bx.buf[i] = buffer[i];
              }
              mySize = mySize + 1;
              bx.buf[mySize] = value_type();
              delete[] buffer;
              return myPtr() + (where - myPtr());
          }
          else
          {
              value_type* buffer = new value_type[myRes + 1];
              size_t num = where - myPtr();
              for (size_t i = 0; i < num; i++)
              {
                  buffer[i] = bx.ptr[i];
              }
              buffer[num] = ch;
              for (size_t i = num; i < mySize; i++)
              {
                  buffer[i + 1] = bx.ptr[i];
              }
              buffer[mySize + 2] = value_type();
              delete[] bx.ptr;
              bx.ptr = buffer;
              mySize = mySize + 1;
              //delete[] buffer;
              return myPtr() + (where - myPtr());
          }

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