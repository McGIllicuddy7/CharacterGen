//
//  Utils.h
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#ifndef Utils_h
#define Utils_h
#pragma once
#include <stdio.h>
#include <stdlib.h>
typedef unsigned char byte_t;
void * MemCat(const void * begin, int bsz, const void *end,int esz);
char * StrAdd(const char * begin, const char *end);
int StrArrayLen(const char ** arr);
char ** StrArrayNew(const char * Seed);
char ** StrArrayAdd(char ** arr, const char * add);
void StrArrayPrint(const char ** arr);
void StrArrayFree(char ** arr);
const char * StrArrayRandomElement(const char ** arr);
u_int64_t  RandomInt(void);
int RandomIntInRange(int min, int max);
double RandomDouble(void);
int RollDice(const char * die);
const char ** StrArrayChoose(const char ** arr, int numChoices);
char ** StrArrayCombine(char ** arr, char ** toadd);
char ** StrArraySelect(char ** arr, int num);
//byte operators
void SetByteElement(byte_t* target,uint8_t index, uint8_t value);
uint8_t GetByteElement(uint8_t index,byte_t b);
void PrintByte(byte_t b);
//int array stuff
typedef struct{
  int * vals;
  int length;
} IntArray_t;
IntArray_t Iterator(int start, int end);
IntArray_t NewIntArray(int length, const int *seed);
void IntArrayAdd(IntArray_t * arr, int value);
int IntArrayGet(IntArray_t * arr, int index);
void IntArraySet(IntArray_t * arr, int index, int value);
void IntArrayRemove(IntArray_t * arr, int index);
void IntArrayFree(IntArray_t * arr);
void IntArrayPrint(IntArray_t * arr);
int IntArrayRandom(IntArray_t * arr);
IntArray_t IntArrayChoose(IntArray_t * arr, int num);
void IntArrayRemoveByValue(IntArray_t * arr, int value);
unsigned char IntArrayContains(IntArray_t * arr, int value);
unsigned char isValid(void * ptr);
#endif /* Utils_h */

