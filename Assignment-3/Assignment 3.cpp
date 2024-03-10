// Polynomial division provided that the quotient and remainder have integer coefficients

#include <fstream>
using std::ifstream;
using std::ios;

#include "Polynomial.h" // include definition of class Polynomial

void load( ifstream &inFile, int &numTerms, int coefficient[], int exponent[] );

const int numTestCases = 200; // the number of test cases
const int arraySize = 20;

int main()
{
   ifstream inFile( "Polynomials.dat", ios::in | ios::binary );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   int numErrors = 2 * numTestCases;
   for( int i = 0; i < numTestCases; i++ )
   {
      int coefficient[ arraySize ] = {};
      int exponent[ arraySize ] = {};
      int numTerms;

      load( inFile, numTerms, coefficient, exponent );
      const Polynomial dividend( numTerms, coefficient, exponent );

      load( inFile, numTerms, coefficient, exponent );
      const Polynomial divisor( numTerms, coefficient, exponent );

      cout << "dividend:  "; dividend.output();

      cout << " divisor:  "; divisor.output();

      // quotient = dividend / divisor
      const Polynomial quotient( dividend.division( divisor ) );

      // remainder = dividend % divisor
      const Polynomial remainder( dividend.modulus( divisor ) );

      // thus, dividend == divisor * quotient + remainder

      cout << "quotient:  "; quotient.output();
      cout << "remainder:  "; remainder.output();
      cout << endl;

      // if divisor is a constant polynomial and remainder is the zero polynomial, then
      // remainder.degree() == divisor.degree() == 0, and hence
      // remainder.degree() < divisor.degree() is false
      if( ( remainder.zero() || remainder.degree() < divisor.degree() ) &&
          dividend.degree() >= divisor.degree() && !quotient.zero() &&
          !dividend.equal( remainder ) )
         numErrors--;

      // buffer = divisor * quotient
      Polynomial buffer( divisor.multiplication( quotient ) );

      // buffer = buffer + remainder = divisor * quotient + remainder
      buffer.addition( remainder );

      // if buffer != dividend, an error occurred!
      if( buffer.equal( dividend ) )
         numErrors--;
   }

   inFile.close();

   cout << "There are " << numErrors << " errors!\n\n";

   system( "pause" );
}

void load( ifstream &inFile, int &numTerms, int coefficient[], int exponent[] )
{
   inFile.read( reinterpret_cast< char * >( coefficient ), arraySize * sizeof( int ) );
   inFile.read( reinterpret_cast< char * >( exponent ), arraySize * sizeof( int ) );

   numTerms = arraySize;
   while( numTerms > 0 && coefficient[ numTerms - 1 ] == 0 )
      numTerms--;
}