#pragma once

namespace NekoEngine
{

	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Platform
	*  @{
	*/

	/** 
		ͬ������
	*/
	class SyncObject : public KernelObject
	{
	public:
		/** 
			�ȴ������׳��ź�,Ȼ�����
			@param
				��ʱʱ��,����,-1��ʾһֱ
			@return
				true��ʾ�����Ѿ������ź�
		*/
		bool Wait( dword milliseconds = -1 );
	};


	/**
		�ź���
	*/
	class EventObject : public SyncObject
	{
	public:

		/**
			����һ���ź�������
			@param
				manualreset �����ź������ֶ����û����Զ�����
			@param
				initialstate �ź�����ʼ״̬��true�����ѱ�����
			@param
				objectname ������Ϊnull���ź�������
			@return
				�����Ƿ�ɹ�
		*/
		bool Create( bool manualreset, bool initialstate, const wchar* objectname = null );

		/**
			��һ���Ѿ��������źŶ���
			@param 
				objectname �¼���������
			@return
				���Ƿ�ɹ�
		*/
		bool Open( const wchar* objectname );

		/**
			�����ź���
			@return
				�����Ƿ�ɹ�
		*/
		bool Set( );

		/**
			ȡ�������ź���
			@return
				�����Ƿ�ɹ�
		*/
		bool Reset( );


		/**
			�����ź���,Ȼ���ڻ��������̺߳�����	
			@return
			�����Ƿ�ɹ�
		*/
		bool Pulse( );
	};

	//----------------------------------------------------------------------------
	// Mutex
	//----------------------------------------------------------------------------

	//! This class represents a mutex object, used for threads synchronization in system.

	//! A mutex object is a synchronization object whose state is set to signaled when it is not
	//! owned by any thread, and nonsignaled when it is owned.
	class MutexObject : public SyncObject
	{
	public:
		//! Create a mutex object with or without a name, if it is alread existed then copy the object handle.
		//! @param		initialowner	Whether the calling thread obtains the initial ownership of the mutex.
		//! @param		objectname		The name of mutex object, can be null indicates no name needed.
		//! @return		True indicates success, false indicates failure.
		bool Create( bool initialowner, const wchar* objectname = null );
		//! Open an existing named mutex object.
		//! @param		objectname		The name of mutex object, case-sensitive.
		//! @return		True indicates success, false indicates failure.
		bool Open( const wchar* objectname );

		//! Releases ownership of themutex object, then it can be obtained by other threads.
		//! @param		none
		//! @return		True indicates success, false indicates failure.
		bool Release( );
	};

	//----------------------------------------------------------------------------
	// Semaphore
	//----------------------------------------------------------------------------

	//! This class represents a semaphore object, used for threads synchronization in system.

	//! A semaphore object is a synchronization object that maintains a count between zero and a
	//! specified maximum value. The count is decremented each time a thread completes a wait for
	//! the semaphore object and incremented each time a thread releases the semaphore. When the
	//! count reaches zero, no more threads can successfully wait for the semaphore object state
	//! to become signaled. The state of a semaphore is set to signaled when its count is greater
	//! than zero, and nonsignaled when its count is zero.
	class SemaphoreObject : public SyncObject
	{
	public:
		//! Create a semaphore object with or without a name, if it is alread existed then copy the object handle.
		//! @param		initialcount	The initial count for the semaphore object
		//! @param		maximumcount	The maximum count for the semaphore object.
		//! @param		objectname		The name of semaphore object, can be null indicates no name needed.
		//! @return		True indicates success, false indicates failure.
		bool Create( dword initialcount, dword maximumcount, const wchar* objectname = null );
		//! Open an existing named semaphore object.
		//! @param		objectname		The name of semaphore object, case-sensitive.
		//! @return		True indicates success, false indicates failure.
		bool Open( const wchar* objectname );

		//! Increases usable count for the semaphore object, then it can be obtained by other threads.
		//! @param		releasecount	Amount by which the semaphore object's current count is to be increased.
		//! @return		True indicates success, false indicates failure.
		bool Release( dword releasecount = 1 );
	};

	//----------------------------------------------------------------------------
	// Timer
	//----------------------------------------------------------------------------

	//! This class represents a timer object, used for threads synchronization in system.

	//! A timer object is a synchronization object whose state is set to signaled when the specified
	//! due time arrives. There are two types of timers that can be created: manual-reset and synchronization.
	//! A timer of either type can also be a periodic timer.
	class TimerObject : public SyncObject
	{
	public:
		//! Create a timer object with or without a name, if it is alread existed then copy the object handle.
		//! @param		manualreset		Whether the timer object is manual-reset or synchronization.
		//! @param		objectname		The name of timer object, can be null indicates no name needed.
		//! @return		True indicates success, false indicates failure.
		bool Create( bool manualreset, const wchar* objectname = null );
		//! Open an existing named timer object.
		//! @param		objectname		The name of timer object, case-sensitive.
		//! @return		True indicates success, false indicates failure.
		bool Open( const wchar* objectname );

		//! Activates the timer, sets the interval and period time of it.
		//! @param		interval		The time-out interval of the timer in milliseconds.
		//!	@param		period			The period of the timer, in milliseconds.
		//! @return		True indicates success, false indicates failure.
		//! @remarks	If period parameter is zero, the timer is signaled once, otherwise it is periodic.
		//!				A periodic timer automatically reactivates each time the period elapses, until the timer
		//!				is canceled using the Cancel function.
		bool SetInterval( dword interval, dword period );
		//! Sets the timer to inactive state.
		//! @param		none
		//! @return		True indicates success, false indicates failure.
		bool Cancel( );
	};

	/** @} */
	/** @} */
};