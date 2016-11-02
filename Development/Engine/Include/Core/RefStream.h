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
		����������
	*/
	class RefStream : public DataStream
	{
	public:
		RefStream( );

		/** 
			������Ҫ�����������
			@param
				data ��Ҫ���õ�����
			@param
				size ��Ҫ���õ����ݴ�С
		*/
		RefStream( const void* data, dword size	);

		/** 
			������Ҫ�������ݵ���
			@param
				m ��Ҫ���õ���
		*/
		RefStream( DataStream* m );

		/** 
			������Ҫ�������ݵ���
			@param
				m ��Ҫ���õ���
			@param
				numberOfBytes ָ��size
		*/
		RefStream( DataStream* m, dword numberOfBytes );

		virtual bool	WriteBuffer( const void* input, dword numberOfBytes );

		virtual char*	GetBuffer( );

		virtual char*	AllocBuffer( dword size );

		/// ���������л�����������
		friend BinarySerializer& operator <<( NekoEngine::BinarySerializer& Ser, RefStream& Data )
		{
			DataStream* Stream = Ser.GetStream();

			Assert( Ser.IsSaving() )		
			Stream->WriteTypes<dword>( Data.GetSize() );
			Stream->WriteBuffer( &Data );			

			return Ser;
		}

	protected:
		const char* mRefData;	// ���÷�ʽ��ȡ����
	};

	/** @} */
	/** @} */
}