//
//  Utils.c
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#include "Utils.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
static unsigned long Seed = 0;
unsigned long RandomInt(void){
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
int RollDice(const char * die){
  int cur = 0;
  int len = (int)strlen(die);
  char nd[10];
  char  ds[10];
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
string StrArrayRandomElement(vector<string> input){
  return input[RandomInt()%input.size()];
}
bool IntArrayContains(vector<int> v, int num){
  for(int i = 0; i<v.size(); i++){
    if(v[i] == num){
      return true;
    }
  }
  return false;
}
vector<int> IntArrayChoose(vector<int> v, int num){
  vector<int> v1;
  vector<int> out;
  for(int i = 0; i<v.size(); i++){
    v1.push_back(i);
  }
  for(int i =0 ; i<num; i++){
    int r = RandomInt()%v1.size();
    out.push_back(v[v1[r]]);
    v1.erase(v1.begin()+r);
  }
  return out;
}
vector<string> StrArrayChoose(vector<string> v, int num){
  vector<int> v1;
  vector<string> out;
  for(int i = 0; i<v.size(); i++){
    v1.push_back(i);
  }
  for(int i =0 ; i<num; i++){
    int r = RandomInt()%v1.size();
    out.push_back(v[v1[r]]);
    v1.erase(v1.begin()+r);
  }
  return out;
}
vector<string> StrArraySelect(vector<string> v, int num){
  vector<string> out;
  for(int i =0 ; i<num; i++){
    int r = RandomInt()%v.size();
    out.push_back(v[r]);
  }
  return out;
}