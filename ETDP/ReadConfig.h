#pragma once
#define KeyLenth 11
#define ValueLenth 50
#define ConfigNameLenth 101

typedef struct configItem * configItem;
struct configItem
{
	char key[KeyLenth];
	char value[ValueLenth];
	configItem nextItem;
};
typedef struct config config;
struct config
{
	int nitem;
	char szName[ConfigNameLenth];
	configItem item;
};
configItem CreatConfigItem();
void ReadConfig(char * path, config CfgList[]);
void PrintConfig(config * pCfgList);
void SaveConfig(config pCfgList[], int n, char * path);
char * GetValue(config * pCfgList, char key[]);