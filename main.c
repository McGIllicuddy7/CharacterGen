//
//  main.c
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#include <stdio.h>
#include "Utils.h"
#include "Arcane.h"
#include "Abilities.h"
#include "Character.h"
#include <string.h>
#include <stdlib.h>
NPC_T * CommandLineCharacter(void){
  ENPC_Type t = Laborer;
  int level = 1;
  int InnateCaster = 0;
  MagicTypes_t MagicType = MagicNONE;
  MartialTypes_t MartialType = MartialNONE;
  NPC_Strength_t Str = Normal;
  char buff[100];
  printf("Enter NPC Class(or h for help): ");
  fgets(buff, 100, stdin);
  if(buff[0] == 'h'){
    printf("(la for laborer, me for merchant, no for noble, fi for fighter, mu for magic user, gi for gish, mut for magic using theif, pr for priest,t for thief)\n");
    return NULL;
  }
  else if(buff[0] == 'l' && buff[1] == 'a'){
    t = Laborer;
  }
  else if(buff[0] == 'm' && buff[1] == 'e'){
    t = Merchant;
  }
  else if(buff[0] == 'n' && buff[1] == 'o'){
    t = Noble;
  }

  else if(buff[0] == 'f' && buff[1] == 'i'){
    t = Fighter;
  }
  else if(buff[0] == 'm' && buff[1] == 'u' && buff[2] != 't'){
    t = Magic_User;
  }
  else if(buff[0] == 'g' && buff[1] == 'i'){
    t = Gish;
  }
  else if(buff[0] == 'm' && buff[1] == 'u' && buff[2] == 't'){
    t =Magic_using_Thief;
  }
  else if(buff[0] == 'p' && buff[1] == 'r'){
    t = Priest;
  }
  else if(buff[0] == 't'){
    t = Thief;
  }
  else{
    printf("please enter a valid input");
    return NULL;
  }
  printf("Enter NPC Level: ");
  memset(buff,'\0',100);
  fgets(buff, 100, stdin);
  level = atoi(buff);
  if(t == Magic_User || t == Gish || t == Magic_using_Thief){
    printf("Enter Innate Caster(t for true f for false): ");
    memset(buff,'\0',100);
    fgets(buff, 100, stdin);
    InnateCaster = (buff[0] == 't');
    printf("Enter Magic Type(a for arcane, d for divine, p for primal, o for occult): ");
    memset(buff,'\0',100);
    fgets(buff, 100, stdin);
    if(buff[0] == 'a'){
      MagicType = Arcane;
    }
    else if(buff[0] == 'd'){
      MagicType = Divine;
    }
    else if(buff[0] == 'p'){
      MagicType = Primal;
    }
    else if(buff[0] =='o'){
      MagicType = Occult;
    }
    else{
      printf("please enter a valid input\n");
      return NULL;
    }
  }
  if(t == Fighter || t == Gish){
    printf("Enter Martial Type(om for organized melle, or for organized ranged, dm for disorganized melle, dr for disorganized ranged): ");
    memset(buff,'\0',100);
    fgets(buff, 100, stdin);
    if(buff[0] == 'd'){
      if(buff[1] == 'm'){
        MartialType = DisorganizedMelle;
      }
      else if(buff[1] == 'r'){
        MartialType = DisorganizedRanged;
      }
      else{
        printf("please enter a valid input\n");
        return NULL;
      }
    }
    else if(buff[0] == 'o'){
      if(buff[1] == 'm'){
        MartialType = OrganizedMelle;
      }
      else if(buff[1] == 'r'){
        MartialType = DisorganizedRanged;
      }
      else{
        printf("please enter a valid input\n");
        return NULL;
      }
    }
    else{
      printf("please enter a valid input\n");
      return NULL;
    }
  }
  return CreateNPC(t, level, InnateCaster, MagicType, MartialType, Str);
}
int main(int argc, const char * argv[]) {
  // insert code here...
  NPC_T * npc = NULL;
  int fs = 0;
  while(npc == NULL&& fs<3 ){
    npc = CommandLineCharacter();
    fs++;
  }
  printf("\n");
  if(npc)
    PrintNpc(stdout,npc);
  printf("\n");
  return 0;
}
