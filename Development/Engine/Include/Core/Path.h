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
		·���ַ���������
	*/
	class Path
	{
	public:
		/** 
			��ȡ·���е��ļ�������
			@param
				fullpath ����·��
			@return
				�����ļ���
			@note
				c:\folder\c.bmp -> c.bmp
		*/
		static WString		GetFileName( const wchar* fullpath );

		/** 
			��ȡ·�����ļ�������
			@param
				fullpath ����·��
			@return
				�������һ���ļ�������
			@note
				c:\folder\c.bmp -> c:\folder
		*/
		static WString		GetDirectoryName( const wchar* fullpath, bool wholepath = true );

		/** 
			��ȡ·���е���չ��
			@param
				fullpath ����·��
			@return
				������չ��
			@note
				c:\folder\c.bmp -> .bmp
		*/

		static const wchar*	GetExtention( const wchar* fullpath );

		/** 
			���·���Ƿ�������·��
			@param
				fullpath ����·��
			@return
				�Ƿ�������·��
			@note
				���·������false
		*/
		static bool			IsFullpath( const wchar* fullpath );

		/** 
			���·���Ƿ����ļ���
			@param
				fullpath ����·��
			@return
				�Ƿ����ļ���
		*/

		static bool			IsDirecty( const wchar* fullpath );

		/** 
			���·���Ƿ������·��
			@param
				fullpath ��յ·��
			@return
				�Ƿ������·��
		*/

		static bool			IsRelative( const wchar* fullpath );

		/** 
			�ϲ�·�����ļ���
			@param
				path ·��
			@param
				file �ļ���
			@return
				�ϲ�������ļ���
		*/
		static WString		Combine( const wchar* path, const wchar* file );

		/** 
			������·���е����·������ȥ��
			@param
				from ���·������
			@param
				to ����·������
			@param
				fromisdir ���·�����ļ���
			@param
				toisdir	����·���������ļ���
			@note
				���ӣ�from = c:\a\ to = c:\a\b.bmp  result = RelativePathTo( from, to, true, false ) = "b.bmp"
		*/
		static WString		RelativePathTo( const wchar* from, const wchar* to, bool fromisdir, bool toisdir );

		/** 
			�ϲ�����·��
			@param
				path ·��1
			@param
				anotherpath ·��2
			@return
				�ϲ����·��
		*/
		static WString		Append( const wchar* path, const wchar* anotherpath );

		/** 
			ȥ��·���е���չ��
			@param
				fullpath ����·��
			@return
				ȥ����չ�����·��
		*/
		static WString		RemoveExtention( const wchar* fullpath );

		/** 
			��׼��·��
			@remark
				·��ȥ����б�ܣ� ͳһб��ΪWindows��׼
			@param
				path[in,out] ·�����뼰�޸ĺ���
		*/
		static void			NormalizePath( WString& path );

		/** 
			��ȡû����չ�����ļ���
			@param
				fullpath ����·��
			@return
				û����չ�����ļ���
			@note
				c:\folder\c.bmp -> c
		*/
		static WString		GetFileNameWithoutExtension( const wchar* fullpath );

		/** 
			�������ļ����е���չ��
			@param
				fullpath ����·��
			@param
				NewExtName ����չ��
			@return
				���������·����
		*/
		static WString		RenameExtension( const wchar* fullpath, const wchar* NewExtName );
	};


	/** @} */
	/** @} */
}