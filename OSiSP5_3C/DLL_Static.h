#pragma once
#include <minwindef.h>
#include <processthreadsapi.h>
extern "C" void __declspec(dllexport) __cdecl ReplaceString(DWORD pid,
	const char* src, const char* res);
class DLL_Static
{
	void ReplaceStatic(const char* src, const char* res)
	{
		DWORD pid = GetCurrentProcessId();
		ReplaceString(pid, src, res);
	}
};

