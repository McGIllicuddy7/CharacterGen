//
//  Utils.c
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#include "Utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
static u_int64_t Seed = 0;
void * MemCat(const void * begin, int bsz, const void *end,int esz){
  char * out = (char *)malloc(bsz+esz);
  memcpy(out,begin, bsz);
  memcpy(out+bsz, end, esz);
  return (void *)out;
}
char * StrAdd(const char * begin, const char *end){
  return (char *)MemCat(begin, (int)strlen(begin),end, (int)strlen(end));
}
int StrArrayLen(const char ** arr){
  int i = 0;
  if(!arr){
    return 0;
  }
  while((char)arr[i] != '\0'){
    i++;
  }
  return i;
}
char ** StrArrayNew(const char * Seed){
  if(!Seed){
    char ** out = malloc(1);
    out[0] = NULL;
    return out;
  }
  char ** out = malloc(16);
  out[0] = malloc(strlen(Seed));
  memcpy(out[0], Seed, strlen(Seed));
  out[1] = NULL;
  return out;
}
char ** StrArrayAdd(char ** arr, const char * add){
  int size = StrArrayLen((const char **)arr);
  char ** out = realloc(arr, (size+1));
  out[size] = (char *)add;
  out[size+1] = NULL;
  return (char **)out;
}
char ** StrArrayCombine(char ** arr, char ** toadd){
  char ** out = arr;
  for(int i = 0; i<StrArrayLen((const char **)toadd); i++){
    out = StrArrayAdd(out, toadd[i]);
  }
  return out;
}
char ** StrArraySelect(char ** arr, int num){
  char ** out = malloc(num*8+8);
  int len  = StrArrayLen((const char **)arr);
  for(int i = 0; i<num; i++){
    int l = RandomInt()%len;
    out[i] = arr[l];
  }
  out[num] = NULL;
  return out;
}
void StrArrayPrint(const char ** arr){
  if(!arr){
    return;
  }
  int i = 0;
  while(arr[i] != NULL){
    if(i != 0){
      printf(" ");
    }
    printf("%s\n", arr[i]);
    i++;
    if(arr[i] != NULL){
      printf(",");
    }
  }
}
void StrArrayFree(char ** arr){
  int i = 0;
  while(arr[i] != NULL){
    free(arr[i]);
    i++;
  }
  free(arr);
}
u_int64_t RandomInt(void){
  if(Seed == 0){
    Seed = time(0);
  }
  Seed ^= Seed >> 7;
  Seed ^= Seed << 9;
  Seed ^= Seed >> 13;
  return Seed;
}
int RandomIntInRange(int min, int max){
  return RandomInt()%(max-min)+min;
}
double RandomDouble(void){
  return ((double)RandomInt())/((double)0xFFFFFFFFFFFFFFFF);
}
double RandomDoubleInRange(double min, double max){
  return RandomDouble()*(max+min)+min;
}
const char * StrArrayRandomElement(const char ** arr){
  int rand = RandomIntInRange(0, StrArrayLen(arr));
  return arr[rand];
}
int RollDice(const char * die){
  int cur = 0;
  int len = (int)strlen(die);
  char * nd = malloc(10);
  char * ds = malloc(10);
  for(int i = 0; i<len; i++){
    if(die[i]== 'd'){
      cur = i;
      i = len;
    }
  }
  memcpy(nd, die, cur);
  memcpy(ds, die+cur+1, len-cur);
  int numdice = atoi(nd);
  int diesize = atoi(ds);
  int total = 0;
  for(int i = 0; i<numdice; i++){
    total += RandomInt()%diesize+1;
  }
  return total;
}
const char ** StrArrayChoose(const char ** arr, int numChoices){
  int len = StrArrayLen(arr);
  if(len<=numChoices){
    const char ** out = malloc(8*len);
    memcpy(out,arr, 8*len);
    return out;
  }
  const char ** out = malloc(8*numChoices+8);
  int * vals = malloc(4*numChoices);
  for(int i = 0; i<len; i++){
    vals[i] = i;
  }
  out[numChoices] = 0;
  for(int i = 0; i<numChoices; i++){
    int r = RandomInt()%(len-i);
    out[i] = arr[vals[r]];
    for(int j = r; j<len-i; j++){
      vals[j] = vals[j+1];
    }
    int * oldvals = vals;
    vals = malloc((len-i)*4);
    memcpy(vals,oldvals, (len-i-1)*4);
    free(oldvals);
  }
  free(vals);
  return out;
}
static const byte_t BytesbyIndex[8] = {1,2,4,8,16,32,64,128};
void SetByteElement(byte_t * target,uint8_t index, uint8_t value){
  if(index>7){
    return;
  }
  byte_t m = !(BytesbyIndex[index]&(*target));
  (*target) += m*BytesbyIndex[index];
  return;
}
uint8_t GetByteElement(uint8_t index, byte_t b){
  if(index>7){
    return 255;
  }
  return BytesbyIndex[index]&b;
}
void PrintByte(byte_t b){
  for(int i = 7; i>-1; i--){
    printf("%d",(BytesbyIndex[i]&b)>0);
  }
  printf("\n");
}
IntArray_t Iterator(int start, int end){
  IntArray_t out;
  if(end<=start){
    out.length = 0;
    out.vals = NULL;
    return out;
  }
  out.length = end-start;
  out.vals = malloc(4*out.length);
  for(int i = 0; i<end-start; i++){
    out.vals[i] = i+start;
  }
  return out;
}
IntArray_t NewIntArray(int length,const int * seed){
  IntArray_t out;
  if(!length){
    out.length = 0;
    out.vals = NULL;
  }
  out.length = length/4;
  out.vals = malloc(length);
  memcpy(out.vals,seed, length);
  return out;
}
void IntArrayAdd(IntArray_t * arr, int value){
  arr->length += 1;
  if(arr->vals == NULL){
    arr->vals = malloc(4);
    arr->vals[0] = value;
  }
  else{
    arr->vals = realloc(arr->vals, arr->length*4);
    arr->vals[arr->length-1] = value;

  }
}
int IntArrayGet(IntArray_t * arr, int index){
  if(index<arr->length){
    return arr->vals[index];
  }
  return -0xFFFFFFFF;
}
void IntArraySet(IntArray_t * arr, int index, int value){
  if(index<arr->length){
    arr->vals[index] = value;
  }
}
void IntArrayRemove(IntArray_t * arr, int index){
  if(index>=arr->length){
    return;
  }
  for(int i = index; i<arr->length-1; i++){
    arr->vals[i] =arr->vals[i+1];
  }
  arr->length -=1;
  arr->vals = realloc(arr->vals, arr->length*4);
}
void IntArrayFree(IntArray_t * arr){
  free(arr->vals);
}
void IntArrayPrint(IntArray_t * arr){
  if(arr->length<1){
    return;
  }
  printf("<%d", arr->vals[0]);
  for(int i = 1; i<arr->length; i++){
    printf(",%d",arr->vals[i]);
  }
  printf(">\n");
}
int IntArrayRandom(IntArray_t * arr){
  if(!arr){
    return 0xFFFFFFFF;
  }
  int r = RandomInt()%arr->length;
  return IntArrayGet(arr,r);
}
void IntArrayRemoveByValue(IntArray_t * arr, int value){
  IntArray_t Indices = NewIntArray(0,NULL);
  for(int i = 0; i<arr->length; i++){
    if(arr->vals[i] == value){
      IntArrayAdd(&Indices, i);
    }
  }
  for(int i = 0; i<Indices.length; i++){
    IntArrayRemove(arr, Indices.vals[i]);
  }
}
IntArray_t IntArrayChoose(IntArray_t * arr, int num){
  if(num == 0){
    return (IntArray_t){NULL,0};
  }
  IntArray_t a = NewIntArray(arr->length,arr->vals);
  if(a.length < 1){
    return (IntArray_t){NULL,0};
  }
  IntArray_t out;
  int r = RandomInt()%a.length;
  out.length =1;
  out.vals = malloc(4);
  out.vals[0] =a.vals[r];
  IntArrayRemove(&a, r);
  for(int i = 1; i<num; i++){
    if(a.length<1){
      IntArrayFree(&a);
      return out;
    }
    r = RandomInt()%a.length;
    IntArrayAdd(&out, a.vals[r]);
    IntArrayRemove(&a, r);
  }
  IntArrayFree(&a);
  return out;
}
unsigned char IntArrayContains(IntArray_t * arr, int value){
  for(int i =0 ; i<arr->length; i++){
    if(arr->vals[i] == value){
      return 1;
    }
  }
  return 0;
}
unsigned char isValid(void * ptr){
  const long maxmem = 281474976710656;
  if((long)ptr<0x050000000|| (long)ptr>maxmem || (long)ptr%2 != 0){
    return 0;
  }
  return 1;
}
