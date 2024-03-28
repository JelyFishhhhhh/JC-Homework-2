// string test program.
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

#include <string>
#include "string.h"

void testInsert1();
void testInsert2();
void testInsert3();
void testInsert4();

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

   for( int i = 0; i < number; i++ )
      capFile >> capacities[ i ];

   capFile.close();

   testInsert1();
   testInsert2();
   testInsert3();
   testInsert4();
   cout << endl;

   system( "pause" );
}

void testInsert1()
{
   int numErrors = 0;
   for( int s = 0; s <= 15; s++ )
   {
      for( int position = 0; position <= s; position++ )
      {
         string string1( s, '\0' );
         std::string string2( s, '\0' );

         for( int i = 0; i < s; i++ )
         {
            char value = static_cast< char >( 97 + rand() % 26 );
            string1[ i ] = value;
            string2[ i ] = value;
         }

         char value = static_cast< char >( 97 + rand() % 26 );
         string1.insert( string1.begin() + position, value );
         string2.insert( string2.begin() + position, value );

         if( !equal( string1, string2 ) )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testInsert2()
{
   const unsigned int number = 7;
   int numErrors = 0;
   for( int i = 0; i < number; i++ )
   {
      int c = capacities[ i ];
      for( int s = 0; s <= c; s++ )
      {
         for( int position = 0; position <= s; position++ )
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
               string1[ j ] = value;
               string2[ j ] = value;
            }
            string1[ s ] = '\0';
            string2[ s ] = '\0';

            char value = static_cast< char >( 97 + rand() % 26 );
            string1.insert( string1.begin() + position, value );
            string2.insert( string2.begin() + position, value );

            if( !equal( string1, string2 ) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testInsert3()
{
   int numErrors = 0;
   for( int s = 0; s < 15; s++ )
   {
      for( int position = 0; position <= s; position++ )
      {
         string str( s, '\0' );
         char *p = str.begin();

         char value = static_cast< char >( 97 + rand() % 26 );
         str.insert( str.begin() + position, value );

         if( str.begin() != p )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testInsert4()
{
   const unsigned int number = 20;
   int numErrors = 0;
   for( int i = 0; i < number; i++ )
   {
      int c = capacities[ i ];
      for( int s = 16; s <= c; s++ )
      {
         for( int position = 0; position <= s; position++ )
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
            char value = static_cast< char >( 97 + rand() % 26 );
            str.insert( str.begin() + position, value );

            if( str.capacity() == c && str.begin() != p )
               numErrors++;

            // str.begin() == p if and only if
            // the array pointed by str.bx.ptr before
            // the excution of str.insert( str.begin() + position, value ) is the same as
            // the array pointed by str.bx.ptr after
            // the excution of str.insert( str.begin() + position, value )
            // i.e., there is no memory allocation during the excution of
            // str.insert( str.begin() + position, value )
         }
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

   for( size_t i = 0; i <= string2.size(); i++ )
   {
      if( string1[ i ] != string2[ i ] )
         return false;
   }

   return true;
}