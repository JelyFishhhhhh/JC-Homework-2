#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

template< typename T >
void solution();

bool zero( string str );

// product = multiplicand * multiplier
template< typename T >
void multiplication( T multiplicand, T multiplier, T &product );

int main()
{
   // Each of the following two instructions should get an AC
   solution< list< int > >();
   //solution< vector< int > >();

   return 0;
}

template< typename T >
void solution()
{
   string strX;
   string strY;

   while( cin >> strX >> strY )
   {
      if( zero( strX ) || zero( strY ) )
         cout << 0 << endl;
      else
      {
         size_t multiplicandSize = strX.size();
         T multiplicand( multiplicandSize );
         typename T::iterator it = multiplicand.begin();
         string::reverse_iterator sit = strX.rbegin();
         for( ; it != multiplicand.end(); ++it, ++sit )
            *it = *sit - '0';

         size_t multiplierSize = strY.size();
         T multiplier( multiplierSize );
         it = multiplier.begin();
         sit = strY.rbegin();
         for( ; it != multiplier.end(); ++it, ++sit )
            *it = *sit - '0';

         T product( multiplicandSize + multiplierSize );

         multiplication( multiplicand, multiplier, product );

         typename T::reverse_iterator rit = product.rbegin();
         for( ; rit != product.rend(); ++rit )
            cout << *rit;
         cout << endl;
      }
   }
}

bool zero( string str )
{
   for( size_t i = 0; i < str.size(); i++ )
      if( str[ i ] != '0' )
         return false;
   return true;
}

template< typename T >
void multiplication( T multiplicand, T multiplier, T &product )
{

    typename T::iterator it1 = multiplicand.begin();
    typename T::iterator it2 = multiplier.begin();
    typename T::iterator it3;
    
    for (int i= 0; it1 != multiplicand.end(); i++, ++it1) {


        it3 = product.begin();
        for (int k = 0; k < i; k++, ++it3);
        for (it2= multiplier.begin(); it2 != multiplier.end(); ++it2, ++it3) {

            *it3 += (*it1 * *it2);
            
        }
    }

    for (it3 = product.begin(); it3 != product.end(); ++it3) {

        if (*it3 >= 10) {

            typename T::iterator it = it3;
            ++it;
            *it += *it3 / 10;
            *it3 %= 10;
        }
    }
    
    --it3;
    if (*it3 == 0) {

        product.pop_back();
    }
}