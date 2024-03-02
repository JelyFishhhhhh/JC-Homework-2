// string test program.
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

#include <string>
#include "string 2-1.h"

void testFromBufferConstructor();
void testFillConstructor();
void testCopyConstructor1();
void testCopyConstructor2();

// return true iff string1 == string2
bool equal( string &string1, std::string &string2 );

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

int capacities[ 200 ];
const unsigned int number = 100;

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

   testFromBufferConstructor();
   testFillConstructor();
   testCopyConstructor1();
   testCopyConstructor2();
   cout << endl;

   system( "pause" );
}

void testFromBufferConstructor()
{
   const unsigned int number = 1000;
   int numErrors = 0;
   for( int s = 0; s <= number; s++ )
   {
      char str[ number + 1 ];
      for( int i = 0; i < s; i++ )
         str[ i ] = static_cast< char >( 97 + rand() % 26 );
      str[ s ] = '\0';

      string string1( str, s );
      std::string string2( str, s );

      if( !equal( string1, string2 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testFillConstructor()
{
   const unsigned int number = 200;
   int numErrors = 0;
   for( int s = 0; s <= number; s++ )
   {
      for( int i = 32; i <= 126; i++ )
      {
         string string1( s, static_cast< char >( i ) );
         std::string string2( s, static_cast< char >( i ) );

         if( !equal( string1, string2 ) )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testCopyConstructor1()
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

      string string3( string1 );
      std::string string4( string2 );

      if( !equal( string3, string4 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testCopyConstructor2()
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
         delete[] *ptr1;
         delete[] *ptr2;
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

         string string3( string1 );
         std::string string4( string2 );

         if( !equal( string3, string4 ) )
            numErrors++;
      }
   }

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

   for( size_t i = 0; i <= string2.size(); i++)
      if( string1.at( i ) != string2[ i ] )
         return false;

   return true;
}