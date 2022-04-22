/*
*Electrochemical Test Data Processing
*Created by SDoHao on 2022/3/16
*This file is from https://github.com/SDoHao/ETDP.git
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
	config RuleList[1], *Rule;
	double area;
	double radius;
	int pH;

	ReadConfig(szrule, RuleList);
	Rule = &RuleList[0];

	radius = atof(GetValue(Rule, "Radius"));
	area = PI * radius * radius / 100;
	printf("\nArea is %f cm^2.\n", area);

	pH = atoi(GetValue(Rule, "pH"));

	OpenDir(GetValue(Rule, "Path"));
	LoadScv();
	ProcessScv(1,area, pH);
	SaveScv();

	system("pause");
	return 0;
}