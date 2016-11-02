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
		�ļ�ʱ��ṹ
	*/
	struct FileTime 
	{
		dword mLowDateTime;
		dword mHighDateTime;

		bool operator == ( const FileTime& Other )
		{
			return memcmp( this, &Other, sizeof( FileTime ) ) == 0;
		}

		bool operator != ( const FileTime& Other )
		{
			return memcmp( this, &Other, sizeof( FileTime ) ) != 0;
		}
	};

	/** 
		�ļ�������
	*/
	class File
	{
	public:
		/** 
			�ж�һ���ļ��Ƿ����
		*/
		static bool		Exists(const wchar* FileName );

		/** 
			����ļ���С
		*/
		static dword	GetFileSize( const wchar* FileName );

		/** 
			����ļ��޸�ʱ��	
		*/
		static bool		GetFileModifyTime( const wchar* FileName, FileTime& Time );

		/** 
			ɾ���ļ�	
		*/
		static bool		Delete( const wchar* FileName );

		/** 
			����ļ��Ƿ�Ϊ�����ļ�	
		*/
		static bool		IsHidden( const wchar* FileName );
	};

	/** @} */
	/** @} */
}