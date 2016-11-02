#pragma once

namespace NekoEngine
{
	class FontFace;
	class FontGlyph;

	struct FontTexture 
	{
		enum{ cGlyphMargin = 2 };

		dword mIndex;

		RenderTexture2D*	mTexture;
		TextureMipMap		mBufferData;

		Point mPrintOffset;		// ��ǰ��ӡͷλ��
		dword mMaxLineHeight;	// ���е�����и�

		dword mDirtyCharCount;	// �����ж��ٸ���д��

		FontTexture( dword Index, dword TextureSize );

		~FontTexture( );
	};

	class FontObject : public IFontObject
	{
	public:
		FontObject( FontFace& Face, dword Size );

		virtual ~FontObject( );

		virtual IFontGlyph* GetGlyph( wchar C );

		virtual void CommitFontTextureByString( const wchar* Text );

	private:

		// ��ȡ��ǰ���õ����������
		FontTexture* GetCurrentFontTexture( );

		// �ύ֮ǰ�Ļ��嵽����, �����µ����������
		FontTexture* AllocFontTexture( );

		FontGlyph* CacheSingleChar( wchar Char );

		// д��һ���ֵ�����
		bool WriteCharToBuffer( dword CharIndex, FontGlyph& Glyph, FontTexture* FontTex );
			
		// ������ģ	
		void CopyGlyph( dword DestX, dword DestY, dword OffsetX, dword OffsetY, word* DestBuffer, FontGlyph& Glyph, FontTexture* FontTex );

		// ˢ��֮ǰ��������
		void FlushDirtyTexture( );
		

	private:
		

		FontFace& mFontFace;

		dword mFontSize;

		

		typedef std::vector<FontGlyph> GlyphsArray;
		GlyphsArray mGlyphsArray;


		typedef dynamic_hash<dword, FontGlyph, 2048 > GlphHash;
		GlphHash mGlphHashMap;



		typedef std::vector<FontTexture*> TextureBufferArray;
		TextureBufferArray mTextureBufferArray;
	};
}