#pragma once
#include <windows.h>
#include <iostream>
class DLL_Dinamic
{
	typedef void __cdecl TReplaceString(DWORD pid, const char* src, const char* res);

public:
	void ReplaceDinamic(const char* src, const char* res)
	{
		DWORD pid = GetCurrentProcessId();
		HINSTANCE lib;
		lib = LoadLibrary(L"DLL_ReplaceString.dll");
		if (lib != NULL) {
			TReplaceString* replaceStr = (TReplaceString*)GetProcAddress(lib, "ReplaceString");
			if (NULL != replaceStr) {
				replaceStr(pid, src, res);
			}
			else {
				std::cout << "Proc not found";
			}
			FreeLibrary(lib);
		}
	}
};

