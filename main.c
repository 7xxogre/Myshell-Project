#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include "builtin.h"
#include "exterior.h"


void main()
{
	pid_t pid;
	pid_t pid_child;
	int status;
	char command[1024];
	char history_list[10][1024];
	int is_background = 0;		// check background command
	int now = -1;

	for (int i = 0;i < 10; i++)
	{
		memset(history_list[i], 0, sizeof(history_list[i]));
	}

	while (1)
	{
		
		printf("12171600 shell$ ");
		fgets(command, sizeof(command) - 1, stdin);
		
		Normalization(command);
		
		now = (now+1) % 10;
		strcpy(history_list[now], command);

		if (strncmp(command, "history", 7) == 0)
		{
			History(history_list, now);
		}
		else if (strncmp(command, "help", 4) == 0)
		{
			Help();
		}
		else if (strncmp(command, "quit", 4) == 0)
		{
			break;
		}
		else if(strncmp(command, "cd", 2) == 0)
		{
			ChangeDir(command);
		}
		else
		{
			if(is_background == 1)
			{
				if(waitpid(pid, &status, WNOHANG) != 0)
					is_background = 0;
			}
			is_background = IsBackground(command);
			pid = fork();
			if (pid == 0)
			{
				ExecuteCommand(command);
				return;
			}
			else
			{
				if(is_background == 0)
				{
					pid_child = wait(&status);
					
				}
			}	
		}
	}
	printf("myshell develpoed by Kim yumin(12171600)\n");
}