#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup System
	*  @{
	*/


	/** 
		�첽�����¼���
	*/
	class AsyncTask
	{
	public:
		AsyncTask( ) : mAsyncTaskFinished( false ){ }
		virtual ~AsyncTask() {}

		/// �����߳�,������
		virtual void OnAsyncTaskProcess() = 0;

		/// ��Ϸ�߳�, �������
		virtual void OnAsyncTaskFinished( ){}

		/// �첽�����Ƿ����
		bool IsAsyncTaskFinished( ){ return mAsyncTaskFinished; }

	protected:
		friend class AsyncTaskThread;
		bool mAsyncTaskFinished;
	};

	/** 
		�첽����ͬ����
	*/
	class AsyncTaskFence : public AsyncTask
	{
	public:
		AsyncTaskFence( bool AutoDeleteSelf = false );

		/** 
			���һ��ͬ�����������߳�
			һ�����������Լ�һ
			�ڼ����߳�ִ��������ָ���,���������Լ�һ
		*/
		void BeginFence( );

		/** 
			�ȴ�ͬ������ָ�ִ��
			@remark
				��������һֱ����ֱ��ǰ��ָ��ȫ����ִ�����
		*/
		void Wait( );

		/** 
			��û�ʣ�¶���ָ��
		*/
		dword GetNumPendingFences() const { return mNumFence; }

	private:
		virtual void OnAsyncTaskProcess();

		virtual void OnAsyncTaskFinished( );

	private:
		volatile dword mNumFence;
		bool mAutoDeleteSelf;
	};


	/** 
		�첽�����߳�
	*/
	class AsyncTaskThread
	{
	public:
		AsyncTaskThread( );

		/// ����첽����
		void Add( AsyncTask* task );

		/// ���첽������
		void Start( );

		/// ֹͣ�첽������
		void Stop( );

		/// ֪ͨ�첽�������
		void NotifyFinishedTask( );

		/// ��������ʣ�µ��첽����
		void Flush( );

		/// �첽�����Ƿ���Խ��д���
		bool IsEnable( );

		/// �жϵ�ǰ�Ƿ����첽�߳�
		bool IsInAsyncTaskThread( );

	public:

		void FinishLoading( AsyncTask* task );

	public:
		Thread		mThread;
		bool		mEnable;

		ringbuffer	mInQueue;
		ringbuffer	mOutQueue;

		AsyncTaskFence mFlushFence;
		
		EventObject		mAsyncTaskEvent;
	};

	extern AsyncTaskThread GAsyncTaskThread;

	/** @} */
	/** @} */
}
