#include <iostream>
using std::cout;
using std::exit;

//#include <algorithm>
//using std::max;

#include "string 2-1.h" // include definition of class String

string::string()
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
}

string::string( const char *const ptr, const size_type count )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   mySize = count;
   myRes = ( mySize / 16 ) * 16 + 15;

   if(mySize> 15){

      bx.ptr= new value_type[myRes+ 1];
      for(size_type i= 0; i< mySize; i++){

         bx.ptr[i]= ptr[i];
      }
      bx.ptr[mySize]= value_type();
      return;
   }

   for(size_type i= 0; i< mySize; i++){

      bx.buf[i]= ptr[i];
   }
   bx.buf[mySize]= value_type();

}

string::string( const size_type count, const char ch )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   // construct from count * ch
   mySize = count;
   myRes = ( mySize / 16 ) * 16 + 15;

   if(mySize> 15){
      delete[] bx.ptr;
      bx.ptr= new value_type[myRes+ 1];
      for(size_type i= 0; i< mySize; i++){

         bx.ptr[i]= static_cast<value_type>(ch);
      }
      bx.ptr[mySize]= value_type();
      return;
   }

   for(size_type i= 0; i< mySize; i++){

      bx.buf[i]= static_cast<value_type>(ch);
   }
   bx.buf[mySize]= value_type();


}

string::string( const string &right )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   mySize = right.mySize;
   myRes = ( mySize / 16 ) * 16 + 15;

   if(mySize== 0){

      return;
   }

   if(mySize> 15){
      
      bx.ptr= new value_type[myRes+ 1];
      for(size_type i= 0; i< mySize; i++){

         bx.ptr[i] = right.bx.ptr ? right.bx.ptr[i] : right.bx.buf[i];
      }
      bx.ptr[mySize]= value_type();
   }
   else{
   
      for(size_type i= 0; i< mySize; i++){

         bx.buf[i]= right.at(i);
      }
      bx.buf[mySize]= value_type();
   }

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

string::reference string::at( const size_type off )
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

string::const_reference string::at( const size_type off ) const
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

string::reference string::front()
{
   return myPtr()[ 0 ];
}

string::const_reference string::front() const
{
   return myPtr()[ 0 ];
}

string::reference string::back()
{
   return myPtr()[ mySize - 1 ];
}

string::const_reference string::back() const
{
   return myPtr()[ mySize - 1 ];
}

const char* string::c_str() const
{
   return myPtr();
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