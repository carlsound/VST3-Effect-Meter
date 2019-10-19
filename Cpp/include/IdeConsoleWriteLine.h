#pragma once

#include "pluginterfaces/base/fplatform.h"

#if(SMTG_OS_MACOS)
    inline void IdeConsoleWriteLine(std::wstring wstr)
    {
        std::wcout << wstr;
    }

    inline void IdeConsoleWriteLine(std::string str)
    {
        
        std::cout << str;
    }
#endif

#if(SMTG_OS_WINDOWS)
#include <atlconv.h>
    inline void IdeConsoleWriteLine(std::wstring wstr)
    {
        OutputDebugStringW(wstr.c_str());
    }

	/*
    void IdeConsoleWriteLine(std::string str)
    {
        OutputDebugString(str);
    }
	*/
#endif
