#include <iostream>
#include <ctime>
using namespace::std;

#include "MakeReservation.h"    // MakeReservation class definition
#include "ReservationInquiry.h" // ReservationInquiry class definition

int inputAnInteger( int begin, int end ); // input an integer in the range [ begin, end ]
Date computeCurrentDate(); // compute current date
bool leapYear( int year ); // if the year is a leap year, return true; otherwise, return false

int main()
{
   cout << "Welcome to Hi-Lai Harbour Taoyuan Location!\n";

   ReservationDatabase reservationDatabase; // reservation information database
   AvailTableDatabase availTableDatabase;   // available table information database

   MakeReservation makeReservation( reservationDatabase, availTableDatabase );
   ReservationInquiry reservationInquiry( reservationDatabase, availTableDatabase );

   bool userExited = false; // user has not chosen to exit
   int choice;

   // loop while user has not chosen option to exit system
   while( !userExited )
   {
      cout << "\n1 - Book a Table\n";
      cout << "2 - My Bookings\n";
      cout << "3 - End\n\n";

      do cout << "Enter your choice: (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );

      // decide how to proceed based on user's menu selection
      switch( choice )
      {
      case 1:
         makeReservation.execute(); // make reservation
         break;
      case 2:
         reservationInquiry.execute(); // reservation inquiry
         break;
      case 3: // user chose to exit
         cout << "\nThank you! Goodbye!\n";
         userExited = true;
         cout << endl;
         break;
      default: // user did not enter an integer from 1-3
         cout << "\nIncorrect choice!" << endl;
      }
   }

   system( "pause" );
}

int inputAnInteger( int begin, int end )
{
   char string[ 80 ];
   cin >> string;

   if( strlen( string ) == 0 )
      exit( 0 );

   for( unsigned int i = 0; i < strlen( string ); i++ )
      if( string[ i ] < '0' || string[ i ] > '9' )
         return -1;

   int number = atoi( string );

   if( number >= begin && number <= end )
      return number;
   else
      return -1;
}

Date computeCurrentDate()
{
   //int remainingSeconds = static_cast< int >( time( 0 ) ) + 8 * 60 * 60;
   //int remainingSeconds = static_cast<int>(time(0)) - 24 * 60 * 60;     // for 6/1
   int remainingSeconds = static_cast<int>(time(0)) + 24 * 60 * 60;     // for 6/3
   int year = 1970;

   int secondsPerYear = 365 * 24 * 60 * 60;
   if( leapYear( year ) )
      secondsPerYear += 24 * 60 * 60;

   while( remainingSeconds >= secondsPerYear )
   {
      remainingSeconds -= secondsPerYear;
      year++;

      secondsPerYear = 365 * 24 * 60 * 60;
      if( leapYear( year ) )
         secondsPerYear += 24 * 60 * 60;
   }

   int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if( leapYear( year ) )
      days[ 2 ] = 29;

   int month = 1;
   while( remainingSeconds >= days[ month ] * 24 * 60 * 60 )
   {
      remainingSeconds -= days[ month ] * 24 * 60 * 60;
      month++;
   }

   int day = remainingSeconds / ( 24 * 60 * 60 ) + 1;

   return Date( year, month, day );
}

bool leapYear( int year )
{
   return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}