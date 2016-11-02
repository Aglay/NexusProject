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
		�ٽ�������
		@remark
			�����߳�ͬ��
	*/
	class LockObject
	{
	private:
		/// Ϊwin32 api ����
		_byte	mReserved[24];
		bool	mEnable;

	public:
		/// ���캯��
		LockObject( );
		
		/// ��������
		~LockObject( );

		/// ����
		void Enable( bool enable );

		/// �����ٽ���
		void Enter( ) const;
		
		/// �뿪�ٽ���
		void Leave( ) const;

		/** 
			���Խ����ٽ���
			@return
				true��ʾ�����߳�ӵ���ٽ�����false��ʾû��
		*/
		bool TryEnter( ) const;

		static int IncrementLock( volatile int* Value);

		static int DecrementLock( volatile int* Value);
	};

	/** 
		�Զ��ٽ���
	*/
	class LockOwner
	{
	private:
		const LockObject&	mLock;

	public:
		/// ����ʱ�Զ������ٽ���
		LockOwner( const LockObject& lock );
		
		/// ����ʱ�Զ��뿪�ٽ���
		~LockOwner( );
	};

	/** @} */
	/** @} */
};