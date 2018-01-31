// ���� SDKDDKVer.h ��������õ���߰汾�� Windows ƽ̨��  
// ���ҪΪ��ǰ�� Windows ƽ̨����Ӧ�ó�������� WinSDKVer.h������  
// WIN32_WINNT ������ΪҪ֧�ֵ�ƽ̨��Ȼ���ٰ��� SDKDDKVer.h��  
// �޸����п⣨�����п��޸�Ϊ"���̣߳�/MT��"��
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

	std::cout << "�ɼ�����ʼ����ʼ" << std::endl;
	short nDevInfo[MAX_USB_DEV_NUMBER];
	hard.m_nDeviceNum = dsoHTSearchDevice(nDevInfo);
	if(hard.m_nDeviceNum > 0)
	{
		hard.Init();
	}
	else
	{
		std::cout << "�ɼ�����ʼ������" << std::endl;
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
		std::cout << "��ʼһ�β���" << i << std::endl;

		hard.CollectData();
		hard.printData();

		deal.filtData();
		deal.printFiltData();

		deal.dBmData();
		deal.printdBmData();
	}

	std::cout << "�����˳�" << std::endl;
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