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
	class StringHelper
	{
	public:
		/** 
			��ʽ���ַ���
			@param
				format ��ʽ�����������ַ���
			@return
				��ʽ������ַ���
		*/
		static WString FormatString( const wchar* format, ... );

		/** 
			��ʽ���ַ�����ʹ��ջ
			@param
				format ��ʽ�����������ַ���
			@param
				arguments ����ָ�룬һ�����Ϊ�ɱ����ʱ��ʹ��(char*)( &format ) + sizeof( format )
			@return
				��ʽ������ַ���
		*/
		static WString FormatStringV( const wchar* format, const void* arguments );

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
		static const wchar* FormatBuffer( wchar* buffer, size_t size, const wchar* format, ... );

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
		static const wchar* FormatBufferV( wchar* buffer, size_t size, const wchar* format, const void* arguments );

		/** 
			�ַ�������
			@remark
				�����ַ���1��2�� �����������1����
			@param
				buffer �ַ���1��������û���
			@param
				source �ַ���2
		*/
		static void Connect(wchar* buffer, const wchar* source);

		/** 
			�ַ����Ƚ�
			@param
				str1 �ַ���1
			@param
				str2 �ַ���2
			@return
				�ַ����Ƿ����
		*/
		static bool Compare( const wchar* str1, const wchar* str2 );

		/** 
			�ַ������������Ƚ�
			@param
				str1 �ַ���1
			@param
				str2 �ַ���2
			@param
				Count ��Ҫ�Ƚϵ��ַ�������
			@return
				�ַ����Ƿ����
		*/
		static bool Compare( const wchar* str1, const wchar* str2, dword Count );

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
		static void Copy(wchar* buffer,const wchar* source,int size = -1 );

		/** 
			�ַ������Դ�Сд�Ƚ�
			@param
				str1 �ַ���1
			@param
				str2 �ַ���2
			@return
				�ַ����Ƿ����
		*/
		static bool CompareLowerCase( const wchar* str1, const wchar* str2 );

		/** 
			����ַ�������
			@param
				buffer �ַ���
			@return
				�ַ�������
		*/
		static dword Length( const wchar* buffer );

		/** 
			��ȡ�ַ����Ҳ���
			@param
				str �����ַ���
			@param
				count ��ȡ��Ŀ
			@return
				��ȡ���ַ���
		*/
		static WString		Right(const WString& str, size_t count);

		/** 
			��ȡ�ַ����󲿷�
			@param
				str �����ַ���
			@param
				count ��ȡ��Ŀ
			@return
				��ȡ���ַ���
		*/
		static WString		Left(const WString& str, size_t count);

		/** 
			��ȡ�ַ����м䲿��
			@param
				str �����ַ���
			@param
				count ��ȡ��Ŀ
			@return
				��ȡ���ַ���
		*/
		static WString		Mid( const WString& str, size_t begin,size_t end);

		/** 
			��ȡ�ַ���ռ���ڴ���
			@param
				str �����ַ���
			@return
				�ֽ���
		*/
		static dword		SizeOfBytes( const wchar* str );

		/** 
			ȥ���ַ�������߶�����ַ���
			@param
				str �����ַ���
			@param
				delims ȥ���Ĳ���			
		*/
		static WString		TrimLeft( WString& str ,const wchar* delims = L" \t\r" );

		/** 
			ȥ���ַ������ұ߶�����ַ���
			@param
				str �����ַ���
			@param
				delims ȥ���Ĳ���			
		*/
		static WString		TrimRight( WString& str ,const wchar* delims = L" \t\r" );

		/** 
			ȥ���ַ����ж�����ַ���
			@param
				str �����ַ���
			@param
				delims ȥ���Ĳ���			
		*/
		static WString		Trim( WString& str, const wchar* delims = L" \t\r" );

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
		static int			Parse( const wchar* str, const wchar* format, ... );

		/** 
			���ַ�������ĸ���ִ�д��Сд
			@param
				str �����ַ���
			@return
				ת������ַ���
		*/
		static WString		Lower( const wchar* str );

		/** 
			���ַ�������ĸ���ִ�д��Сд
			@param
				str ����/����ַ���
		*/
		static void			Lower( WString& str );

		/** 
			�滻�ַ����е�����
			@param
				str �����ַ����� ��������ַ���
			@param
				findchar ��Ҫ���ҵ��ַ�
			@param
				replaceto �滻Ϊ���ַ���
		*/
		static void			Replace( WString& str, wchar findchar, wchar replaceto );

		


		/// ���ַ���
		static const WString cBlank;
	};

	

	/** @} */
	/** @} */

}