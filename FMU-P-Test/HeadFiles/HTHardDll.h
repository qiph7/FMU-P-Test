#ifndef _HT_HARD_DLL_H
#define _HT_HARD_DLL_H

#ifndef DLL_API
#define DLL_API extern "C" __declspec(dllimport)
#endif
#define WIN_API __stdcall


typedef struct _HT_RELAY_CONTROL
{
	BOOL bCHEnable[4];
	WORD nCHVoltDIV[4];
	WORD nCHCoupling[4];
	BOOL bCHBWLimit[4];
	WORD nTrigSource;
	BOOL bTrigFilt;
	WORD nALT;
}RELAYCONTROL,*PRELAYCONTROL;

typedef struct _HT_CONTROL_DATA
{
	WORD nCHSet;
	WORD nTimeDIV;
	WORD nTriggerSource;
	WORD nHTriggerPos;
	WORD nVTriggerPos;
	WORD nTriggerSlope;
	ULONG nBufferLen;
	ULONG nReadDataLen;
	ULONG nAlreadyReadLen;
	WORD nALT;
	WORD nETSOpen;
	WORD nDriverCode;
		
}CONTROLDATA,*PCONTROLDATA;

DLL_API WORD WINAPI dsoHTSearchDevice(short* pDevInfo);

DLL_API WORD WINAPI dsoHTDeviceConnect(WORD nDeviceIndex);

DLL_API BOOL WINAPI dsoSetUSBBus(WORD nDeviceIndex);

DLL_API BOOL WINAPI dsoGetDeviceSN(WORD DeviceIndex,UCHAR* pBuffer);

DLL_API WORD WINAPI dsoGetDriverVersion(WORD DeviceIndex,UCHAR* pBuffer);

DLL_API WORD WINAPI dsoHTSetCHPos(WORD nDeviceIndex,WORD* pLevel,WORD nVoltDIV,WORD nPos,WORD nCH,WORD nDriverCode);

DLL_API WORD WINAPI dsoHTSetVTriggerLevel(WORD nDeviceIndex,WORD* pLevel,WORD nPos,WORD nDriverCode);

DLL_API WORD WINAPI dsoHTSetHTriggerLength(WORD nDeviceIndex,ULONG nBufferLen,WORD HTriggerPos,WORD nTimeDIV,WORD nYTFormat);

DLL_API WORD WINAPI dsoHTSetCHAndTrigger(WORD nDeviceIndex,PRELAYCONTROL pRelayControl,WORD nDriverCode);

DLL_API WORD WINAPI dsoHTSetTriggerAndSyncOutput(WORD nDeviceIndex,WORD nTriggerMode,WORD nTriggerSlope,WORD nPWCondition,ULONG nPW,USHORT nVideoStandard,USHORT nVedioSyncSelect,USHORT nVideoHsyncNumOption,WORD nSync);

DLL_API WORD WINAPI dsoHTSetSampleRate(WORD nDeviceIndex,WORD nTimeDIV,WORD nYTFormat);

DLL_API WORD WINAPI dsoHTStartCollectData(WORD nDeviceIndex);

DLL_API WORD WINAPI dsoHTStartTrigger(WORD nDeviceIndex);

DLL_API WORD WINAPI dsoHTForceTrigger(WORD nDeviceIndex);

DLL_API WORD WINAPI dsoHTGetState(WORD nDeviceIndex);

DLL_API WORD WINAPI dsoHTReadCalibrationData(WORD nDeviceIndex,WORD* pLevel,WORD nLen);

DLL_API WORD WINAPI dsoSDGetData(WORD nDeviceIndex,WORD* pCH1Data,WORD* pCH2Data,WORD* pCH3Data,WORD* pCH4Data,PCONTROLDATA pControl,WORD nInsertMode);

DLL_API ULONG WINAPI dsoHTGetHardFC(WORD nDeviceIndex);

DLL_API WORD WINAPI dsoHTSetHardFC(WORD nDeviceIndex,WORD nType);

//Allow to Suspend
DLL_API WORD WINAPI dsoSDGetData_Suspend(WORD nDeviceIndex,WORD* pCH1Data,WORD* pCH2Data,WORD* pCH3Data,WORD* pCH4Data,PCONTROLDATA pControl,WORD nInsertMode,USHORT* nSuspend);


#endif
