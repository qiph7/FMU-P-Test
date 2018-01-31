// Hard.h: interface for the CHard class.
//
//////////////////////////////////////////////////////////////////////
#include <Windows.h>

#if !defined(AFX_HARD_H__9C4B6FA6_38DA_46DD_84A9_790E05FFA5C4__INCLUDED_)
#define AFX_HARD_H__9C4B6FA6_38DA_46DD_84A9_790E05FFA5C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HeadFiles\\HTDisplayDll.h"
#include "HeadFiles\\HTHardDll.h"
#include "HeadFiles\\HTLANDll.h"

//Import Draw DLL
#pragma comment(lib,"Lib\\HTDisplayDll.lib")

//Import Hard DLL
#pragma comment(lib,"Lib\\HTHardDll.lib")

//Import Lan DLL
#pragma comment(lib,"Lib\\HTLANDll.lib")

//Driver Version define
#define DRIVER_CODE_FIRST			0		//The Driver for Old Board
#define DRIVER_CODE_SECOND			1		//The Driver for New Board

#define MAX_DATA					255
#define BUF_10K_LEN					4000000	//采样长度，即采样点数
#define CH1							0
#define CH2							1
#define CH3							2
#define CH4							3
#define MAX_CH_NUM					4
#define CAL_LEVEL_LEN				400
#define DC							0
#define AC							1
#define GND							2
#define X1							0
#define X10							1
#define X100						2
#define X1000						3
#define EDGE						0
#define RISE						0
#define FALL						1
#define AUTO						0
#define NORMAL						1
#define SINGLE						2


class CHard  
{
public:
	CHard();
	virtual ~CHard();
//Attributes
public:
	USHORT m_nDeviceIndex;
	UCHAR m_chVersion[20];
	UCHAR m_chSerialNo[20];
	USHORT m_nDeviceNum;
	USHORT m_nComType;//0:USB; 1:LAN
	short* m_pSrcData[MAX_CH_NUM];//读取的数据减去零电平的位置(-255 ~ 255)
	USHORT m_nCalLevel[CAL_LEVEL_LEN];//Cal Level
	USHORT m_nTimeDIV;
	USHORT m_nYTFormat;
	CONTROLDATA m_stControl;
	RELAYCONTROL RelayControl;
	USHORT m_nTriggerMode;
	USHORT m_nTriggerSweep;
	USHORT m_nTriggerSlope;
	USHORT m_nLeverPos[MAX_CH_NUM];
	COLORREF m_clrRGB[MAX_CH_NUM];
	//
	USHORT m_nReadOK;//本次读数据是否正确,0,不正确；非0不正确。
//Operations
public:
	void Init();
	int InitLAN();
	void ReadData();
	void CHard::SourceToDisplay(USHORT* pData,ULONG nDataLen,USHORT nCH);

	static USHORT m_nReadData[MAX_CH_NUM][BUF_10K_LEN];
	BOOL m_bStartNew;//是否启动新一次采集
	USHORT m_nAutoTriggerCnt;

	void printData();
	void CollectData();

	enum TimeDIV
	{
		TIME_DIV_5NS,
		TIME_DIV_10NS,
		TIME_DIV_20NS,
		TIME_DIV_50NS,
		TIME_DIV_100NS,
		TIME_DIV_200NS,
		TIME_DIV_500NS,
		TIME_DIV_1US,
		TIME_DIV_2US,
		TIME_DIV_5US,
		TIME_DIV_10US,
		TIME_DIV_20US,
		TIME_DIV_50US,		// 采样率 20M
		TIME_DIV_100US,		// 采样率 10M
		TIME_DIV_200US,		// 采样率 5M
		TIME_DIV_500US,		// 采样率 2M
		TIME_DIV_1MS,		// 采样率 1M
		TIME_DIV_2MS,
		TIME_DIV_5MS,
		TIME_DIV_10MS,
		TIME_DIV_20MS,
		TIME_DIV_50MS,
		TIME_DIV_100MS,
		TIME_DIV_200MS,
		TIME_DIV_500MS,
		TIME_DIV_1S,
		TIME_DIV_2S,
		TIME_DIV_5S,
		TIME_DIV_10S,
		TIME_DIV_20S,
		TIME_DIV_50S,
		TIME_DIV_100S,
		TIME_DIV_200S,
		TIME_DIV_500S,
		TIME_DIV_1000S,
	};

	enum VoltDIV
	{
		VOLT_DEV_10MV,
		VOLT_DEV_20MV,
		VOLT_DEV_50MV,
		VOLT_DEV_100MV,
		VOLT_DEV_200MV,
		VOLT_DEV_500MV,
		VOLT_DEV_1V,
		VOLT_DEV_2V,
		VOLT_DEV_5V,
	};
};

#endif // !defined(AFX_HARD_H__9C4B6FA6_38DA_46DD_84A9_790E05FFA5C4__INCLUDED_)
