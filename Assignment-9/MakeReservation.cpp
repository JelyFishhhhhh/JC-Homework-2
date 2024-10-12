// Member-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

#include "MakeReservation.h"

char branchNames[ 19 ][ 24 ] = { "", "Taipei Dunhua South",   "Taipei Linsen",
                                    "Taipei Zhongxiao", "Taipei Songjiang",
                                     "Taipei Nanjing",       "Taipei Zhonghua New",
                                     "Banqiao Guanqian",    "Yonghe Lehua",
                                     "Taoyuan Zhonghua",    "Taoyuan Nankan",
                                     "Zhongli Zhongyang",   "Hsinchu Beida",
                                     "Taichung Ziyou",      "Chiayi Ren'ai",
                                     "Tainan Ximen",        "Kaohsiung Zhonghua New",
                                     "Kaohsiung Jianxing",  "Pingtung Kending" };

extern int inputAnInteger( int begin, int end );
extern void computeCurrentHour( Date &currentDate, int &currentHour );

MakeReservation::MakeReservation( string userIDNumber,
                                  ReservationDatabase &theReservationDatabase,
                                  AvailBoxes &theAvailBoxes )
   : Transaction( userIDNumber, theReservationDatabase, theAvailBoxes )
{
}

// make reservation
void MakeReservation::execute()
{
   ReservationDatabase &reservationDatabase = getReservationDatabase();

   Date currentDate;
   int currentHour;
   computeCurrentHour( currentDate, currentHour );



   Reservation newReservation( getIDNumber(), branchCode, date, hour, numHours, numCustomers );

   cout << endl << setw( 22 ) << "Branch"
                << setw( 14 ) << "Date" << setw( 8 ) << "Hour"
                << setw( 19 ) << "No of Customers" << endl;

   newReservation.displayReservationInfo();
   cout << "\nReservation Completed!\n";

   reservationDatabase.pushBack( newReservation );
}

int MakeReservation::inputBranchCode( bool available[] )
{
   char string[ 80 ];
   cin.getline( string, 80, '\n' );

   for( unsigned int i = 0; i < strlen( string ); i++ )
      if( string[ i ] < '0' || string[ i ] > '9' )
         return -1;

   int number = atoi( string );

   if( number == 0 )
      return number;

   if( number >= 1 && number <= 18 && available[ number ] )
      return number;
   else
      return -1;
}