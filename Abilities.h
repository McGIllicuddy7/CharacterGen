//
//  Abiliites.h
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/9/23.
//

#ifndef Abiliites_h
#define Abiliites_h

#include <stdio.h>
#include "Character.h"
const char ** GetLaborerAbilities(int Level);
const char ** GetMerchantAbilities(int Level);
const char ** GetFighterAbilities(int Level,MartialTypes_t MartialType);
const char ** GetGishAbilities(int Level, MagicTypes_t MagicType, MartialTypes_t MartialType);
const char ** GetThiefAbilities(int Level,MartialTypes_t MartialType);
const char ** GetNobleAbilities(int Level);
const char ** GetMagicUserAbilities(int Level, MagicTypes_t MagicType);
const char ** GetMagicUsingThiefAbilities(int Level,MartialTypes_t MartialType, MagicTypes_t MagicType);
const char ** GetPriestAbilities(int Level);
# endif /* Abiliites_h */
