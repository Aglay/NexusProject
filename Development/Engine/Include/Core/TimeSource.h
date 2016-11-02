#pragma once


namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Platform
	*  @{
	*/


	struct TimeData
	{
		word mYear;
		word mMonth;
		word mDayOfWeek;
		word mDay;
		word mHour;
		word mMinute;
		word mSecond;
		word mMilliSeconds;
	};

	/// ʱ��Դ
	class TimeSource
	{
	public:
		/// ��ʼ��
		static void	StaticInit( );

		/// ����
		static void	Tick( );

		/// ����ϴ���Ⱦ����ʱ��(ms)
		static float GetElapsedTime( );

		/// ȡ���Գ�ʼ�������ڵ�ʱ��(ms)
		static float GetAppTime( );

		/// ȡ�� ϵͳʱ��
		static void	GetLocalTime(TimeData& Data );

		/// ȡwindows tick time
		static dword GetTickTime( );
	};

	/// �Զ���ʱ������
	class TimeRuler
	{
	public:
		/// ��ʼ��ʱ
		TimeRuler( );

		/// ����Կ�ʼ�����ڻ��ѵ�ʱ��
		float GetCost( );

		/// �ֶ���ʼ��ʱ
		void Start( );

	private:
		float mStartTick;
	};

	/** @} */
	/** @} */
}