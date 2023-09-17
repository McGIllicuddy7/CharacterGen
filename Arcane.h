//
//  Arcane.h
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#ifndef Arcane_h
#define Arcane_h
#pragma once
static const char * Arcane_Cantrips[] = {"Arcane Slash", "Ancient Dust", "Bullhorn", "Chill Touch", "Dancing Lights", "Dancing Lights", "Daze", "Detect Magic",
"Electric Arc", "Gale Blast", "Ghost Sound", "Gouging Claw", "Infectious Enthusiasm", "Invoke True Name", "Light", "Mage Hand", "Message", "Muscial Accompaniment",
"Phase Bolt","Prestidigitation","Produce Flame","Protect Companion", "Puff of Poison","Ray of Frost", "Read Aura","Scatter Scree", "Shield","Sigil","Spout","Tanglefoot",
"Telekinetic Projectile", "Time Sense", "Torturous Trauma", "Warp Step",0};

static const char * Arcane_1st_Level[] = {"Acidic Burst","Admonishing Ray", "Agitate", "Airburst", "Alarm","Animate Dead", "Animate Rope", "Ant Haul", "Anticpate Peril",
"Aqueous Burst", "Befuddle","Breadcrumbs","Briny Bolt","Burning Hands","Charm", "Chilling Spray", "Color Spray", "Command", "Create Water", "Deja Vu", "Draw Ire",
"Echoing Weapon", "Elysian Whimsy", "Endure", "Exchange Image", "Fashionist", "Flashy Disappearance", "Fleet Step", "Flense", "Floating Disk", "Friendfetch", "Goblin Pox",
"Gravitational Pull", "Grease", "Grim Tendrils", "Gritty Wheeze", "Gust of Wind","Helpful Steps", "Horizon Thunder Sphere", "Hydraulic Push", "Illusory Disguise",
"Illusory Object", "Illusory Item", "Invisible Item", "Item Facade", "Jump", "Kinetic Ram", "Lock", "Longstrider", "Mage Armor", "Magic Aura", "Magic Missle", "Magic Weapon",
"Mending", "Message Rune", "Mud Pit", "Necromancers Generosity", "Negate Aroma", "Noxious Vapors", "Nudge the Odds", "Overselling Flourish", "Penumbral Shroud",
"Personal Rain Cloud", "Pest Form", "Pet Cache", "Pocket Library", "Pumelling Rubble", "Quick Sort", "Ray of Enfeeblement","Restyle", "Shadenfreude", "Scorching Blast",
"Seashell of Stolen Sound", "Share Lore", "Scattering Gem", "Shocking Grasp", "Shockwave","Sleep", "Summon Animal", "Summon Construct", "Synchronize", "Synchronize Steps",
"Temporary Tool", "Tether", "Thicket of Knives", "Thoughful Gift", "True Strike", "Unseen Servant", "Ventriloquism",0};

static const char * Arcane_2nd_Level[] = {"Acid Arrow", "Animated Assualt", "Ash Cloud", "Befitting Attire", "Blood Duplicate", "Blood Vendetta", "Blur", "bone Spray",
"Boneshaker", "Charitable Urge", "Comprehend Language", "Confetti Cloud", "Continual Flame", "Create Food", "Dancing Shield", "Darkness","Darkvision", "Deafness",
"Dismantle", "Dispell Magic", "Elemental Zone", "Empathic Link", "Empty Pack", "Endure Elements","Enlarge","Expeditious Excavation","Extract Poison","False Life",
"Fear the Sun", "Feast of Ashes", "Final Sacrifice", "Flame Wisp", "Flaming Sphere", "Gentle Repose", "Glitterdust", "Heat Metal", "HIdeous Laughter","Humanoid Form",
"Horrifying Blood Loss","Ignite Fireworks", "Illusory CReature", "Illusory Shroud", "IMpeccable Flow", "Instant Armor", "Instant Parade", "Invisiblity", "Iron Gut", "Knock",
"Lock Item", "Loose Time's Arrow", "Lucky Number", "Magic Mouth", "Magnetic Attraction", "Magnetic Repulsion", "Mind Games", "Mirror Image", "Misdirection", "Obscuring Mist",
"Penumbral Disguise", "Persistent Servant", "Phatasmal Treasure", "Phantom Crowd", "Radiant Field", "Rapid Adaption", "Resist Energy", "Rime Slick","Scorching Ray",
"Sea surge", "See Invisibilty", "Shadow Zombie", "Shrink", "Slough Skin", "Spectral Hand", "Spider Climb", "Spys  Mark", "Sudden Bolt", "Summon Elemental", "Summoners Precaution",
"Summoners Visage", "Swallow Light", "Telekntic Maneuver", "Timely Tutor", "Touch of Idiocy", "Umbral Extraction","Umbral Mindtheft", "Vicious Jealousy","Vomit Swarm",
"Warriors Regret", "Water Breathing", "Water Walk","Web",0 };

static const char * Arcane_3rd_Level[] = {"Agonizing Despair", "Aqueous Orb", "Bind Undead", "Blazing Dive", "Blindess", "Bottomless Stomach", "Bracing Tendrals",
"Casters Imposition", "Clairaudience", "Cozy Cabin", "Crashing Wave", "Cup of Dust", "Curse of Lost Time", "Days Weight", "Distracting Chatter", "Dividing Trench",
"Dream Message", "Earthbind", "Elemental Absorption", "Enemtal Annihilation Wave", "Enthrall", "Excise Lexicon", "Familiars Face", "Feet to Fins","Fireball",
"Firework Blast","Gasping Marsh", "Ghostly Weapon", "Glyph of Warding", "Gravity Well", "Haste", "Hypnotic Pattern", "Impending Doom", "Invisibilty Sphere", "Lashing Rope",
"Levitate", "Lightning Bolt", "Locate", "Magical Fetters", "Magnetic Acceleration", "Meld into Stone", "Mind of Menace", "Mind Reading", "Nondetection",
"Nothing up my Sleeve", "Oneiric Mire", "Ooze Form", "Organsight", "Paralyze","Percussive Impact","Perseis's Precautions", "Phantom Prison","Pillar of Water", "Pyrotechnics",
"Rally Point", "Roaring Applause", "Rouse Skeletons", "Safe Passage", "Sea of Thought", "Secret Page", "Shadow Projectile", "Shift Blame", "Shifting Sand","Slow","Sparkleskin",
"Stinking Clowd", "Temporal Twin", "Time Jump", "Time Pocket", "Transcibe Conflict", "Unseasonable Squall", "Vampiric Touch", "Wall of Radiance", "Wall of Shadow",
"Wall of Virtue", "Wall of Water", "Wall of Wind", "Warding Aggresion", "Web of Eyes", 0};

static const char * Arcane_4th_Level[] = {"Aerial Form", "Aromatic Lure", "Bestial Curse", "Blink", "Call the Blood", "Chromatic Armor", "Chromatic Ray", "Clairvoyance",
"Clownish Curse", "Compel True Name", "Confusion", "Coral Eruption", "Counless Eyes", "Creation", "Daydreamers Curse", "Detect Creator", "Detect Scrying", "Dimension Door",
"Dimensional Anchor", "Discern Lies", "Draw the Lightning", "Dull Ambition", "Enervation", "Enhance Senses", "False Nature", "Favorable Review", "Fire Shield",
"Fly", "Forgotten Lines", "Gaseous Form","Globe of Invulnerablity", "Hallucinatory Terrain", "Ice Storm", "invisibility Curtain", "Magic Mailbox", "Mirrors Misfortune",
"Morass of Ages", "Necrotic Radiation", "Nighmare", "Ocular Overload", "Outcast's Curse", "Phantasmal Killer", "Private Sanctum", "Ravenous Portal",
"Rebounding Barrier", "Reflective Scales", "Replicate", "Resilient Sphere", "Rope Trick", "Sages Curse", "Sanguine Mist", "Seal Fate", "Shape Stone","Soft Landing",
"Solid Fog", "Spell Immunity", "Steal Voice", "Stoneskin", "Suggestion", "Swarming Wasp Stings", "Telepathy", "Umbral Graft", "Vampiric Maiden", "Variable Gravity", "Veil",
"Vision of Beauty", "Wall of Fire", "Weapon Storm", "Winning Streak", 0};

static const char * Arcane_5th_Level[] = {"Acid Storm", "Bandits Doom", "Banishment", "Belittling Boast", "Black Tentacles", "Blazing Fissure", "Blinding Foam", "Blink Charge", "Blister",
"Blood Feast", "Chromatic Wall", "Cloak of Colors", "Cloudkill", "Cone of Cold", "Control Water", "Crushing Despair", "Desperate Repair", "Drop Dead", "Elemental Form", "Etheric Shards"
, "False Vision", "Flammable Fumes", "Flowing Strike", "Forceful Hand", "Geyser", "Glimmer of Charm", "Grisly Growths", "Hallucination", "Illusory Scene", "Impaling Strike",
"Incendiary Fog", "Infectious Comedy", "Invoke Spirits", "Lashuntas Life Bubble", "Mantle of the Frozen Heart", "Mantle of the Magma Heart", "Mariner's Curse", "Mind Probe",
"Mirror Malfactors", "Passwall","Pillars of Sand","Prying Eye", "Quicken Time", "Return Beacon", "Rewinding Step", "Ritual Obstruction", "Scouring Pulse", "Secret Chest",
"Sending", "Shadow Siphon", "Shadow Walk","Stagnate Time", "Subconscious Suggestion", "Summon Dragon", "Telekninetic Haul", "Telepathic Bond", "Temporary Glyph","Tongues"
,"Transmute Rock and Mud", "Wall of Ice", "Wall of Stone", "Wyvern Sting",0};

static const char * Arcane_6th_Level[] = {"Aura of the Unremarkable", "Awaken Entropy", "Baleful Polymorph", "Bound in Death", "Cast into Time", "Catch your Name", "Chain Lightning",
"Chromatic Image", "Collective Transposition", "Daemon Form", "Demon Form", "Devil Form", "Disintegrate", "Dominate", "Dragon Form", "Elemental Confluence", "Feeblemind",
"Flame Vortex", "Flesh to Stone", "Halcyon Infusion", "Mislead", "Necrotize", "Phatasmal Calamity", "Poltergeists Fury", "Purple Worm Sting", "Ravenous Darkness",
"Repulsion", "Scrying", "Spellwrack", "Teleport", "Temporal Ward", "True Seeing","Unexpected Transposition", "Vampiric Exsanguination", "Virbant Patter", "Wall of Force",
"Word of Revision", "Zero Gravity",0};

static const char * Arcane_7th_Level[] = {"Blightburn Blast", "Contingency", "Control Sand", "Corrosive Body","Dimensional Lock","Duplicate Foe","Eclipse Burst","Energy Aegis",
"Entrancing Eyes","Fiery Body","Force Cage","Frigid Flurry","Inexhaustible Cynicism", "Long Sting","Magnificent Mansion","Mask of Terror","Momentary Recovery","Plane Shift",
"Power Word Blind","Prismatic Armor","Prismatic Spray","Project Image","Return to Essence", "Reverse Gravity","Shadow Raid","Spell Turning","Telekinetic Bombardment",
"Tempest of Shades","Time Beacon","True Target", "Warp Mind", 0 };

static const char * Arcane_8th_Level[] = {"All is One, One is All", "Antimagic Field", "Boil Blood", "Burning Blossoms", "Deluge", "Disappearance", "Discern Location", "Dream Council",
"Earthquake", "Falling Sky", "Horrid Wilting", "Maze", "Mind Blank", "Monstrosity Form", "Polar Ray", "Power Word Stun", "Prismatic Wall", "Prying Survey", "Scintillating Pattern",
"Summon Archmage", "Summon Irii", "Uncontroolable Dance", "Undermine Reality", "Unrelenting Observation", 0};

static const char * Arcane_9th_Level[] = {"Astral Labrynth", "Bilocation", "Disjunction", "Divinity Leech","Foresight","Implosion", "Linnorm Sting", "Massacre", "Meteor Swarm",
"Power word Kill", "Prismatic Shield", "Proliferating Eyes","Resplendent Mansion", "Shapechange", "Summon Ancient Fleshforged", "Summon Draconic Legion", "Telepathic Demand",
"Unspeakable Shadow", "Upheaval","Weird",0};

static const char * Arcane_10th_Level[] = {"Cataclysm", "Fated Confrontation", "Gate", "Indestructibility","Nullify", "Remake","Shadow Army","Time Stop","Wish",0};

#endif /* Arcane_h */
