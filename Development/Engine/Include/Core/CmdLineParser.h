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
		�����н�����
	*/
	class CmdLineParser 
	{
	public:
		CmdLineParser ();

		~CmdLineParser();

		/** 
			ȡ�ò���
			@param
				index ������base 0
			@return
				����������Ӧ�Ĳ���
		*/
		const wchar* GetArg( dword index );

		/// ȡ�ò�������
		dword GetArgCount( );

		/** 
			���ĳ�������Ƿ����
		*/
		bool HasArg( dword index );

		/** 
			���ĳ�����������Ƿ����
		*/
		bool ArgExist( const wchar* ArgName );

		/// ��ò�������Ӧ������
		dword GetArgIndex( const wchar* ArgName );

		/** 
			��ò�������
			@remark
				-file a.dds, ���a.dds
			@param
				ArgName ������
			@return
				��������
		*/
		const wchar* GetArgContent( const wchar* ArgName );
		
	private:
		wchar* m_cmdline; // the command line string

		////////////////////////////////////////////////////////////////////////////////
		// Parse m_cmdline into individual tokens, which are delimited by spaces. If a
		// token begins with a quote, then that token is terminated by the next quote
		// followed immediately by a space or terminator.  This allows tokens to contain
		// spaces.
		// This input string:     This "is" a ""test"" "of the parsing" alg"o"rithm.
		// Produces these tokens: This, is, a, "test", of the parsing, alg"o"rithm
		////////////////////////////////////////////////////////////////////////////////
		void ParseCmdLine (); // ParseCmdLine()
		



	private:
		typedef std::vector<wchar*> CharArray;
		CharArray mCharArray;

	};
}