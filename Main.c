#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 6031 )

#include <stdio.h>
#include <string.h>

#include "Command.h"

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