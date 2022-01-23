#include<stdio.h>
#include<Windows.h>
#include<tlhelp32.h>
#include<string.h>
#include<shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

// to get api function from ntdll.dll
//int __stdcall ZwResumeProcess(int a1)
//{
//	return Wow64SystemServiceCall();
//}

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#endif


typedef NTSTATUS(WINAPI* NtResumeProcessType)(HANDLE ProcessHandle); 

HANDLE* hamadProcess = NULL;

typedef NTSTATUS(NTAPI* NtSuspendProcessType)(
	HANDLE ProcessHandle
	);


DWORD findTargetProcess(PCTSTR Pname, DWORD ignoredProcessId) {
	HANDLE getprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	
	BOOL p = Process32First(getprocess, &pe);
	DWORD proceeID = 0;
	while (p)
	{
		if (pe.th32ProcessID != ignoredProcessId && StrStrIW(pe.szExeFile, Pname)) {
			printf("the process ID = %d | %ws\n", pe.th32ProcessID, pe.szExeFile);
			proceeID = pe.th32ProcessID;
			//readDLll(pe.th32ProcessID);
			break;
		}
		pe.dwSize = sizeof(PROCESSENTRY32);
		p = Process32Next(getprocess, &pe);
		
	}

	CloseHandle(getprocess);
	return proceeID;
	
}

void suspensedProcess(DWORD prox) {
	if (HANDLE op = OpenProcess(PROCESS_ALL_ACCESS, FALSE, prox)) {


		HMODULE noor = GetModuleHandle(L"ntdll.dll");
		NtSuspendProcessType nt = (NtSuspendProcessType)GetProcAddress(noor, "NtSuspendProcess");

		NTSTATUS status = nt(op);
		if (NT_SUCCESS(status))
			printf("[+] Successfully suspended the process\n");
		else
			printf("[-] Failed to suspend the process | status = %#.8x\n", status);
		CloseHandle(op);
	}
	else {
		printf("[-] Failed to suspend the process\n");
	}
}


void resumProcess(DWORD prox) {
	
	if (HANDLE op = OpenProcess(PROCESS_ALL_ACCESS, FALSE, prox)) {


		HMODULE noor = GetModuleHandle(L"ntdll.dll");
		NtResumeProcessType nt = (NtResumeProcessType)GetProcAddress(noor, "NtResumeProcess");

		NTSTATUS status = nt(op);
		if (NT_SUCCESS(status))
			printf("[+] Successfully Ruseme the process\n");
		else
			printf("[-] Failed to Rusume the process | status = %#.8x\n", status);
		CloseHandle(op);
	}
	else {
		printf("[-] Failed to Rusume the process\n");
	}
}





int main() {
	PCTSTR Pname = L"powershell.exe";
	printf("[+] searching for process '%ws'\n", Pname);
	while (true) {
		DWORD processId = findTargetProcess(Pname, 7976);
		if (processId != 0) {
			suspensedProcess(processId);
			break;
			
		}

		Sleep(50);//60 == 1 scand
	}
	


	return 0;
}