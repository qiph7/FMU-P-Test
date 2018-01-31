#include "Windows.h"

#define LPT_DATA_ADDR			0x378
#define LPT_STATE_ADDR			0x379
#define LPT_CONTROL_ADDR		0x37A

typedef void (WINAPI* Out32)(short PortAddr, short Data);	//定义指向dll中函数的函数指针
typedef char (WINAPI* Inp32)(short PortAddr);				//定义指向dll中函数的函数指针


class CDllDrvInpout32
{
public:
	CDllDrvInpout32();
	Out32 m_pfnOut32;
	Inp32 m_pfnInp32;
};