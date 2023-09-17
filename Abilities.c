//
//  Abiliites.c
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/9/23.
//

#include "Abilities.h"
#include "Utils.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
typedef struct{
  const char * TierOneText;
  const char * TierTwoText;
  const char * TierThreeText;
  const char * TierFourText;
  const char * TierFiveText;
} Ability_t;
const Ability_t SneakAttack = {
  "Sneak Attack: Deals an extra 1d6 precision damage to flat-footed creature",  "Sneak Attack: Deals an extra 2d6 precision damage to flat-footed creature",
  "Sneak Attack: Deals an extra 3d6 precision damage to flat-footed creature",  "Sneak Attack: Deals an extra 4d6 precision damage to flat-footed creature",
  "Sneak Attack: Deals an extra 5d6 precision damage to flat-footed creature",
};
const Ability_t QuickDraw = {"Quick Draw[1 action]: The character Interacts to draw a weapon, then Strikes with that weapon",NULL, NULL, NULL, NULL};
const Ability_t SurpiseAttack = {"Surprise Attack: On the first round of combat, creatures that haven’t acted yet are flat footed to the charcater.", NULL, NULL, NULL,NULL};
const Ability_t ScoundrelsFeint = {"Scoundrels Feint: When the character successfully Feints, their target is flat-footed against the character’s attacks until the end of the characters’s next turn. On a critical success, the target is flat-footed against all attacks until the end of the charcater's next turn", NULL, NULL, NULL, NULL};
const Ability_t QuickRummage = {"Quick Rummage: The character always has a few items close at hand. The character Interacts to draw a weapon or item that takes a single action to activate, and then Strikes with the weapon or Activates the Item.", NULL, NULL, NULL, NULL};
const Ability_t VersitilePerformace = {"Versitile Performance: The character can use Performance instead of Diplomacy to Make an Impression and instead of Intimidation to Demoralize. They can also use an acting Performance instead of Deception to Impersonate.", NULL, NULL, NULL, NULL};
const Ability_t DenyAdvantage = { "Deny Advantage: The character isn’t flat-footed to creatures of it's level or lower that are hidden, undetected, flanking, or using surprise attack.", NULL, NULL, NULL, NULL};
const Ability_t Mobility = { "Mobility: When the character Strides half their Speed or less, that movement does not trigger reactions"};
const Ability_t NimbleDodge = {"Nimble Dodge[Reaction]: Trigger The character is targeted with a melee or ranged attack by an attacker it can see; Effect The character gains a +2 circumstance bonus to AC against the triggering attack.", NULL, NULL, NULL, NULL};
const Ability_t BrutalBeating = {"Brutal Beating: The character's brutality shakes foes’ confidence. When the character deals damage on a critical hit, the target is frightened 1, and the character can knock the target up to 10 feet away (this is forced movement).", NULL, NULL, NULL, NULL};
const Ability_t SnaggingStrike = {"Snagging Strike[1 action]: Trigger The character has one hand free, and its target is within reach of that hand; Effect The character makes a melee Strike while keeping one hand free. If this Strike hits, the target is flat-footed until the start of the character's next turn or until it leaves the character's reach, whichever comes first.",NULL,NULL, NULL, NULL};
const Ability_t HealingHands = {"Healing Hands: When the character casts heal, they roll d10s instead of d8s.", NULL,NULL,NULL,NULL};
const Ability_t SteadySpellcasting = {"If another creature’s reaction would disrupt the character’s spellcasting action, the character attempts a DC 15 flat check. If they succeed, their action isn’t disrupted.",NULL,NULL,NULL,NULL};
const Ability_t Smite = {"Smite[2 Actions]: the character expends a prepared damaging spell and makes one melle or ranged attack, instead of its usual effect the spell's damage and any side effects of it on its target is added to the attack", NULL, NULL, NULL, NULL};
const Ability_t CollaborativeTheivery = {" Collaborative Thievery: The character gains a +1 circumstance bonus to Steal or Palm an Object while within 10 feet of an ally who has the pickpocket ability.",NULL,NULL,NULL,NULL};
const Ability_t Pickpocket = {"Pickpocket: The character can Steal or Palm an Object that’s closely guarded without taking the usual –5 penalty. They can Steal objects that would be extremely noticeable or time-consuming to remove (like worn shoes, armor, or actively wielded object.", NULL,NULL,NULL,NULL};
const Ability_t YoureNext = { "You're Next: [reaction] (emotion, fear, mental) Trigger character reduces a creature to 0 Hit Points; Effect The character attempts an Intimidation check with a +2 circumstance bonus to Demoralize a single creature it can see and that can see them.", NULL,NULL,NULL,NULL};
const Ability_t TrickAttack = {"Trick Attack[1 Action]: the character musters their guile to attempt a clever attack that catches their foe unprepared. The character chooses one of their weapons. The next attack with that weapon deals an extra 1d6 precision damage. In addition, character can Interact to draw the weapon (or to reload it if they choose the hand crossbow).",
  "Trick Attack[1 Action]: the character musters their guile to attempt a clever attack that catches their foe unprepared. The character chooses one of their weapons. The next attack with that weapon deals an extra 2d6 precision damage. In addition, character can Interact to draw the weapon (or to reload it if they choose the hand crossbow).",
  "Trick Attack[1 Action]: the character musters their guile to attempt a clever attack that catches their foe unprepared. The character chooses one of their weapons. The next attack with that weapon deals an extra 3d6 precision damage. In addition, character can Interact to draw the weapon (or to reload it if they choose the hand crossbow).",
  "Trick Attack[1 Action]: the character musters their guile to attempt a clever attack that catches their foe unprepared. The character chooses one of their weapons. The next attack with that weapon deals an extra 4d6 precision damage. In addition, character can Interact to draw the weapon (or to reload it if they choose the hand crossbow)."
  "Trick Attack[1 Action]: the character musters their guile to attempt a clever attack that catches their foe unprepared. The character chooses one of their weapons. The next attack with that weapon deals an extra 5d6 precision damage. In addition, character can Interact to draw the weapon (or to reload it if they choose the hand crossbow)."
};
const Ability_t HuntPrey = {"Hunt Prey[1 action] (concentrate) The character  designates a single creature they can see and hear, or one they’re Tracking, as their prey. The character gains a +2 circumstance bonus to Perception checks to Seek the prey and to Survival checks to Track the prey. The first time the character  hits the designated prey in a round, they deal an additional 1d8 precision damage. The character also ignores the penalty for making ranged attacks within their second range increment. These effects last until the character uses Hunt Prey again.",
  "Hunt Prey[1 action] (concentrate) The character  designates a single creature they can see and hear, or one they’re Tracking, as their prey. The character gains a +2 circumstance bonus to Perception checks to Seek the prey and to Survival checks to Track the prey. The first time the character  hits the designated prey in a round, they deal an additional 2d8 precision damage. The character also ignores the penalty for making ranged attacks within their second range increment. These effects last until the character uses Hunt Prey again.",
  "Hunt Prey[1 action] (concentrate) The character  designates a single creature they can see and hear, or one they’re Tracking, as their prey. The character gains a +2 circumstance bonus to Perception checks to Seek the prey and to Survival checks to Track the prey. The first time the character  hits the designated prey in a round, they deal an additional 3d8 precision damage. The character also ignores the penalty for making ranged attacks within their second range increment. These effects last until the character uses Hunt Prey again.",
  "Hunt Prey[1 action] (concentrate) The character  designates a single creature they can see and hear, or one they’re Tracking, as their prey. The character gains a +2 circumstance bonus to Perception checks to Seek the prey and to Survival checks to Track the prey. The first time the character  hits the designated prey in a round, they deal an additional 4d8 precision damage. The character also ignores the penalty for making ranged attacks within their second range increment. These effects last until the character uses Hunt Prey again.",
  "Hunt Prey[1 action] (concentrate) The character  designates a single creature they can see and hear, or one they’re Tracking, as their prey. The character gains a +2 circumstance bonus to Perception checks to Seek the prey and to Survival checks to Track the prey. The first time the character  hits the designated prey in a round, they deal an additional 5d8 precision damage. The character also ignores the penalty for making ranged attacks within their second range increment. These effects last until the character uses Hunt Prey again."
};
const Ability_t SuddenCharge = {"Sudden Charge[2 Actions]: The character Strides twice and makes a melee Strike.",NULL,NULL,NULL,NULL};
const Ability_t AirOfAuthority = {"Air of Authority: (aura, emotion, mental) 10 feet. Creatures in the aura who are the same or lower level than the character take a –2 status penalty to their Will DC against the character's attempts to Coerce or Demoralize them.",NULL,NULL,NULL,NULL};
const Ability_t Bravery = {"Bravery: When the character rolls a success on a Will save against a fear effect, they get a critical success instead. In addition, any time they gain the frightened condition, reduce its value by 1",NULL,NULL,NULL,NULL};
const Ability_t AttackOfOpportunity = {"Attack of Opportunity: The character can make opportunity Attacks as a reaction",NULL,NULL,NULL,NULL};
const Ability_t ShieldBlock = {"The Charcater can Shield Block as a reaction",NULL,NULL,NULL,NULL};
const Ability_t ShieldWarden = {"Shield Warden[Reaction]: When the character has their shield raised, they can Shield Block when an attack is made against an adjacent ally. If they do, the shield prevents that ally from taking damage instead of the character.",NULL,NULL,NULL,NULL};
const Ability_t CounterSpell = {"Counterspell [Reaction] Trigger A creature Casts a Spell the character has can currently cast; Effect The character  expends the spell to counter the triggering creature’s casting of that same spell. The character loses its spell slot as if it had cast the triggering spell. the character then attempts to counteract the triggering spell.",NULL,NULL,NULL,NULL};
const Ability_t AppraisingEye = {"Appraising Eye: The character can use Mercantile Lore to Recall Knowledge about items,including determining their value. They can also attempt to Identify Magic using Mercantile Lore and can do so without first knowing whether the item is magical.",NULL,NULL,NULL,NULL};
const Ability_t CallToAction = {"Call to Action[1 action] (auditory, concentrate, emotion, mental) The character gives a speech to inspire themself and all allies within 60 feet, granting them a +1 status bonus to attack and damage rolls until the start of the character’s next turn.",NULL,NULL,NULL,NULL};
const Ability_t CraftSnare = {"Craft Snare: the character can Craft snares and has the supplies to make up to two caltrop snares and up to two hampering snares.",NULL,NULL,NULL,NULL};
const Ability_t IntimidatingStrike = {"Intimidating Strike[2 actions] The character makes a melee Strike. If they hit and deal damage, the target is frightened 1, or frightened 2 on a critical hit.",NULL,NULL,NULL,NULL};
const Ability_t Evasion = {"Evasion: When the character rolls a success on a Reflex save, they get a critical success instead.",NULL,NULL,NULL,NULL};
const Ability_t GangUp = {"Gang Up: Any enemy is flat‐footed against the character’s melee attacks due to flanking as long as the enemy is within melee reach of both the character and one of the character’s allies.",NULL,NULL,NULL,NULL};
const Ability_t BrutalRally = {"Brutal Rally [Reaction]:(auditory, emotion, linguistic, mental) Trigger The character rolls a critical hit against a creature; Effect All allies that can see the character gain a +1 circumstance bonus to attack rolls until the start of the character’s next turn.",NULL,NULL,NULL,NULL};
const Ability_t FontOfKnowledge = {"Font of Knowledge: The character can attempt to Recall Knowledge on any general subject with a +10 modifier.",NULL,NULL,NULL,NULL};
const Ability_t SentrysAim = {"Sentry’s Aim[2 actions] (concentrate):The character aims carefully and fires. They make a ranged weapon Strike with a +1 circumstance bonus. The Strike ignores the concealed condition, lesser cover, and standard cover, and reduces greater cover to standard cover.",NULL,NULL,NULL,NULL};
const Ability_t ForestWalker = {"Forest Walker The character ignores the effects of difficult terrain from a forest environment. They can Sneak through underbrush without the need to attempt a Stealth check as long as the hunter moves no more than 5 feet at a time and is not within 10 feet of an enemy at any point during their movement.",NULL,NULL,NULL,NULL};
const Ability_t LieToMe = {"The character can use Deception to weave traps to trip up anyone trying to deceive them. If they can engage in conversation with someone trying to Lie to them, use their deception DC if it is higher than their Perception DC to determine whether they succeed. This doesn’t apply if they don’t have a back-and-forth dialogue, such as when someone attempts to Lie during a long speech. ",NULL,NULL,NULL,NULL};
const Ability_t CourtlyGrace = {"The character were raised among the nobility or have learned proper etiquette and bearing, allowing them to present themself as a noble and play games of influence and politics. They can use Society to Make an Impression on a noble, as well as with Impersonate to pretend to be a noble if they aren’t one. If they want to impersonate a specific noble, they still need to use Deception to Impersonate normally, and to Lie when necessary.",NULL,NULL,NULL,NULL};

const char * AbilityText(const Ability_t * Ab, const int level){
  if(!Ab){
    fprintf(stderr, "failed to get ability\n");
    exit(0);
    return NULL;
  }
  if(Ab->TierTwoText){
    if(level<5){
      return Ab->TierOneText;
    }
    if(level<11){
      return Ab->TierTwoText;
    }
    if(level<17){
      return Ab->TierThreeText;
    }
    if(level<20){
      return Ab->TierFourText;
    }
    else{
      return Ab->TierFiveText;
    }
  }
  return Ab->TierOneText;
}
const char ** AbilitiesText(const Ability_t * Default, const Ability_t ** list, const int level, int NumToChoose){
  char ** str;
  if(Default){
    str = StrArrayNew(AbilityText(Default, level));
  }
  else{
    str = (char **){NULL};
  }
  IntArray_t iter = Iterator(0,StrArrayLen((const char **)list));
  for(int i = 0; i<NumToChoose; i++){
    int r = RandomInt()%iter.length;
    str = StrArrayAdd(str, AbilityText(list[iter.vals[r]], level));
    //rintf("%s\n",str[i]);
    IntArrayRemove(&iter, r);
  }
 // IntArrayFree(&iter);
  return (const char **)str;
}
const char ** GetLaborerAbilities(int Level){
  const Ability_t * LaborerAbilities[] = {&QuickDraw, &QuickRummage, &Bravery, &AirOfAuthority, &BrutalBeating, &GangUp,&SnaggingStrike,&AppraisingEye,&IntimidatingStrike,NULL};
  return AbilitiesText(NULL, LaborerAbilities, Level, 1);
}
const char ** GetMerchantAbilities(int Level){
  const Ability_t * Default = &AppraisingEye;
  const Ability_t * MerchantAbilites[] = {&AirOfAuthority, &FontOfKnowledge,&VersitilePerformace,&Bravery,&CallToAction,NULL};
  return AbilitiesText(Default, MerchantAbilites, Level, 1);
}
const char ** GetFighterAbilities(int Level,MartialTypes_t MartialType){
  const Ability_t * Default;
  const Ability_t ** FighterAbilities;
  if(MartialType == OrganizedMelle){
    Default = NULL;
    const Ability_t * OrgMelleAbilities[] = {&SuddenCharge, &SnaggingStrike, &AttackOfOpportunity, &ShieldWarden,&GangUp,&TrickAttack,NULL};
    FighterAbilities = OrgMelleAbilities;
  }
  else if(MartialType == DisorganizedRanged){
    Default = NULL;
    const Ability_t * DisorganizedRangedAbilites[] = {&SurpiseAttack, &HuntPrey, &Evasion,&SneakAttack,&TrickAttack,&CraftSnare, NULL};
    FighterAbilities = DisorganizedRangedAbilites;
  }
  else if(MartialType == OrganizedRanged){
    Default = &SentrysAim;
    const Ability_t * DisorganizedRangedAbilites[] = {&Bravery,&SurpiseAttack, &Evasion,&SneakAttack,&TrickAttack, NULL};
    FighterAbilities = DisorganizedRangedAbilites;
  }
  else{
    Default = NULL;
    const Ability_t *DisorganizedMelleAbilitiers[] = {&QuickDraw, &QuickRummage, &Bravery, &AirOfAuthority, &BrutalBeating, &GangUp,&SnaggingStrike,&AppraisingEye,&IntimidatingStrike,NULL};
    FighterAbilities = DisorganizedMelleAbilitiers;
  }
  return AbilitiesText(Default, FighterAbilities,Level, 2);
}
const char ** GetGishAbilities(int Level, MagicTypes_t MagicType, MartialTypes_t MartialType){
  const Ability_t ** MartialAbilities;
  if(MartialType == OrganizedMelle){
    const Ability_t * OrgMelleAbilities[] = {&SuddenCharge, &SnaggingStrike, &AttackOfOpportunity, &ShieldWarden,&GangUp,&TrickAttack,
      &ScoundrelsFeint, &CourtlyGrace, &LieToMe,NULL};
    MartialAbilities = OrgMelleAbilities;
  }
  else if(MartialType == DisorganizedRanged){
    const Ability_t * DisorganizedRangedAbilites[] = {&SurpiseAttack, &HuntPrey, &Evasion,&SneakAttack,&TrickAttack,&CraftSnare, NULL};
    MartialAbilities = DisorganizedRangedAbilites;
  }
  else if(MartialType == OrganizedRanged){
    const Ability_t * DisorganizedRangedAbilites[] = {&SentrysAim,&Bravery,&SurpiseAttack, &Evasion,&SneakAttack,&TrickAttack, NULL};
    MartialAbilities = DisorganizedRangedAbilites;
  }
  else{
    const Ability_t *DisorganizedMelleAbilities[] = {&QuickDraw, &QuickRummage, &Bravery, &AirOfAuthority, &BrutalBeating, &GangUp,&SnaggingStrike,&AppraisingEye,&IntimidatingStrike,NULL};
    MartialAbilities = DisorganizedMelleAbilities;
  }
  const Ability_t ** MagicAbilities;
  if(MagicType == Arcane || MagicType == Occult){
    const Ability_t *ArcaneAbilites[] = { &SteadySpellcasting,&Smite,&CounterSpell,NULL};
    MagicAbilities = ArcaneAbilites;
  }
  else if(MagicType == Divine){
    const Ability_t *DivineAbilites[] = {&SteadySpellcasting,&Smite,&CounterSpell,&HealingHands,NULL};
    MagicAbilities = DivineAbilites;
  }
  else{
    const Ability_t *PrimalAbilites[] = {&SteadySpellcasting,&Smite,&CounterSpell,&HealingHands,&ForestWalker,&HuntPrey,NULL};
    MagicAbilities = PrimalAbilites;
  }
  char ** out =  (char **)AbilitiesText(NULL,MartialAbilities, Level, 1);
  const char ** maot = AbilitiesText(NULL, MagicAbilities, Level,1);
  for(int i = 0; i<StrArrayLen(maot); i++){
    StrArrayAdd(out, maot[i]);
  }
  return (const char **)out;
}
const char ** GetThiefAbilities(int Level,MartialTypes_t MartialType){
  const Ability_t * Default = &SneakAttack;
  const Ability_t ** Abilities;
  if(MartialType == OrganizedMelle){
    const Ability_t * OrgMelleAbilities[] ={ &QuickDraw ,&SurpiseAttack, &ScoundrelsFeint,&CourtlyGrace,&CollaborativeTheivery, &Pickpocket, &DenyAdvantage ,&Mobility, &NimbleDodge,&TrickAttack,&GangUp};
    Abilities = OrgMelleAbilities;
  }
  if(MartialType == DisorganizedMelle){
    const Ability_t * DisOrgMelleAbilities[] ={ &QuickDraw ,&SurpiseAttack, &ScoundrelsFeint,&CollaborativeTheivery, &Pickpocket, &DenyAdvantage ,&Mobility, &NimbleDodge,&TrickAttack,&SentrysAim,&CraftSnare, &HuntPrey,&ForestWalker,&GangUp};
    Abilities = DisOrgMelleAbilities;
  }
  if(MartialType == OrganizedRanged){
    const Ability_t * OrgRangedAbilities[] ={ &QuickDraw ,&SurpiseAttack, &ScoundrelsFeint,&CourtlyGrace,&CollaborativeTheivery, &Pickpocket, &DenyAdvantage ,&Mobility, &NimbleDodge,&TrickAttack,&SentrysAim,&GangUp};
    Abilities = OrgRangedAbilities;
  }
  else{
    const Ability_t * DisOrgRangedAbilities[] ={ &QuickDraw ,&SurpiseAttack, &ScoundrelsFeint,&CollaborativeTheivery, &Pickpocket, &DenyAdvantage ,&Mobility, &NimbleDodge,&TrickAttack,&SentrysAim,&CraftSnare, &HuntPrey,&ForestWalker,&SentrysAim,&GangUp};
    Abilities = DisOrgRangedAbilities;
  }
  return AbilitiesText(Default, Abilities, Level,2);
}
const char ** GetNobleAbilities(int Level){
  const Ability_t * Default = &CourtlyGrace;
  const Ability_t * Abilities[] = {&CallToAction,&LieToMe, &AirOfAuthority, &Bravery,&Bravery,&TrickAttack};
  return AbilitiesText(Default, Abilities, Level,2);
}
const char ** GetMagicUserAbilities(int Level, MagicTypes_t MagicType){
  const Ability_t *Default = &FontOfKnowledge;
  const Ability_t ** MagicAbilities;
  if(MagicType == Arcane || MagicType == Occult){
    const Ability_t *ArcaneAbilites[] = { &SteadySpellcasting,&Smite,&CounterSpell};
    MagicAbilities = ArcaneAbilites;
  }
  else if(MagicType == Divine){
    const Ability_t *DivineAbilites[] = {&SteadySpellcasting,&Smite,&CounterSpell,&HealingHands};
    MagicAbilities = DivineAbilites;
  }
  else{
    const Ability_t *PrimalAbilites[] = {&SteadySpellcasting,&Smite,&CounterSpell,&HealingHands,&ForestWalker,&HuntPrey};
    MagicAbilities = PrimalAbilites;
  }
  return AbilitiesText(Default, MagicAbilities, Level,2);
}
const char ** GetMagicUsingThiefAbilities(int Level,MartialTypes_t MartialType, MagicTypes_t MagicType){
  const Ability_t * Default = &SneakAttack;
  const Ability_t ** Abilities;
  if(MartialType == OrganizedMelle){
    const Ability_t * OrgMelleAbilities[] ={ &QuickDraw ,&SurpiseAttack, &ScoundrelsFeint,&CourtlyGrace,&CollaborativeTheivery, &Pickpocket, &DenyAdvantage ,&Mobility, &NimbleDodge,&TrickAttack,&GangUp};
    Abilities = OrgMelleAbilities;
  }
  if(MartialType == DisorganizedMelle){
    const Ability_t * OrgMelleAbilities[] ={ &QuickDraw ,&SurpiseAttack, &ScoundrelsFeint,&CollaborativeTheivery, &Pickpocket, &DenyAdvantage ,&Mobility, &NimbleDodge,&TrickAttack,&SentrysAim,&CraftSnare, &HuntPrey,&ForestWalker,&GangUp};
    Abilities = OrgMelleAbilities;
  }
  if(MartialType == OrganizedRanged){
    const Ability_t * OrgMelleAbilities[] ={ &QuickDraw ,&SurpiseAttack, &ScoundrelsFeint,&CourtlyGrace,&CollaborativeTheivery, &Pickpocket, &DenyAdvantage ,&Mobility, &NimbleDodge,&TrickAttack,&SentrysAim,&GangUp};
    Abilities = OrgMelleAbilities;
  }
  else{
    const Ability_t * OrgMelleAbilities[] ={ &QuickDraw ,&SurpiseAttack, &ScoundrelsFeint,&CollaborativeTheivery, &Pickpocket, &DenyAdvantage ,&Mobility, &NimbleDodge,&TrickAttack,&SentrysAim,&CraftSnare, &HuntPrey,&ForestWalker,&SentrysAim,&GangUp};
    Abilities = OrgMelleAbilities;
  }
  const Ability_t ** MagicAbilities;
  if(MagicType == Arcane || MagicType == Occult){
    const Ability_t *ArcaneAbilites[] = { &SteadySpellcasting,&Smite,&CounterSpell};
    MagicAbilities = ArcaneAbilites;
  }
  else if(MagicType == Divine){
    const Ability_t *DivineAbilites[] = {&SteadySpellcasting,&Smite,&CounterSpell,&HealingHands};
    MagicAbilities = DivineAbilites;
  }
  else{
    const Ability_t *PrimalAbilites[] = {&SteadySpellcasting,&Smite,&CounterSpell,&HealingHands,&ForestWalker,&HuntPrey};
    MagicAbilities = PrimalAbilites;
  }
  char ** out =  (char **)AbilitiesText(Default,Abilities, Level, 1);
  const char ** maot = AbilitiesText(NULL, MagicAbilities, Level,1);
  for(int i = 0; i<StrArrayLen(maot); i++){
    StrArrayAdd(out, maot[i]);
  }
  return (const char **)out;
}
const char ** GetPriestAbilities(int Level){
  const Ability_t * Abilities[] = {&CallToAction,&LieToMe, &AirOfAuthority, &Bravery,&Bravery,&TrickAttack};
  return AbilitiesText(NULL, Abilities, Level,1);
}
