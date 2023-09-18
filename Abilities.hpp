//
//  Abiliites.h
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/9/23.
//

#ifndef Abiliites_h
#define Abiliites_h
#include <string>
#include <vector>
#include <stdio.h>
#include "Character.hpp"
using namespace std;
vector<string> GetLaborerAbilities(int Level);
vector<string> GetMerchantAbilities(int Level);
vector<string> GetFighterAbilities(int Level,MartialTypes_t MartialType);
vector<string> GetGishAbilities(int Level, MagicTypes_t MagicType, MartialTypes_t MartialType);
vector<string> GetThiefAbilities(int Level,MartialTypes_t MartialType);
vector<string> GetNobleAbilities(int Level);
vector<string> GetMagicUserAbilities(int Level, MagicTypes_t MagicType);
vector<string> GetMagicUsingThiefAbilities(int Level,MartialTypes_t MartialType, MagicTypes_t MagicType);
vector<string> GetPriestAbilities(int Level);
# endif /* Abiliites_h */
