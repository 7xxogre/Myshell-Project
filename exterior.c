#include "exterior.h"

int IsBackground(char command[1024])
{
	int i = 0;
	while(command[i] != '\0')
		i++;
	if(command[i-2] == '&')
		return 1;
	return 0;
}

char* MakeString(char command[1024], int startidx, int endidx)
{
	
	char* ret = (char*)malloc(sizeof(char) * (endidx - startidx));
	int retcnt = 0;
	for(int i = startidx; i < endidx; i++)
	{
		ret[retcnt++] = command[i];
	}
	
	return ret;
}

void ExecuteCommand(char command[1024])
{
	int j = 0;
	int cnt = 1;
	while(command[j] != '\n')
	{
		j++;
		if(command[j] == ' ')
			cnt++;
	}
	j++;
	int i = 0;

	char** commandptr = (char**)malloc(sizeof(char*) * (cnt + 1));	
	
	commandptr[cnt] = NULL;
	cnt = 0;
	int start = 0;
	int end = 0;
	while(command[i] != '\n')
	{
		start = i;
		while(i < j-2 && command[i] != ' ')
		{
			i++;
		}
		if(i == j-2 && command[i] != ' ' && command[i] != '&')
			i++;
		end = i;

		commandptr[cnt++] = MakeString(command, start, end);
		if(command[i] == '\n'|| command[i] == '&')
			break;
		while(command[i] == ' ')
			i++;
	}

	execvp(commandptr[0], commandptr);
}

void ChangeDir(char command[1024])
{
	int j = 3;
	while(command[j] != '\n')
		j++;
	char* changepath = (char*)malloc(sizeof(char*) * (j - 3));
	for(int i = 0;i < j - 3;i++)
	{
		changepath[i] = command[i+3];
	}
	
	if(chdir(changepath) != 0)
		printf("%s failed!!\n", changepath);
	
}
