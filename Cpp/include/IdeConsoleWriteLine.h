#pragma once

#include "pluginterfaces/base/fplatform.h"


#if(SMTG_OS_MACOS)
    void IdeConsoleWriteLine(std::wstring wstr)
    {
        std::wcout << wstr;
    }

    void IdeConsoleWriteLine(std::string str)
    {
        
        std::cout << str;
    }
#endif

#if(SMTG_WINDOWS)
    void IdeConsoleWriteLine(std::wstring wstr)
    {
        OutputDebugStringW(wstr);
    }

    void IdeConsoleWriteLine(std::string str)
    {
        OutputDebugString(str);
    }
#endif
