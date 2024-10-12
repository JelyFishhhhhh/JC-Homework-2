#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "AvailBoxes.h"

extern int computeCurrentDate( Date &currentDate );

AvailBoxes::AvailBoxes()
{
   loadNumAvailBoxes();

   Date currentDate;

   computeCurrentDate( currentDate );

   cout << startingDate.getYear() << "/"
      << startingDate.getMonth() << "/"
      << startingDate.getDay() << endl;









   for( int branch = 1; branch <= 18; branch++ )
      for( int k = 1; k <= 7; k++ )
      {
         for( int i = 0; i <= 23; i++ )
            cout << setw( 4 ) << numAvailBoxes[ branch ][ k ][ i ];
         cout << endl;
      }
}

AvailBoxes::~AvailBoxes()
{
   saveNumAvailBoxes();
}

bool AvailBoxes::available( int branchCode, int date, int startingHour, int numHours )
{




}

void AvailBoxes::decrease( int branchCode, int date, int startingHour, int numHours )
{




}

void AvailBoxes::increase( int branchCode, int date, int startingHour, int numHours )
{




}

void AvailBoxes::loadNumAvailBoxes()
{




}

void AvailBoxes::saveNumAvailBoxes()
{




}