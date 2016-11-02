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
		Ӧ�ó�����غ���
	*/
	class Application
	{
	public:
		static const dword cCpuResondTimeMS;

		/** 
			���ñ������ó���Instance
		*/
		static void			 SetHandle(handle hInstance);

		/// ��ȡӦ�ó���Instance
		static handle		 GetHandle( );

		/** 
			���Ӧ�ó��������·����
			@return
				Ӧ�ó�������ʱ������·����
		*/
		static WString		 GetExecutablePath( );

		/** 
			���Ӧ�ó���Ľ�������
			@return
				Ӧ�ó���Ľ�������
		*/
		static WString GetExecutableName( );

		/** 
			�������·��
			@return
				Ӧ�ó�������ʱ��·��
		*/
		static WString		 GetStartupPath( );

		/**
			������Ϣ���ڹ���ʱ���Ƿ������ͷ�ʱ��ƬԪ��CPU
		*/
		static void			 SetAutoSleep(bool enable);

		/**
			�����Ϣ���ڹ���ʱ���Ƿ������ͷ�ʱ��ƬԪ��CPU
		*/
		static bool			GetAutoSleep( );

		/// ��ý��̹�����������
		static const wchar*	 GetSystemCommandLine( );

		/// �ͷ�ʱ��ƬԪ
		static void			 Sleep( dword milliseconds );

		/** 
			������Ϣ
			@return
				�Ƿ����������˳���Ϣ
		*/
		static bool			 DoEvents( );
	
		/** 
			������Ŀ¼����Ϊ���������Ŀ¼
			@remark
				����VC����ʱ������Ŀ¼��Ϊ����Ŀ¼
		*/
		static void			SetStartupPathByExecutable();

		/** 
			���������ڵ���Ϣ��ֱ�����ڹر�
		*/
		static bool			Run( WinForm* form,bool autoSleep);

		/** 
			���Ӧ�ó������ݴ��λ��
			@remark
				Vista���ϵĲ���ϵͳ����δ��ù���ԱȨ���£�Ӧ�ó�����д�Լ��ĳ���Ŀ¼��ʹ�ñ�������ÿ�д��Ŀ¼λ��
		*/
		static WString		GetExecutableDataPath( );

		/** 
			���������ļ��������ؿ�д�����������ļ�Ŀ¼
			@param
				ConfigFileName �����ļ���
			@param
				SuggestPath ����·��
			@return
				��д�����������ļ�Ŀ¼
		*/
		static WString		GetConfigCombinedPath( const wchar* ConfigFileName, const wchar* SuggestPath = null );
		
	private:
		static bool mAutoSleep;
		static handle mhInstance;

	};

	/** @} */
	/** @} */
}