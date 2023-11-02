#pragma once
#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"


void maxmin(int arr[],int &x,int &y);
int mu(int x, int y);
void takefile(string &mush, string &acle, string &merl);
int lm(string event);
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void Mu1(string fi,int &HP);
void Mu2(string fi,int &HP);
void Mu3(string fi,int &HP);
void Mu4(string fi,int &HP);
int fibo(int n);
int lenint(int n);
bool chNT(int n);
void Asclepius(string f_i,bool &re, bool &mai, bool &pho);
int sumP(int n);
void countDamge15(int &level,float lvl0,int stage,int &HP,bool lan);
void Melin(string f_i,int &HP);
float baseDamge(int stage);
void running(int turn,int stage,int & HP,int maxHP, int & level, int & remedy, int & maidenkiss, int & phoenixdown,bool &tiny,
             int &tet,int &culvl,int &tef,bool &frog,bool &asc,bool lan,bool &mer,string filein,bool isking,int &rescue);

#endif // __KNIGHT_H__
