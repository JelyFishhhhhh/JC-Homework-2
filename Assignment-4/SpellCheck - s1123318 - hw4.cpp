#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "SpellCheck.h"

SpellCheck::SpellCheck()
   : legalWords()
{
}
   
// Find every word w in the vector "dictionary" which satisfies two conditions:

// 1. the length of w is equal to the length of wordToCheck, and wordToCheck and w are different on exactly one character.
// 2. Put these words into the vector "legalWords".
void SpellCheck::equalLength( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size();
   vector words;
   
   // Find the words in the vector "dictionary" whose length is equal to "length", and put these words into the vector "words"
   findWords( words, dictionary, length );

   for(size_t i= 0; i< words.size(); i++){

      string buf1= words[i], buf2= wordToCheck;
      buf1.erase(0, 1);
      buf2.erase(0, 1);
      if(buf1== buf2){

         legalWords.push_back(words[i]);
         continue;
      }
      for(size_t j= 0; j< length; j++){

         buf1[j]= words[i][j];
         buf2[j]= wordToCheck[j];
         if(buf1== buf2){

            legalWords.push_back(words[i]);
            break;
         }
      }
   }
}

// Find every word w in the vector "dictionary" which satisfies two conditions:

// 1. the length of w is one greater than the length of wordToCheck, and wordToCheck is equal to the substring obtained by deleting a character from w.
// 2. Put these words into the vector "legalWords".

void SpellCheck::shorter( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size() + 1;
   vector words;

   findWords( words, dictionary, length );

   for(size_t i= 0; i< words.size(); i++){

      string buf= words[i];
      buf.erase(0, 1);
      if(buf== wordToCheck){

         legalWords.push_back(words[i]);
         continue;
      }
      for(size_t j= 0; j< length; j++){

         buf[j]= words[i][j];
         if(buf== wordToCheck){

            legalWords.push_back(words[i]);
            break;
         }
      }
   }
}

// Find every word w in the vector "dictionary" which satisfies two conditions:

// 1. the length of w is one less than the length of wordToCheck, and w is equal to the substring obtained by deleting a character from wordToCheck.
// 2. Put these words into the vector "legalWords".

void SpellCheck::longer( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size() - 1;
   vector words;

   findWords( words, dictionary, length );

   for(size_t i= 0; i< words.size(); i++){

      string buf= wordToCheck;
      buf.erase(0, 1);
      if(buf== words[i]){

         legalWords.push_back(words[i]);
         continue;
      }
      for(size_t j= 0; j< length; j++){

         buf[j]= wordToCheck[j];
         if(buf== words[i]){

            legalWords.push_back(words[i]);
            break;
         }
      }
   }
}

void SpellCheck::findWords( vector &words, const vector &dictionary, size_t length )
{

   words.clear();
   for(size_t i= 0; i< dictionary.size(); i++){
      
      if(dictionary[i].size()== length){
         
         words.push_back(dictionary[i]);
      }
   }
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