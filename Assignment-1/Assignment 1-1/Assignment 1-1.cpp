// vector test program.
#include <iostream>
using std::cout;
using std::endl;

#include <ctime>
using std::time;

#include <vector>
#include "vector 1-1.h"

void testFillConstructor();

void testCopyConstructor();

// Determines if two vectors are equal.
bool equal( vector &left, std::vector< int > &right );

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

int main()
{
   srand( static_cast< unsigned int >( time( 0 ) ) );

   testFillConstructor();
   testCopyConstructor();
   cout << endl;

   system( "pause" );
}

void testFillConstructor()
{
   const int n = 1000;
   int numErrors = 0;
   for( int c = 0; c <= n; c++ )
   {
      vector vector1( c );
      std::vector< int > vector2( c );

      if( !equal( vector1, vector2 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testCopyConstructor()
{
   const int n = 300;
   int numErrors = 0;
   for( int c = 0; c <= n; c++ )
   {
      vector vector1( c );
      std::vector< int > vector2( c );
      for( int i = 0; i < c; i++ )
      {
         int value = 1 + rand() % 99;
         vector1.at( i ) = value;
         vector2.at( i ) = value;
      }

      int *first1 = vector1.begin(); // first1 = vector1.myFirst
      int **last1 = reinterpret_cast< int ** >( &vector1 ) + 1;
      // last1 points to vector1.myLast

      int *first2 = *( reinterpret_cast< int ** >( &vector2 ) + offset );
      // first2 points to the first element of the array in vector2
      int **last2 = reinterpret_cast< int ** >( &vector2 ) + 1 + offset;
      for( int s = 0; s <= c; s++ )
      {
         *last1 = first1 + s; // vector1.myLast = vector1.myFirst + s
         *last2 = first2 + s;

         vector vector3( vector1 );
         std::vector< int > vector4( vector2 );

         if( !equal( vector3, vector4 ) )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

// Determines if two vectors are equal.
bool equal( vector &vector1, std::vector< int > &vector2 )
{
   if( vector1.capacity() != vector2.capacity() )
      return false;

   if( vector2.capacity() == 0 )
   {
      int **first1 = reinterpret_cast< int ** >( &vector1 );
      int **last1 = reinterpret_cast< int ** >( &vector1 ) + 1;
      int **end1 = reinterpret_cast< int ** >( &vector1 ) + 2;

      int **first2 = reinterpret_cast< int ** >( &vector2 ) + offset;
      int **last2 = reinterpret_cast< int ** >( &vector2 ) + 1 + offset;
      int **end2 = reinterpret_cast< int ** >( &vector2 ) + 2 + offset;

      if( *first1 != *first2 )
         return false;

      if( *last1 != *last2 )
         return false;

      if( *end1 != *end2 )
         return false;
   }

   if( vector1.size() != vector2.size() )
      return false;

   if( vector2.size() == 0 )
      return true;

   for( size_t i = 0; i < vector2.size(); ++i )
      if( vector1.at( i ) != vector2.at( i ) )
         return false;

   return true;
}