// Date.cpp
// Date-function definitions for class Date.
#include <iostream>
#include <iomanip>
using namespace std;

#include "Date.h"

int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // array of days per month

Date::Date( int y, int m, int d )
{
   setDate( y, m, d );
}

// const return avoids: ( a1 = a2 ) = a3
const Date& Date::operator=( const Date &right )
{
   if( &right != this ) // avoid self-assignment
   {
      year = right.year;
      month = right.month;
      day = right.day;
   }

   return *this; // enables x = y = z, for example
}

void Date::setDate( int y, int m, int d )
{
   setYear( y );
   setMonth( m );
   setDay( d );
}

void Date::setYear( int y )
{
   year = ( y >= 2000 ) ? y : 2000;
}

void Date::setMonth( int m )
{
   month = ( m >= 1 && m <= 12 ) ? m : 1;
}

void Date::setDay( int d )
{
   if( month == 2 && leapYear( year ) )
      day = ( d >= 1 && d <= 29 ) ? d : 1;
   else
      day = ( d >= 1 && d <= days[ month ] ) ? d : 1;
}

int Date::getYear() const
{
   return year;
}

int Date::getMonth() const
{
   return month;
}

int Date::getDay() const
{
   return day;
}

bool Date::operator==( const Date &date2 )
{
   return ( year == date2.year && month == date2.month && day == date2.day );
}

bool Date::operator<( const Date &date2 )
{




}

bool Date::operator<=( const Date &date2 )
{
   return ( *this < date2 || *this == date2 );
}

// if the year is a leap year, return true; otherwise, return false
bool Date::leapYear( int theYear ) const
{
   return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}

// return *this - date2 provided that *this >= date2
int Date::operator-( const Date &date2 )
{




}

Date Date::operator+( int numDays )
{




}

ostream& operator<<( ostream &output, const Date &d )
{
   output << setfill( '0' ) << d.year << "/" << setw( 2 ) << d.month
                                      << '/' << setw( 2 ) << d.day;
   output << setfill( ' ' );
   return output; // enables cascading
}