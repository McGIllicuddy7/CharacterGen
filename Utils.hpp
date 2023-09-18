//
//  Utils.h
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#ifndef Utils_h
#define Utils_h
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <string>
using namespace std;
typedef unsigned char byte_t;
unsigned long RandomInt(void);
int RandomIntInRange(int min, int max);
double RandomDouble(void);
int RollDice(const char * die);
string StrArrayRandomElement(vector<string> input);
bool IntArrayContains(vector<int> v, int num);
vector<int> IntArrayChoose(vector<int> v, int num);
vector<string> StrArrayChoose(vector<string> v, int num);
vector<string> StrArraySelect(vector<string> v, int num);
#endif /* Utils_h */

