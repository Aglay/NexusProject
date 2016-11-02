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
		���ڴ���
	*/
	class HeapStream : public DataStream
	{
	public:
		enum{
			ALIGN_ALLOC_STEP = 1024, ///< Ĭ�Ϸ��䲽��
		};

		/** 
			���캯��
			@param
				prealloc Ԥ�����С
		*/
		HeapStream( dword prealloc = 0 );

		/** 
			�ͷ��ڴ�
		*/
		virtual ~HeapStream( );

		/** 
			������д�뵽��
			@param
				data ����
			@param
				size д������ݴ�С
		*/
		HeapStream( const void* data, dword size );

		/** 
			������д�뵽��
			@param
				m �ڴ���
			@param
				extendbuffersize ���������ڴ��С
			@remark
				ʹ��Heap����FileStream����ΪANSI�ַ�����ʱ��Ӧ������buffersize+1
		*/
		HeapStream( DataStream* m, dword extendbuffersize = 0 );

		/** 
			ȡ�û����ַ
		*/
		virtual char*	GetBuffer( );

		/** 
			���仺��
			@param
				size Ҫ�����С
			@return
				���ط���õĴ�С
		*/
		virtual char*	AllocBuffer( dword size );

		/** 
			�ͷŷ���Ļ���
		*/
		virtual void	ReleaseBuffer( );

		/// ���������кŲ���������
		friend BinarySerializer& operator <<( NekoEngine::BinarySerializer& Ser, HeapStream*& Data )
		{
			DataStream* Stream = Ser.GetStream();
			
			if ( Ser.IsLoading() )
			{
				Data = new HeapStream;
				dword BufferSize = 0;
				Stream->ReadTypes<dword>( BufferSize );

				if ( BufferSize > 0 )
					Stream->ReadBuffer( Data, BufferSize );
			}
			else
			{
				Stream->WriteTypes<dword>( Data->GetSize() );
				Stream->WriteBuffer( Data );
			}
				
			return Ser;
		}

		/// ���������кŲ���������
		friend BinarySerializer& operator <<( NekoEngine::BinarySerializer& Ser, HeapStream& Data )
		{
			DataStream* Stream = Ser.GetStream();

			if ( Ser.IsLoading() )
			{
				dword BufferSize = 0;
				Stream->ReadTypes( BufferSize );

				if ( BufferSize > 0 )
					Stream->ReadBuffer( &Data, BufferSize );
			}
			else
			{
				Stream->WriteTypes<dword>( Data.GetSize() );
				Stream->WriteBuffer( &Data );
			}

			return Ser;
		}

	protected:
		char* mHeapData;		// ��̬�������
	};

	/** @} */
	/** @} */
}