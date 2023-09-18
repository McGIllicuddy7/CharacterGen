//
//  main.c
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#include "Character.hpp"
#include <iostream>
#include <stdio.h>
string get_string_from_in(void){
  string s;
  cin>>s;
  return s;
}
MartialTypes_t get_martial_type(){
  printf("enter martial type(om for organized melle, or for organized range, dm for disorgance melle, dr for disorganized range): ");
  string s = get_string_from_in();
  if(s == "om"){
    return OrganizedMelle;
  }
  else if(s == "or"){
    return OrganizedRanged;
  }
  else if(s == "dm"){
    return DisorganizedMelle;
  }
  else if(s == "dr"){
    return DisorganizedRanged;
  }
  else{
    return MartialNONE;
  }
}
MagicTypes_t get_magic_type(){
  printf("enter magic type(a for arcane, d for divine, o for occult, p for primal): ");
  string s = get_string_from_in();
  if(s == "a"){
    return Arcane;
  }
  else if(s == "d"){
    return Divine;
  }
  else if(s == "o"){
    return Occult;
  }
  else if(s == "p"){
    return Primal;
  }
  else{
    return MagicNONE;
  }
}
bool get_innate_caster(){
  printf("enter i for innate caster or p for prepared caster: ");
  string s = get_string_from_in();
  if(s == "i"){
    return true;
  }
  return false;
}
int main(void) {
  // insert code here...
chargen: 
  printf("enter level: ");
  ENPC_Type npc_type;
  int level = atoi(get_string_from_in().c_str());
  MartialTypes_t Martial = MartialNONE;
  MagicTypes_t Magic = MagicNONE;
  bool innate_caster = false;
  printf("enter npc type or h for help: ");
  string s = get_string_from_in();
  if(s == "h"){
    printf("(la for laborer, me for merchant, no for noble, fi for fighter, mu for magic user, gi for gish, mut for magic using theif, pr for priest,t for thief)\n");
    goto chargen;
  }
  else if(s == "la"){
    npc_type = Laborer;
  }
  else if(s == "me"){
    npc_type = Merchant;
  }
  else if(s == "no"){
    npc_type = Noble;
  }
  else if(s == "fi"){
    npc_type = Fighter;
    Martial = get_martial_type();
    if(Martial == MartialNONE){
      goto invldinput;
    }
  }
  else if(s == "mu"){
    npc_type = Magic_User;
    Magic = get_magic_type();
    if(Magic == MagicNONE){
      goto invldinput;
    }
    innate_caster = get_innate_caster();
  }
  else if(s == "gi"){
    npc_type = Gish;
    Martial = get_martial_type();
    if(Martial == MartialNONE){
      goto invldinput;
    }
    Magic = get_magic_type();
    if(Magic == MagicNONE){
      goto invldinput;
    }
    innate_caster = get_innate_caster();
  }
  else if(s == "mut"){
    npc_type = Magic_using_Thief;
    Magic = get_magic_type();
    if(Magic == MagicNONE){
      goto invldinput;
    }
    innate_caster = get_innate_caster();
  }
  else if(s == "pr"){
    npc_type = Priest;
  }
  else if(s == "t"){
    npc_type = Thief;
  }
  else{
invldinput: 
    printf("please enter a valid input\n");
    goto chargen;
  }
  printf("\n");
  NPC_T * npc = CreateNPC(npc_type, level,innate_caster, Magic, Martial, Normal);
  PrintNpc(stdout, npc);
  return 0;
}
