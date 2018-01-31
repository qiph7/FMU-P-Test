#include <iostream>

#include "DllDrvInpout32.h"
#include "tchar.h"

CDllDrvInpout32::CDllDrvInpout32()
{
	HMODULE m_hDll= LoadLibrary(_T("inpout32.dll"));

	if (m_hDll==NULL)
	{
		std::cout << "获取Inpout32.dll失败" << std::endl;
		system("pause");
		exit(1);
		//return;
	}
	std::cout << "获取Inpout32.dll成功" << m_hDll << std::endl;
	m_pfnOut32 = (Out32)GetProcAddress(m_hDll,_T("Out32"));
	m_pfnInp32 = (Inp32)GetProcAddress(m_hDll,_T("Inp32"));
	std::cout << m_pfnOut32 << std::endl;
	std::cout << m_pfnOut32 << std::endl;
	system("pause");
}