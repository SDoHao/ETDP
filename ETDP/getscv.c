#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include"getscv.h"
int nscv_count = 0;
int ndatenum = 0;
char ScvDataArr[11][70];
double ScvData[12][2][20000];
int offset_p;

void OpenDir(char filedir[])
{
	char tempfiledir[70];
	if (strcmp(filedir, ".") == 0)
		offset_p = 1;
	else
		offset_p = 0;

	if ((pdir = opendir(filedir)) == NULL)
		printf("\nCan't Open Dirent%s   [Failed]\n", filedir);
	else
		printf("\nOpen Dirent Succeed %s   [OK]\n", filedir);
	while ((pdirstu = readdir(pdir)) != NULL)
	{
		if (strcmp(pdirstu->d_name, ".") == 0 || strcmp(pdirstu->d_name, "..") == 0) ///current dir OR parrent dir
			continue;
		strcpy(tempfiledir, filedir);
		strcat(tempfiledir, pdirstu->d_name);
		if (strstr(tempfiledir, ".csv") && (!strstr(tempfiledir, "Output.csv")))
		{
			strcpy(ScvDataArr[nscv_count++], tempfiledir);
			printf("%d %s\n", nscv_count, tempfiledir);
		}
	}
	printf("There are %d files in total.\n\n", nscv_count);
	closedir(pdir);
}

void LoadScv(int modeid)
{
	int i = 0, lines;
	char pcharLine[300];
	char * pchar,* pfindchar;
	double prod;
	FILE * pfile;
	
	for (i = 0; i < nscv_count; i++)
	{
		pchar = ScvDataArr[i] + offset_p;
		if ((pfile = fopen(pchar, "r")) != NULL)
		{
			lines = 0;
			printf("Read [  %s  ]  Succeed   [OK]\n", pchar);
			while(fgets(pcharLine, 100, pfile) != EOF)
			{
				pfindchar = strstr(pcharLine, "Potential/V");
				if (pfindchar != NULL)
				{
					fgets(pcharLine, 100, pfile);
					break;
				}
				//fscanf(pfile, "%[^\n]%*c", pcharLine);
				//printf("%d %s\n", lines,pcharLine);
				//if(lines == 6 || lines == 16)
				//	fscanf(pfile, "%*c");
				//else if (lines == 14 || lines == 15)
				//	fscanf(pfile, "%*c%*c");
			}
			ndatenum = 0;
			if (modeid == 1)
			{
				while (fscanf(pfile, "%lf, %lf", &ScvData[i][0][ndatenum], &ScvData[i][1][ndatenum]) != EOF)
				{
					ndatenum++;
				}

			}
				
			else if (modeid == 2)
			{
				while (fscanf(pfile, "%lf, %lf, %lf", &ScvData[i][0][ndatenum], &ScvData[i][1][ndatenum], &prod) != EOF)
				{
					ndatenum++;
				}
			}

			printf("There are %d rows of data in total.\n\n", ndatenum);
			fclose(pfile);
		}
		else
			printf("Read %s Falied.   [Falied]\n", pchar);

	}
}

void ProcessScv(int modeid, double area, int pH, int refe)
{
	int i,k;
	double addvalue;
	addvalue = 0.059 * pH;
	if (refe == 1)
	{
		addvalue += 0.24;
		printf("E(SCE) + 0.059 * %d + 0.24(%lf)\n", pH, addvalue);
		
	}
		
	else if (refe == 2)
	{
		addvalue += 0.197;
		printf("E(SCE) + 0.059 * %d + 0.197(%lf)\n", pH, addvalue);
		
	}
	for (i = 0; i < ndatenum; i++)
	{
		if (i < ndatenum)
		{
			//printf("%lf\n", ScvData[0][0][i]);
			ScvData[0][0][i] = ScvData[0][0][i] + addvalue;
		}
		
	}
	for (i = 0; i < nscv_count; i++)
		for (k = 0; k < ndatenum; k++)
		{
			ScvData[i][1][k] = ScvData[i][1][k] * 1000 / area;
		}
			
	printf("\nData processing completed.\n");
}

void SaveScv(int modeid,int st,int ed)
{
	int i, k;
	char *pchar;
	if (ed != 0)
		ndatenum = ed;
	//if (access("Output.csv", 2) == 0)
	//{
		FILE * pfile = fopen("Output.csv", "w+");
		fprintf(pfile, "Potential / V vs.RHE");
		for (k = 0; k < nscv_count; k++)
		{
			pchar = ScvDataArr[k] + offset_p;
			fprintf(pfile, ",%s", pchar);
		}
		fprintf(pfile, "\n");
		for (i = ndatenum - 1; i >= st; i--)
		{
			fprintf(pfile, "%lf", ScvData[0][0][i]);
			//printf("%lf\n", ScvData[0][0][i]);
			for (k = 0; k < nscv_count; k++)
			{
				fprintf(pfile, ",%.12lf", ScvData[k][1][i]);
			}
			fprintf(pfile, "\n");
		}
		printf("\nAll data output.  [Output.csv]\n\n");
		fclose(pfile);
	//}
}