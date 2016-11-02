#include "CorePCH.h"
#include "NekoCore_Stream.h"

namespace NekoEngine
{
	StackStream::StackStream( )
	{
		mAllocedSize = DEFAULT_PREALLOC_SIZE;
	}

	StackStream::StackStream( const void* data, dword size	)
	{
		mAllocedSize = DEFAULT_PREALLOC_SIZE;
		WriteBuffer( data, size );
	}

	char* StackStream::GetBuffer() 
	{
		return mStackData;
	}

	char* StackStream::AllocBuffer( dword size )
	{
		// �ڴ�������,���������2������
		dword newalloc = mDataSize + size;//Math::Align(mDataSize + size, ALIGN_ALLOC_STEP );

		// û������Ҫ����ʱ��ʹ��ԭ���Ѿ�������Ŀռ�
		if ( newalloc < mAllocedSize && mAllocedSize > 0)
		{
			return mStackData;
		}

		Assert( "Out of StackStream DEFAULT_PREALLOC_SIZE");

		return null;
	}

}