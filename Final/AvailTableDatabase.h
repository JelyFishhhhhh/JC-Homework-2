#ifndef AVAIL_TABLE_DATABASE_H
#define AVAIL_TABLE_DATABASE_H

#include <vector>
#include "AvailTable.h"

class AvailTableDatabase
{
public:  
   AvailTableDatabase(); // calls loadAvailTables() and adds new available table informations

   ~AvailTableDatabase(); // call storeAvailTables

   // decreases the number of available tables by one on date and timeCode for corresponding table type
   void decreaseAvailTables( int numCustomers, Date date, int timeCode );

   // returns true if there are available tables on date for corresponding table type
   bool availableTables( int numCustomers, Date date );

   // returns true if there are available tables on date and timeCode for corresponding table type
   bool availableTables( int numCustomers, Date date, int timeCode );

private:
   const int totalNumTables = 2;     // suppose there are totally 2 tables for all types
   vector< AvailTable > availTables; // vector of available tables

   void loadAvailTables();  // loads availTables from the file AvailTables.dat and
                          // removes outdated available table informations
   void storeAvailTables(); // stores availTables into the file AvailTables.dat

   // returns an iterator that points to the AvailTable object containing specified date
   vector< AvailTable >::iterator getAvailTable( Date date );
};

#endif // AVAIL_TABLE_DATABASE_H