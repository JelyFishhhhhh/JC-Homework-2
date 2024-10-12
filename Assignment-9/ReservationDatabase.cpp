// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;
#include "ReservationDatabase.h"

extern int computeCurrentDate( Date &currentDate );
extern void computeCurrentHour( Date &currentDate, int &currentHour );

ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

ReservationDatabase::~ReservationDatabase()
{
   saveReservations();
}

bool ReservationDatabase::empty()
{
   return ( reservations.size() == 0 );
}

bool ReservationDatabase::exist( string IDNumber )
{




}

bool ReservationDatabase::allowed( string IDNumber, Date date, int hour )
{




}

int ReservationDatabase::displayReservationInfo( string IDNumber )
{
   cout << endl << setw( 25 ) << "Branch"
                << setw( 14 ) << "Date" << setw( 8 ) << "Hour"
                << setw( 19 ) << "No of Customers" << endl;

   int count = 0;
   vector< Reservation >::iterator it;
   for( it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIDNumber() == IDNumber )
      {
         cout << ++count << ". ";
         it->displayReservationInfo();
      }

   return count;
}

void ReservationDatabase::cancelReservation( string IDNumber, int n,
                                             int &branchCode, int &dateCode, int &startingHour, int &numHours )
{
   Date currentDate;
   computeCurrentDate( currentDate );




}

void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

void ReservationDatabase::loadReservations()
{




}

void ReservationDatabase::saveReservations()
{




}