#include<stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdint.h>

int fileSizeONeForTest = 0;
char* fileOneData = NULL;
char* fileTwoData = NULL;

//$Codigo = '...' //fileOneData
//$OWjuxD = [System.Text.Encoding]::Unicode.GetString([System.Convert]::FromBase64String($Codigo.replace('â¤', 'A'))).replace('...')
//
//powershell.exe - windowstyle hidden - ExecutionPolicy Bypss - NoProfile - Command $OWjuxD

//get the size file from desk and loaded in the heap
void readFile_FromDesk(char* filePath, char** theFileData, int* sizeOneFile) {
	FILE* hamadFile = fopen(filePath, "rb");
	if (hamadFile) {
		fseek(hamadFile, 0, SEEK_END);
		int fileSize = ftell(hamadFile);
		fseek(hamadFile, 0, SEEK_SET);

		char* fileData = (char*)malloc(fileSize);

		if (fread(fileData, 1, fileSize, hamadFile) == fileSize) {
			printf("file reads successfully\n");
			if (sizeOneFile) {
				*sizeOneFile = fileSize;
			}
		}
		else
		{
			printf("failed to read file\n");
		}

		
		*theFileData = fileData;//fileOneData = fileData;
		
			
		fclose(hamadFile);
	}
}

void findtheCharecter() {
	char* newFileMemory = (char*)malloc(fileSizeONeForTest);
	
	memset(newFileMemory, 0, fileSizeONeForTest);
	
	int currentIndex = 0;// original counter..
	/*loop thrugh the file one data*/
	for (int i = 0; i < fileSizeONeForTest; currentIndex++) {

		//if (fileOneData[i] == 0xE2 && fileOneData[i+1] == 0xA4 ) {
		if (fileOneData[i] == 'â' && fileOneData[i + 1] == '¤') {
			newFileMemory[currentIndex] = 'A';
			i += 2;
		}
		else {
			newFileMemory[currentIndex] = fileOneData[i];
			i++;
		}
		
	
	}

	//for (int i = 0; i < fileSizeONeForTest; i++) {

	//	//if (fileOneData[i] == 0xE2 && fileOneData[i+1] == 0xA4 ) {
	//	if (fileOneData[currentIndex] == 'â' && fileOneData[currentIndex + 1] == '¤') {
	//		newFileMemory[i] = 'A';
	//		currentIndex += 2;
	//	}
	//	else {
	//		newFileMemory[i] = fileOneData[currentIndex];
	//		currentIndex++;
	//	}

	//}
	FILE* deskFile = fopen("C:\\Users\\DFIR\\Desktop\\aliMalwarw\\powershellScript\\powershellScript\\Source.txt", "w+");
	if (deskFile) {
		printf("i got ittt :)))");
		fwrite(newFileMemory, 1, fileSizeONeForTest, deskFile);
		fclose(deskFile);
	}




}


int main() {
	char fileOneName[] = "C:\\Users\\DFIR\\Desktop\\aliMalwarw\\malware\\file1.bin";
	readFile_FromDesk(fileOneName, &fileOneData, &fileSizeONeForTest);


	char fileTwoName[] = "C:\\Users\\DFIR\\Desktop\\aliMalwarw\\malware\\file2.bin";
	readFile_FromDesk(fileTwoName, &fileTwoData, NULL);


	findtheCharecter();

	getchar();
	return 0;
}


