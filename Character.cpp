//
//  Character.c
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#include "Character.hpp"
#include "Names.hpp"
#include "Utils.hpp"
#include "Abilities.hpp"
#include "Arcane.hpp"
#include "Divine.hpp"
#include "Primal.hpp"
#include "Occult.hpp"
#include "Spellcasting.hpp"
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
int calculate_ac_and_per_bonus(int Level){
  int numexpert = Level/5*(Level>4);
  int nummastered = Level/10 * (Level>9);
  int numLegendary = Level/15 *(Level>14);
  return 2*(numexpert>0+nummastered>0+numLegendary>0+1);
}
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
      bool fin = out->weapons[i].Finnese;
      bool ran = out->weapons[i].Ranged;
      out->weapons[i].Bonus = calculate_ac_and_per_bonus(out->Level)+CalculateModifier(out->Strength)*(!fin && !ran)+CalculateModifier(out->Dexterity)*(fin ||ran);
      out->weapons[i].DamageBonus = CalculateModifier(out->Strength)*(!ran);
  }
}
static string RandFirstName(vector<string> BaseArray, EGender Gender){
  int s = RandomInt()%100;
  if(s<25){ return (Gender == Female ? StrArrayRandomElement(HumanFemmeFirstNames) :StrArrayRandomElement(HumanMascFirstNames));}
  if(s<50){return (Gender == Female ? StrArrayRandomElement(GiffFemmeFirstnames) :StrArrayRandomElement(GiffMascFirstNames));}
  if(s<75){return (Gender == Female ? StrArrayRandomElement(TieflingFemmeFirstNames) :StrArrayRandomElement(TieflingMascFirstNames));}
  return StrArrayRandomElement(BaseArray);
}
static string RandLastName(vector<string> BaseArray){
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
string GenerateName(EAncestries Ancestry, EGender Gender){
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
  vector<string> FnameArray = TieflingFemmeFirstNames;
  if(a == Catfolk){FnameArray = ( g == Female ? HalflingFemmeFirstNames : HalflingMascFirstNames);}
  if(a == Dwarf){FnameArray = ( g == Female ? DwarfFemmeFirstNames : DwarfMascFirstNames);}
  if(a == Elf){FnameArray =( g == Female ? ElfFemmeFirstNames : ElfMascFirstNames);}
  if(a == Goblin){FnameArray =( g == Female ? GoblinFemmeFirstNames : GoblinMascFirstNames);}
  if(a == Gnome){FnameArray = GnomeFirstNames;}
  if(a == Halfling){FnameArray = ( g == Female ? HalflingFemmeFirstNames : HalflingMascFirstNames);}
  if(a == Human){FnameArray = ( g == Female ? HumanFemmeFirstNames : HumanMascFirstNames);}
  if(a == Orc){FnameArray = ( g == Female ? OrcFemmeFirstNames : OrcMascFirstNames);}
  string FirstName = RandFirstName(FnameArray, g);
  EAncestries b = Ancestry;
  vector<string> LnameArray = TieflingLastNames;
  if(RandomInt()%100<80){b = RandomAncestry();}
  if(b == Catfolk){LnameArray = HalflingLastNames;}
  if(b == Dwarf){LnameArray = DwarfLastNames;}
  if(b == Elf){LnameArray = ElfLastNames;}
  if(b == Goblin){LnameArray = GoblinLastNames;}
  if(b == Gnome){LnameArray = GnomeLastNames;}
  if(b == Halfling){LnameArray = HalflingLastNames;}
  if(b == Human){LnameArray = humanLastNames;}
  if(b == Orc){LnameArray = OrcLastNames;}
  string LastName = RandLastName(LnameArray);
  return FirstName+" "+LastName;
}
static vector<string> Sanity = {"Sanity: Very Stable", "Sanity: Normal","Sanity: Normal", "Sanity: Normal","Sanity: Normal", "Sanity :Normal", "Sanity: Neurotic", "Sanity: Unstable", "Sanity: Insane", "Sanity: Maniacal"};
static vector<string> GeneralTendencies = {"Optimist", "Pessimist", "Hedonist", "Altruist", "Kindly","Careless", "Carpcious", "Mischievious",
  "Sober", "Moody","Inquisitive","Trusting", "Suspicious","Cautious", "Precise", "Exacting", "Perceptive", "Opinionated", "Contrarian", "Violent", "Sudious",
  "Foul","Cruel","Callous", "Prankster","Servile","Obseqious","Fanatical", "Obsessive", "Maleovolent", "Loquacious"};
static vector<string> AveragePersonality = {"Modest","Agoist", "Arrogant", "Friendly","Aloof","Hostile", "Well Spoken", "Diplomatic", "Abrasitve"};
static vector<string> ExtrovertedPersonality = {"Forceful","Overbearing", "Friendly","Blustering","Antagonistic", "Rude", "Rash","Diplomatic"};
static vector<string> IntrovertedPersonality = {"Retiring","Taciturn","Friendly","Aloof","Hostile","Rude","Courteous","Solidary","Secretive"};
static vector<string> Disposition = {"Cheerful","Morose", "Compassionate","Sensitive","Unfeeling","Insensitive","Humble","Proud","Haughty","Even Tempered","Easy Going","Harsh"};
static vector<string> PersonalityNature = {"Soft Hearted","Forgiving","Hard Hearted","Unforgiving","Jealous","Vengeful"};
static vector<string> PersonalityMaterialism = {"Materialism: Aestethic","Materialism: Intellectualist", "Materialism: Average", "Materialism: Covetous","Materialism: Greedy",
  "Materialism: Avaricious"};
static vector<string> PersonalityHonesty = {"Scrupulous", "Very Honorable","Truthful","Average Honesty","Average Honesty","Average Honesty","Liar","Decietful"};
static vector<string> PersonalityBravery = {"Normal Bravery", "Normal Bravery", "Normal Bravery","Foolhardy","Brave","Fearless","Cowardly","Craven"};
static vector<string> PersonalityEnergy = {"Slothful","Lazy","Normal Energy","Normal Energy","Normal Energy","Energetic","Energetic","Driven"};
static vector<string> PersonalityThrift = {"Miserly","Mean Thrift","Thrifty","Average Thrift","Average Thrift","Spendthrift","Spendthrift","Wastrel"};
static vector<string> PersonalityMorals = {"Aesthetic Morals","Virtous Morals","Normal Morals","Normal Morals","Lusty Morals","Lusty Morals","Lustful Morals","Immoral",
  "Amoral","Perverted","Depraved","Sadistic"};
static vector<string> PersonalityPiety = {"Saintly","Zealot","Pious","Reverent","Average Piety","Average Piety","Average Piety","Average Piety","Average Piety","Impious",
  "Irreverent","Iconoclastic","Irreligious"};
static vector<string> Interests = {"Interested in: Religion","Interested in: Legends","Interested in: History","Interested in: Nature",
  "Interested in: Horticulture","Interested in: Animal Husbandry","Interested in: Exotic Animals","Interested in: Hunting","Interested in: Fishing","Interested in: Handicrafts",
  "Interested in: Athletics","Interested in: Politics","Interested in: Wine and Spirits","Interested in: Foods and Preperation","Interested in: Gambling",
  "Interested in: Drugs","Knife and Dagger Collector","Sword Collector","Weapon Collector","Weapon Collector","Shield and Weapon Collector","Armor Collector","Book and Scroll Collector","Mineral and Gem Collector","Ornament and Jewelry Collector","Coin and Token Collector",
  "Trophy and Skin Collector","Porcelain,China, and Crystal Collector","Art Collector","Interested in: Community Service","Interested in: Altruism","Interested in: Not Much"
};
vector<string> GeneratePersonality(void){
  vector<string> Personality;
  int r;
  r = RollDice("1d10");
  if(r>8){ r = RollDice("1d10");}
  Personality.push_back(Sanity[r-1]);
  Personality.push_back(StrArrayRandomElement(GeneralTendencies));
  r = RollDice("1d8");
  if(r<6){
    Personality.push_back(StrArrayRandomElement(AveragePersonality));
  }
  else if(r<8){
    Personality.push_back(StrArrayRandomElement(ExtrovertedPersonality));
  }
  else{
    Personality.push_back(StrArrayRandomElement(IntrovertedPersonality));
  }
  Personality.push_back(StrArrayRandomElement(Disposition));
  Personality.push_back(StrArrayRandomElement(PersonalityNature));
  Personality.push_back(StrArrayRandomElement(PersonalityMaterialism));
  Personality.push_back(StrArrayRandomElement(PersonalityHonesty));
  Personality.push_back(StrArrayRandomElement(PersonalityBravery));
  Personality.push_back(StrArrayRandomElement(PersonalityEnergy));
  Personality.push_back(StrArrayRandomElement(PersonalityThrift));
  r = RollDice("1d12");
  if(r>9){
    r = RollDice("1d12");
  }
  Personality.push_back(PersonalityMorals[r-1]);
  Personality.push_back(StrArrayRandomElement(PersonalityPiety));
  Personality.push_back(StrArrayRandomElement(Interests));
  return Personality;
}
typedef enum{
  Arcana, Athletics,Acrobatics,Crafting, Deception, Diplomacy, Intimidation, Lore, Medicine, Nature, Occultism, Performance, Religion, Society, Survival,Stealth, Thievery,
}Skills;
typedef enum{
  Strength, Constitution, Dexterity, Intelligence, Wisdom, Charisma,
} AbilityScores;

int CalculateSkillMod(int index, NPC_T * out,AbilityScores Score, vector<int> TrainedSkills, vector<int> ExpertSkills, vector<int> MasteredSkills,vector<int> LegendarySkills){
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
  base += (2+out->Level)*IntArrayContains(TrainedSkills, index)+(4+out->Level)*IntArrayContains(ExpertSkills, index)+(6+out->Level)*IntArrayContains(MasteredSkills, index)+(8+out->Level)*IntArrayContains(LegendarySkills,index);
  return base;
}
#define SetUpSkills(NPC, T, Ability) NPC->T = CalculateSkillMod(T,out, Ability, TrainedSkills,ExpertSkills, MasteredSkills, LegendarySkills)
void CalculateSkills(NPC_T * out, vector<int> TrainedSkills, vector<int> ExpertSkills,vector<int> MasteredSkills,vector<int> LegendarySkills){
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
  out->Perception_Bonus = 0+CalculateModifier(out->Wisdom);
}
void SelectSkills(NPC_T * out,vector<int> Skills, int numskills,int numexpert,int nummastered, int numlegendary){
  vector<int> TrainedSkills = IntArrayChoose(Skills, numskills);
  vector<int> ExpertSkills = IntArrayChoose(TrainedSkills, numexpert);
  vector<int> MasteredSkills = IntArrayChoose(ExpertSkills,nummastered);
  vector<int> LegendarySkills = IntArrayChoose(MasteredSkills, numlegendary);
  CalculateSkills(out, TrainedSkills, ExpertSkills, MasteredSkills,LegendarySkills);
  //IntArrayFree(&TrainedSkills);
  //IntArrayFree(&ExpertSkills);
  //IntArrayFree(&MasteredSkills);
  //IntArrayFree(&LegendarySkills);
}
#define CasterAbilityScores(Highest)\
if(MagicType == Arcane){Out->Intelligence = Highest; Out->Wisdom = MediumAbilityScore(); Out->Charisma = MediumAbilityScore();}\
if(MagicType == Divine || MagicType == Primal){Out->Intelligence =MediumAbilityScore(); Out->Wisdom = Highest;Out->Charisma = MediumAbilityScore();}\
if(MagicType == Occult){Out->Intelligence =MediumAbilityScore();  Out->Wisdom = MediumAbilityScore(); Out->Charisma = Highest;}
static vector<string> CantripsLut[] = { Arcane_Cantrips, Divine_Cantrips,Primal_Cantrips, Occult_Cantrips};
static vector<string> Spells1stLevelLut[] = { Arcane_1st_Level, Divine_1st_Level, Primal_1st_Level, Occult_1st_Level};
static vector<string> Spells2ndLevelLut[] = { Arcane_2nd_Level, Divine_2nd_Level, Primal_2nd_Level, Occult_2nd_Level};
static vector<string> Spells3rdLevelLut[] = { Arcane_3rd_Level, Divine_3rd_Level, Primal_3rd_Level, Occult_3rd_Level};
static vector<string> Spells4thLevelLut[] = { Arcane_4th_Level, Divine_4th_Level, Primal_4th_Level, Occult_4th_Level};
static vector<string> Spells5thLevelLut[] = { Arcane_5th_Level, Divine_5th_Level, Primal_5th_Level, Occult_5th_Level};
static vector<string> Spells6thLevelLut[] = { Arcane_6th_Level, Divine_6th_Level, Primal_6th_Level, Occult_6th_Level};
static vector<string> Spells7thLevelLut[] = { Arcane_7th_Level, Divine_7th_Level, Primal_7th_Level, Occult_7th_Level};
static vector<string> Spells8thLevelLut[] = { Arcane_8th_Level, Divine_8th_Level, Primal_8th_Level, Occult_8th_Level};
static vector<string> Spells9thLevelLut[] = { Arcane_9th_Level, Divine_9th_Level, Primal_9th_Level, Occult_9th_Level};
static vector<string> Spells10thLevelLut[]= { Arcane_10th_Level, Divine_10th_Level, Primal_10th_Level, Occult_10th_Level};
#define SpellbookAdd(T) for(int i = 0; i< T.size(); i++){\
  out->SpellBook.push_back(T[i]);\
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
    out->Cantrips = StrArrayChoose(CantripsLut[out->MagicType], Slots.Cantrips);
    out->FirstLevelSpells = StrArrayChoose(Spells1stLevelLut[out->MagicType], Slots.Level1);
    out->SecondLevelSpells =StrArrayChoose(Spells2ndLevelLut[out->MagicType], Slots.Level2);
    out->ThirdLevelSpells = StrArrayChoose(Spells3rdLevelLut[out->MagicType], Slots.Level3);
    out->FourthLevelSpells = StrArrayChoose(Spells4thLevelLut[out->MagicType], Slots.Level4);
    out->FifthLevelSpells = StrArrayChoose(Spells5thLevelLut[out->MagicType], Slots.Level5);
    out->SixthLevelSpells = StrArrayChoose(Spells6thLevelLut[out->MagicType], Slots.Level6);
    out->SeventhLevelSpells = StrArrayChoose(Spells7thLevelLut[out->MagicType], Slots.Level7);
    out->EightLevelSpells = StrArrayChoose(Spells8thLevelLut[out->MagicType], Slots.Level8);
    out->NinthLevelSpells = StrArrayChoose(Spells9thLevelLut[out->MagicType], Slots.Level9);
    out->TenthLevelSpells = StrArrayChoose(Spells10thLevelLut[out->MagicType], Slots.Level10);
  }
  else{
    SpellSlots_t Book = PreparedSpellBookByLevel(level);
    SpellSlots_t Slots = PreparedSpellSlotsByLevel(level);
    vector<string> CantripBuff = StrArrayChoose(CantripsLut[out->MagicType], Book.Cantrips);
    vector<string> FirstLevelBuff = StrArrayChoose(Spells1stLevelLut[out->MagicType], Book.Level1);
    vector<string> SecondLevelBuff = StrArrayChoose(Spells2ndLevelLut[out->MagicType], Book.Level2);
    vector<string> ThirdLevelBuff = StrArrayChoose(Spells3rdLevelLut[out->MagicType], Book.Level3);
    vector<string> FourthLevelBuff = StrArrayChoose(Spells4thLevelLut[out->MagicType], Book.Level4);
    vector<string> FifthLevelBuff = StrArrayChoose(Spells5thLevelLut[out->MagicType], Book.Level5);
    vector<string> SixthLevelBuff = StrArrayChoose(Spells6thLevelLut[out->MagicType], Book.Level6);
    vector<string> SeventhLevelBuff = StrArrayChoose(Spells7thLevelLut[out->MagicType], Book.Level7);
    vector<string> EightLevelBuff = StrArrayChoose(Spells8thLevelLut[out->MagicType], Book.Level8);
    vector<string> NinthLevelBuff = StrArrayChoose(Spells9thLevelLut[out->MagicType], Book.Level9);
    vector<string> TenthLevelBuff = StrArrayChoose(Spells10thLevelLut[out->MagicType], Book.Level10);
    out->Cantrips = StrArrayChoose(CantripsLut[out->MagicType], Slots.Cantrips);
    out->FirstLevelSpells = StrArraySelect(Spells1stLevelLut[out->MagicType], Slots.Level1);
    out->SecondLevelSpells = StrArraySelect(Spells2ndLevelLut[out->MagicType], Slots.Level2);
    out->ThirdLevelSpells = StrArraySelect(Spells3rdLevelLut[out->MagicType], Slots.Level3);
    out->FourthLevelSpells = StrArraySelect(Spells4thLevelLut[out->MagicType], Slots.Level4);
    out->FifthLevelSpells = StrArraySelect(Spells5thLevelLut[out->MagicType], Slots.Level5);
    out->SixthLevelSpells = StrArraySelect(Spells6thLevelLut[out->MagicType], Slots.Level6);
    out->SeventhLevelSpells = StrArraySelect(Spells7thLevelLut[out->MagicType], Slots.Level7);
    out->EightLevelSpells = StrArraySelect(Spells8thLevelLut[out->MagicType], Slots.Level8);
    out->NinthLevelSpells = StrArraySelect(Spells9thLevelLut[out->MagicType], Slots.Level9);
    out->TenthLevelSpells = StrArraySelect(Spells10thLevelLut[out->MagicType], Slots.Level10);
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
    //free(CantripBuff);
    //free(FirstLevelBuff);
    //free(SecondLevelBuff);
    //free(ThirdLevelBuff);
    //free(FourthLevelBuff);
    //free(FifthLevelBuff);
    //free(SixthLevelBuff);
    //free(SeventhLevelBuff);
    //free(EightLevelBuff);
    //free(NinthLevelBuff);
    //free(TenthLevelBuff);
  }
}
vector<int> SkillsList = { Acrobatics,Arcana,Athletics,Crafting,Deception,Diplomacy,Intimidation,Lore,Medicine,Nature,Occultism,Performance,Religion,
  Society,Stealth,Survival,Thievery};
vector<int> DefaultSkillsList = SkillsList;
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
  Out->ArmorClass  = 10+CalculateModifier(Out->Dexterity)+Level+calculate_ac_and_per_bonus(Level);
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
  Out->ArmorClass  = 10+CalculateModifier(Out->Dexterity)+Level+calculate_ac_and_per_bonus(Level);
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
  Out->ArmorClass  = 10+CalculateModifier(Out->Dexterity)+Level+calculate_ac_and_per_bonus(Level);
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
    Out->ArmorClass  = 18+CalculateModifier(Out->Dexterity)+Level+calculate_ac_and_per_bonus(Level);
    Out->HitPoints = (10+CalculateModifier(Out->Constitution))*Level;
  }
  if(MartialType == DisorganizedMelle){
    Out->Strength = VeryHighAbilityScore();
    Out->Dexterity =  HighAbilityScore();
    Out->Constitution = HighAbilityScore();
    Out->Intelligence = MediumAbilityScore();
    Out->Wisdom= MediumAbilityScore();
    Out->Charisma= MediumAbilityScore();
    Out->ArmorClass  = 15+CalculateModifier(Out->Dexterity)+Level+calculate_ac_and_per_bonus(Level);
    Out->HitPoints = (12+CalculateModifier(Out->Constitution))*Level;
  }
  if(MartialType == OrganizedRanged){
    Out->Strength = MediumAbilityScore();
    Out->Dexterity = VeryHighAbilityScore();
    Out->Constitution = MediumAbilityScore();
    Out->Intelligence = MediumAbilityScore();
    Out->Wisdom= HighAbilityScore();
    Out->Charisma= HighAbilityScore();
    Out->ArmorClass  = 13+CalculateModifier(Out->Dexterity)+Level+calculate_ac_and_per_bonus(Level);
    Out->HitPoints = (8+CalculateModifier(Out->Constitution))*Level;
  }
  if(MartialType == DisorganizedRanged){
    Out->Strength = HighAbilityScore();
    Out->Dexterity =  VeryHighAbilityScore();
    Out->Constitution = HighAbilityScore();
    Out->Intelligence = MediumAbilityScore();
    Out->Wisdom= MediumAbilityScore();
    Out->Charisma= MediumAbilityScore();
    Out->ArmorClass  = 12+CalculateModifier(Out->Dexterity)+Level+calculate_ac_and_per_bonus(Level);
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
  Out->ArmorClass  = 15+CalculateModifier(Out->Dexterity)+Level+calculate_ac_and_per_bonus(Level);
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
  Out->ArmorClass  = 10+CalculateModifier(Out->Dexterity)+Level+calculate_ac_and_per_bonus(Level);;
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
  Out->ArmorClass  = 11+CalculateModifier(Out->Dexterity)+Level+calculate_ac_and_per_bonus(Level);
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
  Out->ArmorClass  = 10+CalculateModifier(Out->Dexterity)+Level+calculate_ac_and_per_bonus(Level);
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
  Out->ArmorClass  = 12+CalculateModifier(Out->Dexterity)+Level+calculate_ac_and_per_bonus(Level);
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
  NPC_T *out = new NPC_T;
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
  out->Perception_Bonus+= calculate_ac_and_per_bonus(Level);
  return out;
}
NPC_T * CreateNPC_From_Template(CharacterTemplate_t temp,int level, NPC_Strength_t str){
  return NULL;
}
void DestroyNPC(NPC_T* NPC){return;};
static const char * GenderLUT[] = {"Male","Female","Nonbinary"};
static const char * TypeLUT[] = {"Laborer","Merchant","Noble","Fighter","Magic User","Gish","Magic Using Thief","Priest","Thief"};
static const char * AncestryLut[] = {"Dwarf","Elf","Gnome","Goblin","Halfing","Human","Catfolk","Orc"};
static const  char * StrLUT[] = {"Elite","Normal","Weak"};
#define PrintSpellList(T) for(int i = 0; i<NPC->T.size(); i++){fprintf(f,"%s, ",NPC->T[i].c_str());}

#define PrintSpellSlots(T) if(NPC->InnateCaster){printf("[%d slots]: ",GetElement(InnateSpellSlotsByLevel(NPC->Level*(NPC->Class == Magic_User)+NPC->Level/3*(NPC->Class != Magic_User)), T));} else{fprintf(f,": ");}
void PrintNpc(FILE * f,NPC_T * NPC){
  fprintf(f,"%s\n",NPC->Name.c_str());
  fprintf(f, "%s ",GenderLUT[NPC->Gender]);
  fprintf(f,"%s ",TypeLUT[NPC->Class]);
  fprintf(f,"%s ",AncestryLut[NPC->Ancestry]);
  fprintf(f, "%s Strength\n",StrLUT[NPC->Npc_strength]);
  fprintf(f,"Level: %d\n",NPC->Level);
  fprintf(f,"Perception:+%d\n",NPC->Perception_Bonus);
  fprintf(f,"Hit Points:%d\n",NPC->HitPoints);
  fprintf(f,"AC:%d\n",NPC->ArmorClass);
  fprintf(f,"Strength: %d | Constitution: %d | Dexterity: %d | Intelligence: %d | Wisdom: %d | Charisma %d\n",NPC->Strength, NPC->Constitution,NPC->Dexterity,
          NPC->Intelligence,NPC->Wisdom, NPC->Charisma);
  fprintf(f,"Reflex:+%d | Fortitude:+%d | Will:+%d\n", NPC->ReflexSave, NPC->FortitudeSave, NPC->WillSave);
  fprintf(f,"Skills: Arcana:+%d, Atheletics:+%d, Crafting:+%d, Deception:+%d, Diplomacy:+%d, Intimidation:+%d, Lore:+%d, Medicine:+%d, Nature:+%d, Occultism:+%d, Performance:+%d, Religion:+%d, Society:+%d, Stealth:+%d, Survival:+%d, Thievery:+%d\n",
          NPC->Arcana, NPC->Athletics,NPC->Crafting, NPC->Deception, NPC->Diplomacy, NPC->Intimidation, NPC->Lore, NPC->Medicine,NPC->Nature, NPC->Occultism, NPC->Performance, NPC->Religion, NPC->Society,NPC->Stealth, NPC->Survival,NPC->Thievery);
  fprintf(f,"\nAbilities and Features: ");
    for(int i = 0; i<NPC->SpecialFeaturesAndAbilities.size(); i++){
      fprintf(f,"%s", NPC->SpecialFeaturesAndAbilities[i].c_str());
      fprintf(f,"\n");
    }
  fprintf(f,"Weapons: ");
  for(int i = 0; i<5; i++){
    if(NPC->weapons[i].Name.size()>0){
      Weapon_T * t =&NPC->weapons[i];
      fprintf(f,"%s +%d %s+%d(%s)\n",t->Name.c_str(), t->Bonus,t->DamageDie.c_str(), t->DamageBonus, t->Text.c_str());
    }
  }
  if(NPC->Cantrips.size()>0){    
    fprintf(f,"Cantrips: ");
    for(int i = 0; i<NPC->Cantrips.size(); i++){
      fprintf(f,"%s, ",NPC->Cantrips[i].c_str());
    }
  }
  if(NPC->FirstLevelSpells.size()>0){
    fprintf(f,"\nFirst Level Spells");
    PrintSpellSlots(1);
    PrintSpellList(FirstLevelSpells);
  }
  if(NPC->SecondLevelSpells.size()){
    fprintf(f,"\nSecond Level Spells");
    PrintSpellSlots(2);
    PrintSpellList(SecondLevelSpells);
  }
  if(NPC->ThirdLevelSpells.size()){
    fprintf(f,"\nThird Level Spells");
    PrintSpellSlots(3);
    PrintSpellList(ThirdLevelSpells);
  }
  if(NPC->FourthLevelSpells.size()){
    fprintf(f,"\nFourth Level Spells");
    PrintSpellSlots(4);
    PrintSpellList(FourthLevelSpells);
  }
  if(NPC->FifthLevelSpells.size()){
    fprintf(f,"\nFifth Level Spells");
    PrintSpellSlots(5);
    PrintSpellList(FifthLevelSpells);
  }
  if(NPC->SixthLevelSpells.size()){
    fprintf(f,"\nSixth Level Spells");
    PrintSpellSlots(6);
    PrintSpellList(SixthLevelSpells);
  }
  if(NPC->SeventhLevelSpells.size()){
    fprintf(f,"\nSeventh Level Spells");
    PrintSpellSlots(7);
    PrintSpellList(SeventhLevelSpells);
  }
  if(NPC->EightLevelSpells.size()){
    fprintf(f,"\n Eigth Level Spells");
    PrintSpellSlots(8);
    PrintSpellList(EightLevelSpells);
  }
  if(NPC->NinthLevelSpells.size()){
    fprintf(f,"\nNinth Level Spells");
    PrintSpellSlots(9);
    PrintSpellList(NinthLevelSpells);
  }
  if(NPC->TenthLevelSpells.size()){
    fprintf(f,"\nTenth Level Spells");
    PrintSpellSlots(10);
    PrintSpellList(TenthLevelSpells);
  }
  fprintf(f,"\nPersonality: ");
  for(int i =0 ; i<NPC->Personality.size(); i++){
    fprintf(f,"%s, ", NPC->Personality[i].c_str());
  }
  if(NPC->SpellBook.size()>0){
    fprintf(f,"\nSpellbook: ");
  }
  for(int i =0; NPC->SpellBook.size(); i++){
    fprintf(f,"%s,", NPC->SpellBook[i].c_str());
  }
  fprintf(f,"\n");
}
