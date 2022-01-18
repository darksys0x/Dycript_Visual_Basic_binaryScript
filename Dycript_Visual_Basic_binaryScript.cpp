#include<stdio.h>
#include <stdlib.h>


char* fileOneData = NULL;
char* fileTwoData = NULL;

//get the size file from desk and loaded in the heap
void readFile_FromDesk(uintptr_t filePath, char** theFileData) {
	FILE* hamadFile = fopen(filePath, "rb");
	if (hamadFile) {
		fseek(hamadFile, 0, SEEK_END);
		int fileSize = ftell(hamadFile);
		fseek(hamadFile, 0, SEEK_SET);

		char* fileData = (char*)malloc(fileSize);

		if (fread(fileData, 1, fileSize, hamadFile) == fileSize) {
			printf("file read successfuly");
			*theFileData = fileData;//fileOneData = fileData;
		}
		else
		{
			printf("failed to read file");
		}

		
		
		free(fileData);
		fclose(hamadFile);
	}
}

void findtheCharecter() {
	char* p = fileOneData;
}


int main() {
	char fileOneName[] = "C:\\file1.bin";
	readFile_FromDesk((uintptr_t)fileOneName, &fileOneData);


	char fileTwoName[] = "C:\\file2.bin";
	readFile_FromDesk((uintptr_t)fileTwoName, &fileTwoData);


	getchar();
	return 0;
}


