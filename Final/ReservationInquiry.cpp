#include <iostream>
using namespace::std;

#include "ReservationInquiry.h"

extern int inputAnInteger( int begin, int end );

ReservationInquiry::ReservationInquiry( ReservationDatabase &theReservationDatabase,
                                        AvailTableDatabase &theAvailTableDatabase )
   : reservationDatabase( theReservationDatabase ),
     availTableDatabase( theAvailTableDatabase )
{
}

// reservation inquiry
void ReservationInquiry::execute()
{
   if( reservationDatabase.empty() )
   {
      cout << "\nNo reservations!\n";
      return;
   }

   cout << "\nEnter reservation number: ";
   string reservationNumber;
   cin >> reservationNumber;

   if( !reservationDatabase.exist( reservationNumber ) )
   {
      cout << "\nNo reservations with this reservation number!\n";
      return;
   }

   cout << "\nEnter reservation password: ";
   string password;
   cin >> password;
   cout << endl;

   if( !reservationDatabase.legal( reservationNumber, password ) )
   {
      cout << "The password is illegal!\n";
      return;
   }

   reservationDatabase.displayReservationInfo( reservationNumber );
}