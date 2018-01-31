#ifndef _HT_LAN_DLL_H_H
#define _HT_LAN_DLL_H_H

#ifndef DLL_API
#define DLL_API extern "C" __declspec(dllimport)
#endif
#define WIN_API __stdcall

#include "HTHardDll.h"

DLL_API WORD WINAPI dsoLANInitSocket(WORD nDeviceIndex,USHORT* pIP,USHORT iPort);

DLL_API WORD WINAPI dsoLANClose(WORD nDeviceIndex);

DLL_API WORD WINAPI dsoLANGetDriverVersion(WORD DeviceIndex,UCHAR* pBuffer);

DLL_API WORD WINAPI dsoLANSetCHPos(WORD nDeviceIndex,WORD* pLevel,WORD nVoltDIV,WORD nPos,WORD nCH,WORD nDriverCode);

DLL_API WORD WINAPI dsoLANSetVTriggerLevel(WORD nDeviceIndex,WORD* pLevel,WORD nPos,WORD nDriverCode);

DLL_API WORD WINAPI dsoLANSetHTriggerLength(WORD nDeviceIndex,ULONG nBufferLen,WORD HTriggerPos,WORD nTimeDIV,WORD nYTFormat);

DLL_API WORD WINAPI dsoLANSetCHAndTrigger(WORD nDeviceIndex,PRELAYCONTROL pRelayControl,WORD nDriverCode);

DLL_API WORD WINAPI dsoLANSetTriggerAndSyncOutput(WORD nDeviceIndex,WORD nTriggerMode,WORD nTriggerSlope,WORD nPWCondition,ULONG nPW,USHORT nVideoStandard,USHORT nVedioSyncSelect,USHORT nVideoHsyncNumOption,WORD nSync);

DLL_API WORD WINAPI dsoLANSetSampleRate(WORD nDeviceIndex,WORD nTimeDIV,WORD nYTFormat);

DLL_API WORD WINAPI dsoLANStartCollectData(WORD nDeviceIndex);

DLL_API WORD WINAPI dsoLANStartTrigger(WORD nDeviceIndex);

DLL_API WORD WINAPI dsoLANForceTrigger(WORD nDeviceIndex);

DLL_API WORD WINAPI dsoLANGetState(WORD nDeviceIndex);

DLL_API WORD WINAPI dsoLANReadCalibrationData(WORD nDeviceIndex,WORD* pLevel,WORD nLen,WORD nDriverCode);

DLL_API WORD WINAPI dsoSDLANGetData(WORD nDeviceIndex,WORD* pCH1Data,WORD* pCH2Data,WORD* pCH3Data,WORD* pCH4Data,PCONTROLDATA pControl,WORD nInsertMode);

DLL_API ULONG WINAPI dsoLANGetHardFC(WORD nDeviceIndex);

DLL_API WORD WINAPI dsoLANSetHardFC(WORD nDeviceIndex,WORD nType);

DLL_API WORD WINAPI dsoLANModeSetIPAddr(WORD DeviceIndex,ULONG nIP,ULONG nSubnetMask,ULONG nGateway,USHORT nPort,BYTE* pMac);

DLL_API WORD WINAPI dsoLANModeGetIPAddr(WORD DeviceIndex,ULONG* pIP,ULONG* pSubnetMask,ULONG* pGateway,USHORT* pPort,BYTE* pMac);

DLL_API WORD WINAPI dsoLANGetRestartLANStatus(WORD DeviceIndex);

DLL_API WORD WINAPI dsoLANOpenConnet(WORD DeviceIndex,WORD nMode);

#endif                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           