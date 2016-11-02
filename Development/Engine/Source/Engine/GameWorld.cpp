#include "EnginePCH.h"
#include "NekoEngine_System.h"
#include "NekoEngine_Model.h"
#include "NekoEngine_Extend.h"

namespace NekoEngine
{
	IMPLEMENT_RTTI_CLASS( GameWorld )

	const wchar* cNullActorFactoryString = L"@NullActorFactory";
	const wchar* cWorldRootActorName = L"@WorldRoot";

	GameWorld::GameWorld( dword Index )
	{
		mRenderQueue = new RenderQueue;

		mRootActor = GObjectManager->ConstructObject<Actor>( StringHelper::FormatString(L"%s%d",cWorldRootActorName, Index ) );

		mRootActor->AddRef();

		// ��������ͼ�ͷ
		mRootActor->AddComponent<GridAxisComponent>( );

		// ���ڵ���Զ�ɼ�
		mRootActor->SetBoundingBox( AABB::cMaxBox );

	
	}

	GameWorld::~GameWorld()
	{
		Kill(  mRootActor );

		mRootActor->RemoveRef();

		mRootActor->RemoveAllChild();

		GObjectManager->DestructObject( mRootActor );

		mRootActor = null;

		for ( ActorFactoryMap::iterator it( mActorFactoryMap );it;++it)
		{
			ActorFactory* Factory = it.get_value();
			delete Factory;
		}

		mActorFactoryMap.clear();


		SafeDelete( mRenderQueue );
	}







	Actor* GameWorld::SpawnActor( RTTIClass* FactoryClass, const WString& Name, Actor* Parent, void* Parameter )
	{
		ActorFactory* Factory = GetActorFactory( FactoryClass );

		if ( Factory == null )
		{
			Factory = mActorFactoryMap.set( FactoryClass, RTTI_CAST(ActorFactory, FactoryClass->CreateInstance() ) );
			Factory->mOwner = this;
		}

		Actor* A = Factory->CreateActor( Name, Parameter );
		if ( A == null )
			return A;

		A->mWorld = this;
		A->mFactoryClass = FactoryClass;

		// Worldֻ�����һ������,Actor��ʹ���������ջ���
		A->AddRef();

		if ( Parent == null )
			Parent = mRootActor;

		Parent->AddChild( A );

		return A;
	}




	void GameWorld::Draw( SceneView* RV )
	{
		mRenderQueue->Clear();

		mRootActor->RefreshCombineBoundingBox( );

		mRootActor->FindVisibleObject( RV, mRenderQueue );

		mRenderQueue->Draw( RV );
	}

	Camera* GameWorld::GetCamera( const WString& Name )
	{
		CameraActor* CamObj = RTTI_CAST( CameraActor, GObjectManager->FindObject( RTTI_CLASS_INFO(CameraActor), Name ) );
		if ( CamObj == null )
			return null;

		return CamObj->GetCamera();
	}

	void GameWorld::Kill( const WString& Name, RTTIClass* ClassInfo )
	{
		Kill( GetActor( Name, ClassInfo ) );
	}	

	Actor* GameWorld::GetActor( const WString& Name, RTTIClass* ClassInfo  )
	{
		return RTTI_CAST( Actor, GObjectManager->FindObject( ClassInfo, Name ) );
	}

	void GameWorld::Kill( Actor* A )
	{
		// ����ɾ����
		for ( Actor* Child = A->GetChildFirst(); 
			Child != null; 
			Child = A->GetChildNext() )
		{
			Kill( Child );
		}

		// ɾ���Լ�
		if ( A != mRootActor )
		{
			A->RemoveAllChild();


			Actor* Parent = A->GetParent();
			
			if ( Parent != null )
				Parent->RemoveChild( A );

			// ����������������������Ĺ���
			CameraActor* CamA = A->Cast<CameraActor>( );
			if ( CamA != null )
			{
				GEngine->NotifyDestoryCamera( CamA->GetCamera() );
			}

			// ɾ��World���������
			A->RemoveRef();

			// ��ǰɾ��,�����Զ���������
			GObjectManager->DestructObject( A );
		}
	}


	dword GetActorCountViaFlag( Actor* Parent, dword IncludeFlag )
	{
		dword ActorCount = 0;

		for ( Actor* Child = Parent->GetChildFirst(); 
			Child != null; 
			Child = Parent->GetChildNext() )
		{
			// ���ܱ���༭�����
			if ( !Child->HasFlag( IncludeFlag ) )
				continue;

			ActorCount++;
		}

		return ActorCount;
	}

	void GameWorld::SerializeActors( BinarySerializer& Ser, Actor* Parent, dword IncludeFlag, ActorArray* RootChildActors )
	{
		if ( Ser.IsLoading() )
		{
			dword ChildCount = 0;
			WString FactoryClassString;
			WString ActorName;

			Ser << ChildCount
				<< FactoryClassString 
				<< ActorName;

		
			Actor* ThisActor;

			if ( FactoryClassString != cNullActorFactoryString )
			{
				RTTIClass* FactoryClass = RTTIObject::FindClass( NameRef( FactoryClassString.c_str(), NameBuild_Find ) );

				Assert( FactoryClass != null );
				if ( FactoryClass == null )
					return;

				ThisActor = SpawnActor( FactoryClass, ActorName, Parent );


				ThisActor->Serialize( Ser );

				if ( Parent == mRootActor && RootChildActors != null )
				{
					RootChildActors->push_back( ThisActor );
				}
			}
			else
			{
				ThisActor = Parent;
			}


			for (dword i = 0 ;i< ChildCount; i++)
			{
				SerializeActors( Ser, ThisActor, IncludeFlag, RootChildActors );
			}
		}
		else
		{
			

			Ser << GetActorCountViaFlag( Parent , IncludeFlag );

			if ( Parent->mFactoryClass == null )
				Ser << cNullActorFactoryString;
			else
				Ser << Parent->mFactoryClass->GetRTTIClassString();

				Ser << Parent->GetName();

			if ( Parent->mFactoryClass != null )
			{
				Parent->Serialize( Ser );
			}

			for ( Actor* Child = Parent->GetChildFirst(); 
				Child != null; 
				Child = Parent->GetChildNext() )
			{
				// ���ܱ���༭�����
				if ( !Child->HasFlag( IncludeFlag ) )
					continue;

				SerializeActors( Ser, Child, IncludeFlag );
			}
		}
	}

	

	void GameWorld::IsolateFromSystem( Actor* A )
	{
		GObjectManager->RemoveNamedObject( A );

		for ( Actor* Child = A->GetChildFirst();
			Child != null;
			Child = A->GetChildNext() )
		{
			IsolateFromSystem( Child );
		}
	}

	void GameWorld::RestoreFromSystem( Actor* A )
	{
		GObjectManager->AddNamedObject(A);

		for ( Actor* Child = A->GetChildFirst();
			Child != null;
			Child = A->GetChildNext() )
		{
			RestoreFromSystem( Child );
		}
	}

	void GameWorld::Serialize( BinarySerializer& Ser )
	{
		SerializeActors( Ser, mRootActor, 0 );
	}



}