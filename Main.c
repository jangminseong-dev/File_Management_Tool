#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 6031 )

#include <stdio.h>
#include <string.h>

#include "Command.h"
#include "FileIO.h"

void main()
{
	char input[100] = "";

	while (1)
	{
		printf("FMT Console > ");
		gets_s(input, sizeof(input));

		if (!strcmp(input, ""))
			continue;

		char* commands[7] = { NULL };
		splitString(input, " ", commands);

		cmds mainCommand = divideCommand(commands[0]);
		switch (mainCommand)
		{
		case help:
			printf("Enter help command.\n");
			break;
		case order:
			if (divideCommand(commands[2]) != by || (divideCommand(commands[3]) != asc && divideCommand(commands[3]) != desc))
			{
				printf("-FMT: %s: Command line option syntax error.\n", commands[0]);
				break;
			}
			char* path = (char*)openFolderDialog();
			if (strcmp(path, ""))
			{
				fileInfo* list = (fileInfo*)malloc(sizeof(struct fileInfo) * fileCount(path));
				fileSearch(path, list);

				if (divideCommand(commands[3]) == asc)
				{
					fileAsc(list, commands[1]);
				}
				else if (divideCommand(commands[3]) == desc)
				{
					fileDesc(list, commands[1]);
				}
				char answer = 'n';
				printf("-FMT : Do you want to apply the changes(y/n)? ");
				scanf("%c", &answer);
				if (answer == 'y')
					fileNameChange(list);
				free(list);
			}
			break;
		case exit_:
			return;
			break;
		default:
			printf("-FMT: %s: command not found\n", commands[0]);
			break;
		}
	}
}