#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

void printFileInfo(fileInfo*);
void printTableLine(int, int);
void printLogo();

void printFileInfo(fileInfo* list)
{
	int oldName_maxLen = strlen("Existing name");
	int newName_maxLen = strlen("Change Name");
	for (int i = 0; i < (int)(_msize(list) / sizeof(struct fileInfo)); i++)
	{
		int oldName_tempLen = strlen(list[i].oldName);
		int newName_tempLen = strlen(list[i].newName);
		
		if (oldName_maxLen < oldName_tempLen)
			oldName_maxLen = oldName_tempLen;
		if (newName_maxLen < newName_tempLen)
			newName_maxLen = newName_tempLen;
	}

	char stringFormat[50] = "  |%-";
	char oldName_maxLenStr[5];
	char newName_maxLenStr[5];
	_itoa(oldName_maxLen, oldName_maxLenStr, 10);
	_itoa(newName_maxLen, newName_maxLenStr, 10);
	strcat(stringFormat, oldName_maxLenStr);
	strcat(stringFormat, "s|%-");
	strcat(stringFormat, newName_maxLenStr);
	strcat(stringFormat, "s|\n");

	printTableLine(oldName_maxLen, newName_maxLen);
	printf(stringFormat, "Existing name", "Change Name");
	printTableLine(oldName_maxLen, newName_maxLen);

	for (int i = 0; i < (int)(_msize(list) / sizeof(struct fileInfo)); i++)
		printf(stringFormat, list[i].oldName, list[i].newName);
	printTableLine(oldName_maxLen, newName_maxLen);
}

void printTableLine(int oldName_maxLen, int newName_maxLen)
{
	printf("  +");
	for (int i = 0; i < oldName_maxLen; i++)
		printf("-");
	printf("+");
	for (int i = 0; i < newName_maxLen; i++)
		printf("-");
	printf("+\n");
}

void printLogo()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	printf(" _____ _ _        _____                                   _      _____         _ \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("|   __|_| |___   |     |___ ___ ___ ___ ___ _____ ___ ___| |_   |_   _|___ ___| |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("|   __| | | -_|  | | | | .'|   | .'| . | -_|     | -_|   |  _|    | | | . | . | |\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("|__|  |_|_|___|  |_|_|_|__,|_|_|__,|_  |___|_|_|_|___|_|_|_|      |_| |___|___|_|\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	printf("                                   |___|                                         \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("Welcome to File Management Tool\n\n");
}
