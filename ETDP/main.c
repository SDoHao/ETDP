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
	double area;
	double radius;
	int pH;

	ReadConfig(szrule, RuleList);
	pRule = &RuleList[0];

	radius = atof(GetValue(pRule, "Radius"));
	area = PI * radius * radius / 100;
	printf("\nArea is %f cm^2.\n", area);

	pH = atoi(GetValue(pRule, "pH"));

	OpenDir(GetValue(pRule, "Path"));
	LoadScv();
	ProcessScv(1,area, pH);
	SaveScv();

	system("pause");
	return 0;
}