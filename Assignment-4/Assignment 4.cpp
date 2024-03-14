#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

#include <cstring>

#include "SpellCheck.h"

// read all strings from a text file, and put them to the vector "stringVector"
void readTextFile( const char fileName[], vector &stringVector );

// return true if and only if wordToCheck == dictionary[ i ] for some i
bool legal( const string &wordToCheck, const vector &dictionary );

int main()
{
//   srand( 1 );

   vector dictionary;
   readTextFile( "Dictionary.txt", dictionary );

   vector answer;
   readTextFile( "Answer.txt", answer );

   int index = 0;
   int numErrors = 0;
   for( int i = 0; i < 100; i++ )
   {
      string wordToCheck;
      wordToCheck = dictionary[ rand() + dictionary.size() - 32768 ]; // skip short words
      // cout<< "ori: "<< wordToCheck.c_str()<< '\n';
      wordToCheck.erase( rand() % wordToCheck.size(), 1 );
      // cout<< "lat: "<< wordToCheck.c_str()<< '\n';

      if( !legal( wordToCheck, dictionary ) )
      {
         cout << "Word to check: " << wordToCheck.c_str() << endl;

         SpellCheck spellCheck;
         spellCheck.equalLength( wordToCheck, dictionary );
         spellCheck.shorter( wordToCheck, dictionary );
         spellCheck.longer( wordToCheck, dictionary );

         // compare spellCheck.legalWords with answer to find the numner of errors
         for( size_t i = 0; i < spellCheck.getLegalWords().size(); i++, index++ )
            if( spellCheck.getLegalWords()[ i ] != answer[ index ] )
               numErrors++;

         cout << "Similar legal words: ";
         spellCheck.output();
      }
   }

   cout << "There are " << numErrors << " errors.\n\n";

   system( "pause" );
}

void readTextFile( const char fileName[], vector &stringVector )
{
   ifstream inFile( fileName, ios::in );

   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   char word[ 21 ];
   while( inFile >> word )
   {
      string buffer( word, strlen( word ) );
      stringVector.push_back( buffer );
   }

   inFile.close();
}

bool legal( const string &wordToCheck, const vector &dictionary )
{
   for( size_t i = 0; i < dictionary.size(); i++ ){

      if( dictionary[ i ] == wordToCheck ){

         return true;
      }
   }
   return false;
}