#include <iostream>

#include "DllDrvInpout32.h"
#include "tchar.h"

using namespace std;

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

BOOL CDllDrvInpout32::setFreq(short freq)
{
	if (freq < 0 || freq>255)
	{
		cout << "ÊäÈë·¶Î§´íÎó" << endl;
		return FALSE;
	}
	m_pfnOut32(LPT_DATA_ADDR, freq);
	return TRUE;
}