#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Platform
	*  @{
	*/


	// filter = "ONF��ʽ����(*.onf)\0*.onf\0\0")

	/** 
		�򿪶Ի���
	*/
	class WinFileDialog
	{
	public:
		/** 
			���캯��
			@param
				��ʼ·��
		*/
		WinFileDialog(  const wchar* initpath  );

		WinFileDialog( );

		/// ȡ�Ի��򷵻ص��ļ���
		const wchar*	GetFileName(void);

		/// ����Ĭ���ļ���
		void			SetDefaultExt(const wchar* ext);

		/// ���ó�ʼ�ļ���
		void			SetInitDir( const wchar* path );
	
		/// ���ļ��Ի���
		bool			OpenFileDialog(const wchar* pFilter, handle parentwindow);

		/// �����ļ��Ի���
		bool			SaveFileDialog(const wchar* pFilter, handle parentwindow );

		/// ��ѡ���ļ��жԻ���
		static bool	GetFolderDialog( const wchar* root, handle parentwindow, WString& path );

		/// ȡ�ϴδ򿪶Ի���ǰ��·��
		const wchar* GetLastBrowserPath( );

	private:
		WString		mFileName;
		WString		mDefaultExt;
		WString		mInitPath;
		WString		mLastBrowserPath;// �ϴ����·��
	};

	/** @} */
	/** @} */
}
