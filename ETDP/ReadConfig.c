#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ReadConfig.h"

configItem CreatConfigItem()
{
	configItem pcfgItem = (configItem)malloc(sizeof(struct configItem));
	if (pcfgItem == NULL)
		printf("Initialization Failed	[101]\n");
	else
		pcfgItem->nextItem = NULL;
	return pcfgItem;
}

void InsertConfigItem(config * pCfg,configItem pCfgItem)
{
	configItem ptcfgitem = pCfg->item;
	if (ptcfgitem == NULL)
	{
		pCfg->item = pCfgItem;
		return;
	}
	else
		while (ptcfgitem->nextItem != NULL)
			ptcfgitem = ptcfgitem->nextItem;
	ptcfgitem->nextItem = pCfgItem;
}

void ReadConfig(char * path,config CfgList[])
{
	char pcharLine[100];
	config * pCfg;
	configItem pCfgItem;
	int i,nUserNum = 0;
	FILE * pfile = fopen(path, "r");
	
	while (fscanf(pfile, "%[^\n]", pcharLine)!=EOF)
	{	
		if (strchr(pcharLine, '#') == NULL)
		{
			char * pst, *ped;
			pst = strchr(pcharLine, '[');
			ped = strchr(pcharLine, ']');
			if (pst != NULL && ped != NULL)
			{
				*ped = '\0';
				pCfg = &CfgList[nUserNum++];
				strcpy(pCfg->szName, pst + 1);
				pCfg->nitem = 0;
				pCfg->item = NULL;
			}
			else
			{
				pst = strchr(pcharLine, '=');
				ped = strchr(pcharLine, '\0');
				if (pst != NULL && ped != NULL)
				{
					pCfg->nitem++;
					*pst = '\0';
					pCfgItem = CreatConfigItem();
					strcpy(pCfgItem->key, pcharLine);
					strcpy(pCfgItem->value, pst + 1);
					InsertConfigItem(pCfg, pCfgItem);
				}
			}
		}
		fgetc(pfile);//Ìø¹ý»»ÐÐ·û
	}
	printf("Open Rule.ini Succeed.   [OK]\n");
	for (i = 0; i < nUserNum;i++)
		PrintConfig(&CfgList[i]);

	fclose(pfile);
	//SaveConfig(CfgList, nUserNum, "test.txt");
}

char * GetValue(config * pCfgList, char key[])
{
	int i;
	configItem pcfgitem = pCfgList->item;
	for (i = 0; i < pCfgList->nitem; i++, pcfgitem = pcfgitem->nextItem)
	{
		if (strcmp(pcfgitem->key, key) == 0)
			return pcfgitem->value;
	}	
}

void PrintConfig(config * pCfgList)
{
	int i;
	configItem pcfgitem = pCfgList->item;
	printf("[%s]\n",pCfgList->szName);
	for (i = 0; i < pCfgList->nitem; i++, pcfgitem = pcfgitem->nextItem)
		printf("%s = %s\n", pcfgitem->key, pcfgitem->value);
}


void SaveConfig(config CfgList[],int n,char * path)
{
	int i;
	config * pcfg_t;
	configItem pcfgitem;
	FILE * pfile = fopen(path, "w+");
	for (i = 0; i < n; i++)
	{
		pcfg_t = &CfgList[i];
		pcfgitem = pcfg_t->item;
		fprintf(pfile,"[%s]\n", pcfg_t->szName);
		while (pcfgitem != NULL)
		{
			fprintf(pfile, "%s = %s\n", pcfgitem->key, pcfgitem->value);
			pcfgitem = pcfgitem->nextItem;
		}
	}
	fclose(pfile);
}