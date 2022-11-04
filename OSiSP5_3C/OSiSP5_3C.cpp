#include "OSiSP5_3C.h"
#include "DLL_Static.h"
#include "DLL_Dinamic.h"
#include "DLL_Inject.h"

int main()
{
    std::string src;
    std::cout << "String to be replaced : ";
    std::cin >> src;
    std::string res;
    std::cout << "String to replace: ";
    std::cin >> res;

    std::cout << "Menu:" << "\n";
    std::cout << "1)  Static import" << "\n";
    std::cout << "2)  Dynamic import" << "\n";
    std::cout << "3)  Inject DLL" << "\n";
    std::cout << "0)  Exit" << "\n";

    int menu;
    std::cin >> menu;
    switch (menu)
    {
    case 0:
        break;
    case 1:
        DLL_Static staticCall;
        staticCall.ReplaceStatic(src.c_str(), res.c_str());
        break;
    case 2:
        DLL_Dinamic dinamicCall;
        dinamicCall.ReplaceDinamic(src.c_str(), res.c_str());
        break;
    case 3:
    {

        DWORD pid = GetCurrentProcessId();
        DLL_Inject injectThreadCall;
        injectThreadCall.ReplaceInject(pid, src.c_str(), res.c_str());
        break;
    }
    default:
        std::cout << "Inccorect number" << "\n";
        break;
    }

}

