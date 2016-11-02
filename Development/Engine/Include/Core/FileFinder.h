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
		�ļ������¼�
	*/
	class FindFileListener
	{
	public:
		/** 
			�ҵ�һ���ļ�
			@param
				path ·��
			@param
				name �ļ���
			@return
				true��ʾ����������falseֹͣ����
		*/
		virtual bool OnFindFile( const wchar* path, const wchar* name ){ return true; }

		/** 
			�ҵ�һ���ļ���
			@param
				path ·��
			@param
				recursive �Ƿ�ݹ�
			@return
				true��ʾ����������falseֹͣ����
		*/
		virtual bool OnFindDirectory( const wchar* path , bool& recursive ){ return true; }
	};


	/** 
		�ļ��ݹ�������
	*/
	class FileFinder
	{	
	public:
		struct FileInfo
		{
			WString	mName;
			dword	mSize;
			dword	mAttributes;
		};

		enum FileAttributes
		{
			Attribute_ReadOnly		= 0x00000001,
			Attribute_Hiden			= 0x00000002,
			Attribute_System		= 0x00000004,
			Attribute_Directory		= 0x00000010,
			Attribute_Archive		= 0x00000020,
			Attribute_Normal		= 0x00000080,
		};

		FileFinder( );
		~FileFinder( );

		/** 
			���ҵ�һ���ļ�
			@param
				filename Ҫ���ҵ��ļ�����һ��ʹ�����磺 c:\folder\*
			@param
				fileinfo ���ҵ����ļ���Ϣ
			@return
				�Ƿ��ҵ��ļ�
		*/
		bool FindFirst( const wchar* filename, FileInfo& fileinfo );

		/** 
			������һ���ļ�
			@param
				fileinfo ���ҵ����ļ���Ϣ
			@return
				�Ƿ��ҵ��ļ�
		*/
		bool FindNext( FileInfo& fileinfo );

		/** 
			����Ŀ¼
			@param
				dir �ļ�����
			@param
				listener �����е��¼��ص�
		*/
		static void ScanDirectory( const wchar* dir, FindFileListener* listener );

	private:
		handle		mFinderHandle;

	};


	/** @} */
	/** @} */
}