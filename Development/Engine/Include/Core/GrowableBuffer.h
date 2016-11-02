#pragma once


namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Basic
	*  @{
	*/


	/** 
		�Զ��쳤����
		@remark
			���չ̶������Զ�����������洢����
		@par
			����ʹ��vector/array�ȵĲ�͸��ʵ����ɵĽṹ���㷨���Ӷ����
		@param
			TType Ԫ������
		@param
			ALLOC_STEP ���䲽��
	*/
	template <class TType, dword ALLOC_STEP >
	class growable_buffer
	{
	public:
		TType*	mTypeData;
		dword	mAllocedSize;
		dword	mDataSize;

		growable_buffer( )
			: mTypeData( null )
			, mAllocedSize( 0 )
			, mDataSize( 0 )
		{
		
		}

		~growable_buffer( )
		{
			clear();
		}

		/** 
			��ȡ����ָ��
			@return
				��ȡ�����ַ
		*/
		void* getdata( ) const
		{
			return mTypeData;
		}

		/** 
			��ȡָ��������Ԫ������
			@param
				index ����
			@return
				Ԫ������
		*/
		TType& operator [] ( dword index )
		{
			return *at( index );
		}

		/** 
			��ȡָ��������Ԫ��ָ��
			@param
				index ����
			@return
				Ԫ��ָ�룬��Ԫ�ز����ڣ�����null
		*/
		TType* at( dword index )
		{
			// �ڷ�Χ��,ȡԭ����
			if ( index < mAllocedSize )
				return mTypeData + index;

			// ����, �ҵ�һ�����ʲ���
			dword finalsize = mAllocedSize;
			while ( index >= finalsize )
			{
				finalsize += ALLOC_STEP;
			}
			
			// ���·����ڴ�
			resize( finalsize );

			return mTypeData + index;
		}

		/** 
			����һ����Ԫ��
			@return
				���ظ�����Ԫ�ص�ָ��
		*/
		TType* push_advance( )
		{
			return at( mDataSize++ );
		}

		/** 
			����һ����Ԫ��
			@param
				data ��һ����Ԫ�ؿ�������������ڴ���
		*/
		void push_advance( const TType& data )
		{
			*at( mDataSize++ ) = data;
		}

		/** 
			��û����С
			@return
				��û����С
		*/
		dword size( ) const
		{
			return mDataSize;
		}

		/** 
			���û����С
						
		*/
		void reset( )
		{
			mDataSize = 0;
		}

		/** 
			����ڴ�
			@note
				�����������ͷ��ڴ棬�����������
		*/
		void clear( )
		{
			for ( dword i = 0;i< mAllocedSize;i++)
			{
				type_destructor( mTypeData + i );
			}

			free( mTypeData );
			mTypeData = null;
			mAllocedSize = 0;
			mDataSize = 0;
		}

	private:
		void resize( dword newsize )
		{
			for ( dword i = 0;i< mAllocedSize;i++)
			{
				type_destructor( mTypeData + i );
			}

			mTypeData = (TType*)realloc( mTypeData, sizeof(TType) * newsize );
			mAllocedSize = newsize;

			for ( dword i = 0;i< mAllocedSize;i++)
			{
				type_constructor( mTypeData + i );
			}
		}
	};

	/** @} */
	/** @} */
}