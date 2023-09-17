//
//  Character.h
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#ifndef Character_h
#define Character_h
#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "Ancestries.h"
typedef enum{
  Male, Female, Nonbinary
}EGender;
typedef enum{
  Laborer, Merchant, Noble, Fighter, Magic_User, Gish, Magic_using_Thief, Priest, Thief
} ENPC_Type;
typedef enum{
  MagicNONE,Arcane, Divine, Primal,Occult,
} MagicTypes_t;
typedef enum{
  MartialNONE,OrganizedRanged,OrganizedMelle, DisorganizedRanged,DisorganizedMelle,
} MartialTypes_t;
typedef enum{
  Elite, Normal, Weak
} NPC_Strength_t;
typedef enum{
  Untrained, Trained,Expert,Master,Legendary
}TrainingLevel_t;
typedef struct{
  char * Name;
  char * Text;
  bool Finnese;
  bool Ranged;
  int Bonus;
  char * DamageDie;
  int DamageBonus;
} Weapon_T;
typedef struct{
  ENPC_Type Class;
  MagicTypes_t MagicType;
  TrainingLevel_t Acrobatics;
  TrainingLevel_t Arcana;
  TrainingLevel_t Athletics;
  TrainingLevel_t Crafting;
  TrainingLevel_t Deception;
  TrainingLevel_t Diplomacy;
  TrainingLevel_t Intimidation;
  TrainingLevel_t Lore;
  TrainingLevel_t Medicine;
  TrainingLevel_t Nature;
  TrainingLevel_t Occultism;
  TrainingLevel_t Performance;
  TrainingLevel_t Religion;
  TrainingLevel_t Society;
  TrainingLevel_t Stealth;
  TrainingLevel_t Survival;
  TrainingLevel_t Thievery;
  const char ** SpecialFeaturesAndAbilities;
  Weapon_T weapons[5];
} CharacterTemplate_t;
typedef struct{
  const wchar_t * Name;
  EGender Gender;
  ENPC_Type Class;
  EAncestries Ancestry;
  MagicTypes_t MagicType;
  bool InnateCaster;
  int Age;
  NPC_Strength_t Npc_strength;
  int Level;
  int Perception_Bonus;
  int HitPoints;
  int ArmorClass;
  int Strength;
  int Constitution;
  int Dexterity;
  int Intelligence;
  int Wisdom;
  int Charisma;
  int ReflexSave;
  int FortitudeSave;
  int WillSave;
  int Acrobatics;
  int Arcana;
  int Athletics;
  int Crafting;
  int Deception;
  int Diplomacy;
  int Intimidation;
  int Lore;
  int Medicine;
  int Nature;
  int Occultism;
  int Performance;
  int Religion;
  int Society;
  int Stealth;
  int Survival;
  int Thievery;
  const char ** SpecialFeaturesAndAbilities;
  int SpellAttackBonus;
  int SpellSaveDc;
  Weapon_T weapons[5];
  char ** Cantrips;
  char ** FirstLevelSpells;
  char ** SecondLevelSpells;
  char ** ThirdLevelSpells;
  char ** FourthLevelSpells;
  char ** FifthLevelSpells;
  char ** SixthLevelSpells;
  char ** SeventhLevelSpells;
  char ** EightLevelSpells;
  char ** NinthLevelSpells;
  char ** TenthLevelSpells;
  char ** Personality;
  char ** SpellBook;
} NPC_T;

NPC_T * CreateNPC(ENPC_Type T,int Level, bool InnateCaster, MagicTypes_t MagicType,MartialTypes_t MartialType, NPC_Strength_t str);
NPC_T * CreateNPC_From_Template(CharacterTemplate_t temp,int level, NPC_Strength_t str);
void DestroyNPC(NPC_T* NPC);
char * PrintNpc(FILE * f,NPC_T * NPC);
char ** GeneratePersonality(void);
NPC_T * CommandLineCharacter(void);
#endif /* Character_h */
