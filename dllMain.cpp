#include "pch.h"
#include <stdio.h>
#include <Windows.h>
#include <psapi.h>
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")


//
//int GetModuleFileNameEx(
//    int hProcess,
//    int hModule,
//    Pointer<Utf16> lpFilename,
//    int nSize
//);
void mb() {
    DWORD h = GetCurrentProcessId();
    TCHAR buffer[100];
    wsprintf(buffer, L"process has been injectied", h);
    MessageBox(NULL, buffer,(LPCTSTR)L"Hamad", MB_ICONWARNING | MB_DEFBUTTON2 | MB_OK);

}
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        // 1. getmodulenameex(); .. 
        // FileNt, fi
        // 2. pathFindFileName(); >> 
        // 3. pathFile
        DWORD cureent = GetCurrentProcessId();

        HANDLE hamad = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, cureent);
        if (hamad) {
            TCHAR buffer[MAX_PATH];

            GetModuleBaseNameW(hamad, 0, buffer, MAX_PATH); // includes the full path of current process
            printf("get module current process = %ws\n", buffer);

            TCHAR* exe = PathFindFileName(buffer); //the return address 
            if (exe) {
                if (wcscmp(exe, L"powershell.exe") == 0) {
                    mb();
                }
            }
            CloseHandle(hamad);
        }



    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

