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
		�ļ��в�����װ
	*/
	class Directory
	{
	public:
		/** 
			�ݹ鴴���ļ���
		*/
		static bool			Create( const wchar* pathname );

		/** 
			ȡ�õ�ǰ�ļ���
		*/
		static const wchar*	GetCurrent(void);

		/** 
			���õ�ǰ�ļ���
		*/
		static void			SetCurrent(const wchar* path);

		/** 
			ȡ���ļ���������·��
		*/
		static const wchar* GetFullPath(const wchar* file);

		/** 
			�ж�һ���ļ����Ƿ����
		*/
		static bool			Exists(const wchar* foldername);

		/** 
			�ж�һ���ļ����Ƿ��д
			@remark
				��ʹ���κ�api��ֱ��дһ����ʱ�ļ���
		*/
		static bool			IsWritable( const wchar* PathName );

		/** 
			���һ���ļ����Ƿ�Ϊ�����ļ���
		*/
		static bool			IsHidden( const wchar* FileName );
	};

	/** 
		�ļ�������ջ
	*/
	class DirectoryStack
	{
	public:
		DirectoryStack(const wchar* newPath);

		DirectoryStack( );

		void Caputure( );

		void Push( const wchar* newPath );

		~DirectoryStack( );
		
	private:
		WString mOldDirectory;
	};
}