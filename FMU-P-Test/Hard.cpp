// Hard.cpp: implementation of the CHard class.
//
//////////////////////////////////////////////////////////////////////
#include <iostream>
#include "Hard.h"
#include <iomanip>

//#ifdef _DEBUG
//#undef THIS_FILE
//static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
//#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHard::CHard()
{
	ULONG i = 0;
	m_nDeviceIndex = 0;
	m_nDeviceNum = 0;
	for(i=0;i<MAX_CH_NUM;i++)
	{
		m_pSrcData[i] = new short[BUF_10K_LEN];
	}
	m_clrRGB[CH1] = RGB(255,255,0);
	m_clrRGB[CH2] = RGB(0,255,255);
	m_clrRGB[CH3] = RGB(255,0,255);
	m_clrRGB[CH4] = RGB(0,255,0);
	memset(m_nCalLevel,0,sizeof(m_nCalLevel));
	m_nTimeDIV = TIME_DIV_200US;			// 时基
	m_nYTFormat = 0;						// 3种采样格式。 0: Normal, 1: Scan, 2: Roll
	m_stControl.nCHSet = 0x0F;				// 第0-3位：表示 CH1-4 开或者关. 0:关， 1 开
	m_stControl.nTimeDIV = TIME_DIV_200US;	// 时基
	m_stControl.nTriggerSource = CH1;		// 触发源
	m_stControl.nHTriggerPos = 0;			// 水平触发位置，0~100%
	m_stControl.nVTriggerPos = 0;			// 垂直触发位置
	m_stControl.nTriggerSlope = RISE;		// 边沿触发触发沿
	m_stControl.nBufferLen = BUF_10K_LEN;	// 内存长度
	m_stControl.nReadDataLen = BUF_10K_LEN;	// 读取数据长度
	m_stControl.nAlreadyReadLen = BUF_10K_LEN;// Factory Setup
	m_stControl.nALT = 0;					//Factory Setup
	for(i=0;i<MAX_CH_NUM;i++)
	{
		RelayControl.bCHEnable[i] = 1;		// 开或者关. 0:关， 1 开
		RelayControl.nCHVoltDIV[i] = VOLT_DEV_500MV;	// 电压档位
		RelayControl.nCHCoupling[i] = DC;	// 耦合方式。DC 为 0； AC 为 1； GND 为 2；
		RelayControl.bCHBWLimit[i] = 0;		// 带宽限制。1 为打开带宽限制； 0 为关闭带宽限制
	}	
	RelayControl.nTrigSource = 5;			// 触发源。CH1 为 0； CH2 为 1； CH3 为 2； CH4 为 3；如果有外部触发，则 EXT为 5； 如果有 EXT/10 触发， 则取值为 6。
	RelayControl.bTrigFilt = 0;				// 高频抑制。取值： 1 表示打开高频抑制， 0 表示关闭高频抑制。
	RelayControl.nALT = 0;					// 是否交替。 取值： 1 为交替， 0 为非交替。
	m_nTriggerMode = EDGE;					// 触发模式，
	m_nTriggerSlope = RISE;
	m_nTriggerSweep = AUTO;
	m_nLeverPos[CH1] = 255;	// 64;
	m_nLeverPos[CH2] = 255;	// 96;
	m_nLeverPos[CH3] = 255;	// 160;
	m_nLeverPos[CH4] = 255;	// 192;
	//
	m_nReadOK = 0;
	m_nComType = 0;
	m_nAutoTriggerCnt = 0;
	m_bStartNew = TRUE;
}

CHard::~CHard()
{

}

USHORT CHard::m_nReadData[MAX_CH_NUM][BUF_10K_LEN];

void CHard::Init()
{
	m_nDeviceIndex = 0;
	if(m_nComType == 0)//USB
	{
		//Set USB Bus
		dsoSetUSBBus(m_nDeviceIndex);
		//Get Driver Version
		memset(m_chVersion,0,sizeof(m_chVersion));
		m_stControl.nDriverCode = dsoGetDriverVersion(m_nDeviceIndex,m_chVersion);
		//Get Device Serial No
		memset(m_chSerialNo,0,sizeof(m_chSerialNo));
		dsoGetDeviceSN(m_nDeviceIndex,m_chSerialNo);
		//Read Calibrate Data
		memset(m_nCalLevel,0,sizeof(m_nCalLevel));
		dsoHTReadCalibrationData(m_nDeviceIndex,m_nCalLevel,CAL_LEVEL_LEN);
		//Set Sample Rate to FPGA
		dsoHTSetSampleRate(m_nDeviceIndex,m_nTimeDIV,m_nYTFormat);
		//Set Relay Control for Channels and Trigger
		dsoHTSetCHAndTrigger(m_nDeviceIndex,&RelayControl,m_stControl.nDriverCode);
		//Set Trigger State and Sync Output
		dsoHTSetTriggerAndSyncOutput(m_nDeviceIndex,m_nTriggerMode,m_nTriggerSlope,0,2,0,0,1,0);
		//Set Channels' Zero Level or GND Level
		for(int i=0;i<MAX_CH_NUM;i++)
		{
			dsoHTSetCHPos(m_nDeviceIndex,m_nCalLevel,RelayControl.nCHVoltDIV[i],MAX_DATA-m_nLeverPos[i],i,m_stControl.nDriverCode);
		}
		//Set Trigger Level
		dsoHTSetVTriggerLevel(m_nDeviceIndex,m_nCalLevel,MAX_DATA-m_nLeverPos[CH1],m_stControl.nDriverCode);
		//Set Memory Buffer Size
		dsoHTSetHTriggerLength(m_nDeviceIndex,m_stControl.nBufferLen,m_stControl.nHTriggerPos,m_nTimeDIV,m_nYTFormat);
	}
	else//LAN/WIFI
	{
	//	m_stControl.nDriverCode = DRIVER_CODE_FIRST;	//LAN Only for Old Board
		memset(m_chVersion,0,sizeof(m_chVersion));
		m_stControl.nDriverCode = dsoLANGetDriverVersion(m_nDeviceIndex,m_chVersion);
		dsoLANReadCalibrationData(m_nDeviceIndex,m_nCalLevel,CAL_LEVEL_LEN,m_stControl.nDriverCode);
		dsoLANSetSampleRate(m_nDeviceIndex,m_nTimeDIV,m_nYTFormat);
		dsoLANSetCHAndTrigger(m_nDeviceIndex,&RelayControl,m_stControl.nDriverCode);
		dsoLANSetTriggerAndSyncOutput(m_nDeviceIndex,m_nTriggerMode,m_nTriggerSlope,0,2,0,0,1,0);
		for(int i=0;i<MAX_CH_NUM;i++)
		{
			dsoLANSetCHPos(m_nDeviceIndex,m_nCalLevel,RelayControl.nCHVoltDIV[i],MAX_DATA-m_nLeverPos[i],i,m_stControl.nDriverCode);
		}
		dsoLANSetVTriggerLevel(m_nDeviceIndex,m_nCalLevel,MAX_DATA-m_nLeverPos[CH1],m_stControl.nDriverCode);
		dsoLANSetHTriggerLength(m_nDeviceIndex,m_stControl.nBufferLen,m_stControl.nHTriggerPos,m_nTimeDIV,m_nYTFormat);
	}
}

int CHard::InitLAN()
{
	USHORT abcd[4] = {192,168,1,20};//192.168.1.20
	if(dsoLANInitSocket(m_nDeviceIndex,abcd,50000) != 1)
	{
		//AfxMessageBox(_T("InitLAN Fail!"));
		return 0;
	}
	return 1;
}

void CHard::ReadData()
{
	if(m_nComType == 0)
	{
		m_nReadOK = dsoSDGetData(m_nDeviceIndex,m_nReadData[CH1],m_nReadData[CH2],m_nReadData[CH3],m_nReadData[CH4],&m_stControl,2);
	}
	else
	{
		m_nReadOK = dsoSDLANGetData(m_nDeviceIndex,m_nReadData[CH1],m_nReadData[CH2],m_nReadData[CH3],m_nReadData[CH4],&m_stControl,2);
	}
	if(m_nReadOK == 1)
	{
		//printData();
		//SourceToDisplay(m_nReadData[i],m_stControl.nReadDataLen,i);
	}
	else
	{
		std::cout << "error: m_nReadOK=" << m_nReadOK << std::endl;
	}
}

void CHard::SourceToDisplay(USHORT* pData,ULONG nDataLen,USHORT nCH)
{
	for(ULONG i=0;i<nDataLen;i++)
	{
		*(m_pSrcData[nCH]+i) = *(pData+i) - (MAX_DATA - m_nLeverPos[nCH]);
	}
}

void CHard::printData()
{
	//USHORT nDataMax;
	//USHORT nDataMin;
	for(int nCh=0;nCh<MAX_CH_NUM;nCh++)
	{
		std::cout << "通道" << nCh << "：";
		for(ULONG i=0;i<10;i++)
		{
			std::cout << std::setw(6) << std::left << m_nReadData[nCh][BUF_10K_LEN/10*i] ;
		}
		//nDataMax = m_nReadData[nCh][0];
		//nDataMin = m_nReadData[nCh][0];
		//for(ULONG i=0;i<BUF_10K_LEN;i++)
		//{
		//	if( m_nReadData[nCh][i] > nDataMax )
		//		nDataMax = m_nReadData[nCh][i];
		//	if( m_nReadData[nCh][i] < nDataMin )
		//		nDataMin = m_nReadData[nCh][i];
		//}
		//std::cout << "Max " << std::setw(5) << std::left << nDataMax;
		//std::cout << "Min " << std::setw(5) << std::left << nDataMin;
		std::cout << std::endl;
	}
}

void CHard::CollectData()
{
	short nState = 0;

	if(m_bStartNew)
	{
		if(this->m_nComType == 0)
		{
			dsoHTStartCollectData(this->m_nDeviceIndex);
			dsoHTStartTrigger(this->m_nDeviceIndex);
		}
		else
		{
			dsoLANStartCollectData(this->m_nDeviceIndex);
			dsoLANStartTrigger(this->m_nDeviceIndex);
		}
		m_nAutoTriggerCnt = 0;
		m_bStartNew = FALSE;
	}
	Sleep(1000);		// 等待一会，以便得到正确的nState，否则dsoHTGetState可能返回0
	if(this->m_nComType == 0)
	{
		nState = dsoHTGetState(this->m_nDeviceIndex);
	}
	else
	{
		nState = dsoLANGetState(this->m_nDeviceIndex);
	}
	std::cout << "nState=" << nState << std::endl;
	if(nState == 1)// 1	
	{
		if(this->m_nTriggerSweep == AUTO)
		{
			if(this->m_nComType == 0)
			{
				dsoHTStartTrigger(this->m_nDeviceIndex);
			}
			else
			{
				dsoLANStartTrigger(this->m_nDeviceIndex);
			}
			m_nAutoTriggerCnt++;
			if(m_nAutoTriggerCnt > 5)//
			{
				if(this->m_nComType == 0)
				{
					dsoHTForceTrigger(this->m_nDeviceIndex);
				}
				else
				{
					dsoLANForceTrigger(this->m_nDeviceIndex);
				}
				m_nAutoTriggerCnt = 0;
			}
		}
	}
	else//
	{
		if(nState == 3)//---3	
		{
			;//
		}
		else if(nState == 7)//---7	
		{
			this->ReadData();
			m_bStartNew = TRUE;
			m_nAutoTriggerCnt = 0;
		}
	}
}