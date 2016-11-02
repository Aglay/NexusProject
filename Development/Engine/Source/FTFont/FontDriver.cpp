#include "FontDrvPCH.h"
#include "FontFiles.h"

namespace NekoEngine
{
	IFontDriver* FontDrv = null;

	void FontDriverInitialize( )
	{
		FontDrv = new FontDriver;
	}

	FontDriver::FontDriver()
		: mTextureSize( 256 )
	{
		FT_Init_FreeType( &mLibrary );
	}

	FontDriver::~FontDriver( )
	{
		// not call here
	}

	void FontDriver::Release()
	{

		for ( FontFaceMap::iterator it(mFontFaceMap); it;++it)
		{
			FontFace* Face = it.get_value();
			delete Face;
		}

		mFontFaceMap.clear();

		FT_Done_FreeType( mLibrary );

		delete this;
	}


	IFontObject* FontDriver::CreateFontType( const wchar* FontPathName, dword FontSize )
	{
		WString StrFontPathName = StringHelper::Lower( FontPathName );

		FontFace* Face = GetFace( StrFontPathName );

		// �����µ�Face
		if ( Face == null )
		{
			Face = new FontFace( this );
			if ( !Face->Load( mLibrary, FontPathName ) )
			{
				delete Face;

				return null;
			}

			mFontFaceMap.set( StrFontPathName, Face );
		}

		// û��Font����ʱ����
		IFontObject* FontObj = Face->GetFontObject( FontSize );
		if ( FontObj == null )
		{
			FontObj = Face->CreateFontObject( FontSize );
		}

		FT_Face& FF = Face->GetFTFace();

		FT_F26Dot6 ftSize = (FT_F26Dot6)(FontSize * (1 << 6));
		FT_Set_Char_Size( FF, ftSize, 0, 96, 96);

	
		//FontObj->DrawText( Vector2::cZero, Color::cWhite, L"hello");

		//const dword MaxTextureSize = 1024;
		//TextureMipMap MipMap;
		//word* Buffer = (word*)MipMap.Alloc( MaxTextureSize, MaxTextureSize,PF_A8L8 );

		//::memset( Buffer, 0, MipMap.mDataSize );
		//for ( dword i = 19968; i < 40869 ;i ++)

		//Point CharPrintOffset(cGlyphMargin, cGlyphMargin );
		//int MaxLineHeight = cGlyphMargin;


		//for ( dword i = 33; i < 166;i ++)
		//{
		//	if ( !WriteFont(i, FF,  Buffer, CharPrintOffset, MaxTextureSize, MaxLineHeight, FontSize ) )
		//		break;

		//}

		//for ( dword i = 19968; i < 40869 ;i ++)
		//{
		//	if ( !WriteFont(i, FF,  Buffer, CharPrintOffset, MaxTextureSize, MaxLineHeight, FontSize ) )
		//		break;
		//}
		

		//MipMap.SetMip( 0, (_byte*)Buffer, MipMap.mDataSize );

		//mTexture2D = new RenderTexture2D( MipMap );
		//mTexture2D->BeginInitResource();

		//mTexture2D->WaitReady();

		//mTexture2D->mTextureRHI->Save( L"t.png");

		//MipMap.Release();
 

		return FontObj;
	}

	FontFace* FontDriver::GetFace( const WString& FontPathName )
	{
		// Сд·����Ϣ��Ϊkey
		FontFace** FaceRef = mFontFaceMap.find( FontPathName );

		if ( FaceRef == null )
			return null;

		return *FaceRef;
	}

	IFontObject* FontDriver::GetFont( const WString& FontPathName, dword FontSize )
	{
		FontFace* Face = GetFace( FontPathName );

		if ( Face == null )
			return null;

		return Face->GetFontObject( FontSize );
	}

	//bool FontDriver::WriteFont( dword i, FT_Face& FF, word* Buffer, Point &CharPrintOffset, const dword MaxTextureSize, int& MaxLineHeight, dword FontSize )
	//{
	//	wchar_t c = wchar_t(i);

	//	if (FT_Load_Char( FF, i, FT_LOAD_RENDER ))
	//		return false;

	//	
	//	int GlyphX = FF->glyph->bitmap.width + cGlyphMargin;
	//	int GlyphY = FF->glyph->bitmap.rows + cGlyphMargin;
	//	
	//	// ��ģ�����ƫ�ƣ�����gҪ��ƫ��һ��
	//	int GlyphOffsetX = FF->glyph->bitmap_left;
	//	int GlyphOffsetY = FontSize - FF->glyph->bitmap_top;

	//	// ȡ������ߵ�Ϊ���иߣ�����ض�
	//	MaxLineHeight = Math::Max( GlyphY + GlyphOffsetY , MaxLineHeight );
	//	
	//	// ������ģ�ұ߽�=��ǰ��ӡλ��+��ģ��С���������+��ģƫ��
	//	dword GlyphRight = CharPrintOffset.x + GlyphX + GlyphOffsetX;
	//	
	//	// �����ұ߽����
	//	if ( GlyphRight > MaxTextureSize )
	//	{
	//		// ��λ�����
	//		CharPrintOffset.x = cGlyphMargin;

	//		// ���¼����µ��ұ߽�
	//		GlyphRight = CharPrintOffset.x + GlyphX;

	//		// ����һ��
	//		CharPrintOffset.y += MaxLineHeight;

	//		// �����и����¼���
	//		MaxLineHeight = cGlyphMargin;
	//	}

	//	// ������ģ�±߽�=��ǰ��ӡλ��+��ģ��С���������+��ģƫ��
	//	dword GlyphBottom = CharPrintOffset.y + GlyphY + GlyphOffsetY ;

	//	// �����±߽磬��ֹ���
	//	if ( GlyphBottom > MaxTextureSize )
	//	{
	//		return false;
	//	}

	//	// ��FF����ģ���忽����ָ������֮��
	//	CopyGlyph( CharPrintOffset.x + GlyphOffsetX, CharPrintOffset.y +GlyphOffsetY , MaxTextureSize, Buffer, FF );

	//	// ��Ӧλ��ת����һ��λ��
	//	CharPrintOffset.x = GlyphRight;

	//	return true;
	//}

	//void FontDriver::CopyGlyph( dword DestX, dword DestY, dword TextureSize, word* DestBuffer, FT_Face& Face )
	//{
	//	FT_Bitmap& bitmap = Face->glyph->bitmap;
	//
	//	// ���㿽��Ŀ���ƫ��λ��
	//	word* Dest = DestBuffer +  DestY * TextureSize  + DestX;

	//	for ( int y = 0; y < bitmap.rows ;y++ )
	//	{
	//		_byte* src = bitmap.buffer + ( y * bitmap.pitch );
	//		_byte* pDest = (_byte*)Dest;

	//		// ����һ��
	//		for ( int x = 0; x < bitmap.width; x ++ )
	//		{
	//			*pDest ++ = (*src++);
	//			*pDest ++ = 0xFF;
	//		}

	//		Dest += TextureSize;
	//	}
	//}

}