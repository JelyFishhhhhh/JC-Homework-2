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

         size_type position = where - myPtr();     // modify
         value_type* temp = new value_type[newMyRes + 1];
         /* myPtr()-> temp */
         for (size_t i = 0; i < mySize; i++)
         {
             temp[i] =myPtr()[i];
         }
         // temp[position] = ch;    delete

         if (newMyRes > 15)      // modify
         {
               // delete[] myPtr();    delete
               bx.ptr= new value_type[newMyRes];      // added
         
               /* copy from 0~ position */
               for (size_t i = 0; i < position; i++)
               {
                  bx.ptr[i] = temp[i];
               }
               bx.ptr[position]= ch;     // added
               for (size_t i = position, j = 0; i < mySize; i++, j++)//modify
               {
                  bx.ptr[i +1] = temp[i];//modify
               }

               // delete[] temp;    delete

               bx.ptr[++mySize] = value_type();    // modify
               myRes = newMyRes;
         }     // modify
         // added start
         else{

            value_type buffer, tmp;
            tmp = ch;
            for (size_type i = where - myPtr(); i < mySize + 1; i++) {

               buffer = myPtr()[i];
               myPtr()[i] = tmp;
               tmp = buffer;
            }
            myRes= newMyRes;
            myPtr()[++mySize] = value_type();
         }
         // added end

         return myPtr() + position;//modify
      }
      else
      {
          value_type position = where - myPtr();
          value_type buffer, tmp = ch;//add

         //  myPtr()[mySize] = ch;     delete

          for (size_t i = position; i <mySize+1; i++)//modify
          {
              //myPtr()[i] = myPtr()[i - 1]; delete
              buffer = myPtr()[i];
              myPtr()[i] = tmp;
              tmp = buffer;
          }
          ++mySize;
          myPtr()[mySize]= value_type();     // added

          return myPtr() + position;//modify

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