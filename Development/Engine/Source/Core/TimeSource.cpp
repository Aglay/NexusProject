#include "CorePCH.h"
#include <time.h>
#include "NekoCore_Platform.h"

namespace NekoEngine
{
	LONGLONG		GTicksPerSec;		//ÿ���Ƶ��
	LONGLONG		GLastElapsedTime;	//QPFʹ�õ��ϴμ���ʱ��
	LARGE_INTEGER	GInitTime;
	LARGE_INTEGER	GAbsTime;
	float			GElapsedTime;

	//////////////////////////////////////////////////////////////////////////
	// TimeSource
	//////////////////////////////////////////////////////////////////////////
	void TimeSource::StaticInit( )
	{
		LARGE_INTEGER qwTicksPerSec;
		::QueryPerformanceFrequency( &qwTicksPerSec );
		GTicksPerSec = qwTicksPerSec.QuadPart;
		::QueryPerformanceCounter( &GInitTime );//��¼����ʱ��
		GLastElapsedTime = GInitTime.QuadPart;
		GElapsedTime = 0.2f;
	}

	float TimeSource::GetElapsedTime( )
	{
		return GElapsedTime;
	}

	void TimeSource::Tick( )
	{
		LARGE_INTEGER qwTime;
		::QueryPerformanceCounter( &qwTime );
		GElapsedTime = 1000 * (float) ( qwTime.QuadPart - GLastElapsedTime ) / (float) GTicksPerSec;
		GLastElapsedTime = qwTime.QuadPart;

	}

	float TimeSource::GetAppTime( )
	{
		::QueryPerformanceCounter( &GAbsTime );
		return float((GAbsTime.QuadPart- GInitTime.QuadPart)/(float)GTicksPerSec*1000);
	}


	void TimeSource::GetLocalTime(TimeData& Data)
	{
		::GetLocalTime( (LPSYSTEMTIME)&Data );		
	}

	NekoEngine::dword TimeSource::GetTickTime()
	{
		return ::GetTickCount();
	}

	//////////////////////////////////////////////////////////////////////////
	// TimeRuler
	//////////////////////////////////////////////////////////////////////////
	TimeRuler::TimeRuler( )
	{
		Start();
	}

	float TimeRuler::GetCost()
	{
		return TimeSource::GetAppTime() - mStartTick;
	}

	void TimeRuler::Start()
	{
		mStartTick = TimeSource::GetAppTime();
	}

}
