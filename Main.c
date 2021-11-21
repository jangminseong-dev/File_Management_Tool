#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 6031 )

#include <stdio.h>
#include <string.h>

void splitString(char*, char*, char**);
enum cmds divideCommand(char*);

struct command
{
	char name[50];
	enum cmds cmd;
}typedef command;
enum cmds
{
	help=0, order, by, debug 
}typedef cmds;

command cmd[] = { {"help", help}, {"order", order}, {"by", by}, {"debug", debug} };

void main()
{
	char input[100] = "";
	gets_s(input, sizeof(input));

	char* commands[7] = { NULL };
	splitString(input, " ", commands);

	cmds mainCommand = divideCommand(commands[0]);
	switch (mainCommand)
	{
		case help:
			printf("Enter help command.\n");
			break;
		case order:
			printf("Enter order command.\n");
			break;
		case debug:
			printf("Enter debug command.\n");
			break;
		default:
			printf("command not found.\n");
			break;
	}

	for (int i = 0; i < 7; i++)
	{
		if (commands[i] != NULL)
			printf("commands[%d] = %s\n", i, commands[i]);
	}
}

void splitString(char* str, char* ch, char** arr)
{
	char* ptr = strtok(str, ch);
	arr[0] = ptr;
	int i = 1;
	while (ptr != NULL)
	{
		ptr = strtok(NULL, ch);
		arr[i] = ptr;
		i++;
	}
}

enum cmds divideCommand(char* str)
{
	enum cmds result;
	for (int i = 0; i < sizeof(cmd) / sizeof(struct command); i++)
	{
		if (!strcmp(str, cmd[i].name))
			result = cmd[i].cmd;
	}
	return result;
}