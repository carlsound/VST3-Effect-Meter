// https://code.msdn.microsoft.com/windowsdesktop/Consuming-C-Library-in-937458e5

#pragma once

#ifdef __cplusplus
	extern "C"
	{
#endif
		__declspec(dllexport)  void loadChildWindow(void* hWnd);

#ifdef __cplusplus 
	}
#endif 