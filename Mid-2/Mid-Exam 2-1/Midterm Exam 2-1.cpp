#include <iostream>
using std::cout;
using std::endl;

#include <list>
#include "list.h" // include definition of class template list

template< typename T >
void testList();

template< typename T >
void testInsert1();

template< typename T >
void testInsert2();

template< typename T >
void testErase1();

template< typename T >
void testErase2();

template< typename T >
void testErase3();

// return true iff list1 == list2
template< typename T >
bool equal( list< T > &list1, std::list< T > &list2 );

int main()
{
   srand( static_cast< unsigned int >( time( 0 ) ) );

   testList< char >();
   testList< short >();
   testList< long >();
   testList< long long >();

   system( "pause" );
}

template< typename T >
void testList()
{
   testInsert1< T >();
   testInsert2< T >();
   testErase1< T >();
   testErase2< T >();
   testErase3< T >();
   cout << endl;
}

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

template< typename T >
void testInsert1()
{
   list< T > list1( 0 );
   std::list< T > list2( 0 );

   typename list< T >::iterator it1 = list1.begin();
   typename std::list< T >::iterator it2 = list2.begin();

   T value = 1 + rand() % 99;
   typename list< T >::iterator rit1 = list1.insert( it1, value );
   typename std::list< T >::iterator rit2 = list2.insert( it2, value );

   int numErrors = 0;
   if( !equal( list1, list2 ) || *rit1 != *rit2 )
      numErrors++;

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testInsert2()
{
   const int number = 100;
   int numErrors = 0;
   for( int n = 1; n < number; n++ )
      for( int position = 0; position <= n; position++ )
      {
         list< T > list1( n );
         std::list< T > list2( n );

         size_t *head1 = *( reinterpret_cast< size_t ** >( &list1 ) );
         size_t *head2 = *( reinterpret_cast< size_t ** >( &list2 ) + offset );
         size_t *p1 = *( reinterpret_cast< size_t ** >( head1 ) );
         size_t *p2 = *( reinterpret_cast< size_t ** >( head2 ) );
         for( int i = 1; i <= n; i++ )
         {
            size_t value = 1 + rand() % 99;
            *( p1 + 2 ) = value;
            *( p2 + 2 ) = value;
            p1 = *( reinterpret_cast< size_t ** >( p1 ) );
            p2 = *( reinterpret_cast< size_t ** >( p2 ) );
         }

         typename list< T >::iterator it1 = list1.begin();
         typename std::list< T >::iterator it2 = list2.begin();
         for( int i = 0; i < position; i++ )
         {
            ++it1;
            ++it2;
         }

         T value = 1 + rand() % 99;
         typename list< T >::iterator rit1 = list1.insert( it1, value );
         typename std::list< T >::iterator rit2 = list2.insert( it2, value );

         if( !equal( list1, list2 ) || *rit1 != *rit2 )
            numErrors++;
      }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testErase1()
{
   list< T > list1( 0 );

   typename list< T >::iterator it1 = list1.begin();
   typename list< T >::iterator rit1 = list1.erase( it1 );

   int numErrors = 0;
   if( list1.size() > 0 )
      numErrors++;

   if( rit1 != list1.end() )
      numErrors++;

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testErase2()
{
   list< T > list1( 1 );
   std::list< T > list2( 1 );

   size_t *head1 = *( reinterpret_cast< size_t ** >( &list1 ) );
   size_t *p1 = *( reinterpret_cast< size_t ** >( head1 ) );
   *( p1 + 2 ) = 1 + rand() % 99;

   typename list< T >::iterator it1 = list1.begin();
   typename list< T >::iterator rit1 = list1.erase( it1 );

   int numErrors = 0;
   if( list1.size() > 0 )
      numErrors++;

   if( rit1 != list1.end() )
      numErrors++;

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testErase3()
{
   const int number = 100;
   int numErrors = 0;
   for( int n = 2; n < number; n++ )
      for( int position = 0; position < n; position++ )
      {
         list< T > list1( n );
         std::list< T > list2( n );

         size_t *head1 = *( reinterpret_cast< size_t ** >( &list1 ) );
         size_t *head2 = *( reinterpret_cast< size_t ** >( &list2 ) + offset );
         size_t *p1 = *( reinterpret_cast< size_t ** >( head1 ) );
         size_t *p2 = *( reinterpret_cast< size_t ** >( head2 ) );
         for( int i = 1; i <= n; i++ )
         {
            size_t value = 1 + rand() % 99;
            *( p1 + 2 ) = value;
            *( p2 + 2 ) = value;
            p1 = *( reinterpret_cast< size_t ** >( p1 ) );
            p2 = *( reinterpret_cast< size_t ** >( p2 ) );
         }

         typename list< T >::iterator it1 = list1.begin();
         typename std::list< T >::iterator it2 = list2.begin();
         for( int i = 0; i < position; i++ )
         {
            ++it1;
            ++it2;
         }

         typename list< T >::iterator rit1 = list1.erase( it1 );
         typename std::list< T >::iterator rit2 = list2.erase( it2 );

         if( !equal( list1, list2 ) )
            numErrors++;

         if( list2.size() > 0 && rit2 != list2.end() && *rit1 != *rit2 )
            numErrors++;

         if( rit2 == list2.end() && rit1 != list1.end() )
            numErrors++;
      }

   cout << "There are " << numErrors << " errors\n";
}

// return true iff list1 == list2
template< typename T >
bool equal( list< T > &list1, std::list< T > &list2 )
{
   if( list1.size() != list2.size() ) // different number of elements
      return false;

   if( list2.size() == 0 )
      return true;

   typename list< T >::iterator it1 = list1.begin();
   typename std::list< T >::iterator it2 = list2.begin();
   for( ; it2 != list2.end(); ++it1, ++it2 )
      if( *it1 != *it2 )
         return false;

   return true;
}