//
//  Ancestries.h
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#ifndef Ancestries_h
#define Ancestries_h

#include <stdio.h>
typedef enum{
    Dwarf,Elf,Gnome,Goblin, Halfling, Human, Catfolk, Orc,
} EAncestries;
const static int GlobalDwarfPopulationPercent = 12;
const static int GlobalElfPopulationPercent = 8;
const static int GlobalGnomePopulationPercent = 10;
const static int GlobalGoblinPopulationPercent = 15;
const static int GlobalHalflingPopulationPercent = 15;
const static int GlobalHumanPopulationPercent = 25;
const static int GlobalCatfolkPopulationPercent = 5;
const static int GlobalOrcPopulationPercent = 10;
//temporay values
static int DwarfPopulationPercent = 12;
static int ElfPopulationPercent = 8;
static int GnomePopulationPercent = 10;
static int GoblinPopulationPercent = 15;
static int HalflingPopulationPercent = 15;
static int HumanPopulationPercent = 25;
static int CatfolkPopulationPercent =5;
static int OrcPopulationPercent = 10;
EAncestries RandomAncestry(void);
void RandomizeAncestries(void);
#endif /* Ancestries_h */
