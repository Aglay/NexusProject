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
		�ַ�����ʽ�������ò�����
	*/
	class StringHelperA
	{
	public:
		/** 
			��ʽ���ַ���
			@param
				format ��ʽ�����������ַ���
			@return
				��ʽ������ַ���
		*/
		static AString FormatString( const char* format, ... );

		/** 
			��ʽ���ַ�����ʹ��ջ
			@param
				format ��ʽ�����������ַ���
			@param
				arguments ����ָ�룬һ�����Ϊ�ɱ����ʱ��ʹ��(char*)( &format ) + sizeof( format )
			@return
				��ʽ������ַ���
		*/
		static AString FormatStringV( const char* format, const void* arguments );

		/** 
			��ʽ���ַ�������
			@param
				buffer ����������
			@param
				size �����������С
			@param
				format ��ʽ�����������ַ���
			@return
				��ʽ������ַ���
		*/
		static const char* FormatBuffer( char* buffer, size_t size, const char* format, ... );

		/** 
			��ʽ���ַ������壬ʹ��ջ
			@param
				buffer ����������
			@param
				size �����������С
			@param
				format ��ʽ�����������ַ���
			@param
				arguments ����ָ�룬һ�����Ϊ�ɱ����ʱ��ʹ��(char*)( &format ) + sizeof( format )
			@return
				��ʽ������ַ���
		*/
		static const char* FormatBufferV( char* buffer, size_t size, const char* format, const void* arguments );

		/** 
			�ַ�������
			@remark
				�����ַ���1��2�� �����������1����
			@param
				buffer �ַ���1��������û���
			@param
				source �ַ���2
		*/
		static void Connect(char* buffer, const char* source);

		/** 
			�ַ����Ƚ�
			@param
				str1 �ַ���1
			@param
				str2 �ַ���2
			@return
				�ַ����Ƿ����
		*/
		static bool Compare( const char* str1, const char* str2 );

		/** 
			�ַ�������
			@remark
				��Դ�ַ������ݿ�����Ŀ�껺����
			@param
				buffer Ŀ���ַ�������
			@param
				source Դ�ַ���
			@param
				size �������ַ���������-1��ʾ���������ַ���
		*/
		static void Copy(char* buffer,const char* source,int size = -1 );

		/** 
			�ַ������Դ�Сд�Ƚ�
			@param
				str1 �ַ���1
			@param
				str2 �ַ���2
			@return
				�ַ����Ƿ����
		*/
		static bool CompareLowerCase( const char* str1, const char* str2 );

		/** 
			����ַ�������
			@param
				buffer �ַ���
			@return
				�ַ�������
		*/
		static dword Length( const char* buffer );

		/** 
			��ȡ�ַ����Ҳ���
			@param
				str �����ַ���
			@param
				count ��ȡ��Ŀ
			@return
				��ȡ���ַ���
		*/
		static AString		Right(const AString& str, size_t count);

		/** 
			��ȡ�ַ����󲿷�
			@param
				str �����ַ���
			@param
				count ��ȡ��Ŀ
			@return
				��ȡ���ַ���
		*/
		static AString		Left(const AString& str, size_t count);

		/** 
			��ȡ�ַ����м䲿��
			@param
				str �����ַ���
			@param
				count ��ȡ��Ŀ
			@return
				��ȡ���ַ���
		*/
		static AString		Mid( const AString& str, size_t begin,size_t end);

		/** 
			��ȡ�ַ���ռ���ڴ���
			@param
				str �����ַ���
			@return
				�ֽ���
		*/
		static dword		SizeOfBytes( const char* str );

		/** 
			ȥ���ַ�������߶�����ַ���
			@param
				str �����ַ���
			@param
				delims ȥ���Ĳ���
			@return
				ȥ������ַ���
		*/
		static AString		TrimLeft( const char* str ,const char* delims = " \t\r" );

		/** 
			ȥ���ַ������ұ߶�����ַ���
			@param
				str �����ַ���
			@param
				delims ȥ���Ĳ���
			@return
				ȥ������ַ���
		*/
		static AString		TrimRight( const char* str ,const char* delims = " \t\r" );

		/** 
			��ʽ�������ַ���
			@remark
				��Ҫ����Ҫ��ȡ�ı�����ָ�뷽ʽ�����ڿ�ѡ������
			@param
				str �����ַ���
			@param
				format ������ʽ
			@return
				���ν���ʶ��ı�����
		*/
		static int			Parse( const char* str, const char* format, ... );

		/** 
			���ַ�������ĸ���ִ�д��Сд
			@param
				str �����ַ���
			@return
				ת������ַ���
		*/
		static AString		Lower( const char* str );
	};

	/** @} */
	/** @} */

}