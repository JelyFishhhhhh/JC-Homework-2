#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "SpellCheck.h"

SpellCheck::SpellCheck()
   : legalWords()
{
}

void SpellCheck::equalLength( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size();
   vector words;

   findWords( words, dictionary, length );




}

void SpellCheck::shorter( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size() + 1;
   vector words;

   findWords( words, dictionary, length );




}

void SpellCheck::longer( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size() - 1;
   vector words;

   findWords( words, dictionary, length );




}

void SpellCheck::findWords( vector &words, const vector &dictionary, size_t length )
{



}

const vector SpellCheck::getLegalWords() const
{
   return legalWords;
}

void SpellCheck::output()
{
   cout << legalWords[ 0 ].c_str();
   for( size_t i = 1; i < legalWords.size(); i++ )
      cout << ", " << legalWords[ i ].c_str();
   cout << endl << endl;
}