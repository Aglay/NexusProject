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
		�ַ�ת����
	*/
	class StringConverter
	{
	public:
		/** 
			�ͷ���ת���з�����ڴ�
		*/
		~StringConverter( );

		/** 
			Ansi��Unicodeת��
			@remark
				�Զ�������Ҫת���ַ�����С�����м仺��
			@param
				string ��Ҫת�����ַ���
			@param
				number ת���ĳ��ȣ�-1��ʾת�������ַ���
		*/
		wchar_t*	AnsiToUnicode( const char* string,dword number = -1 );

		/** 
			Unicode��Ansiת��
			@remark
				�Զ�������Ҫת���ַ�����С�����м仺��
			@param
				string ��Ҫת�����ַ���
			@param
				number ת���ĳ��ȣ�-1��ʾת�������ַ���
		*/
		char*		UnicodeToAnsi(const wchar_t* string, dword number = -1 );

		/** 
			UTF8��Unicodeת��
			@remark
				�Զ�������Ҫת���ַ�����С�����м仺��
			@param
				string ��Ҫת�����ַ���
			@param
				number ת���ĳ��ȣ�-1��ʾת�������ַ���
		*/
		wchar_t*	UTF8ToUnicode( const char* string, dword number = -1 );

		/** 
			Unicode��UTF8ת��
			@remark
				�Զ�������Ҫת���ַ�����С�����м仺��
			@param
				string ��Ҫת�����ַ���
			@param
				number ת���ĳ��ȣ�-1��ʾת�������ַ���
		*/
		char*		UnicodeToUTF8(const wchar_t* string, dword number = -1 );

		/** 
			Ansi��UTF8ת��
			@remark
				�Զ�������Ҫת���ַ�����С�����м仺��
			@param
				string ��Ҫת�����ַ���
			@param
				number ת���ĳ��ȣ�-1��ʾת�������ַ���
		*/
		char*		AnsiToUTF8( const char* str );

		/** 
			Ansi��Unicode��ת��
			@remark
				�ṩһ�����壬��ת�����д��
			@param
				buffer ת�������unicode����
			@param
				size �������Ĵ�С
			@param
				string ��Ҫת�����ַ���
		*/
		static wchar* AnsiToUnicode( wchar* buffer, dword size, const char* string );

		/** 
			Unicode��Ansi��ת��
			@remark
				�ṩһ�����壬��ת�����д��
			@param
				buffer ת�������ansi����
			@param
				size �������Ĵ�С
			@param
				string ��Ҫת�����ַ���
		*/
		static char* UnicodeToAnsi( char* buffer, dword size, const wchar* string );

		/** 
			�ͷ�ת���з�����ڴ�
		*/
		void		FreeBuffer();

	private:
		std::list<wchar_t*> mUniBufferArray;
		std::list<char*> mAnsiBufferArray;
	};

	/** @} */
	/** @} */
}

