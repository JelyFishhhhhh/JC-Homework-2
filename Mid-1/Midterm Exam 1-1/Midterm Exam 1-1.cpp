// vector test program.
#include <iostream>
using std::cout;
using std::endl;

#include <ctime>
using std::time;

#include <vector>
#include "vector.h"

void testInsert1();

void testInsert2();

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

   testInsert1();
   testInsert2();
   cout << endl;

   system( "pause" );
}

void testInsert1()
{
   const int number = 40;
   int numErrors = 0;
   for( int c = 0; c <= number; c++ )
   {
      for( int s = 0; s <= c; s++ )
      {
         for( int position = 0; position <= s; position++ )
         {
            vector vector1( c );
            std::vector< int > vector2( c );

            for( int i = 0; i < c; i++ )
            {
               int value = 1 + rand() % 99;
               vector1[ i ] = value;
               vector2[ i ] = value;
            }

            int *first1 = vector1.begin(); // first1 = vector1.myFirst
            int **last1 = reinterpret_cast< int ** >( &vector1 ) + 1;
            // last1 points to vector1.myLast

            int *first2 = *( reinterpret_cast< int ** >( &vector2 ) + offset );
            // first2 points to the first element of the array in vector2

            int **last2 = reinterpret_cast< int ** >( &vector2 ) + 1 + offset;
            *last1 = first1 + s; // vector1.myLast = vector1.myFirst + s
            *last2 = first2 + s;

            int value = 1 + rand() % 99;

            typename vector::iterator it1;
            typename std::vector< int >::iterator it2;
            it1 = vector1.insert( vector1.begin() + position, value );
            it2 = vector2.insert( vector2.begin() + position, value );

            if( !(equal( vector1, vector2 ) && *it1 == *it2) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testInsert2()
{
   const int number = 60;
   int numErrors = 0;
   for( int c = 0; c <= number; c++ )
   {
      for( int s = 0; s <= c; s++ )
      {
         for( int position = 0; position <= s; position++ )
         {
            vector v( c );
            for( int i = 0; i < c; i++ )
               v[ i ] = 1 + rand() % 99;

            int *first = v.begin(); // first = v.myFirst
            int **last = reinterpret_cast< int ** >( &v ) + 1; // last points to v.myLast
            *last = first + s; // v.myLast = v.myFirst + s

            v.insert( v.begin() + position, 1 + rand() % 99 );

            if( v.capacity() == c && v.begin() != first )
               numErrors++;

            // v.begin() == first if and only if
            // the array pointed by v.myFirst before
            // the excution of v.insert( v.begin() + position, value ) is the same as
            // the array pointed by v.myFirst after
            // the excution of v.insert( v.begin() + position, value )
            // i.e., there is no memory allocation during the excution of
            // v.insert( v.begin() + position, value )
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
      if( vector1[ i ] != vector2[ i ] )
         return false;

   return true;
}