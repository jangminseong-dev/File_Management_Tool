#pragma warning( disable : 4172 )
#pragma warning( disable : 6384 )
#pragma warning( disable : 6011 )

#define MAX_FILENAME_LEN 100

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <direct.h>
#include <string.h>
#include <ShlObj.h>
#include <windows.h>
#include <tchar.h>
#include <io.h>

const char* openFolderDialog();
void fileSearch(char*, struct fileInfo*);
int fileCount(char*);
const char* extractExtension(char*);
void fileDesc(struct fileInfo*, char*);
void fileAsc(struct fileInfo*, char*);
const char* newNameSort(char*, char*, int);
void fileNameChange(struct fileInfo*);

struct fileInfo
{
	char path[MAX_PATH];
	char oldName[MAX_FILENAME_LEN];
	char newName[MAX_FILENAME_LEN];
	char extension[10];
}typedef fileInfo;

struct path {
	char old[MAX_PATH];
	char tmp[MAX_PATH];
	char new[MAX_PATH];
}typedef PATH;

const char* openFolderDialog()
{
	BROWSEINFO fileDialog;
	LPITEMIDLIST pDirList;
	TCHAR pathBuffer[MAX_PATH];
	char path[MAX_PATH] = "";

	fileDialog.hwndOwner = NULL;
	fileDialog.pidlRoot = NULL;
	fileDialog.lpszTitle = _T("폴더를 선택하십시오.");
	fileDialog.pszDisplayName = pathBuffer;
	fileDialog.ulFlags = 0;
	fileDialog.lpfn = NULL;
	fileDialog.lParam = 0;
	fileDialog.iImage = -1;
	pDirList = SHBrowseForFolder(&fileDialog);
	if (pDirList == NULL) return "";
	if (SHGetPathFromIDList(pDirList, pathBuffer))
		WideCharToMultiByte(CP_ACP, 0, pathBuffer, MAX_PATH, path, MAX_PATH, NULL, NULL);
	return path;
}

void fileSearch(char* path, struct fileInfo* list)
{
	char searchPath[MAX_PATH];
	int idx = 0;
	strcpy_s(searchPath, sizeof(searchPath), path);
	strcat_s(searchPath, sizeof(searchPath), "\\*.*");

	struct _finddata_t fd;
	long handle;
	int result = 1;
	handle = _findfirst(searchPath, &fd);

	if (handle == -1)
	{
		printf("이곳엔 파일이 존재하지 않습니다.\n");
		return;
	}
	printf("폴더 내 파일 목록 :\n");
	while (result != -1)
	{
		if (fd.attrib != 17 && fd.attrib != 16)
		{
			strcpy(list[idx].path, path);
			strcpy(list[idx].oldName, fd.name);
			strcpy(list[idx].newName, "");
			strcpy(list[idx].extension, extractExtension(fd.name));
			printf("\t%40s\t%5s\t%u\n", list[idx].oldName, list[idx].extension, fd.attrib);
			idx++;
		}
		result = _findnext(handle, &fd);
	}

	_findclose(handle);
}

int fileCount(char* path)
{
	char searchPath[MAX_PATH];
	int count = 0;
	strcpy_s(searchPath, sizeof(searchPath), path);
	strcat_s(searchPath, sizeof(searchPath), "\\*.*");

	struct _finddata_t fd;
	long handle;
	int result = 1;
	handle = _findfirst(searchPath, &fd);

	if (handle == -1)
		return -1;

	while (result != -1)
	{
		if (fd.attrib != 17 && fd.attrib != 16)
			count++;
		result = _findnext(handle, &fd);
	}

	_findclose(handle);
	return count;
}

const char* extractExtension(char* fileName)
{
	char* ptr = strtok(fileName, ".");
	char* ext = ptr;
	while (ptr != NULL)
	{
		ptr = strtok(NULL, ".");
		if (ptr != NULL)
			ext = ptr;
	}
	return ext;
}

void fileDesc(struct fileInfo* fileList, char* newName)
{
	int size = _msize(fileList) / sizeof(struct fileInfo);
	for (int i = 0; i < size; i++) {
		printf("%s\t->\t", fileList[i].oldName);
		strcpy_s(fileList[i].newName, sizeof(fileList[i].newName), newNameSort(newName, fileList[i].extension, size - i));
		printf("%s\n", fileList[i].newName);
	}
}

void fileAsc(struct fileInfo* fileList, char* newName)
{
	int size = _msize(fileList) / sizeof(struct fileInfo);
	for (int i = 0; i < size; i++) {
		printf("%s\t->\t", fileList[i].oldName);
		strcpy_s(fileList[i].newName, sizeof(fileList[i].newName), newNameSort(newName, fileList[i].extension, i + 1));
		printf("%s\n", fileList[i].newName);
	}
}

const char* newNameSort(char* newname, char* extension, int num)
{
	char itoa_buf[10];
	sprintf_s(itoa_buf, sizeof(itoa_buf), "%d", num);
	char res_name[MAX_FILENAME_LEN];
	strcpy_s(res_name, sizeof(res_name), itoa_buf);
	strcat_s(res_name, sizeof(res_name), "_");
	strcat_s(res_name, sizeof(res_name), newname);
	strcat_s(res_name, sizeof(res_name), ".");
	strcat_s(res_name, sizeof(res_name), extension);
	return res_name;
}

void fileNameChange(struct fileInfo* fileList) {
	int size = _msize(fileList) / sizeof(struct fileInfo);
	PATH* path = (PATH*)malloc(sizeof(PATH) * size);
	for (int i = 0; i < size; i++) {
		char* ptr = strtok(fileList[i].path, ".");
		char tmp_path[MAX_PATH] = { NULL };
		while (ptr != NULL)
		{
			strcat_s(tmp_path, sizeof(tmp_path), ptr);
			ptr = strtok(NULL, ".");
			if (ptr != NULL)
				strcat_s(tmp_path, sizeof(tmp_path), "\\");
		}
		strcpy_s(path[i].old, sizeof(path[i].old), tmp_path);
		strcat_s(path[i].old, sizeof(path[i].old), "\\");
		strcat_s(path[i].old, sizeof(path[i].old), fileList[i].oldName);
		strcpy_s(path[i].tmp, sizeof(path[i].tmp), tmp_path);
		strcat_s(path[i].tmp, sizeof(path[i].tmp), "\\");
		strcat_s(path[i].tmp, sizeof(path[i].tmp), "[tmp]");
		strcat_s(path[i].tmp, sizeof(path[i].tmp), fileList[i].newName);
		strcpy_s(path[i].new, sizeof(path[i].new), tmp_path);
		strcat_s(path[i].new, sizeof(path[i].new), "\\");
		strcat_s(path[i].new, sizeof(path[i].new), fileList[i].newName);
		rename(path[i].old, path[i].tmp);
	}
	for (int i = 0; i < size; i++) {
		rename(path[i].tmp, path[i].new);
	}
	free(path);
}