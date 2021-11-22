#pragma warning( disable : 26812 )

#include <stdio.h>
#include <string.h>

struct command
{
	char name[50];
	enum cmds cmd;
}typedef command;
enum cmds
{
	error=-1, help=0, order, by, asc, desc, exit_
}typedef cmds;

command cmd[] = { {"help", help}, {"order", order}, {"by", by}, {"exit", exit_}, {"asc", asc}, {"desc", desc} };

void splitString(char* str, char* ch, char** arr)
{
	char* ptr = strtok(str, ch);
	arr[0] = ptr;
	int i = 1;
	while (ptr != NULL)
	{
		ptr = strtok(NULL, ch);
		arr[i++] = ptr;
	}
}

enum cmds divideCommand(char* str)
{
	enum cmds result = error;
	for (int i = 0; i < sizeof(cmd) / sizeof(struct command); i++)
	{
		if (!strcmp(str, cmd[i].name))
			result = cmd[i].cmd;
	}
	return result;
}
