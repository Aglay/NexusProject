#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Render
	*  @{
	*/


	/** 
		��Ҫ�ύ����Ⱦ�̵߳Ĳ���
	*/
	struct RenderFontTextureParameter 
	{
		/// GDI+��λͼ����
		handle	mGDIPlusBitmap;

		/// GDI+��ͼԪ���ƶ���
		handle	mGDIGraphics;

		/// ��ģ�������ϵ�λ��
		Point	mCharPos;

		/// ��ģ�ߴ�
		Point	mCharSize;
	};

	/** 
		��������
	*/
	class RenderFontTexture: public RenderTexture
	{
	public:
		RenderFontTexture::RenderFontTexture( dword TextureSize );

		virtual void InitRHI( );

		void SyncData( const RenderFontTextureParameter& Parameter );

		void WaitSync( );

	private:
		dword mTextureSize;		
		RenderCommandFence	mSyncFence;
	};


	/** 
		������
		@remark
			����һ������̶��ߴ��������
	*/
	class RenderFont
	{
	public:

		/** 
			���캯��
			@param
				fontname ��������
			@param
				filename �����ļ�,Ĭ��Ϊ��
			@param
				size ����ߴ�
			@param
				border �����Ƿ��б�
			@param
				bold �Ƿ�Ӻ�
			@param
				italic б��
			@param
				underline �Ƿ����»���
		*/
		RenderFont( const wchar* fontname, 
					const wchar* filename, 
					dword size, 
					dword border, 
					bool bold, 
					bool italic, 
					bool underline );

		~RenderFont( );

		/// �����������
		const wchar*	GetFontName( ) const;

		/// �������ߴ�
		dword		GetFontSize( ) const;

		dword		GetFontBorder( ) const;
		bool		IsBlod( ) const;
		bool		IsItalic( ) const;
		bool		IsUnderline( ) const;

		/** 
			ȡ��һ���ֵĿ��
		*/
		dword GetCharacterWidth( wchar character );

		/** 
			ȡ��һ���ַ������
		*/
		dword GetStringWidth( const wchar* string );		

		void  SetFontColor( dword color );
		dword GetFontColor( ) const;
		void  SetBorderColor( dword color );
		dword GetBorderColor( ) const;

		/** 
			ȡ����ģ��Ӧ����������
			@param
				character ��
			@param
				uv �ֵ���������
			@param
				uvsize ���������С
			@param
				charsize �ִ�С
		*/
		RenderFontTexture* GetFontTexture( wchar character, Vector2& uv, Vector2& uvsize, Vector2& charsize );

		static void StaticInit( );

		static void StaticExit( );

		void Save( const wchar* FileName );

	private:
		/** 
			����һ����
		*/
		void CacheChar( dword code );		

		/** 
			����һ������
		*/
		RenderFontTexture* AllocTexture( );

		/** 
			ȡ����д��λ��
		*/
		bool GetCharWritePos( dword CharWidth, dword CharHeight, Point& CharWritePos );
	private:
		enum { _TEXTURE_SIZE = 512 };		
		enum{ cGlyphMargin = 2 };

		typedef std::vector< RenderFontTexture* > TextureArray;

		struct FontCode
		{
			dword	mTextureIndex;
			dword	mWidth;
			dword	mHeight;
			int		mStartX;
			int		mStartY;
		};

		WString			mFontName;
		dword			mFontSize;
		bool			mBlod;
		bool			mItalic;
		bool			mUnderline;

		handle			mOldFont;
		handle			mGDIFont;
		handle			mOldMemBitmap;
		handle			mGDIMemBitmap;
		handle			mGDIMemDC;

		dword			mMaxCharWidth;
		dword			mMaxCharHeight;

		dword			mFontColor;
		dword			mBorderColor;


		FontCode		mCodeList[65536];
		TextureArray	mFontTextureArray;

		int				mPrintHeaderX;
		int				mPrintHeaderY;
		int				mMaxLineHeight;

	};

	/** @} */
	/** @} */
}
