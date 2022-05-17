#pragma once
#include"dirent.h"
DIR *pdir;
struct dirent *pdirstu;

void OpenDir(char filedir[]);
void LoadScv(int modeid);
void ProcessScv(int modeid,double area,int pH,int refe);
void SaveScv(int modeid, int st, int ed);