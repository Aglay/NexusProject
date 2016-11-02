#pragma once
 
namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Stream
	*  @{
	*/

	/** 
		ջ�ڴ���
	*/
	class StackStream : public DataStream
	{
	public:
		enum{
			DEFAULT_PREALLOC_SIZE = 4096, ///< Ĭ�Ϸ����ջ��С
		};

		StackStream( );

		/** 
			���ڴ�д�뵽ջ��
		*/
		StackStream( const void* data, dword size );
		
		virtual char*	GetBuffer( );

		virtual char*	AllocBuffer( dword size );

	protected:
		char mStackData[DEFAULT_PREALLOC_SIZE];
	};

	/** @} */
	/** @} */
}