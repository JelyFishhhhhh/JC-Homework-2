#include <iostream>
using std::cout;
using std::exit;

#include <algorithm>
using std::max;

#include "string.h" // include definition of class String

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

      bx.ptr= new value_type[myRes+ 1]();
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
      
      bx.ptr= new value_type[myRes+ 1]();
      for(size_type i= 0; i< mySize; i++){

         bx.ptr[i] = right.bx.ptr ? right.bx.ptr[i] : right.bx.buf[i];
      }
      bx.ptr[mySize]= value_type();
   }
   else{
   
      for(size_type i= 0; i< mySize; i++){

         bx.buf[i]= right[i];
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

//string& string::assign( const string &right )
string& string::operator=( const string &right )
{
   if( this != &right )
   {
      if( right.mySize > myRes )
      {
         if( myRes > 15 )
            delete[] bx.ptr;

         myRes = myRes * 3 / 2;
         if( myRes < ( right.mySize / 16 ) * 16 + 15 )
            myRes = ( right.mySize / 16 ) * 16 + 15;

         bx.ptr= new value_type[myRes+ 1];
         for(size_type i= 0; i< right.mySize; i++){

            myPtr()[i]= right.myPtr()[i];
         }
      }
      else{

         if(myRes> 15){
   
            for(size_type i= 0; i< right.mySize; i++){
               
               bx.ptr[i]= right.myPtr()[i];
            }

         }
         else{

            for(size_type i= 0; i< right.mySize; i++){
               
               myPtr()[i]= right.myPtr()[i];
            }

         }
      }
      
      mySize= right.mySize;
      myPtr()[mySize]= value_type();
   }

   return *this;
}

bool string::operator==( const string &right ) const
{

   if(this->size()!=right.size()){

      return false;
   }
   for(size_type i= 0; i< this->size(); i++){

      if(myPtr()[i]!=right.myPtr()[i]){

         return false;
      }
   }
   return true;
}

bool string::operator!=( const string &right ) const
{
   return !operator==( right );
}

string& string::erase( const size_type off, size_type count )
{
   if( off < mySize )
   {
      
      if(off+ count> mySize){

         count= mySize- off;
      }
      
      for(size_type i = off; i + count < mySize; ++i){
         myPtr()[i] = myPtr()[i + count];
      }

      this->resize(mySize- count);
      // for(size_type i= mySize- count; i< mySize; i++){

      //    myPtr()[i]= value_type();
      // }
   }

   return *this;
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

void string::push_back( char ch )
{
   if( mySize == myRes )
   {
      size_type newMyRes = myRes * 3 / 2;
      if( newMyRes < ( ( mySize + 1 ) / 16 ) * 16 + 15 )
         newMyRes = ( ( mySize + 1 ) / 16 ) * 16 + 15;

      value_type* newPtr= new value_type[newMyRes+ 1]();
      for(size_type i= 0; i< mySize; i++){

         newPtr[i]= myPtr()[i];
      }
      
      if(myRes> 15){

         delete[] bx.ptr;
      }

      newPtr[mySize++]= ch;
      newPtr[mySize]= value_type();

      bx.ptr= newPtr;
      myRes= newMyRes;
   }
   else{

      if(mySize> 15){

         myPtr()[mySize++]= ch;
         myPtr()[mySize]= value_type();
      }
      else{

         myPtr()[mySize++]= ch;
         myPtr()[mySize]= value_type();
      }
   }
}

void string::pop_back()
{
   if( mySize > 0 )
   {
      --mySize;
      myPtr()[ mySize ] = value_type();
   }
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

void string::resize( const size_type newSize, const char ch )
{
   // determine new length, padding with ch elements as needed
   if( newSize > mySize )
   {
      if( newSize > myRes )
      {
         size_type newMyRes = myRes * 3 / 2;
         if( newMyRes < ( newSize / 16 ) * 16 + 15 )
            newMyRes = ( newSize / 16 ) * 16 + 15;

         value_type* newPtr= new value_type[newMyRes+ 1]();
         
         for(size_type i= 0; i< mySize; i++){

            newPtr[i]= myPtr()[i];
         }
         for(size_type i= mySize; i< newSize; i++){

            newPtr[i]= ch;
         }

         newPtr[newSize]= value_type();

         if(myRes> 15){

            delete[] bx.ptr;
         }
         
         bx.ptr= newPtr;
         myRes= newMyRes;
      }
      else{
         
         for(size_type i= mySize; i< newSize; i++){

            myPtr()[i]= ch;
         }
         myPtr()[newSize]= value_type();
      }
      mySize= newSize;
   }
   else if(newSize< mySize){

      mySize= newSize;
      myPtr()[mySize]= value_type();
   }

}

string::size_type string::capacity() const
{
   return myRes;
}

bool string::empty() const
{
   return mySize == 0;
}