#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Basic
	*  @{
	*/

	class Logger;

	/** 
		��־����豸
		@remark
			��־����豸�ĳ������
	*/
	class LogDevice
	{
	public:
		virtual ~LogDevice( ){ }

		virtual void OnAttach( ){}
		/** 
			�ͷ���־����
			@remark
				��DLLɾ��ʱ����ʹ��Release
		*/
		virtual void Release();

		/** 
			�ֶ����ó�ʼ���˺���������
			
		*/
		virtual void Initialize( ){ }

		/** 
			Logger��д������ʱ����
			@param
				prefix ��־ǰ׺����������:ShaderMaster, ObjectMaster
			@param
				level ��־����, @enum Logger::eLogLevel
			@param
				content ��ʽ��������־����
		*/
		virtual void WriteLogContent( const wchar* prefix, dword level, const wchar* content ) = 0;

		/** 
			д��ǰ�ĸ�ʽ�����ݲ���
			@param
				prefix ��־ǰ׺����������:ShaderMaster, ObjectMaster
			@param
				level ��־����, @enum Logger::eLogLevel
			@param
				content ��ʽ��������־����
			@return
				ʹ���豸�ṩ��mFormatBuffer���ظ�ʽ�������־����
		*/
		virtual const wchar* GetFormatString( const wchar* prefix, dword level, const wchar* content );

	protected:
		friend class Logger;
		enum{ MAX_FORMATBUFFERSIZE = 1024 };
		wchar	mFormatBuffer[MAX_FORMATBUFFERSIZE];
		Logger* mLogger;
	};

	/**
		��־�ļ�����
	*/
	enum eFileLogType
	{
		FLT_SingleFile,				///< �����ļ�һֱ���
		FLT_FilePerProcessLaunch,	///< ÿ�ν�����������һ�����ڲ�ͬ����־
	};

	/** 
		��ͨ�ļ���־�豸
		@remark
			������ӷ�ʽ���ļ���־�豸
	*/
	class FileLog : public LogDevice
	{
	public:
		/** 
			���캯��
			@param logfilename ��־�ļ���
		*/
		FileLog( eFileLogType Type = FLT_SingleFile );

		/** 
			��������
			@remark
				�ر���־�ļ�
		*/
		virtual ~FileLog( );

		/** 
			��ʼ��
			@remark
				���ļ�
		*/
		virtual void Initialize( );

		/**
			������־���·��
			@remark
				����: SetFolder(L"Log");
		*/
		void SetFolder( const wchar* FileName );		

		/**
			�����ļ�д������
		*/
		void SetFileLogType( eFileLogType Type ){ mFileLogType = Type; }


		virtual void WriteLogContent( const wchar* prefix, dword level, const wchar* content );

	protected:
		virtual const wchar* GetFormatString( const wchar* prefix, dword level, const wchar* content );

	protected:
		handle			mFile;
		WString			mFolder;
		eFileLogType	mFileLogType;
	};

	/** 
		VC�������
	*/
	class IDELog : public LogDevice
	{
	public:
		virtual void WriteLogContent( const wchar* prefix, dword level, const wchar* content );
	};

	/** 
		����̨���
		@remark
			�����Ĭ�������д���
	*/
	class ConsoleLog : public LogDevice
	{
	public:
		virtual void WriteLogContent( const wchar* prefix, dword level, const wchar* content );
	};

	/**
		��־����	
	*/
	enum eLogLevel
	{ 
		LogLevel_Debug = 0,		///< ���Լ���
		LogLevel_Info  = 1,		///< ��Ϣ�������
		LogLevel_Alert = 2,		///< ���漶��
		LogLevel_Error = 3,		///< ���󼶱�
		LogLevel_Fatal = 4,		///< ��������
		LogLevel_Max,
	};

	class PropertySerializer;

	/** 
		��־��
		@remark
			�ṩ��־�㼶д�룬�ҽ���־�豸����
	*/
	class Logger
	{
	public:


		Logger( );

		virtual ~Logger( );

		void Initialize( );

		/** 
			�ҽ�һ����־�豸
			@param
				dev ��־�豸
		*/
		void AttachDevice( LogDevice* dev );

		/** 
			�Ͽ�һ����־�豸
			@param
				dev ��־�豸
		*/
		void DetachDevice( LogDevice* dev );

		/** 
			���ñ���־
			@param
				enable �Ƿ�����
		*/
		void SetEnable(bool enable) {mEnable = enable;}

		/** 
			����־�Ƿ�����
			@return
				�Ƿ�����
		*/
		bool GetEnable( ){ return mEnable; }

		/** 
			������־�ȼ�������
			@remark
				���ڴ˵ȼ�����־�ȼ�������¼
			@param
				@enum Logger::eLogLevel
			@note
				��ʼֵΪLevel_Debug
		*/
		void SetLevelFilter( dword level ) {mLeve = level; }

		/** 
			��ȡ��ǰ��־�������ȼ�
			@return
				��ǰ��־�������ȼ� @enum Logger::eLogLevel 
			
		*/
		dword GetLevelFilter( ){ return mLeve; }

		/// �����Ƿ�����־����ʾTheadID
		void SetShowThreadID( bool Value ){ mShowThreadID = Value; }

		/// �Ƿ�����־����ʾTheadID
		bool GetShowThreadID( ){ return mShowThreadID; }

		/// ���Եȼ���ʽ�������־
		void Debug( const wchar* format, ...  );

		/// ��Ϣ�ȼ���ʽ�������־
		void Info( const wchar* format, ...  );

		/// ����ȼ���ʽ�������־
		void Alert( const wchar* format, ...  );

		/// ����ȼ���ʽ�������־
		void Error( const wchar* format, ...  );

		/// �����ȼ���ʽ�������־
		void Fatal( const wchar* format, ...  );

		/** 
			д��һ����־
			@param
				level ��־�ȼ��� @enum Logger::eLogLevel
			@param
				format ��ʽ���ַ���
		*/
		void WriteLine(dword level, const wchar* format, ...  );

		static const wchar* GetLevelString(  dword level  );

		/** 
			������־ǰ׺
			@remark
				ͨ��������־�������࣬����ShaderMaster��ObjectMaster
		*/
		void SetPrefix( const wchar* prefix ){ mPrefix = prefix; }

		/// �����־ǰ׺
		const wchar* GetPrefix( ){ return mPrefix.c_str(); }

		void SerializeConfig( PropertySerializer& Ser );

		/// ���WriteDebugStringͯ��
		static void WriteDebugInfo( const wchar* Format, ... );
		
		/**
			�ṩ��ʽ��������WriteLine�汾
			@remark
				WriteLine��ʵ��:
				WriteLine( dword level, const wchar* format, ... )
				{
					WriteLineV( mPrefix.c_str(), level, format, (char*)( &format ) + sizeof( format ) );
				}
		*/
		void WriteLineV( const wchar* prefix, dword level, const wchar* format, const void* arguments );
		
	private:
		bool		mEnable;
		typedef std::set<LogDevice*> DeviceSet;
		DeviceSet	mDeviceSet;
		dword		mLeve;
		WString		mPrefix;
		bool		mShowThreadID;
	};

	/** 
		����־��
		@remark
			�����VC���Դ���
	*/
	class SimpleLog : public Logger
	{
	public:
		SimpleLog( );
	};

	/** 
		�����й�������־��
		@remark
			�����VC���Դ��ڼ�������
	*/
	class CmdToolLog : public Logger
	{
	public:
		CmdToolLog( );
	};


	/** 
		����������־��
		@remark
			�����VC���Դ��ڣ������м��ļ�
	*/
	class ServerLog : public Logger
	{
	public:
		ServerLog( );
	};

	/** 
		�ͻ�������־��
		@remark
			�����VC���Դ��ڼ��ļ�
	*/
	class ClientLog : public Logger
	{
	public:
		ClientLog( );
	};

	/** @} */
	/** @} */
}
