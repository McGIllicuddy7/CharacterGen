//
//  Character.c
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#include "Character.h"
#include "Names.h"
#include "Utils.h"
#include "Abilities.h"
#include "Arcane.h"
#include "Divine.h"
#include "Primal.h"
#include "Occult.h"
#include "Spellcasting.h"
#include <string.h>
/*typedef struct{
 char * Name;
 char * Text;
 bool Finesse;
 bool Ranged,
 int Bonus;
 char * DamageDie;
 int DamageBonus;
} Weapon_T;
*/
Weapon_T Club = {"Club","Thrown 10 ft.",false,false,0,"1d4",0};
Weapon_T Dagger = {"Dagger","Agile, finesse, thrown 10 ft., versatile S.",true,false,0,"1d4",0};
Weapon_T LongSpear = {"Long Spear","Reach",false,false,0,"1d6",0};
Weapon_T Staff = {"Staff","Two-hand d8",false,false,0,"1d4",0};
Weapon_T BastardSword = {"Bastard sword","Two-hand d12",false,false,0,"1d8",0};
Weapon_T BattleAxe = {"Battle axe","Sweep",false,false,0,"1d8",0};
Weapon_T Greatsword = {"Greatsword","Versatile P",false,false,0,"1d12",0};
Weapon_T Longsword = {"Longsword", "Versatile P",false,false,0,"1d8",0};
Weapon_T Rapier = {"Rapier","Deadly d8, disarm, finesse",true,false, 0,"1d6",0};
Weapon_T Shortsword = {"Shortsword","Agile, finesse, versatile S",true,false,0,"1d6",0};
Weapon_T Crossbow = {"Crossbow","Range 120",false,true,0,"1d8",0};
Weapon_T HeavyCrossbow = {"Heavy Crossbow","Range 120",false,true,0,"1d10",0};
Weapon_T Longbow = {"Longbow","Range 100",false,true,0,"1d8",0};
Weapon_T Shortbow = {"Shortbow","Range 60",false,true,0,"1d6",0};
int VeryHighAbilityScore(void){
  int val = RollDice("1d4")+14;
  if(val>20){
    val = 20;
  }
  return val;
}
int HighAbilityScore(void){
  int val = RollDice("2d4")+10;
  return val;
}
int MediumAbilityScore(void){
  return RollDice("2d4")+6;
}
int LowAbilityScore(void){
  return RollDice("4d4")+2;
}
int CalculateModifier(int StatValue){
  return (StatValue-10)/2;
};
void WeaponCalculation(NPC_T * out,MartialTypes_t Mt){
  if(Mt == MartialNONE){
    if(out->Class == Thief || out->Class == Magic_using_Thief){
      if(RandomInt()%3 == 0){
        out->weapons[0] = Rapier;
      }
      else{
        out->weapons[0] = Shortsword;
      }
      if(RandomInt()%3 == 0){
        out->weapons[1] = Longbow;
      }
      else{
        out->weapons[1] = Shortbow;
      }
      out->weapons[2] = Dagger;
    }
    else{
      if(RandomInt()%2 == 0){
        out->weapons[0] = Dagger;
      }
      else{
        out->weapons[0] = Staff;
      }
    }
  }
  else if(Mt == OrganizedMelle){
    int r = RandomInt()%5;
    if(r == 0){
      out->weapons[0] = LongSpear;
    }
    if(r == 1){
      out->weapons[0] = Greatsword;
    }
    if(r == 2){
      out->weapons[0] = Rapier;
    }
    if(r>2){
      out->weapons[0] = Longsword;
    }
    if(RandomInt()%3 == 0){
      out->weapons[1] = Longbow;
    }
    else{
      out->weapons[1] = Crossbow;
    }
    out->weapons[2] = Dagger;
  }
  else if(Mt == OrganizedRanged){
    if(RandomInt()%3 == 0){
      out->weapons[0] = HeavyCrossbow;
    }
    else{
      out->weapons[0] = Longbow;
    }
    if(RandomInt()%3 == 0){
      out->weapons[1] = Rapier;
    }
    else{
      out->weapons[1] = Shortsword;
    }
  }
  else if(Mt ==DisorganizedRanged){
    if(RandomInt()%3 == 0){
      out->weapons[0] = Longbow;
    }
    else{
      out->weapons[0] = Crossbow;
    }
    out->weapons[1] = Dagger;
  }
  else if(Mt == DisorganizedMelle){
    if(RandomInt()%3 == 0){
      out->weapons[0] = Shortsword;
    }
    else{
      if(out->Dexterity>out->Strength){
        out->weapons[0] = Dagger;
      }
      else{
        out->weapons[0] = Club;
      }
    }
  }
  for(int i = 0; i<5; i++){
    if(out->weapons[i].Name){
      bool fin = out->weapons[i].Finnese;
      bool ran = out->weapons[i].Ranged;
      out->weapons[i].Bonus = 2+CalculateModifier(out->Strength)*(!fin && !ran)+CalculateModifier(out->Dexterity)*(fin ||ran);
      out->weapons[i].DamageBonus = CalculateModifier(out->Strength)*(!ran);
    }
  }
}
static const char *  RandFirstName(const char ** BaseArray, EGender Gender){
  int s = RandomInt()%100;
  if(s<25){ return (Gender == Female ? StrArrayRandomElement(HumanFemmeFirstNames) :StrArrayRandomElement(HumanMascFirstNames));}
  if(s<50){return (Gender == Female ? StrArrayRandomElement(GiffFemmeFirstnames) :StrArrayRandomElement(GiffMascFirstNames));}
  if(s<75){return (Gender == Female ? StrArrayRandomElement(TieflingFemmeFirstNames) :StrArrayRandomElement(TieflingMascFirstNames));}
  return StrArrayRandomElement(BaseArray);
}
static const char *  RandLastName(const char ** BaseArray){
  int s = RandomInt()%100;
  if(s<25){ return StrArrayRandomElement(humanLastNames);}
  if(s<50){return StrArrayRandomElement(GiffLastnames);}
  if(s<75){StrArrayRandomElement(TieflingLastNames);}
  return StrArrayRandomElement(BaseArray);
}
static EGender GenerateGender(void){
  int s = RandomInt()%100;
  if(s<45){
    return Female;
  }
  if(s<90){
    return  Male;
  }
  return Nonbinary;
};
char * GenerateName(EAncestries Ancestry, EGender Gender){
  EAncestries a = Ancestry;
  EGender g = Gender;
  if(Gender == Nonbinary){
    if(RandomInt()%100<50){
      g = Female;
    }
    else{
      g = Male;
    }
  }
  if(RandomInt()%100<90){a = RandomAncestry();}
  const char ** FnameArray = TieflingFemmeFirstNames;
  if(a == Catfolk){FnameArray = ( g == Female ? HalflingFemmeFirstNames : HalflingMascFirstNames);}
  if(a == Dwarf){FnameArray = ( g == Female ? DwarfFemmeFirstNames : DwarfMascFirstNames);}
  if(a == Elf){FnameArray =( g == Female ? ElfFemmeFirstNames : ElfMascFirstNames);}
  if(a == Goblin){FnameArray =( g == Female ? GoblinFemmeFirstNames : GoblinMascFirstNames);}
  if(a == Gnome){FnameArray = GnomeFirstNames;}
  if(a == Halfling){FnameArray = ( g == Female ? HalflingFemmeFirstNames : HalflingMascFirstNames);}
  if(a == Human){FnameArray = ( g == Female ? HumanFemmeFirstNames : HumanMascFirstNames);}
  if(a == Orc){FnameArray = ( g == Female ? OrcFemmeFirstNames : OrcMascFirstNames);}
  const char * FirstName = RandFirstName(FnameArray, g);
  EAncestries b = Ancestry;
  const char ** LnameArray = TieflingLastNames;
  if(RandomInt()%100<80){b = RandomAncestry();}
  if(b == Catfolk){LnameArray = HalflingLastNames;}
  if(b == Dwarf){LnameArray = DwarfLastNames;}
  if(b == Elf){LnameArray = ElfLastNames;}
  if(b == Goblin){LnameArray = GoblinLastNames;}
  if(b == Gnome){LnameArray = GnomeLastNames;}
  if(b == Halfling){LnameArray = HalflingLastNames;}
  if(b == Human){LnameArray = humanLastNames;}
  if(b == Orc){LnameArray = OrcLastNames;}
  const char * LastName = RandLastName(LnameArray);
  uint64_t l = strlen(FirstName)+strlen(LastName);
  uint64_t fl = strlen(FirstName);
  char * name = malloc(l);
  for(int i = 0; i<strlen(FirstName)-1;i++){
    name[i] = FirstName[i];
  }
  name[fl-1] = ' ';
  for(int i = 0;i<strlen(LastName); i++ ){
    name[i+fl] = LastName[i];
  }
  return name;
}
static const char * Sanity[] = {"Sanity: Very Stable", "Sanity: Normal","Sanity: Normal", "Sanity: Normal","Sanity: Normal", "Sanity :Normal", "Sanity: Neurotic", "Sanity: Unstable", "Sanity: Insane", "Sanity: Maniacal", NULL};
static const char * GeneralTendencies[] = {"Optimist", "Pessimist", "Hedonist", "Altruist", "Kindly","Careless", "Carpcious", "Mischievious",
  "Sober", "Moody","Inquisitive","Trusting", "Suspicious","Cautious", "Precise", "Exacting", "Perceptive", "Opinionated", "Contrarian", "Violent", "Sudious",
  "Foul","Cruel","Callous", "Prankster","Servile","Obseqious","Fanatical", "Obsessive", "Maleovolent", "Loquacious",NULL};
static const char * AveragePersonality[] = {"Modest","Agoist", "Arrogant", "Friendly","Aloof","Hostile", "Well Spoken", "Diplomatic", "Abrasitve", NULL};
static const char * ExtrovertedPersonality[] = {"Forceful","Overbearing", "Friendly","Blustering","Antagonistic", "Rude", "Rash","Diplomatic",NULL};
static const char * IntrovertedPersonality[] = {"Retiring","Taciturn","Friendly","Aloof","Hostile","Rude","Courteous","Solidary","Secretive",NULL};
static const char * Disposition[] = {"Cheerful","Morose", "Compassionate","Sensitive","Unfeeling","Insensitive","Humble","Proud","Haughty","Even Tempered","Easy Going","Harsh",NULL};
static const char * PersonalityNature[] = {"Soft Hearted","Forgiving","Hard Hearted","Unforgiving","Jealous","Vengeful",NULL};
static const char * PersonalityMaterialism[] = {"Materialism: Aestethic","Materialism: Intellectualist", "Materialism: Average", "Materialism: Covetous","Materialism: Greedy",
  "Materialism: Avaricious", NULL};
static const char * PersonalityHonesty[] = {"Scrupulous", "Very Honorable","Truthful","Average Honesty","Average Honesty","Average Honesty","Liar","Decietful",NULL};
static const char * PersonalityBravery[] = {"Normal Bravery", "Normal Bravery", "Normal Bravery","Foolhardy","Brave","Fearless","Cowardly","Craven",NULL};
static const char * PersonalityEnergy[] = {"Slothful","Lazy","Normal Energy","Normal Energy","Normal Energy","Energetic","Energetic","Driven",NULL};
static const char * PersonalityThrift[] = {"Miserly","Mean Thrift","Thrifty","Average Thrift","Average Thrift","Spendthrift","Spendthrift","Wastrel",NULL};
static const char * PersonalityMorals[] = {"Aesthetic Morals","Virtous Morals","Normal Morals","Normal Morals","Lusty Morals","Lusty Morals","Lustful Morals","Immoral",
  "Amoral","Perverted","Depraved","Sadistic",NULL};
static const char * PersonalityPiety[] = {"Saintly","Zealot","Pious","Reverent","Average Piety","Average Piety","Average Piety","Average Piety","Average Piety","Impious",
  "Irreverent","Iconoclastic","Irreligious",NULL};
static const char * Interests[] = {"Interested in: Religion","Interested in: Legends","Interested in: History","Interested in: Nature",
  "Interested in: Horticulture","Interested in: Animal Husbandry","Interested in: Exotic Animals","Interested in: Hunting","Interested in: Fishing","Interested in: Handicrafts",
  "Interested in: Athletics","Interested in: Politics","Interested in: Wine and Spirits","Interested in: Foods and Preperation","Interested in: Gambling",
  "Interested in: Drugs","Knife and Dagger Collector","Sword Collector","Weapon Collector","Weapon Collector","Shield and Weapon Collector","Armor Collector","Book and Scroll Collector","Mineral and Gem Collector","Ornament and Jewelry Collector","Coin and Token Collector",
  "Trophy and Skin Collector","Porcelain,China, and Crystal Collector","Art Collector","Interested in: Community Service","Interested in: Altruism","Interested in: Not Much",NULL
};
char ** GeneratePersonality(void){
  char ** Personality = StrArrayNew(NULL);
  int r;
  r = RollDice("1d10");
  if(r>8){ r = RollDice("1d10");}
  Personality = StrArrayAdd(Personality,Sanity[r-1]);
  Personality = StrArrayAdd(Personality,StrArrayRandomElement(GeneralTendencies));
  r = RollDice("1d8");
  if(r<6){
    Personality = StrArrayAdd(Personality,StrArrayRandomElement(AveragePersonality));
  }
  else if(r<8){
    Personality = StrArrayAdd(Personality,StrArrayRandomElement(ExtrovertedPersonality));
  }
  else{
    Personality = StrArrayAdd(Personality,StrArrayRandomElement(IntrovertedPersonality));
  }
  Personality = StrArrayAdd(Personality, StrArrayRandomElement(Disposition));
  Personality = StrArrayAdd(Personality, StrArrayRandomElement(PersonalityNature));
  Personality = StrArrayAdd(Personality, StrArrayRandomElement(PersonalityMaterialism));
  Personality = StrArrayAdd(Personality, StrArrayRandomElement(PersonalityHonesty));
  Personality = StrArrayAdd(Personality, StrArrayRandomElement(PersonalityBravery));
  Personality = StrArrayAdd(Personality, StrArrayRandomElement(PersonalityEnergy));
  Personality = StrArrayAdd(Personality, StrArrayRandomElement(PersonalityThrift));
  r = RollDice("1d12");
  if(r>9){
    r = RollDice("1d12");
  }
  Personality = StrArrayAdd(Personality, PersonalityMorals[r-1]);
  Personality = StrArrayAdd(Personality, StrArrayRandomElement(PersonalityPiety));
  Personality = StrArrayAdd(Personality, StrArrayRandomElement(Interests));
  Personality = StrArrayAdd(Personality, NULL);
  return Personality;
}
typedef enum{
  Arcana, Athletics,Acrobatics,Crafting, Deception, Diplomacy, Intimidation, Lore, Medicine, Nature, Occultism, Performance, Perception, Religion, Society, Survival,Stealth, Thievery,
}Skills;
typedef enum{
  Strength, Constitution, Dexterity, Intelligence, Wisdom, Charisma,
} AbilityScores;

int CalculateSkillMod(int index, NPC_T * out,AbilityScores Score,IntArray_t TrainedSkills, IntArray_t ExpertSkills, IntArray_t MasteredSkills,IntArray_t LegendarySkills){
  int base = 0;
  if(Score == Strength){
    base += CalculateModifier(out->Strength);
  }
  if(Score == Constitution){
    base += CalculateModifier(out->Constitution);
  }
  if(Score == Dexterity){
    base += CalculateModifier(out->Dexterity);
  }
  if(Score == Intelligence){
    base += CalculateModifier(out->Intelligence);
  }
  if(Score == Wisdom){
    base += CalculateModifier(out->Wisdom);
  }
  if(Score == Charisma){
    base += CalculateModifier(out->Charisma);
  }
  base += (2+out->Level)*IntArrayContains(&TrainedSkills, index)+(4+out->Level)*IntArrayContains(&ExpertSkills, index)+(6+out->Level)*IntArrayContains(&MasteredSkills, index)+(8+out->Level)*IntArrayContains(&LegendarySkills,index);
  return base;
}
#define SetUpSkills(NPC, T, Ability) NPC->T = CalculateSkillMod(T,out, Ability, TrainedSkills,ExpertSkills, MasteredSkills, LegendarySkills)
void CalculateSkills(NPC_T * out, IntArray_t TrainedSkills, IntArray_t ExpertSkills, IntArray_t MasteredSkills,IntArray_t LegendarySkills){
  SetUpSkills(out, Arcana, Intelligence);
  SetUpSkills(out, Athletics, Strength);
  SetUpSkills(out, Acrobatics, Dexterity);
  SetUpSkills(out, Crafting, Intelligence);
  SetUpSkills(out, Deception, Charisma);
  SetUpSkills(out,Diplomacy, Charisma);
  SetUpSkills(out,Intimidation, Charisma);
  SetUpSkills(out, Lore, Intelligence);
  SetUpSkills(out, Medicine, Wisdom);
  SetUpSkills(out, Nature,Wisdom);
  SetUpSkills(out, Occultism, Intelligence);
  SetUpSkills(out, Performance, Charisma);
  SetUpSkills(out, Religion, Wisdom);
  SetUpSkills(out,Society,Charisma);
  SetUpSkills(out, Stealth, Dexterity);
  SetUpSkills(out, Thievery, Dexterity);
  out->Perception_Bonus = CalculateSkillMod(Perception,out, Wisdom, TrainedSkills,ExpertSkills,MasteredSkills, LegendarySkills);
}
void SelectSkills(NPC_T * out,IntArray_t Skills, int numskills,int numexpert,int nummastered, int numlegendary){
  IntArray_t TrainedSkills = IntArrayChoose(&Skills, numskills);
  IntArray_t ExpertSkills = IntArrayChoose(&TrainedSkills, numexpert);
  IntArray_t MasteredSkills = IntArrayChoose(&ExpertSkills,nummastered);
  IntArray_t LegendarySkills = IntArrayChoose(&MasteredSkills, numlegendary);
  CalculateSkills(out, TrainedSkills, ExpertSkills, MasteredSkills,LegendarySkills);
  IntArrayFree(&TrainedSkills);
  IntArrayFree(&ExpertSkills);
  IntArrayFree(&MasteredSkills);
  IntArrayFree(&LegendarySkills);
}
#define CasterAbilityScores(Highest)\
if(MagicType == Arcane){Out->Intelligence = Highest; Out->Wisdom = MediumAbilityScore(); Out->Charisma = MediumAbilityScore();}\
if(MagicType == Divine || MagicType == Primal){Out->Intelligence =MediumAbilityScore(); Out->Wisdom = Highest;Out->Charisma = MediumAbilityScore();}\
if(MagicType == Occult){Out->Intelligence =MediumAbilityScore();  Out->Wisdom = MediumAbilityScore(); Out->Charisma = Highest;}
static const char ** CantripsLut[] = {NULL, Arcane_Cantrips, Divine_Cantrips,Primal_Cantrips, Occult_Cantrips};
static const char ** Spells1stLevelLut[] = {NULL, Arcane_1st_Level, Divine_1st_Level, Primal_1st_Level, Occult_1st_Level};
static const char ** Spells2ndLevelLut[] = {NULL, Arcane_2nd_Level, Divine_2nd_Level, Primal_2nd_Level, Occult_2nd_Level};
static const char ** Spells3rdLevelLut[] = {NULL, Arcane_3rd_Level, Divine_3rd_Level, Primal_3rd_Level, Occult_3rd_Level};
static const char ** Spells4thLevelLut[] = {NULL, Arcane_4th_Level, Divine_4th_Level, Primal_4th_Level, Occult_4th_Level};
static const char ** Spells5thLevelLut[] = {NULL, Arcane_5th_Level, Divine_5th_Level, Primal_5th_Level, Occult_5th_Level};
static const char ** Spells6thLevelLut[] = {NULL, Arcane_6th_Level, Divine_6th_Level, Primal_6th_Level, Occult_6th_Level};
static const char ** Spells7thLevelLut[] = {NULL, Arcane_7th_Level, Divine_7th_Level, Primal_7th_Level, Occult_7th_Level};
static const char ** Spells8thLevelLut[] = {NULL, Arcane_8th_Level, Divine_8th_Level, Primal_8th_Level, Occult_8th_Level};
static const char ** Spells9thLevelLut[] = {NULL, Arcane_9th_Level, Divine_9th_Level, Primal_9th_Level, Occult_9th_Level};
static const char ** Spells10thLevelLut[] = {NULL, Arcane_10th_Level, Divine_10th_Level, Primal_10th_Level, Occult_10th_Level};
#define SpellbookAdd(T) for(int i = 0; i<StrArrayLen((const char **)T)-1; i++){\
  out->SpellBook[counter] = T[i];\
  counter ++;\
}
void GenerateSpells(NPC_T * out){
  int level = out->Level;
  if(out->Class != Magic_User){
    level = level/3;
    if(level<1){
      level = 1;
    }
  }
  if(out->InnateCaster){
    SpellSlots_t Slots = InnateSpellSlotsByLevel(level);
    out->Cantrips = (char **)StrArrayChoose(CantripsLut[out->MagicType], Slots.Cantrips);
    out->FirstLevelSpells = (char **)StrArrayChoose(Spells1stLevelLut[out->MagicType], Slots.Level1);
    out->SecondLevelSpells =(char **)StrArrayChoose(Spells2ndLevelLut[out->MagicType], Slots.Level2);
    out->ThirdLevelSpells = (char **)StrArrayChoose(Spells3rdLevelLut[out->MagicType], Slots.Level3);
    out->FourthLevelSpells = (char **)StrArrayChoose(Spells4thLevelLut[out->MagicType], Slots.Level4);
    out->FifthLevelSpells = (char **)StrArrayChoose(Spells5thLevelLut[out->MagicType], Slots.Level5);
    out->SixthLevelSpells = (char **)StrArrayChoose(Spells6thLevelLut[out->MagicType], Slots.Level6);
    out->SeventhLevelSpells = (char **)StrArrayChoose(Spells7thLevelLut[out->MagicType], Slots.Level7);
    out->EightLevelSpells = (char **)StrArrayChoose(Spells8thLevelLut[out->MagicType], Slots.Level8);
    out->NinthLevelSpells = (char **)StrArrayChoose(Spells9thLevelLut[out->MagicType], Slots.Level9);
    out->TenthLevelSpells = (char **)StrArrayChoose(Spells10thLevelLut[out->MagicType], Slots.Level10);
  }
  else{
    SpellSlots_t Book = PreparedSpellBookByLevel(level);
    SpellSlots_t Slots = PreparedSpellSlotsByLevel(level);
    char ** CantripBuff = (char **)StrArrayChoose(CantripsLut[out->MagicType], Book.Cantrips);
    char ** FirstLevelBuff = (char **)StrArrayChoose(Spells1stLevelLut[out->MagicType], Book.Level1);
    char ** SecondLevelBuff = (char **)StrArrayChoose(Spells2ndLevelLut[out->MagicType], Book.Level2);
    char ** ThirdLevelBuff = (char **)StrArrayChoose(Spells3rdLevelLut[out->MagicType], Book.Level3);
    char ** FourthLevelBuff = (char **)StrArrayChoose(Spells4thLevelLut[out->MagicType], Book.Level4);
    char ** FifthLevelBuff = (char **)StrArrayChoose(Spells5thLevelLut[out->MagicType], Book.Level5);
    char ** SixthLevelBuff = (char **)StrArrayChoose(Spells6thLevelLut[out->MagicType], Book.Level6);
    char ** SeventhLevelBuff = (char **)StrArrayChoose(Spells7thLevelLut[out->MagicType], Book.Level7);
    char ** EightLevelBuff = (char **)StrArrayChoose(Spells8thLevelLut[out->MagicType], Book.Level8);
    char ** NinthLevelBuff = (char **)StrArrayChoose(Spells9thLevelLut[out->MagicType], Book.Level9);
    char ** TenthLevelBuff = (char **)StrArrayChoose(Spells10thLevelLut[out->MagicType], Book.Level10);
    out->Cantrips = (char **)StrArrayChoose((const char **)CantripsLut[out->MagicType], Slots.Cantrips);
    out->FirstLevelSpells = StrArraySelect((char **)Spells1stLevelLut[out->MagicType], Slots.Level1);
    out->SecondLevelSpells = StrArraySelect((char **)Spells2ndLevelLut[out->MagicType], Slots.Level2);
    out->ThirdLevelSpells = StrArraySelect((char **)Spells3rdLevelLut[out->MagicType], Slots.Level3);
    out->FourthLevelSpells = StrArraySelect((char **)Spells4thLevelLut[out->MagicType], Slots.Level4);
    out->FifthLevelSpells = StrArraySelect((char **)Spells5thLevelLut[out->MagicType], Slots.Level5);
    out->SixthLevelSpells = StrArraySelect((char **)Spells6thLevelLut[out->MagicType], Slots.Level6);
    out->SeventhLevelSpells = StrArraySelect((char **)Spells7thLevelLut[out->MagicType], Slots.Level7);
    out->EightLevelSpells = StrArraySelect((char **)Spells8thLevelLut[out->MagicType], Slots.Level8);
    out->NinthLevelSpells = StrArraySelect((char **)Spells9thLevelLut[out->MagicType], Slots.Level9);
    out->TenthLevelSpells = StrArraySelect((char **)Spells10thLevelLut[out->MagicType], Slots.Level10);
    int num = (14+level*2)*8;
    out->SpellBook = malloc(num);
    int counter = 0;
    SpellbookAdd(CantripBuff);
    SpellbookAdd(FirstLevelBuff);
    SpellbookAdd(SecondLevelBuff);
    SpellbookAdd(ThirdLevelBuff);
    SpellbookAdd(FourthLevelBuff);
    SpellbookAdd(FifthLevelBuff);
    SpellbookAdd(SixthLevelBuff);
    SpellbookAdd(SeventhLevelBuff);
    SpellbookAdd(EightLevelBuff);
    SpellbookAdd(NinthLevelBuff);
    SpellbookAdd(TenthLevelBuff);
    out->SpellBook[num] = NULL;
    free(CantripBuff);
    free(FirstLevelBuff);
    free(SecondLevelBuff);
    free(ThirdLevelBuff);
    free(FourthLevelBuff);
    free(FifthLevelBuff);
    free(SixthLevelBuff);
    free(SeventhLevelBuff);
    free(EightLevelBuff);
    free(NinthLevelBuff);
    free(TenthLevelBuff);
  }
}
int SkillsList[] = { Acrobatics,Arcana,Athletics,Crafting,Deception,Diplomacy,Intimidation,Lore,Medicine,Nature,Occultism,Perception,Performance,Religion,
  Society,Stealth,Survival,Thievery};
IntArray_t DefaultSkillsList = {SkillsList,sizeof(SkillsList)/4};
//laborers high hit points, high strength, high damage, low attack, low ac
void GenerateLaborer(NPC_T * Out, int Level){
  Out->Strength = HighAbilityScore();
  Out->Dexterity = MediumAbilityScore();
  Out->Constitution = HighAbilityScore();
  Out->Intelligence =MediumAbilityScore();
  Out->Wisdom= MediumAbilityScore();
  Out->Charisma= MediumAbilityScore();
  Out->MagicType =MagicNONE;
  Out->SpecialFeaturesAndAbilities =GetLaborerAbilities(Level);
  Out->ArmorClass  = 10+CalculateModifier(Out->Dexterity)+Level+2;
  Out->HitPoints = (9+CalculateModifier(Out->Constitution))*Level;
  Out->ReflexSave = 2+CalculateModifier(Out->Dexterity)+Level;
  Out->FortitudeSave = 4+CalculateModifier(Out->Constitution)+Level;
  Out->WillSave = 2+CalculateModifier(Out->Wisdom)+Level;
  int numSkills = rand()%4+2;
  int numexpert = Level/5*(Level>4);
  int nummastered = Level/10 * (Level>9);
  int numLegendary = Level/15 *(Level>14);
  SelectSkills(Out,DefaultSkillsList, numSkills, numexpert, nummastered,numLegendary);
}
//low hit points, high charisma, low ac, low damage, low attack

void GenerateMerchant(NPC_T * Out, int Level){
  Out->Strength = MediumAbilityScore();
  Out->Dexterity = MediumAbilityScore();
  Out->Constitution = MediumAbilityScore();
  Out->Intelligence =HighAbilityScore();
  Out->Wisdom= MediumAbilityScore();
  Out->Charisma= HighAbilityScore();
  Out->MagicType =MagicNONE;
  Out->SpecialFeaturesAndAbilities = GetMerchantAbilities(Level);
  Out->ArmorClass  = 10+CalculateModifier(Out->Dexterity)+Level+2;
  Out->HitPoints = (6+CalculateModifier(Out->Constitution))*Level;
  int numSkills = rand()%4+2;
  int numexpert = Level/5*(Level>4);
  int nummastered = Level/10 * (Level>9);
  int numLegendary = Level/15 *(Level>14);
  Out->ReflexSave = 2+CalculateModifier(Out->Dexterity)+Level;
  Out->FortitudeSave = 2+CalculateModifier(Out->Constitution)+Level;
  Out->WillSave = 4+CalculateModifier(Out->Wisdom)+Level;
  SelectSkills(Out,DefaultSkillsList, numSkills, numexpert, nummastered,numLegendary);
}
//high ac, high attack, mid hit points, mid damage, wealth and power
void GenerateNoble(NPC_T * Out, int Level){
  Out->Strength = MediumAbilityScore();
  Out->Dexterity = MediumAbilityScore();
  Out->Constitution = MediumAbilityScore();
  Out->Intelligence =HighAbilityScore();
  Out->Wisdom= MediumAbilityScore();
  Out->Charisma= HighAbilityScore();
  Out->MagicType = MagicNONE;
  Out->SpecialFeaturesAndAbilities = GetNobleAbilities(Level);
  Out->ArmorClass  = 10+CalculateModifier(Out->Dexterity)+Level+2;
  Out->HitPoints = (6+CalculateModifier(Out->Constitution))*Level;
  Out->ReflexSave = 2+CalculateModifier(Out->Dexterity)+Level;
  Out->FortitudeSave = 2+CalculateModifier(Out->Constitution)+Level;
  Out->WillSave = 4+CalculateModifier(Out->Wisdom)+Level;
  Out->SpecialFeaturesAndAbilities = GetNobleAbilities(Level);
  int numSkills = rand()%4+2;
  int numexpert = Level/5*(Level>4);
  int nummastered = Level/10 * (Level>9);
  int numLegendary = Level/15 *(Level>14);
  SelectSkills(Out,DefaultSkillsList, numSkills, numexpert, nummastered,numLegendary);
}
//high ac, high attack, mid damage, high hit points
void GenerateFighter(NPC_T * Out, int Level,MartialTypes_t MartialType){
  if(MartialType == OrganizedMelle){
    Out->Strength = VeryHighAbilityScore();
    Out->Dexterity = MediumAbilityScore();
    Out->Constitution = MediumAbilityScore();
    Out->Intelligence = MediumAbilityScore();
    Out->Wisdom= HighAbilityScore();
    Out->Charisma= HighAbilityScore();
    Out->ArmorClass  = 18+CalculateModifier(Out->Dexterity)+Level+2;
    Out->HitPoints = (10+CalculateModifier(Out->Constitution))*Level;
  }
  if(MartialType == DisorganizedMelle){
    Out->Strength = VeryHighAbilityScore();
    Out->Dexterity =  HighAbilityScore();
    Out->Constitution = HighAbilityScore();
    Out->Intelligence = MediumAbilityScore();
    Out->Wisdom= MediumAbilityScore();
    Out->Charisma= MediumAbilityScore();
    Out->ArmorClass  = 15+CalculateModifier(Out->Dexterity)+Level+2;
    Out->HitPoints = (12+CalculateModifier(Out->Constitution))*Level;
  }
  if(MartialType == OrganizedRanged){
    Out->Strength = MediumAbilityScore();
    Out->Dexterity = VeryHighAbilityScore();
    Out->Constitution = MediumAbilityScore();
    Out->Intelligence = MediumAbilityScore();
    Out->Wisdom= HighAbilityScore();
    Out->Charisma= HighAbilityScore();
    Out->ArmorClass  = 13+CalculateModifier(Out->Dexterity)+Level+2;
    Out->HitPoints = (8+CalculateModifier(Out->Constitution))*Level;
  }
  if(MartialType == DisorganizedRanged){
    Out->Strength = HighAbilityScore();
    Out->Dexterity =  VeryHighAbilityScore();
    Out->Constitution = HighAbilityScore();
    Out->Intelligence = MediumAbilityScore();
    Out->Wisdom= MediumAbilityScore();
    Out->Charisma= MediumAbilityScore();
    Out->ArmorClass  = 12+CalculateModifier(Out->Dexterity)+Level+2;
    Out->HitPoints = (10+CalculateModifier(Out->Constitution))*Level;
  }
  Out->ReflexSave = 2+CalculateModifier(Out->Dexterity)+Level;
  Out->FortitudeSave = 4+CalculateModifier(Out->Constitution)+Level;
  Out->WillSave = 2+CalculateModifier(Out->Wisdom)+Level;
  Out->MagicType = MagicNONE;
  Out->SpecialFeaturesAndAbilities = GetFighterAbilities(Level, MartialType);
  int numSkills = rand()%4+2;
  int numexpert = Level/5*(Level>4);
  int nummastered = Level/10 * (Level>9);
  int numLegendary = Level/15 *(Level>14);
  SelectSkills(Out,DefaultSkillsList, numSkills, numexpert, nummastered,numLegendary);
}
//base mid ac, mid hit points, mid damage, high attack
void GenerateGish(NPC_T * Out, int Level,MartialTypes_t MartialType,MagicTypes_t MagicType){
  Out->Strength = VeryHighAbilityScore();
  Out->Dexterity = HighAbilityScore();
  Out->Constitution = HighAbilityScore();
  CasterAbilityScores(HighAbilityScore());
  Out->MagicType = MagicType;
  Out->SpecialFeaturesAndAbilities = GetGishAbilities(Level, MagicType, MartialType);
  GenerateSpells(Out);
  Out->ArmorClass  = 15+CalculateModifier(Out->Dexterity)+Level+2;
  Out->HitPoints = (9+CalculateModifier(Out->Constitution))*Level;
  int numSkills = rand()%4+2;
  int numexpert = Level/5*(Level>4);
  int nummastered = Level/10 * (Level>9);
  int numLegendary = Level/15 *(Level>14);
  SelectSkills(Out,DefaultSkillsList, numSkills, numexpert, nummastered,numLegendary);
  Out->ReflexSave = 2+CalculateModifier(Out->Dexterity)+Level;
  Out->FortitudeSave = 4+CalculateModifier(Out->Constitution)+Level;
  Out->WillSave = 2+CalculateModifier(Out->Wisdom)+Level;
}
//low ac, low hit points, low damage, low attack, low damage
void GenerateMagicUser(NPC_T * Out, int Level, MagicTypes_t MagicType){
  Out->Strength = LowAbilityScore();
  Out->Dexterity = MediumAbilityScore();
  Out->Constitution = MediumAbilityScore();
  CasterAbilityScores(VeryHighAbilityScore());
  Out->MagicType = MagicType;
  Out->SpecialFeaturesAndAbilities = GetMagicUserAbilities(Level, MagicType);
  GenerateSpells(Out);
  Out->ArmorClass  = 10+CalculateModifier(Out->Dexterity)+Level;
  Out->HitPoints = (6+CalculateModifier(Out->Constitution))*Level;
  int numSkills = rand()%4+2;
  int numexpert = Level/5*(Level>4);
  int nummastered = Level/10 * (Level>9);
  int numLegendary = Level/15 *(Level>14);
  SelectSkills(Out,DefaultSkillsList, numSkills, numexpert, nummastered,numLegendary);
  Out->ReflexSave = 2+CalculateModifier(Out->Dexterity)+Level;
  Out->FortitudeSave = 2+CalculateModifier(Out->Constitution)+Level;
  Out->WillSave = 4+CalculateModifier(Out->Wisdom)+Level;
}

//mid ac, low hit points, high damage, high attack,
void GenerateMagicUsingThief(NPC_T * Out, int Level,MagicTypes_t MagicType){
  Out->Strength = MediumAbilityScore();
  Out->Dexterity = VeryHighAbilityScore();
  Out->Constitution = MediumAbilityScore();
  CasterAbilityScores(HighAbilityScore());
  Out->MagicType = MagicType;
  Out->SpecialFeaturesAndAbilities = GetMagicUsingThiefAbilities(Level, OrganizedMelle, MagicType);
  GenerateSpells(Out);
  Out->ArmorClass  = 11+CalculateModifier(Out->Dexterity)+Level;
  Out->HitPoints = (7+CalculateModifier(Out->Constitution))*Level;
  int numSkills = rand()%4+2;
  int numexpert = Level/5*(Level>4);
  int nummastered = Level/10 * (Level>9);
  int numLegendary = Level/15 *(Level>14);
  SelectSkills(Out,DefaultSkillsList, numSkills, numexpert, nummastered,numLegendary);
  Out->ReflexSave = 4+CalculateModifier(Out->Dexterity)+Level;
  Out->FortitudeSave = 2+CalculateModifier(Out->Constitution)+Level;
  Out->WillSave = 2+CalculateModifier(Out->Wisdom)+Level;
}
//high ac, mid hit points, low damage, mid attack, support abilites
void GeneratePriest(NPC_T * Out, int Level){
  Out->Strength = MediumAbilityScore();
  Out->Dexterity = MediumAbilityScore();
  Out->Constitution = MediumAbilityScore();
  Out->Intelligence = MediumAbilityScore();
  Out->Wisdom= HighAbilityScore();
  Out->Charisma= HighAbilityScore();
  Out->MagicType =MagicNONE;
  Out->SpecialFeaturesAndAbilities = GetPriestAbilities(Level);
  GenerateSpells(Out);
  Out->ArmorClass  = 10+CalculateModifier(Out->Dexterity)+Level+2;
  Out->HitPoints = (8+CalculateModifier(Out->Constitution))*Level;
  int numSkills = rand()%4+2;
  int numexpert = Level/5*(Level>4);
  int nummastered = Level/10 * (Level>9);
  int numLegendary = Level/15 *(Level>14);
  SelectSkills(Out,DefaultSkillsList, numSkills, numexpert, nummastered,numLegendary);
  Out->ReflexSave = 2+CalculateModifier(Out->Dexterity)+Level;
  Out->FortitudeSave = 2+CalculateModifier(Out->Constitution)+Level;
  Out->WillSave = 4+CalculateModifier(Out->Wisdom)+Level;
}
//mid ac, low hit points, high damage, high attack, stealth.
void GenerateThief(NPC_T * Out, int Level){
  Out->Strength = MediumAbilityScore();
  Out->Dexterity = VeryHighAbilityScore();
  Out->Constitution = MediumAbilityScore();
  Out->Intelligence = MediumAbilityScore();
  Out->Wisdom= MediumAbilityScore();
  Out->Charisma= HighAbilityScore();
  Out->MagicType = MagicNONE;
  Out->ArmorClass  = 12+CalculateModifier(Out->Dexterity)+Level;
  Out->HitPoints = (8+CalculateModifier(Out->Constitution))*Level;
  int numSkills = rand()%4+2;
  int numexpert = Level/5*(Level>4);
  int nummastered = Level/10 * (Level>9);
  int numLegendary = Level/15 *(Level>14);
  Out->SpecialFeaturesAndAbilities = GetThiefAbilities(Level,OrganizedMelle);
  SelectSkills(Out,DefaultSkillsList, numSkills, numexpert, nummastered,numLegendary);
  Out->ReflexSave = 4+CalculateModifier(Out->Dexterity)+Level;
  Out->FortitudeSave = 2+CalculateModifier(Out->Constitution)+Level;
  Out->WillSave = 2+CalculateModifier(Out->Wisdom)+Level;
}
NPC_T * CreateNPC(ENPC_Type T,int Level,bool InnateCaster, MagicTypes_t MagicType, MartialTypes_t MartialType, NPC_Strength_t str){
  NPC_T *out = (NPC_T*)malloc(sizeof(NPC_T));
  memset(out,'\0',sizeof(NPC_T));
  out->Ancestry = RandomAncestry();
  out->Gender = GenerateGender();
  out->Name = GenerateName(out->Ancestry,out->Gender);
  out->Class = T;
  out->Level = Level;
  out->InnateCaster = InnateCaster;
  out->MagicType = MagicType;
  out->Npc_strength = str;
  out->Personality = GeneratePersonality();
  if(T == Laborer){GenerateLaborer(out, Level);}
  if(T == Merchant){GenerateMerchant(out, Level);}
  if(T == Noble){GenerateMerchant(out,Level);}
  if(T == Fighter){GenerateFighter(out,Level,MartialType);}
  if(T == Gish){GenerateGish(out, Level,MartialType,MagicType);}
  if(T == Magic_User){GenerateMagicUser(out,Level,MagicType);}
  if(T == Magic_using_Thief){GenerateMagicUsingThief(out,Level,MagicType);}
  if(T == Priest){GeneratePriest(out, Level);}
  if(T == Thief){GenerateThief(out, Level);}
  if(out->Class != Gish){
    WeaponCalculation(out, MartialType);
  }
  else{
    if(out->Dexterity>out->Strength){
      WeaponCalculation(out, OrganizedRanged);
    }
    else{
      WeaponCalculation(out, OrganizedMelle);
    }
  }
  if(out->Class != Gish && out->Class != Magic_User && out->Class != Magic_using_Thief){
    out->Cantrips = malloc(1);
    out->Cantrips[0] = NULL;
    out->FirstLevelSpells = malloc(1);
    out->FirstLevelSpells[0] = NULL;
    out->SecondLevelSpells = malloc(1);
    out->SecondLevelSpells[0] = NULL;
    out->ThirdLevelSpells = malloc(1);
    out->ThirdLevelSpells[0] = NULL;
    out->FourthLevelSpells = malloc(1);
    out->FourthLevelSpells[0] = NULL;
    out->FifthLevelSpells = malloc(1);
    out->FifthLevelSpells[0] = NULL;
    out->SixthLevelSpells = malloc(1);
    out->SixthLevelSpells[0] =NULL;
    out->SeventhLevelSpells = malloc(1);
    out->SeventhLevelSpells[0] = NULL;
    out->EightLevelSpells = malloc(1);
    out->EightLevelSpells[0] = NULL;
    out->NinthLevelSpells = malloc(1);
    out->NinthLevelSpells[0] = NULL;
    out->TenthLevelSpells = malloc(1);
    out->TenthLevelSpells[0] = NULL;
  }
  if(StrArrayLen(out->SpecialFeaturesAndAbilities)){
    out->SpecialFeaturesAndAbilities[StrArrayLen(out->SpecialFeaturesAndAbilities)-1] = NULL;
  }
  return out;
}
NPC_T * CreateNPC_From_Template(CharacterTemplate_t temp,int level, NPC_Strength_t str){
  return NULL;
}
void DestroyNPC(NPC_T* NPC){
  if(NPC->Class != Gish && NPC->Class != Magic_User && NPC->Class != Magic_using_Thief){
    free(NPC->Cantrips[0]);
    free(NPC->FirstLevelSpells[0]);
    free(NPC->SecondLevelSpells[0]);
    free(NPC->ThirdLevelSpells[0]);
    free(NPC->FourthLevelSpells[0]);
    free(NPC->FifthLevelSpells[0]);
    free(NPC->SixthLevelSpells[0]);
    free(NPC->SeventhLevelSpells[0]);
    free(NPC->EightLevelSpells[0]);
    free(NPC->NinthLevelSpells[0]);
    free(NPC->TenthLevelSpells[0]);
  }
  free((int *)NPC->Name);
  free(NPC->SpecialFeaturesAndAbilities);
  free(NPC->Cantrips);
  free(NPC->FirstLevelSpells);
  free(NPC->SecondLevelSpells);
  free(NPC->ThirdLevelSpells);
  free(NPC->FourthLevelSpells);
  free(NPC->FifthLevelSpells);
  free(NPC->SixthLevelSpells);
  free(NPC->SeventhLevelSpells);
  free(NPC->EightLevelSpells);
  free(NPC->NinthLevelSpells);
  free(NPC->TenthLevelSpells);
  free(NPC->Personality);
  free(NPC->SpellBook);
}
static const char * GenderLUT[] = {"Male","Female","Nonbinary"};
static const char * TypeLUT[] = {"Laborer","Merchant","Noble","Fighter","Magic User","Gish","Magic Using Thief","Priest","Thief"};
static const char * AncestryLut[] = {"Dwarf","Elf","Gnome","Goblin","Halfing","Human","Catfolk","Orc"};
static const  char * StrLUT[] = {"Elite","Normal","Weak"};
#define PrintSpellList(T) for(int i = 0; i<StrArrayLen((const char **)NPC->T); i++){fprintf(f,"%s, ",NPC->T[i]);}

#define PrintSpellSlots(T) if(NPC->InnateCaster){printf("[%d slots]: ",GetElement(InnateSpellSlotsByLevel(NPC->Level*(NPC->Class == Magic_User)+NPC->Level/3*(NPC->Class != Magic_User)), T));} else{fprintf(f,": ");}
char * PrintNpc(FILE * f,NPC_T * NPC){
  char * out = malloc(100);
  fprintf(f,"%s\n", (char *)NPC->Name);
  sprintf(out, "%s ",GenderLUT[NPC->Gender]);
  fprintf(f,"%s",out);
  sprintf(out,"%s ",TypeLUT[NPC->Class]);
  fprintf(f,"%s",out);
  sprintf(out,"%s ",AncestryLut[NPC->Ancestry]);
  fprintf(f,"%s",out);
  sprintf(out, "%s Strength\n",StrLUT[NPC->Npc_strength]);
  fprintf(f,"%s",out);
  sprintf(out,"Level: %d\n",NPC->Level);
  fprintf(f,"%s",out);
  sprintf(out,"Perception:+%d\n",NPC->Perception_Bonus);
  fprintf(f,"%s",out);
  sprintf(out,"Hit Points:%d\n",NPC->HitPoints);
  fprintf(f,"%s",out);
  sprintf(out,"AC:%d\n",NPC->ArmorClass);
  fprintf(f,"%s",out);
  sprintf(out,"Strength: %d | Constitution: %d | Dexterity: %d | Intelligence: %d | Wisdom: %d | Charisma %d\n",NPC->Strength, NPC->Constitution,NPC->Dexterity,
          NPC->Intelligence,NPC->Wisdom, NPC->Charisma);
  fprintf(f,"%s",out);
  sprintf(out,"Reflex:+%d | Fortitude:+%d | Will:+%d\n", NPC->ReflexSave, NPC->FortitudeSave, NPC->WillSave);
  fprintf(f,"%s",out);
  sprintf(out,"Skills: Arcana:+%d, Atheletics:+%d, Crafting:+%d, Deception:+%d, Diplomacy:+%d, Intimidation:+%d, Lore:+%d, Medicine:+%d, Nature:+%d, Occultism:+%d, Performance:+%d, Religion:+%d, Society:+%d, Stealth:+%d, Survival:+%d, Thievery:+%d\n",
          NPC->Arcana, NPC->Athletics,NPC->Crafting, NPC->Deception, NPC->Diplomacy, NPC->Intimidation, NPC->Lore, NPC->Medicine,NPC->Nature, NPC->Occultism, NPC->Performance, NPC->Religion, NPC->Society,NPC->Stealth, NPC->Survival,NPC->Thievery);
  fprintf(f,"%s",out);
  fprintf(f,"\nAbilities and Features: ");
  for(int i = 0; i<StrArrayLen((const char **)NPC->SpecialFeaturesAndAbilities); i++){
    if(NPC->SpecialFeaturesAndAbilities[i]>(const char *)0x600000000000 && (NPC->SpecialFeaturesAndAbilities[i])<(const char *)0xa00000000000){
      fprintf(f,"%s", NPC->SpecialFeaturesAndAbilities[i]);
      fprintf(f,"\n");
    }
  }
  fprintf(f,"Weapons: ");
  for(int i = 0; i<5; i++){
    if(NPC->weapons[i].Name){
      Weapon_T * t =&NPC->weapons[i];
      fprintf(f,"%s +%d %s+%d(%s)\n",t->Name, t->Bonus,t->DamageDie, t->DamageBonus, t->Text);
    }
  }
  if(NPC->Cantrips[0]){
    fprintf(f,"Cantrips: ");
    for(int i = 0; i<StrArrayLen((const char **)NPC->Cantrips); i++){
      fprintf(f,"%s, ",NPC->Cantrips[i]);
    }
  }
  if(NPC->FirstLevelSpells[0]){
    fprintf(f,"\nFirst Level Spells");
    PrintSpellSlots(1);
    PrintSpellList(FirstLevelSpells);
  }
  if(NPC->SecondLevelSpells[0]){
    fprintf(f,"\nSecond Level Spells");
    PrintSpellSlots(2);
    PrintSpellList(SecondLevelSpells);
  }
  if(NPC->ThirdLevelSpells[0]){
    fprintf(f,"\nThird Level Spells");
    PrintSpellSlots(3);
    PrintSpellList(ThirdLevelSpells);
  }
  if(NPC->FourthLevelSpells[0]){
    fprintf(f,"\nFourth Level Spells");
    PrintSpellSlots(4);
    PrintSpellList(FourthLevelSpells);
  }
  if(NPC->FifthLevelSpells[0]){
    fprintf(f,"\nFifth Level Spells");
    PrintSpellSlots(5);
    PrintSpellList(FifthLevelSpells);
  }
  if(NPC->SixthLevelSpells[0]){
    fprintf(f,"\nSixth Level Spells");
    PrintSpellSlots(6);
    PrintSpellList(SixthLevelSpells);
  }
  if(NPC->SeventhLevelSpells[0]){
    fprintf(f,"\nSeventh Level Spells");
    PrintSpellSlots(7);
    PrintSpellList(SeventhLevelSpells);
  }
  if(NPC->EightLevelSpells[0]){
    fprintf(f,"\n Eigth Level Spells");
    PrintSpellSlots(8);
    PrintSpellList(EightLevelSpells);
  }
  if(NPC->NinthLevelSpells[0]){
    fprintf(f,"\nNinth Level Spells");
    PrintSpellSlots(9);
    PrintSpellList(NinthLevelSpells);
  }
  if(NPC->TenthLevelSpells[0]){
    fprintf(f,"\nTenth Level Spells");
    PrintSpellSlots(10);
    PrintSpellList(TenthLevelSpells);
  }
  fprintf(f,"\nPersonality: ");
  for(int i = 0; i<StrArrayLen((const char ** )NPC->Personality); i++){
    if(isValid(NPC->Personality[i])){
      fprintf(f,"%s, ",NPC->Personality[i]);
    }
  }
  if(StrArrayLen((const char **)NPC->SpellBook)>0){
    fprintf(f,"\nSpellbook: ");
  }
  for(int i =0; i<StrArrayLen((const char **)NPC->SpellBook); i++){
    if(isValid(NPC->SpellBook[i])){
      fprintf(f,"%s, ",NPC->SpellBook[i]);
    }
  }
  free(out);
  return NULL;
}
