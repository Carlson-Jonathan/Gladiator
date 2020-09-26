/******************************************************************************
* general.h
* Author: Jonathan Carlson
* Last Updated: September 2020
* Description:
*    Contains generic functions not belonging to any specific class.
******************************************************************************/
#ifndef GENERAL_H
#define GENERAL_H
#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <limits>
#include <vector>
#include <string>
using namespace std;

// Min is the minimum random number and the max is min + range
int random(int min, int range);

// Example: getUserInput("Attack", "Defend", "Flee");
short getUserInput(vector<string> options);

int random(int min, int range) {
   srand(time(0));
   return rand() % range + min;
}

short getUserInput(vector<string> options) {
   short userSelection;
	
   cout << "Make your selection:\n";
   for(int i = 0; i < options.size(); i++)
      cout << (i + 1) << ".) " << options[i] << endl;

   do {
      cout << ">> ";
      cin >> userSelection;	    
      while(cin.fail()) {
         cin.clear();
         cin.ignore(std::numeric_limits<int>::max(),'\n');
         userSelection = 0;
      }
   } while(userSelection < 1 || userSelection > options.size());
   cout << endl;
   
   return userSelection;
}

#endif // GENERAL_H