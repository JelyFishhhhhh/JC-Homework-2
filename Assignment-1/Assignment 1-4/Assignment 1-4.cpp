// vector test program.
#include <iostream>
using std::cout;
using std::endl;

#include <ctime>
using std::time;

#include <vector>
#include "vector 1-4.h"

void testResize1();

void testResize2();

// Determines if two vectors are equal.
bool equal( vector &vector1, std::vector< int > &vector2 );

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

int main()
{
   srand( static_cast< unsigned int >( time( 0 ) ) );

   testResize1();
   testResize2();
   cout << endl;

   system( "pause" );
}

void testResize1()
{
   const int n = 50;
   int numErrors = 0;
   for( int c = 0; c <= n; c++ )
   {
      for( int s = 0; s <= c; s++ )
      {
         for( int newSize = s; newSize <= n; newSize++ )
         {
            vector vector1( c );
            std::vector< int > vector2( c );
            for( int i = 0; i < s; i++ )
            {
               int value = 1 + rand() % 99;
               vector1.at( i ) = value;
               vector2.at( i ) = value;
            }

            int *first1 = vector1.begin(); // first1 = vector1.myData.myFirst
            int **last1 = reinterpret_cast< int ** >( &vector1 ) + 1;
            // last1 points to vector1.myData.myLast

            int *first2 = *( reinterpret_cast< int ** >( &vector2 ) + offset );
            // first2 points to the first element of the array in vector2

            int **last2 = reinterpret_cast< int ** >( &vector2 ) + 1 + offset;
            *last1 = first1 + s; // vector1.myData.myLast = vector1.myData.myFirst + s
            *last2 = first2 + s;

            vector1.resize( newSize );
            vector2.resize( newSize );

            if( !equal( vector1, vector2 ) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testResize2()
{
   const int n = 80;
   int numErrors = 0;
   for( int c = 0; c <= n; c++ )
   {
      for( int s = 0; s <= c; s++ )
      {
         for( int newSize = 0; newSize <= c; newSize++ )
         {
            vector v( c );
            for( int i = 0; i < s; i++ )
               v.at( i ) = 1 + rand() % 99;

            int *first = v.begin(); // first1 = v.myData.myFirst

            int **last = reinterpret_cast< int ** >( &v ) + 1;
            // last1 points to v.myData.myLast

            *last = first + s; // v.myData.myLast = v.myData.myFirst + s

            v.resize( newSize );

            if( v.capacity() == c && v.begin() != first )
               numErrors++;

            // v.begin() == first if and only if
            // the array pointed by v.myData.myFirst before
            // the excution of v.resize( newSize ) is the same as
            // the array pointed by v.myData.myFirst after
            // the excution of v.resize( newSize )
            // i.e., there is no memory allocation during the excution of
            // v.resize( newSize )
         }
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