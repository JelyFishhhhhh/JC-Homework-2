// Member-function definitions for class MemberDatabase.
#include <iostream>
#include <fstream>
using namespace::std;

#include "MemberDatabase.h"

MemberDatabase::MemberDatabase()
{
   loadFromMemberFile();
}

MemberDatabase::~MemberDatabase()
{
   saveToMemberFile();
}

// returns true if userPassword match that of an Account with userIDNumber
bool MemberDatabase::authenticateUser( string userIDNumber, string userPassword )
{




}

// returns true if there is an Account containing userIDNumber
bool MemberDatabase::exist( string &userIDNumber )
{




}

// add newMember at the end of members
void MemberDatabase::pushBack( MemberInfo &newMember )
{
   members.push_back( newMember );
}

// loads members from the file MemberInfo.dat
void MemberDatabase::loadFromMemberFile()
{




}

// stores members into the file MemberInfo.dat
void MemberDatabase::saveToMemberFile()
{




}