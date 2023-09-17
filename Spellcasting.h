//
//  Spellcasting.h
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#ifndef Spellcasting_h
#define Spellcasting_h
#pragma once
#include <stdio.h>
typedef struct{
  unsigned char Cantrips;
  unsigned char Level1;
  unsigned char Level2;
  unsigned char Level3;
  unsigned char Level4;
  unsigned char Level5;
  unsigned char Level6;
  unsigned char Level7;
  unsigned char Level8;
  unsigned char Level9;
  unsigned char Level10;
} SpellSlots_t;
SpellSlots_t InnateSpellSlotsByLevel(int Level);
SpellSlots_t PreparedSpellSlotsByLevel(int Level);
SpellSlots_t PreparedSpellBookByLevel(int Level);
int GetElement(SpellSlots_t t, int index);
#endif /* Spellcasting_h */
