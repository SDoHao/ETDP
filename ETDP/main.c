/*
*Electrochemical Test Data Processing
*Created by SDoHao on 2022/4/22
*This file is from https://github.com/SDoHao/ETDP
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include"getscv.h"
#include"ReadConfig.h"
#define PI acos(-1.0)

char szrule[] = { "Rule.ini" };

int main()
{
	config RuleList[1], *pRule;
	char * pszMode;
	char * pszRefeElecRode;
	double area;
	double radius;
	int pH;
	int RefeId;//RefeId 1 SCE 2 AgCl--Ag/AgCl
	int ModeId;//ModeId 1 LSV 2 CV
	int Start;
	int End;
	ReadConfig(szrule, RuleList);
	pRule = &RuleList[0];

	pszRefeElecRode = GetValue(pRule, "RefeElecRode");
	pszMode = GetValue(pRule, "Mode");
	if (strcmp(pszMode, "LSV") == 0)
		ModeId = 1;
	else if (strcmp(pszMode, "CV") == 0)
		ModeId = 2;
	printf("\nMode ID is %d\n", ModeId);
	if (strcmp(pszRefeElecRode, "SCE") == 0)
		RefeId = 1;
	else if (strcmp(pszRefeElecRode, "AgCl") == 0|| strcmp(pszRefeElecRode, "Ag/AgCl") == 0 )
		RefeId =2;
	printf("Reference electrode ID is %d\n", RefeId);

	radius = atof(GetValue(pRule, "Radius"));
	area = PI * radius * radius / 100;
	printf("\nArea is %f cm^2.\n", area);

	pH = atoi(GetValue(pRule, "pH"));

	Start = atoi(GetValue(pRule, "Start"));
	//printf("start = %d\n", atoi(GetValue(pRule, "Start")));
	End = atoi(GetValue(pRule, "End"));

	OpenDir(GetValue(pRule, "Path"));
	LoadScv(ModeId);
	ProcessScv(1,area, pH, RefeId);
	SaveScv(ModeId,Start,End);

	system("pause");
	return 0;
}