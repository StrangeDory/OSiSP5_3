#pragma once
#pragma comment(lib, "E:\\Œ—Ë—œ\\OSiSP5_3C\\Debug\\DLL_ReplaceString.lib")

#include <windows.h>
#include <iostream>
extern "C" void __declspec(dllexport) __cdecl ReplaceString(DWORD pid,
	const char* src, const char* res);
class DLL_Static
{
public:

	void ReplaceStatic(const char* src, const char* res)
	{
		DWORD pid = GetCurrentProcessId();
		ReplaceString(pid, src, res);
	}
};

