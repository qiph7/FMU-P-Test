#include "DataDeal.h"
#include <iostream>
#include <iomanip>

CDataDeal::CDataDeal()
{
	m_fAK[0] = 84;
	m_fAK[1] = 96;
	m_fAK[2] = 109;
	m_fAK[3] = 156;
	m_fAK[4] = 171;
	m_fKK[0] = ( m_fAK[1] - m_fAK[0] ) / 10;
	m_fKK[1] = ( m_fAK[2] - m_fAK[1] ) / 10;
	m_fKK[2] = ( m_fAK[3] - m_fAK[2] ) / 30;
	m_fKK[3] = ( m_fAK[4] - m_fAK[3] ) / 10;
}

//CDataDeal::~CDataDeal()
//{
//
//}

USHORT CDataDeal::m_nDataSam[MAX_CH_NUM][NUM_WINDOW];
FLOAT  CDataDeal::m_fDatadBm[MAX_CH_NUM][NUM_WINDOW];

void CDataDeal::filtData()
{
	ULONG n=0;

	for(ULONG i=0; i<NUM_WINDOW; i++)
	{
		for(ULONG ch=0; ch<MAX_CH_NUM; ch++)
		{
			m_nDataSam[ch][i] = 0;
		}
	}

	for(ULONG cir=0; cir<NUM_CIRCLE; cir++)
	{
		for(ULONG win=0; win<NUM_WINDOW; win++)
		{
			for(ULONG i=0; i<NUM_PER_WIN; i++)
			{
				for(ULONG ch=0; ch<MAX_CH_NUM; ch++)
				{
					if (CHard::m_nReadData[ch][n] > m_nDataSam[ch][win]) 
					{
						m_nDataSam[ch][win] = CHard::m_nReadData[ch][n];
					}
				}
				n++;
			}
		}
	}
}

void CDataDeal::dBmData()
{
	for(ULONG win=0; win<NUM_WINDOW; win++)
	{
		for(ULONG ch=0; ch<MAX_CH_NUM; ch++)
		{
			m_fDatadBm[ch][win] = samTodBm((FLOAT)m_nDataSam[ch][win]);
		}
	}
}

FLOAT CDataDeal::samTodBm(FLOAT sam)
{
	FLOAT dBm;

	if( sam > m_fAK[3] )
	{
		dBm = (sam - m_fAK[3]) / m_fKK[3] - 30;
	}
	else if( sam > m_fAK[2] )
	{
		dBm = (sam - m_fAK[2]) / m_fKK[2] - 60;
	}
	else if( sam > m_fAK[1] )
	{
		dBm = (sam - m_fAK[1]) / m_fKK[1] - 70;
	}
	else
	{
		dBm = (sam - m_fAK[0]) / m_fKK[0] - 80;
	}
		
	return dBm;
	//Select Case (Sam)
 //       Case Is > Ak2(4)
 //       SamTodBm = (Sam - Ak2(4)) / Kk2(4) - 30 + RE272
 //       Case Ak2(3) To Ak2(4)
 //       SamTodBm = (Sam - Ak2(3)) / Kk2(3) - 60 + RE272
 //       Case Ak2(2) To (Ak2(3) - 0.0001)
 //       SamTodBm = (Sam - Ak2(2)) / Kk2(2) - 70 + RE272
 //       Case Is < Ak2(2)
 //       SamTodBm = (Sam - Ak2(1)) / Kk2(1) - 80 + RE272
 //   End Select
}

void CDataDeal::printFiltData()
{
	for(int nCh=0;nCh<MAX_CH_NUM;nCh++)
	{
		std::cout << "filt" << nCh << "£º";
		for(ULONG i=0;i<10;i++)
		{
			std::cout << std::setw(6) << std::left << m_nDataSam[nCh][NUM_WINDOW/10*i] ;
		}
		std::cout << std::endl;
	}
}

void CDataDeal::printdBmData()
{
	for(int nCh=0;nCh<MAX_CH_NUM;nCh++)
	{
		std::cout << "dBm" << nCh << "£º ";
		for(ULONG i=0;i<10;i++)
		{
			std::cout << std::setw(6)  << std::setprecision(3) << std::left << m_fDatadBm[nCh][NUM_WINDOW/10*i] ;
		}
		std::cout << std::endl;
	}
}