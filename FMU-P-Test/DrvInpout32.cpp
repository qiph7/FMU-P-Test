#include <iostream>

#include "DllDrvInpout32.h"
#include "tchar.h"

CDllDrvInpout32::CDllDrvInpout32()
{
	HMODULE m_hDll= LoadLibrary(_T("inpout32.dll"));

	if (m_hDll==NULL)
	{
		std::cout << "»ñÈ¡Inpout32.dllÊ§°Ü" << std::endl;
		system("pause");
		exit(1);
		//return;
	}
	m_pfnOut32 = (Out32)GetProcAddress(m_hDll,_T("Out32"));
	m_pfnInp32 = (Inp32)GetProcAddress(m_hDll,_T("Inp32"));
}