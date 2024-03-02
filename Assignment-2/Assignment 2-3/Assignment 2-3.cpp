 // string test program.
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

#include <string>
#include "string 2-3.h"

void testPushBack1();
void testPushBack2();
void testPushBack3();
void testPushBack4();

// return true iff string1 == string2
bool equal( string &string1, std::string &string2 );

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

int capacities[ 200 ];
const unsigned int number = 80;

int main()
{
   ifstream capFile( "capacities.txt", ios::in );

   if( !capFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   for( int i = 0; i <= number; i++ )
      capFile >> capacities[ i ];

   capFile.close();

   testPushBack1();
   testPushBack2();
   testPushBack3();
   testPushBack4();
   cout << endl;

   system( "pause" );
}

void testPushBack1()
{
   int numErrors = 0;
   for( int s = 0; s <= 15; s++ )
   {
      string string1( s, '\0' );
      std::string string2( s, '\0' );

      for( int i = 0; i < s; i++ )
      {
         char value = static_cast< char >( 97 + rand() % 26 );
         string1.at( i ) = value;
         string2[ i ] = value;
      }

      char value = static_cast< char >( 97 + rand() % 26 );
      string1.push_back( value );
      string2.push_back( value );

      if( !equal( string1, string2 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testPushBack2()
{
   const unsigned int number = 30;
   int numErrors = 0;
   for( int i = 0; i <= number; i++ )
   {
      int c = capacities[ i ];
      for( int s = 0; s <= c; s++ )
      {
         string string1( s, '\0' );
         std::string string2( s, '\0' );

         char **ptr1 = reinterpret_cast< char ** >( &string1 );
         char **ptr2 = reinterpret_cast< char ** >( &string2 ) + offset;
         delete[] * ptr1;
         delete[] * ptr2;
         *ptr1 = new char[ c + 1 ];
         *ptr2 = new char[ c + 1 ];

         size_t *myCap1;
         size_t *myCap2;
         if( sizeof( size_t ) == 4 )
         {
            myCap1 = reinterpret_cast< size_t * >( &string1 ) + 5;
            myCap2 = reinterpret_cast< size_t * >( &string2 ) + 5 + offset;
         }
         else
         {
            myCap1 = reinterpret_cast< size_t * >( &string1 ) + 3;
            myCap2 = reinterpret_cast< size_t * >( &string2 ) + 3 + offset;
         }

         *myCap1 = c;
         *myCap2 = c;

         for( int j = 0; j < s; j++ )
         {
            char value = static_cast< char >( 97 + rand() % 26 );
            string1.at( j ) = value;
            string2[ j ] = value;
         }
         string1.at( s ) = '\0';
         string2[ s ] = '\0';

         char value = static_cast< char >( 97 + rand() % 26 );
         string1.push_back( value );
         string2.push_back( value );

         if( !equal( string1, string2 ) )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testPushBack3()
{
   int numErrors = 0;
   for( int s = 0; s < 15; s++ )
   {
      string str( s, '\0' );
      char *p = str.begin();

      str.push_back( static_cast< char >( 97 + rand() % 26 ) );

      if( str.begin() != p )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testPushBack4()
{
   int numErrors = 0;
   for( int i = 0; i <= number; i++ )
   {
      int c = capacities[ i ];
      for( int s = 16; s <= c; s++ )
      {
         string str( s, '\0' );

         char **ptr = reinterpret_cast< char ** >( &str );
         delete[] * ptr;
         *ptr = new char[ c + 1 ];

         size_t *myCap;
         if( sizeof( size_t ) == 4 )
            myCap = reinterpret_cast< size_t * >( &str ) + 5;
         else
            myCap = reinterpret_cast< size_t * >( &str ) + 3;

         *myCap = c;

         char *p = str.begin();
         str.push_back( static_cast< char >( 97 + rand() % 26 ) );

         if( str.capacity() == c && str.begin() != p )
            numErrors++;
      }
   }

   // str.begin() == p if and only if
   // the array pointed by str.bx.ptr before
   // the excution of str.push_back( value ) is the same as
   // the array pointed by str.bx.ptr after
   // the excution of str.push_back( value )
   // i.e., there is no memory allocation during the excution of
   // str.push_back( value )

   cout << "There are " << numErrors << " errors.\n";
}

// return true iff string1 == string2
bool equal( string &string1, std::string &string2 )
{
   if( string1.capacity() != string2.capacity() )
      return false;

   if( string1.size() != string2.size() )
      return false;

   if( string2.size() == 0 )
      return true;

   for( size_t i = 0; i <= string2.size(); i++ )
      if( string1.at( i ) != string2[ i ] )
         return false;

   return true;
}