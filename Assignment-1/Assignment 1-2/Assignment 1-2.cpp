// vector test program.
#include <iostream>
using std::cout;
using std::endl;

#include <ctime>
using std::time;

#include <vector>
#include "vector 1-2.h"

void testAssignment1();

void testAssignment2();

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

   testAssignment1();
   testAssignment2();
   cout << endl;

   system( "pause" );
}

void testAssignment1()
{
   const int n = 20;
   int numErrors = 0;
   for( int c1 = 0; c1 <= n; c1++ )
   {
      vector vector1( c1 );
      std::vector< int > vector2( c1 );

      for( int i = 0; i < c1; i++ )
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
      for( int s1 = 0; s1 <= c1; s1++ )
      {
         *last1 = first1 + s1; // vector1.myLast = vector1.myFirst + s1
         *last2 = first2 + s1;

         for( int c2 = 0; c2 <= n; c2++ )
         {
            for( int s2 = 0; s2 <= c2; s2++ )
            {
               vector vector3( c2 );
               std::vector< int > vector4( c2 );

               for( int i = 0; i < c2; i++ )
               {
                  int value = 1 + rand() % 99;
                  vector3.at( i ) = value;
                  vector4.at( i ) = value;
               }

               int *first3 = vector3.begin(); // first3 = vector3.myFirst
               int **last3 = reinterpret_cast< int ** >( &vector3 ) + 1;
               // last3 points to vector3.myLast

               int *first4 = *( reinterpret_cast< int ** >( &vector4 ) + offset );
               // first4 points to the first element of the array in vector4

               int **last4 = reinterpret_cast< int ** >( &vector4 ) + 1 + offset;
               *last3 = first3 + s2; // vector3.myLast = vector3.myFirst + s2
               *last4 = first4 + s2;

               vector3.assign( vector1 );
               vector4 = vector2;

               if( !equal( vector3, vector4 ) )
                  numErrors++;
            }
         }
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment2()
{
   const int n = 30;
   int numErrors = 0;
   for( int c1 = 0; c1 <= n; c1++ )
   {
      vector vector1( c1 );
      for( int i = 0; i < c1; i++ )
         vector1.at( i ) = 1 + rand() % 99;

      int *first1 = vector1.begin(); // first1 = vector1.myFirst
      int **last1 = reinterpret_cast< int ** >( &vector1 ) + 1;
      // last1 points to vector1.myLast
      for( int s1 = 0; s1 <= c1; s1++ )
      {
         *last1 = first1 + s1;

         for( int c2 = 0; c2 <= n; c2++ )
         {
            for( int s2 = 0; s2 <= c2; s2++ )
            {
               vector vector2( c2 );
               for( int i = 0; i < s2; i++ )
                  vector2.at( i ) = 1 + rand() % 99;

               int *first2 = vector2.begin(); // first2 = vector2.myFirst
               int **last2 = reinterpret_cast< int ** >( &vector2 ) + 1;
               // last2 points to vector2.myLast
               *last2 = first2 + s2; // vector2.myLast = vector2.myFirst + s2

               vector2.assign( vector1 );

               if( vector2.capacity() == c2 && vector2.begin() != first2 )
                  numErrors++;
            }
         }
      }
   }

   // vector2.begin() == first2 if and only if
   // the array pointed by vector2.myFirst before
   // the excution of vector2 = vector1 is the same as
   // the array pointed by vector2.myFirst after
   // the excution of vector2 = vector1
   // i.e., there is no memory allocation during the excution of vector2.assign( vector1 )

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