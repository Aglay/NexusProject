#include "FontDrvPCH.h"
#include "FontFiles.h"

namespace NekoEngine
{
	//////////////////////////////////////////////////////////////////////////
	// FontTexture
	//////////////////////////////////////////////////////////////////////////
	FontTexture::FontTexture( dword Index, dword TextureSize ) : mIndex( Index )
		, mPrintOffset( FontTexture::cGlyphMargin, FontTexture::cGlyphMargin )
		, mMaxLineHeight( 0 )
		, mDirtyCharCount( 0 )
	{
		_byte* Data = mBufferData.Alloc( TextureSize, TextureSize, PF_A8L8 );
		mBufferData.SetMip( 0, Data,  mBufferData.mDataSize );

		mTexture = new RenderTexture2D( mBufferData );


		mTexture->BeginInitResource();
	}

	FontTexture::~FontTexture()
	{
		mBufferData.Release();

		mTexture->BeginReleaseResource();
		mTexture->WaitRelease();

		delete mTexture;
	}


	//////////////////////////////////////////////////////////////////////////
	// FontObject
	//////////////////////////////////////////////////////////////////////////
	FontObject::FontObject( FontFace& Face, dword Size )
		: mFontFace( Face )
		, mFontSize( Size )		
	{
		FT_Face& FTFace = Face.GetFTFace();

		mGlyphsArray.resize( FTFace->num_glyphs );




	}

	FontObject::~FontObject()
	{
		for ( dword i = 0;i<mTextureBufferArray.size();i++)
		{
			FontTexture* Tex = mTextureBufferArray[i];
			delete Tex;
		}
	}

	IFontGlyph* FontObject::GetGlyph( wchar C )
	{
		return CacheSingleChar( C );
	}

	FontTexture* FontObject::GetCurrentFontTexture( )
	{
		if ( mTextureBufferArray.size() == 0 )
			return AllocFontTexture();

		return mTextureBufferArray.back();
	}

	FontTexture* FontObject::AllocFontTexture(  )
	{
		// �ύ��ǰ��������
		FlushDirtyTexture( );

		FontTexture* Texture = new FontTexture( mTextureBufferArray.size(), mFontFace.mDriver->GetTextureSize() );

		mTextureBufferArray.push_back( Texture );

		return Texture;
	}

	void FontObject::CommitFontTextureByString( const wchar* Text )
	{
		for ( dword i = 0; Text[i]; i++)
		{
			CacheSingleChar( Text[i] );			
		}

		FlushDirtyTexture();
	}

	bool FontObject::WriteCharToBuffer( dword CharIndex, FontGlyph& Glyph, FontTexture* FontTex )
	{		
		FT_Face& FF = mFontFace.GetFTFace();

		if (FT_Load_Glyph( FF, CharIndex, FT_LOAD_RENDER ))
			return true;

		dword TextureSize = mFontFace.mDriver->GetTextureSize();

		dword GlyphX = FF->glyph->bitmap.width + FontTexture::cGlyphMargin;
		dword GlyphY = FF->glyph->bitmap.rows + FontTexture::cGlyphMargin;

		// ��ģ�����ƫ�ƣ�����gҪ��ƫ��һ��
		dword GlyphOffsetX = FF->glyph->bitmap_left;
		dword GlyphOffsetY = mFontSize - FF->glyph->bitmap_top;

		// ȡ������ߵ�Ϊ���иߣ�����ض�
		FontTex->mMaxLineHeight = Math::Max( GlyphY + GlyphOffsetY , FontTex->mMaxLineHeight );

		// ������ģ�ұ߽�=��ǰ��ӡλ��+��ģ��С���������+��ģƫ��
		dword GlyphRight = FontTex->mPrintOffset.x + GlyphX + GlyphOffsetX;

		// �����ұ߽����
		if ( GlyphRight > TextureSize )
		{
			// ��λ�����
			FontTex->mPrintOffset.x = FontTexture::cGlyphMargin;

			// ���¼����µ��ұ߽�
			GlyphRight = FontTex->mPrintOffset.x + GlyphX;

			// ����һ��
			FontTex->mPrintOffset.y += FontTex->mMaxLineHeight;

			// �����и����¼���
			FontTex->mMaxLineHeight = FontTexture::cGlyphMargin;
		}

		// ������ģ�±߽�=��ǰ��ӡλ��+��ģ��С���������+��ģƫ��
		dword GlyphBottom = FontTex->mPrintOffset.y + GlyphY + GlyphOffsetY ;


		// �����±߽磬��ֹ���
		if ( GlyphBottom > TextureSize )
		{
			return false;
		}

		// ��FF����ģ���忽����ָ������֮��
		CopyGlyph(	FontTex->mPrintOffset.x + GlyphOffsetX , 
					FontTex->mPrintOffset.y + GlyphOffsetY,
					GlyphOffsetX, 
					 GlyphOffsetY , 
					(word*)FontTex->mBufferData.mData,
					Glyph, 
					FontTex);

		// ��Ӧλ��ת����һ��λ��
		FontTex->mPrintOffset.x = GlyphRight;

		FontTex->mDirtyCharCount++;

		return true;
	}

	void FontObject::CopyGlyph( dword DestX, dword DestY, dword OffsetX, dword OffsetY, word* DestBuffer, FontGlyph& Glyph, FontTexture* FontTex   )
	{
		dword TextureSize = mFontFace.mDriver->GetTextureSize();

		FT_Bitmap& bitmap = mFontFace.GetFTFace()->glyph->bitmap;

		// ���㿽��Ŀ���ƫ��λ��
		word* Dest = DestBuffer +  DestY  * TextureSize  + DestX ;

		for ( int y = 0; y < bitmap.rows ;y++ )
		{
			_byte* src = bitmap.buffer + ( y * bitmap.pitch );
			_byte* pDest = (_byte*)Dest;

			// ����һ��
			for ( int x = 0; x < bitmap.width; x ++ )
			{
				*pDest ++ = (*src++);
				*pDest ++ = 0xFF;
			}

			Dest += TextureSize;
		}

		Glyph.SetInfo( Point( DestX, DestY ),
					   Point( bitmap.width, bitmap.rows ),
					   Point( OffsetX, OffsetY ),
					   FontTex );
	}


	void FontObject::FlushDirtyTexture( )
	{
		if ( mTextureBufferArray.size() == 0 )
			return;

		FontTexture* DirtyTexture = mTextureBufferArray.back();

		// û������ַ�,�����ύ
		if ( DirtyTexture->mDirtyCharCount == 0 )
			return;

		DirtyTexture->mDirtyCharCount = 0;

		ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(
			SyncFontData,
			RenderTexture2D*,Tex,DirtyTexture->mTexture,
		{
			Tex->SyncData();
		});

		if ( 0 )
		{
			DirtyTexture->mTexture->WaitSync();
			DirtyTexture->mTexture->mTextureRHI->Save(L"t.png");
		}
	}


	FontGlyph* FontObject::CacheSingleChar( wchar Char )
	{
		FT_Face& FF = mFontFace.GetFTFace();

		dword CharIndex = FT_Get_Char_Index( FF, Char );

		// �Ҳ��������
		if ( CharIndex == 0 )
			return null;
		
		FontGlyph* GlyphRef = mGlphHashMap.find( CharIndex );

		if ( GlyphRef != null )
			return GlyphRef;


		FontTexture* Texture = GetCurrentFontTexture( );

		FontGlyph Glyph;
		dword Times = 0;

		while ( !WriteCharToBuffer( Char, Glyph, Texture ) )
		{
			// �����ڳ���2�������治�µ����
			Assert( Times == 0 )
			if ( Times > 0 )
				break;

			// ���������Ѿ��޷�����, �����µı���
			Texture = AllocFontTexture();
			Times++;
		}

		return &mGlphHashMap.set( CharIndex, Glyph);
	}





}