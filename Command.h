#include <stdio.h>
#include <string.h>

struct command
{
	char name[50];
	enum cmds cmd;
}typedef command;
enum cmds
{
	help = 0, order, by, debug
}typedef cmds;

command cmd[] = { {"help", help}, {"order", order}, {"by", by}, {"debug", debug} };

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
