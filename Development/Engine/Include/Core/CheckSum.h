#pragma once


namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Basic
	*  @{
	*/

	/** ����У��
		
	*/

	class CheckSum
	{
	public:
		/// ȫ�ֳ�ʼ��
		static void StaticInit( );

		/** 
			�ڴ�ѭ��CRC����У��	
			@param
				InData �����ڴ�
			@param
				Length �ڴ泤��
			@param
				CRC ��ѡ��һ����ʼCRCֵ
		*/ 
		static dword	MemCRC( const void* InData, int Length, dword CRC = 0 );

		/// Unicode�ַ���Hash����
		static dword	StrHash( const wchar* Data );

		/// ANSI�ַ���Hash����
		static dword	StrHash( const char* Data );

		/// Unicode�ַ���Hash��������Сд������
		static dword	StrHashNoCase(const wchar* Data);

		/// ANSI�ַ���Hash��������Сд������
		static dword	StrHashNoCase(const char* Data );

		
		/** 
			��ѩ�ã�Unicode�ַ���Hash����
			@remarks
				��ѩϵ���ַ����ظ��ʵͣ�Ч�ʸ�
			@param
				str �����ַ���
			@param
				type 0 Ϊhash������ 1��2Ϊcompare key
		*/
		static dword	BLZStrHash(const wchar* str, dword type );

		/** 
			��ѩ�ã�ANSI�ַ���Hash��������Сд������
			@remarks
				��ѩϵ���ַ����ظ��ʵͣ�Ч�ʸ�
			@param
				str �����ַ���
			@param
				type 0 Ϊhash������ 1��2Ϊcompare key
		*/
		static dword	BLZStrHash(const char* str, dword type );

	private:
		static void BLZStaticInit( );

	private:
		static bool mInitialized;

		// Blizzard Powerful Hash stuff
		enum{ BLZBUFFER_SIZE = 0x500 };

		typedef dword	BLZBuffer[BLZBUFFER_SIZE];

		static BLZBuffer mBLZBuffer;
	};

	/** @} */
	/** @} */
}
