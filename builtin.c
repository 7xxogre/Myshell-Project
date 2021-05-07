#include "builtin.h"

void Normalization(char command[1024])
{
	char temp[1024];
	int tempidx = 0;
	for (int i = 0;i < 1024;)
	{
		while(command[i] == ' ' && i < 1024)
			i++;

		while(command[i] != ' ' && i < 1024 && command[i] != '\n')
		{
			temp[tempidx++] = command[i++];
		}
		if(command[i] == '\n')
			break;
		temp[tempidx++] = ' ';
	}
	if(tempidx > 0 && temp[tempidx - 1] == ' ')
		tempidx--;
	if(tempidx > 1 && temp[tempidx - 1] == '&' && temp[tempidx - 2] == ' ')
	{
		temp[tempidx-2] = '&';
		tempidx--;
	}
	temp[tempidx] = '\n';
	temp[tempidx+1] = '\0';
	for(int i = 0; i< 1024; i++)
	{
		command[i] = temp[i];
	}

	return;
}

void History(char command_list[10][1024], int now)
{
	for (int i = (now + 1) % 10; i != now; i = (i + 1) % 10)
	{
		if(command_list[i][0] == 0)
		{
			continue;
		}
		else
		{
			printf("%s", command_list[i]);
		}
	}
	printf("%s", command_list[now]);
	return;
}

void Help()
{
	printf("DESCRIPTION\n\tmyshell is a simple shell...\n");
	printf("\tThis shell have 3 built-in instructions. (history, help, quit)\n");
	printf("\tYou can output the last 10 commands by typing 'history' in this shell.\n");
	printf("\tOr if you type 'quit', then shell will terminate.\n");
	printf("\tOn the other hand, if you type exterior instruction to this shell then this shell will parsing the instruction and then execute that instruction\n");
	
}
