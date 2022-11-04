#pragma once
#ifndef DLL_REPLACE
#define DLL_REPLACE __declspec( dllimport )
#endif
extern "C" void __declspec(dllexport) __cdecl ReplaceString(DWORD pid,
	const char* src, const char* res)
{
	HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE
		| PROCESS_QUERY_INFORMATION, FALSE, pid);

	if (hProcess)
	{
        SIZE_T sourceLen = strlen(src);
        SIZE_T targetLen = strlen(res);

        SYSTEM_INFO si;
        GetSystemInfo(&si);

        MEMORY_BASIC_INFORMATION info;
        auto baseAddress = (LPSTR)si.lpMinimumApplicationAddress;

        while (baseAddress < si.lpMaximumApplicationAddress)
        {
            if (VirtualQuery(baseAddress, &info, sizeof(info)) == sizeof(info))
            {
                if (info.State == MEM_COMMIT && info.AllocationProtect == PAGE_READWRITE)
                {
                    baseAddress = (LPSTR)info.BaseAddress;
                    char* memory = (char*)malloc(info.RegionSize);
                    SIZE_T bytesRead;

                    if (memory != 0)
                    {
                        if (ReadProcessMemory(hProcess, baseAddress, memory, info.RegionSize, &bytesRead))
                        {
                            for (SIZE_T i = 0; i < bytesRead - sourceLen; i++)
                            {
                                if (strcmp(baseAddress + i, src) == 0)
                                {
                                    memcpy(baseAddress + i, res, targetLen + 1);
                                }
                            }
                        }
                        free(memory);
                    }

                }
            }
            baseAddress += info.RegionSize;
        }
	}
}