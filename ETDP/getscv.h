#pragma once
#include"dirent.h"
DIR *pdir;
struct dirent *pdirstu;

void OpenDir(char filedir[]);
void LoadScv();
void ProcessScv(int mode,double area,int pH);
void SaveScv();