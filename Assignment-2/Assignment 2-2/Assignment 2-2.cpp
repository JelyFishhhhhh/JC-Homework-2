// string test program.
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

#include <string>
#include "string 2-2.h"

void testAssignment1();
void testAssignment2();
void testAssignment3();
void testAssignment4();

// return true iff string1 == string2 
bool equal( string &string1, std::string &string2 );

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

int capacities[ 200 ];
const unsigned int number = 50;

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

   testAssignment1();
   testAssignment2();
   testAssignment3();
   testAssignment4();
   cout << endl;

   system( "pause" );
}

void testAssignment1()
{
   int numErrors = 0;
   for( int s1 = 0; s1 <= 15; s1++ )
   {
      string string1( s1, '\0' );
      std::string string2( s1, '\0' );

      for( int i = 0; i < s1; i++ )
      {
         char value = static_cast< char >( 97 + rand() % 26 );
         string1.at( i ) = value;
         string2[ i ] = value;
      }

      for( int s2 = 0; s2 <= 15; s2++ )
      {
         string string3( s2, '\0' );
         std::string string4( s2, '\0' );

         for( int i = 0; i < s2; i++ )
         {
            char value = static_cast< char >( 97 + rand() % 26 );
            string3.at( i ) = value;
            string4[ i ] = value;
         }

         string3.assign( string1 );
         string4.assign( string2 );

         if( !equal( string3, string4 ) )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment2()
{
   const unsigned int number = 3;
   int numErrors = 0;
   for( int i1 = 0; i1 <= number; i1++ )
   {
      int c1 = capacities[ i1 ];
      for( int s1 = 0; s1 <= c1; s1++ )
      {
         string string1( s1, '\0' );
         std::string string2( s1, '\0' );

         char **ptr1 = reinterpret_cast< char ** >( &string1 );
         char **ptr2 = reinterpret_cast< char ** >( &string2 ) + offset;
         delete[] * ptr1;
         delete[] * ptr2;
         *ptr1 = new char[ c1 + 1 ];
         *ptr2 = new char[ c1 + 1 ];

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

         *myCap1 = c1;
         *myCap2 = c1;

         for( int j1 = 0; j1 < s1; j1++ )
         {
            char value = static_cast< char >( 97 + rand() % 26 );
            string1.at( j1 ) = value;
            string2[ j1 ] = value;
         }
         string1.at( s1 ) = '\0';
         string2[ s1 ] = '\0';

         for( int i2 = 0; i2 <= number; i2++ )
         {
            int c2 = capacities[ i2 ];
            for( int s2 = 0; s2 <= c2; s2++ )
            {
               string string3( s2, '\0' );
               std::string string4( s2, '\0' );

               char **ptr3 = reinterpret_cast< char ** >( &string3 );
               char **ptr4 = reinterpret_cast< char ** >( &string4 ) + offset;
               delete[] * ptr3;
               delete[] * ptr4;
               *ptr3 = new char[ c2 + 1 ];
               *ptr4 = new char[ c2 + 1 ];

               size_t *myCap3;
               size_t *myCap4;
               if( sizeof( size_t ) == 4 )
               {
                  myCap3 = reinterpret_cast< size_t * >( &string3 ) + 5;
                  myCap4 = reinterpret_cast< size_t * >( &string4 ) + 5 + offset;
               }
               else
               {
                  myCap3 = reinterpret_cast< size_t * >( &string3 ) + 3;
                  myCap4 = reinterpret_cast< size_t * >( &string4 ) + 3 + offset;
               }

               *myCap3 = c2;
               *myCap4 = c2;

               for( int j2 = 0; j2 < s2; j2++ )
               {
                  char value = static_cast< char >( 97 + rand() % 26 );
                  string3.at( j2 ) = value;
                  string4[ j2 ] = value;
               }
               string3.at( s2 ) = '\0';
               string4[ s2 ] = '\0';

               string3.assign( string1 );
               string4.assign( string2 );

               if( !equal( string3, string4 ) )
                  numErrors++;
            }
         }
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment3()
{
   int numErrors = 0;
   for( int s1 = 0; s1 <= 15; s1++ )
   {
      string string1( s1, '\0' );

      for( int i = 0; i < s1; i++ )
      {
         char value = static_cast< char >( 97 + rand() % 26 );
         string1.at( i ) = value;
      }

      for( int s2 = 0; s2 <= 15; s2++ )
      {
         string string2( s2, '\0' );

         for( int i = 0; i < s2; i++ )
         {
            char value = static_cast< char >( 97 + rand() % 26 );
            string2.at( i ) = value;
         }

         char *p = string2.begin();
         string2.assign( string1 );

         if( string2.capacity() == 15 && string2.begin() != p )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment4()
{
   const unsigned int number = 4;
   int numErrors = 0;
   for( int i1 = 0; i1 <= number; i1++ )
   {
      int c1 = capacities[ i1 ];
      for( int s1 = 0; s1 <= c1; s1++ )
      {
         string string1( s1, '\0' );

         char **ptr1 = reinterpret_cast< char ** >( &string1 );
         delete[] * ptr1;
         *ptr1 = new char[ c1 + 1 ];

         size_t *myCap1;
         if( sizeof( size_t ) == 4 )
            myCap1 = reinterpret_cast< size_t * >( &string1 ) + 5;
         else
            myCap1 = reinterpret_cast< size_t * >( &string1 ) + 3;

         *myCap1 = c1;

         for( int j1 = 0; j1 < s1; j1++ )
         {
            char value = static_cast< char >( 97 + rand() % 26 );
            string1.at( j1 ) = value;
         }
         string1.at( s1 ) = '\0';

         for( int i2 = 0; i2 <= number; i2++ )
         {
            int c2 = capacities[ i2 ];
            for( int s2 = 16; s2 <= c2; s2++ )
            {
               string string2( s2, '\0' );

               char **ptr2 = reinterpret_cast< char ** >( &string2 );
               delete[] * ptr2;
               *ptr2 = new char[ c2 + 1 ];

               size_t *myCap2;
               if( sizeof( size_t ) == 4 )
                  myCap2 = reinterpret_cast< size_t * >( &string2 ) + 5;
               else
                  myCap2 = reinterpret_cast< size_t * >( &string2 ) + 3;

               *myCap2 = c2;

               for( int j2 = 0; j2 < s2; j2++ )
               {
                  char value = static_cast< char >( 97 + rand() % 26 );
                  string2.at( j2 ) = value;
               }
               string2.at( s2 ) = '\0';

               char *p = string2.begin();
               string2.assign( string1 );

               if( string2.capacity() == c2 && string2.begin() != p )
                  numErrors++;
            }
         }
      }
   }

   // string2.begin() != p if and only if
   // the array pointed by string2.bx.ptr before
   // the excution of string2.assign( string1 ) is the same as
   // the array pointed by string2.bx.ptr after
   // the excution of string2.assign( string1 )
   // i.e., there is no memory allocation during
   // the excution of string2.assign( string1 )

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