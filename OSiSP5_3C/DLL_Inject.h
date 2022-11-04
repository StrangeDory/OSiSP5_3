#pragma once
#include <winscard.h>
#include <iostream>
class DLL_Inject
{
    typedef struct
    {
        const char* source;
        const char* target;
    } TStringReplace;

public:
    void ReplaceInject(DWORD pid, const char* src, const char* res)
    {
        HANDLE hProc = OpenProcess(PROCESS_CREATE_THREAD |
            PROCESS_VM_OPERATION |
            PROCESS_VM_WRITE, FALSE, pid);
        if (hProc)
        {
            TStringReplace stringReplace;
            stringReplace.source = src;
            stringReplace.target = res;
            PCSTR baseAddress = (PCSTR)VirtualAllocEx(hProc, NULL, sizeof(stringReplace), MEM_COMMIT, PAGE_READWRITE);
            if (baseAddress)
            {
                if (WriteProcessMemory(hProc, (LPVOID)baseAddress, &stringReplace, sizeof(stringReplace), NULL))
                {
                    PTHREAD_START_ROUTINE startRoutine = (PTHREAD_START_ROUTINE)GetProcAddress(LoadLibraryA("DLL_ReplaceString.dll"), "ReplaceString");
                    if (startRoutine)
                    {
                        HANDLE hThread = CreateRemoteThread(hProc, NULL, 0, (PTHREAD_START_ROUTINE)startRoutine, (LPVOID)baseAddress, 0, NULL);

                        if (hThread)
                        {
                            WaitForSingleObject(hThread, INFINITE);
                            
                        }
                    }
                }
            }
        }

    }
};

