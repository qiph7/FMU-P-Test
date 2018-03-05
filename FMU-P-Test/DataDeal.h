#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "Hard.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NUM_WINDOW					(400)		// 时间窗个数
#define NUM_CIRCLE					(40)		// 工频周波数
#define NUM_PER_WIN					(BUF_10K_LEN/NUM_WINDOW/NUM_CIRCLE)		// 每个时间窗采样点数

class CDataDeal  
{
public:
	CDataDeal();
	//virtual ~CDataDeal();

	static USHORT m_nDataSam[MAX_CH_NUM][NUM_WINDOW];
	static FLOAT  m_fDatadBm[MAX_CH_NUM][NUM_WINDOW];

	std::vector<FLOAT> m_fAK;
	std::vector<FLOAT> m_fKK;

public:
	void filtData();
	void dBmData();
	FLOAT samTodBm(FLOAT sam);
	void printFiltData();
	void printdBmData();

private:
	BOOL readBiaoding();
};