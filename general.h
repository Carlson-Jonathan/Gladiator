/******************************************************************************
* general.h
* Author: Jonathan Carlson
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

int random(int min, int range) {
   srand(time(0));
   return rand() % range + min;
}

#endif // GENERAL_H