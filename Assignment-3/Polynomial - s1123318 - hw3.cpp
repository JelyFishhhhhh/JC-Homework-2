#include <iostream>
using std::cout;
using std::endl;

#include "Polynomial.h" // include definition of class Polynomial

Polynomial::Polynomial( size_t n )
   : polynomial( n )
{
}

Polynomial::Polynomial( size_t n, int coefficient[], int exponent[] )
   : polynomial( n )
{
   for( size_t i = 0; i < n; i++ )
   {
      polynomial.at( i ).coef = coefficient[ i ];
      polynomial.at( i ).expon = exponent[ i ];
   }
}

Polynomial::Polynomial( const Polynomial &right )
   : polynomial( right.polynomial )
{
}

Polynomial::~Polynomial()
{
}

const Polynomial Polynomial::assign( const Polynomial &right )
{
   if( &right != this ) // avoid self-assignment
      polynomial.assign( right.polynomial );

   return *this; // enables x = y = z, for example
}

bool Polynomial::equal( const Polynomial &right ) const
{
   return polynomial.equal( right.polynomial );
}

void Polynomial::addition( const Polynomial &adder )
{
   Polynomial sum( polynomial.size() + adder.polynomial.size() );
   size_t i = 0;
   size_t j = 0;
   size_t k = 0;

   if(this->polynomial.empty()){

      polynomial.assign(adder.polynomial);
      return;
   }

   while(k< sum.polynomial.size() && i< polynomial.size() && j< adder.polynomial.size()){

      if(polynomial.at(i).expon> adder.polynomial.at(j).expon){
         
         if(polynomial.at(i).coef== 0){

            i++;
            continue;
         }
         sum.polynomial.at(k).expon= polynomial.at(i).expon;
         sum.polynomial.at(k).coef= polynomial.at(i).coef;
         i++;
      }
      else if(polynomial.at(i).expon< adder.polynomial.at(j).expon){

         if(adder.polynomial.at(j).coef== 0){

            j++;
            continue;
         }
         sum.polynomial.at(k).expon= adder.polynomial.at(j).expon;
         sum.polynomial.at(k).coef= adder.polynomial.at(j).coef;
         j++;
      }
      else{

         if((polynomial.at(i).coef+ adder.polynomial.at(j).coef)== 0){
            i++;
            j++;
            continue;
         }
         sum.polynomial.at(k).expon= polynomial.at(i).expon;
         sum.polynomial.at(k).coef= polynomial.at(i).coef+ adder.polynomial.at(j).coef;
         i++;
         j++;
      }
      k++;
   }

   while (i< polynomial.size()){
      
      if(polynomial.at(i).coef== 0){

         i++;
         continue;
      }
      sum.polynomial.at(k).expon= polynomial.at(i).expon;
      sum.polynomial.at(k).coef= polynomial.at(i).coef;
      i++;
      k++;
   }
   while (j< adder.polynomial.size()){
      
      if(adder.polynomial.at(j).coef== 0){
         j++;
         continue;
      }
      sum.polynomial.at(k).expon= adder.polynomial.at(j).expon;
      sum.polynomial.at(k).coef= adder.polynomial.at(j).coef;
      j++;
      k++;
   }
   

   if( sum.polynomial.size() != k )
      sum.polynomial.resize( k );

   polynomial.assign( sum.polynomial );

   if( !zero() && hasZeroTerm() )
      cout << "addend has a zero term!\n";
}

void Polynomial::subtraction( const Polynomial &subtrahend )
{
   Polynomial buffer( subtrahend.minus() );

   addition( buffer ); // minuend = minuend + buffer = minuend - subtrahend

   if( !zero() && hasZeroTerm() )
      cout << "minuend has a zero term!\n";
}

Polynomial Polynomial::multiplication( const Polynomial &multiplier ) const
{
   Polynomial product;
   Polynomial buffer(polynomial.size());
   for(size_t i= 0; i< multiplier.polynomial.size(); i++){


      for(size_t j= 0; j< polynomial.size(); j++){
         
         if(polynomial.at(j).coef* multiplier.polynomial.at(i).coef== 0){

            continue;
         }
         buffer.polynomial.at(j).expon= polynomial.at(j).expon+ multiplier.polynomial.at(i).expon;
         buffer.polynomial.at(j).coef= polynomial.at(j).coef* multiplier.polynomial.at(i).coef;
      }
      product.addition(buffer);
   }

   if( !product.zero() && product.hasZeroTerm() )
      cout << "product has a zero term!\n";
      
   // cout<< "m: ";this->output();multiplier.output();product.output();
   return product;
}

Polynomial Polynomial::division( const Polynomial &divisor ) const
{

   Polynomial remainder(*this);
   Polynomial quotient(polynomial.size()- divisor.polynomial.size()+ 1);
   while (!remainder.zero() && remainder.degree() >= divisor.degree()){

      Polynomial monomial(1);
      monomial.polynomial.at(0).expon= remainder.polynomial.at(0).expon- divisor.polynomial.at(0).expon;
      monomial.polynomial.at(0).coef= remainder.polynomial.at(0).coef/ divisor.polynomial.at(0).coef;

      quotient.addition(monomial);
      Polynomial buffer;
      buffer.assign(divisor.multiplication(monomial));
      remainder.subtraction(buffer);
      
   }
   if( !quotient.zero() && quotient.hasZeroTerm() )
      cout << "quotient has a zero term!\n";

   return quotient;
}

Polynomial Polynomial::modulus( const Polynomial &divisor ) const
{

   Polynomial remainder(*this);
   Polynomial quotient(polynomial.size()- divisor.polynomial.size()+ 1);
   while (!remainder.zero() && remainder.degree() >= divisor.degree()){

      Polynomial monomial(1);
      monomial.polynomial.at(0).expon= remainder.polynomial.at(0).expon- divisor.polynomial.at(0).expon;
      monomial.polynomial.at(0).coef= remainder.polynomial.at(0).coef/ divisor.polynomial.at(0).coef;

      quotient.addition(monomial);
      Polynomial buffer(divisor.multiplication(monomial));
      remainder.subtraction(buffer);
   }
   if( !remainder.zero() && remainder.hasZeroTerm() )
      cout << "remainder has a zero term!\n";

   return remainder;
}

void Polynomial::output() const
{
   // the current polynomial is zero polynomial
   if( zero() )
      cout << 0;
   else
   {
      if( leadingCoef() < 0 )
         cout << "-" << -leadingCoef();
      else if( leadingCoef() > 0 )
         cout << leadingCoef();

      if( degree() > 0 )
      {
         if( degree() == 1 )
            cout << "x";
         else
            cout << "x^" << degree();
      }

      for( size_t i = 1; i < polynomial.size(); i++ )
      {
         if( polynomial.at( i ).coef < 0 )
            cout << " - " << -polynomial.at( i ).coef;
         else if( polynomial.at( i ).coef > 0 )
            cout << " + " << polynomial.at( i ).coef;

         if( polynomial.at( i ).expon > 0 )
         {
            if( polynomial.at( i ).expon == 1 )
               cout << "x";
            else
               cout << "x^" << polynomial.at( i ).expon;
         }
      }
   }

   cout << endl;
}

bool Polynomial::hasZeroTerm() const
{
   if( !zero() )
      for( size_t i = 0; i < polynomial.size(); i++ )
         if( polynomial.at( i ).coef == 0 )
            return true;

   return false;
}

Polynomial Polynomial::minus() const
{
   Polynomial minus( polynomial.size() );
   for( size_t i = 0; i < minus.polynomial.size(); i++ )
   {
      minus.polynomial.at( i ).coef = -polynomial.at( i ).coef;
      minus.polynomial.at( i ).expon = polynomial.at( i ).expon;
   }

   return minus;
}

bool Polynomial::zero() const
{
   return polynomial.empty();
}

int Polynomial::degree() const
{
   if( polynomial.empty() )
      return 0;
   else
      return polynomial.front().expon;
}

int Polynomial::leadingCoef() const
{
   if( polynomial.empty() )
      return 0;
   else
      return polynomial.front().coef;
}