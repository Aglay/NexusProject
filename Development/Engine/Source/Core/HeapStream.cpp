#include "CorePCH.h"
#include "NekoCore_Stream.h"
#include "NekoCore_Math.h"

namespace NekoEngine
{
	HeapStream::HeapStream( const void* data, dword size	)
		: mHeapData( null )
	{
		WriteBuffer( data, size );
	}

	HeapStream::HeapStream( DataStream* m, dword extendbuffersize )
		: mHeapData( null )
	{
		Assert( m != null );
		m->ReadBuffer( this, extendbuffersize );
	}

	HeapStream::HeapStream(dword prealloc )
		: mHeapData( null )
	{
		if ( prealloc > 0)
			AllocBuffer( prealloc );
	}

	HeapStream::~HeapStream()
	{
		ReleaseBuffer();
	}

	char* HeapStream::AllocBuffer( dword size )
	{	
		// �ڴ�������,���������2������
		dword newalloc = mDataSize + size;//Math::Align(mDataSize + size, ALIGN_ALLOC_STEP );

		// û������Ҫ����ʱ��ʹ��ԭ���Ѿ�������Ŀռ�
		if ( newalloc <= mAllocedSize )
		{
			return mHeapData;
		}

		// ��һ�δ�StackתΪHeap����Ҫ�ֶ�������
		if ( mHeapData == null )
		{
			mHeapData = (char*)::malloc( newalloc );
		}
		else
		{
			mHeapData = (char*)::realloc( mHeapData, newalloc );
		}

		mAllocedSize = newalloc;

		return mHeapData;
	}

	void HeapStream::ReleaseBuffer()
	{
		__super::ReleaseBuffer( );
		free( mHeapData );
		mHeapData = null;
		mAllocedSize = 0;
	}

	char* HeapStream::GetBuffer()
	{
		return mHeapData;
	}


}