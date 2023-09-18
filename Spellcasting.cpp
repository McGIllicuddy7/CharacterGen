//
//  Spellcasting.c
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#include "Spellcasting.hpp"
//also known spell amounts
static const SpellSlots_t Innate[20] = {
  //level 1
  {5,3,0,0,0,0,0,0,0,0,0},
  //level 2
  {5,4,0,0,0,0,0,0,0,0,0},
  //level 3
  {5,4,3,0,0,0,0,0,0,0,0},
  //level 4
  {5,4,4,0,0,0,0,0,0,0,0},
  //level 5
  {5,4,4,3,0,0,0,0,0,0,0},
  //level 6
  {5,4,4,4,0,0,0,0,0,0,0},
  //level 7
  {5,4,4,4,3,0,0,0,0,0,0},
  //level 8
  {5,4,4,4,4,0,0,0,0,0,0},
  //level 9
  {5,4,4,4,4,3,0,0,0,0,0},
  //level 10
  {5,4,4,4,4,4,0,0,0,0,0},
  //level 11
  {5,4,4,4,4,4,3,0,0,0,0},
  //level 12
  {5,4,4,4,4,4,4,0,0,0,0},
  //level 13
  {5,4,4,4,4,4,4,3,0,0,0},
  //level 14
  {5,4,4,4,4,4,4,4,0,0,0},
  //level 15
  {5,4,4,4,4,4,4,4,3,0,0},
  //level 16
  {5,4,4,4,4,4,4,4,4,0,0},
  //level 17
  {5,4,4,4,4,4,4,4,4,3,0},
  //level 18
  {5,4,4,4,4,4,4,4,4,4,0},
  //level 19
  {5,4,4,4,4,4,4,4,4,4,1},
  //level 20
  {5,4,4,4,4,4,4,4,4,4,1},
};
static const SpellSlots_t Prepared[20] = {
  //level 1
  {5,2,0,0,0,0,0,0,0,0,0},
  //level 2
  {5,3,0,0,0,0,0,0,0,0,0},
  //level 3
  {5,3,2,0,0,0,0,0,0,0,0},
  //level 4
  {5,3,3,0,0,0,0,0,0,0,0},
  //level 5
  {5,3,3,2,0,0,0,0,0,0,0},
  //level 6
  {5,3,3,3,0,0,0,0,0,0,0},
  //level 7
  {5,3,3,3,2,0,0,0,0,0,0},
  //level 8
  {5,3,3,3,3,0,0,0,0,0,0},
  //level 9
  {5,3,3,3,3,2,0,0,0,0,0},
  //level 10
  {5,3,3,3,3,3,0,0,0,0,0},
  //level 11
  {5,3,3,3,3,3,2,0,0,0,0},
  //level 12
  {5,3,3,3,3,3,3,0,0,0,0},
  //level 13
  {5,3,3,3,3,3,3,2,0,0,0},
  //level 14
  {5,3,3,3,3,3,3,3,0,0,0},
  //level 15
  {5,3,3,3,3,3,3,3,2,0,0},
  //level 16
  {5,3,3,3,3,3,3,3,3,0,0},
  //level 17
  {5,3,3,3,3,3,3,3,3,2,0},
  //level 18
  {5,3,3,3,3,3,3,3,3,3,0},
  //level 19
  {5,3,3,3,3,3,3,3,3,3,1},
  //level 20
  {5,3,3,3,3,3,3,3,3,3,1},
};
const static SpellSlots_t SpellbookNumbers[20] = {
  //level 1
  {10,5,0,0,0,0,0,0,0,0,0},
  //level 2
  {10,7,0,0,0,0,0,0,0,0,0},
  //level 3
  {10,7,2,0,0,0,0,0,0,0,0},
  //level 4
  {10,7,4,0,0,0,0,0,0,0,0},
  //level 5
  {10,7,4,2,0,0,0,0,0,0,0},
  //level 6
  {10,7,4,4,0,0,0,0,0,0,0},
  //level 7
  {10,7,4,4,2,0,0,0,0,0,0},
  //level 8
  {10,7,4,4,4,0,0,0,0,0,0},
  //level 9
  {10,7,4,4,4,2,0,0,0,0,0},
  //level 10
  {10,7,4,4,4,4,0,0,0,0,0},
  //level 11
  {10,7,4,4,4,4,2,0,0,0,0},
  //level 12
  {10,7,4,4,4,4,4,0,0,0,0},
  //level 13
  {10,7,4,4,4,4,4,2,0,0,0},
  //level 14
  {10,7,4,4,4,4,4,4,0,0,0},
  //level 15
  {10,7,4,4,4,4,4,4,2,0,0},
  //level 16
  {10,7,4,4,4,4,4,4,4,0,0},
  //level 17
  {10,7,4,4,4,4,4,4,4,2,0},
  //level 18
  {10,7,4,4,4,4,4,4,4,2,0},
  //level 19
  {10,7,4,4,4,4,4,4,4,2,2},
  //level 20
  {10,7,5,5,4,4,4,4,4,2,2},
};
SpellSlots_t InnateSpellSlotsByLevel(int Level){
  return Innate[Level-1];
}
SpellSlots_t PreparedSpellSlotsByLevel(int Level){
  return Prepared[Level-1];
}
SpellSlots_t PreparedSpellBookByLevel(int Level){
  return SpellbookNumbers[Level-1];
}
int GetElement(SpellSlots_t t, int index){
  if(index == 0){
    return t.Cantrips;
  }
  if(index == 1){
    return t.Level1;
  }
  if(index == 2){
    return t.Level2;
  }
  if(index == 3){
    return t.Level3;
  }
  if(index == 4){
    return t.Level4;
  }
  if(index == 5){
    return t.Level5;
  }
  if(index == 6){
    return t.Level6;
  }
  if(index == 7){
    return t.Level7;
  }
  if(index == 8){
    return t.Level8;
  }
  if(index == 9){
    return t.Level9;
  }
  if(index>9){
    return t.Level10;
  }
  return 0;
}
