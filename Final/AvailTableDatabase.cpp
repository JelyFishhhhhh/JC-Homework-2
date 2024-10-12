#include <iostream>
#include <fstream>
using namespace::std;

#include "AvailTableDatabase.h"

// tableTypes[ i ] is the table type for i customers
const int tableTypes[ 10 ] = { 0, 1, 1, 2, 2, 3, 4, 4, 5, 5 };

extern Date computeCurrentDate();

// calls loadAvailTables(), removes outdated available table informations and
// adds new available table informations
AvailTableDatabase::AvailTableDatabase()
{
   loadAvailTables();

   Date currentDate = computeCurrentDate();

   while (availTables.size() <= 30) {
       Date i = (currentDate + availTables.size());
       AvailTable buf;
       buf.setDate(i);
       for (int i = 1; i < 4; i++) {

           for (int j = 1; j < 6; j++) {

               buf.setNumAvailTables(i, j, totalNumTables);
           }
       }
       availTables.push_back(buf);
   }
}

// call storeAvailTables
AvailTableDatabase::~AvailTableDatabase()
{
   storeAvailTables();
}

// decreases the number of available tables by one on date and timeCode for corresponding table type
void AvailTableDatabase::decreaseAvailTables( int numCustomers, Date date, int timeCode )
{
   int tableType = tableTypes[ numCustomers ];
   vector< AvailTable >::iterator it = getAvailTable( date );
   it->decreaseAvailTables( timeCode, tableType );
}

// returns true if there are available tables on date for corresponding table type
bool AvailTableDatabase::availableTables( int numCustomers, Date date )
{
   vector< AvailTable >::iterator it = getAvailTable( date );

   for (int i = 1; i < 4; i++) {

       if (it->getNumAvailTables(i, tableTypes[numCustomers]) > 0) {

           return true;
       }
   }

   return false;
}

// returns true if there are available tables on date and timeCode for corresponding table type
bool AvailTableDatabase::availableTables( int numCustomers, Date date, int timeCode )
{
   vector< AvailTable >::iterator it = getAvailTable( date );

   if (it->getNumAvailTables(timeCode, tableTypes[numCustomers]) > 0) {

       return true;
   }

   return false;
}

void AvailTableDatabase::loadAvailTables()
{

    ifstream inFile("AvailTables.dat", ios::binary);
    if (!inFile.is_open()) {

        cout << "File cannot be opened.\n";
        return;
    }

    availTables.clear();
    inFile.clear();
    inFile.seekg(0, ios::beg);
    AvailTable table;
    while (inFile.read(reinterpret_cast<char*>(&table), sizeof(AvailTable))) {   // modify
        
        // inFile.read(reinterpret_cast<char*>(&table), sizeof(table));    // deleted
        if (table.getDate() <= computeCurrentDate()) {                     // modify

            continue;
        }
        availTables.push_back(table);
    }
    inFile.close();         // added
}

void AvailTableDatabase::storeAvailTables()
{


    ofstream outFile("AvailTables.dat", ios::binary);   // modify
    outFile.clear();
    outFile.seekp(0, ios::beg);
    
    vector< AvailTable >::iterator it = availTables.begin();
    for (; it != availTables.end(); ++it)
        outFile.write(reinterpret_cast<char*>(&(*it)), sizeof(AvailTable));     // modify

    outFile.close();        // added
}

// returns an iterator that points to the AvailTable object containing specified date
vector< AvailTable >::iterator AvailTableDatabase::getAvailTable( Date date )
{
   vector< AvailTable >::iterator it = availTables.begin();
   for( ; it != availTables.end(); ++it )
      if( it->getDate() == date )
         return it;
   return availTables.end();
}