#pragma once


namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Basic
	*  @{
	*/


	/** �����з�װ��
		
	*/

	class Console
	{
	public:
		/** ��
			�����������ԣ�Ĭ��Ϊ����
			@remarks
				������������Ŀ�������Щ������Ϊ���룬��Ҫͨ���˺�������encoding����
			@param
				localstr Ĭ��Ϊ����
		*/
		static void SetLocal(const char* localstr = null);

		/// �����ʽ�����ֵ�������
		static int Write( const wchar* format, ... );

		/// �����ʽ�����֣� �Զ�����
		static int WriteLine( const wchar* format, ... );

		/// �������н��ܸ�ʽ������
		static int Input( const wchar* format, ... );

		/// �Ӽ��̵ȴ�һ�������ַ�
		static wchar GetChar( );

		/** 
			����̨�¼��ص���������
			@remarks
				�˺������ڽ��������еĸ����¼�
			@param
				CtrlType �¼����ͣ������MSDN SetConsoleCtrlHandler
			@return
				1������¼��ѱ����� 0����δ����
		*/
		typedef int (*ConsoleEvent)(dword CtrlType );
		
		/** 
			����̨�¼��ص�����
			@remarks
				�����������������¼�
			@param
				handle ���غ�������
			@return
				�����Ƿ�ɹ�
			@remark
				ע��: 
				1.�ص�����������������߳�
				2. �ص���,���̻ᱻ�����п�������ֹ,ʱ�䲻ȷ��
				3. ���Ƽ��ڷ������ر�ʱʹ��
		*/
		static bool SetConsoleEventCallBack( ConsoleEvent handle );
		
	};

	/** @} */
	/** @} */
}