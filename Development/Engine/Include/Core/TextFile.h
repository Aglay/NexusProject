#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Stream
	*  @{
	*/

	/** 
		�ı��ļ���д��
	*/
	class TextFile
	{
	public:
		TextFile( );
		virtual ~TextFile( );

		/** 
			��һ���ı��ļ�
		*/
		bool	Open( const wchar* filename );

		/** 
			����һ���ı��ļ�
			@param
				filename �ļ���
			@param
				UnicodeFormat �Ƿ���Unicodeģʽ
			@return
				�Ƿ񴴽��ɹ�
		*/
		bool	Create( const wchar* filename, bool UnicodeFormat = true );

		/** 
			��һ������һ���ı��ļ�
		*/
		bool	Open( DataStream* stream, bool copymemory = false );
		
		/** 
			����һ���ı��ļ�
			@param
				stream ��Դ��
			@param
				UnicodeFormat �Ƿ���Unicodeģʽ
			@return
				�Ƿ񴴽��ɹ�
		*/
		bool	Create(  DataStream* stream, bool UnicodeFormat = true);
		
		/** 
			�ļ��Ƿ�ΪUnicode��ʽ
		*/
		bool	IsUnicode( void );

		/** 
			��ʽ��д��һ���ı�
		*/
		bool	WriteLine(const wchar* format, ... );

		/** 
			��ȡһ���ı�
		*/
		bool	ReadLine( WString& str );

		/** 
			�ı��Ƿ����
		*/
		bool	IsEnd( );

		/** 
			�ر��ļ�
		*/
		void Close( );
	private:
		bool			mIsUnicode;		// unicode��ʶ
		WString			mDivision;		// Trimʱ�зַ�
		DataStream*	mStream;
		FileStream*		mFile;
		StringConverter mConv;
		bool			mDeleteStream;
	};

	/** @} */
	/** @} */
}
