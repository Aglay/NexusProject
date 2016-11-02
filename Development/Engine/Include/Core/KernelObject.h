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
		����ϵͳ���Ķ���
	*/
	class KernelObject
	{
	protected:
		
		handle		mObjectHandle;

	public:
		/// ���캯��
		KernelObject( );
		
		/// ��ֵ���캯��
		KernelObject( handle objecthandle );
		
		/// �������캯��
		KernelObject( const KernelObject& kernelobject );
		
		/// ��������
		~KernelObject( );

		/// ��ֵ����
		KernelObject& operator = ( const KernelObject& kernelobject );

		/// ����ת��
		inline operator handle ( ) const;

		/// �رն���
		void Close( );

		/// ��ֵһ�����
		handle CloneHandle( ) const;

		/// ��֤����Ƿ���Ч
		inline bool Valid( ) const;
	};



	KernelObject::operator handle ( ) const
	{
		return mObjectHandle;
	}

	bool KernelObject::Valid( ) const
	{
		return mObjectHandle != null;
	}

	/** @} */
	/** @} */
};