// 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。  
// 如果要为以前的 Windows 平台生成应用程序，请包括 WinSDKVer.h，并将  
// WIN32_WINNT 宏设置为要支持的平台，然后再包括 SDKDDKVer.h。  
// 修改运行库（将运行库修改为"多线程（/MT）"）
#include <WinSDKVer.h>  
#define _WIN32_WINNT _WIN32_WINNT_WINXP  
#include <SDKDDKVer.h>  

#include <iostream>
#include <Windows.h>
#include <stdlib.h>

#include "Hard.h"
#include "DataDeal.h"
#include "DllDrvInpout32.h"

#define MAX_USB_DEV_NUMBER 64
void printDevInf(CHard &hard);

int main(int argc, char* argv[])
{
	CHard hard;

	std::cout << "采集卡初始化开始" << std::endl;
	short nDevInfo[MAX_USB_DEV_NUMBER];
	hard.m_nDeviceNum = dsoHTSearchDevice(nDevInfo);
	if(hard.m_nDeviceNum > 0)
	{
		hard.Init();
	}
	else
	{
		std::cout << "采集卡初始化错误" << std::endl;
		system("pause");
		exit(1);
	}

	printDevInf(hard);

	CDllDrvInpout32 inpout;
	(*(inpout.m_pfnOut32))(LPT_DATA_ADDR, 0x0);

	int i=0;
	CDataDeal deal;
	while( i++ < 1000 )
	{
		Sleep(1000);
		std::cout << "开始一次采样" << i << std::endl;

		hard.CollectData();
		hard.printData();

		deal.filtData();
		deal.printFiltData();

		deal.dBmData();
		deal.printdBmData();
	}

	std::cout << "程序退出" << std::endl;
	return 0;
}

void printDevInf(CHard &hard)
{
	std::cout << "m_nDeviceIndex\t" << hard.m_nDeviceIndex << std::endl;
	std::cout << "m_chVersion\t" << hard.m_chVersion << std::endl;
	std::cout << "m_chSerialNo\t" << hard.m_chSerialNo << std::endl;
	std::cout << "m_nDeviceNum\t" << hard.m_nDeviceNum << std::endl;
	std::cout << "m_nComType\t" << hard.m_nComType << std::endl;
	std::cout << "m_nTimeDIV\t" << hard.m_nTimeDIV << std::endl;
	std::cout << "m_nTriggerMode\t" << hard.m_nTriggerMode << std::endl;
	std::cout << "m_nTriggerSweep\t" << hard.m_nTriggerSweep << std::endl;
	std::cout << "m_nTriggerSlope\t" << hard.m_nTriggerSlope << std::endl;

}