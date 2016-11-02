#include "EngineDemoPCH.h"
#include "PCH_Scene.h"


IMPLEMENT_RTTI_CLASS(Demo_Font)

Demo_Font::Demo_Font()
{

}


void Demo_Font::OnCreate()
{
	

	RenderFont::StaticInit();
}

void Demo_Font::OnEnter()
{

	GEngine->GetRenderTarget( 0 )->AddListener( this );

	mFontObject = new RenderFont( L"����", L"", 10, 0, false,false, false);

}

void Demo_Font::OnLeave()
{
	delete mFontObject;
}

void Demo_Font::OnDestroy()
{
	RenderFont::StaticExit();
}

void Demo_Font::OnUpdate( float elapse )
{
	
}

void Demo_Font::PostSceneViewDraw( SceneView* RV )
{
	//Vector2 v1, v2;
	//mFontObject->GetFontTexture( L'��', v1, v2 );

	const wchar* a = L" : 554,user(gl#10002625) lock bean total cost 31, time�����Ƿ����ɽ����׶����� ���Ѳ������� ��Ѷ�����Ƴ���Ͷ�� ���ӱ��� ս������6ǧ�����ˡ�ȫ����·���ٵ�ͼ�������� ����ͣ��9�Ը����г����ݵǴ����ݽ� ���й�����Ϊ�����������ҵ����";
	RV->GetCanvas()->DrawString( mFontObject, Vector2(100, 100), Color::cWhite, L"����Console.Print(\"hello world\");");
	if ( 0 )
	{
		mFontObject->Save(L"t.png");
	}
}
