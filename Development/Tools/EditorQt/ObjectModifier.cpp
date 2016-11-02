#include "EditorPCH.h"
#include "PrivateInclude.h"




ObjectModifier::ObjectModifier()
: mEditorAxis( AAxis_None )
, mLastTranslationDelta( Vector3::cZero )
, mIsAdjustingGizmo( false )
, mIsVolumeSelecting( false )
, mGizmoAdjustMode( AdjustMode_None )
, mGizmoAdjustSpace( AdjustSpace_World )
, mSelectedObject( null )
{	



	mSelectedObject = new EditorObject;
}


ObjectModifier::~ObjectModifier( )
{
	SafeDelete( mSelectedObject );
}


void ObjectModifier::Initialize( GameWorld* World )
{
	mWorld = World;

	mEditorHelper = World->SpawnActor( RTTI_CLASS_INFO(ActorFactoryEditor), L"@EditorHelper" );
	

	CreateGizmo();	

	// ��ʼ���Դ��������
}




Actor* ObjectModifier::PickSingleObject( const Ray& PickRay )
{

	WorldPick Pick( mWorld ) ;

	ActorFactoryGizmo* GizmoFactory = mWorld->GetActorFactory<ActorFactoryGizmo>( );
	Assert( GizmoFactory != null );

	// �Խ������
	if ( Pick.Pick( PickRay, true ) )
	{
		for( dword i = 0;i < Pick.GetCount(); i++)
		{
			Actor* A = Pick.GetActor(i);

			// ��ȡGizmo
			eAdjustAxis Part = GizmoFactory->CheckGizmoPart( A );
			if ( Part != AAxis_None )
				continue;

			return A;
		}	
	}

	return null;
}


void ObjectModifier::OnMouseLeftButtonDown( const Point& MP )
{
	BeginAdjustGizmo( MP );

	// û��ѡ�е���,�Ϳ��Կ�ʼ��ѡ
	if ( mEditorAxis == AAxis_None )
	{
		mVolumeSelectPt1 = mVolumeSelectPt2 = MP;
		mIsVolumeSelecting = true;
	}
	
}

void ObjectModifier::OnMouseLeftButtonUp( const Point& MP )
{
	if ( mIsAdjustingGizmo )
	{
		EndAdjustGizmo( );

		GEditorFrame->OnObjectChangeProperties( mSelectedObject );

		// �е�������������ʱ,��Ҫ����Node�Ĵ�С
		mSelectedObject->UpdateWrapper();
	}
	else
	{	
		if ( mIsVolumeSelecting )
		{
			if (!VolumeSelect( mVolumeSelectPt1, mVolumeSelectPt2))
			{
				// �������ѡ������̫С,���е�ѡ
				SingleSelect( MP );
			}

			mIsVolumeSelecting = false;
		}
		else
		{
			// û�ж�ѡʱ,��ѡ
			SingleSelect( MP );
		}
	
	}

	
}


void ObjectModifier::OnMouseMove( const Point& MP )
{
	AdjustGizmo( MP );

	// ���¿�ѡĿ��
	if ( mIsVolumeSelecting )
	{
		mVolumeSelectPt2 = MP;
	}
}





EditorObject* ObjectModifier::GetSelectedObject()
{
	return mSelectedObject;
}



void ObjectModifier::CmdSetSelection( const SelectedActorArray& SelectedActor, bool KeepOld, bool Remove )
{
	EditorObject* SelObj = null;

	// ����Ƿ����ظ�ѡ��
	bool SameSelection = true;

	// ѡ����һ��,�������
	if ( SelectedActor.size() == mSelectedObject->GetActorCount() )
	{
		for ( dword i = 0;i< SelectedActor.size();i ++ )
		{
			Actor* A = SelectedActor[i];

			if ( !mSelectedObject->Exists( A ) )
			{
				SameSelection = false;
				break;
			}
		}
	}
	else
	{
		SameSelection = false;
	}

	// ����ͬ��ѡ�񲻽���cmd��¼, ��������ѡ�����
	if ( SameSelection && !Remove )
		return;



	CmdActorSelect* Cmd = new CmdActorSelect( GetSelectedObject() );
	if ( SelectedActor.size() > 0 )
	{
		// ����Ҫ����������, ����Ҫ��ѡʱ,�����ǰѡ��
		if ( !KeepOld && !Remove )
		{
			mSelectedObject->Clear();	
		}


		for ( dword i = 0;i< SelectedActor.size();i ++ )
		{
			Actor* A = SelectedActor[i];

			// ��ѡ
			if ( Remove )
			{
				mSelectedObject->Remove( A );
			}
			else
			{
				// ���ڵ�ȡ��ѡ��, û�е�,ѡ��
				if ( mSelectedObject->Exists( A ) )
					mSelectedObject->Remove( A );
				else
					mSelectedObject->Add( SelectedActor[i] );
			}
		}

		mSelectedObject->UpdateWrapper();
	}
	else
	{
		mSelectedObject->Clear();
	}


	GCommandManager->Add( Cmd );

	mGizmo->SetVisible( mSelectedObject->GetActorCount() > 0 );

	GEditorFrame->OnObjectSelectionChange( mSelectedObject );
}


void ObjectModifier::SingleSelect( const Point& MP )
{
	SceneView* View = GEditorFrame->GetScenePanel()->GetRenderWindow()->GetView( 0 );

	Ray PickRay = View->CreateRay( MP.x, MP.y );

	Actor* A = PickSingleObject( PickRay );

	SelectedActorArray SelectedArray;

	if ( A != null )
		SelectedArray.push_back( A );

	IInputDriver* InputDrv = GEditorFrame->GetScenePanel()->GetRenderWindow()->GetInputDriver();

	CmdSetSelection(	SelectedArray, 
		InputDrv->IsKeyDown(KB_LeftControl),
		InputDrv->IsKeyDown(KB_LeftAtl) );
}

Vector3 ObjectModifier::GetGroupSpawnPoint( const Point& MP )
{
	SceneView* View = GEditorFrame->GetScenePanel()->GetRenderWindow()->GetView( 0 );

	Ray PickRay = View->CreateRay( MP.x, MP.y );

	float Distance = 0.0f;
	Plane::Intersect( PickRay, Plane::cXYPlane, Distance );

	return PickRay.DistanceVector( Distance );
}

bool ObjectModifier::VolumeSelect( const Point& Pt1, const Point& Pt2 )
{
	int Left	= Math::Min( Pt1.x, Pt2.x ) + 1;
	int Right	= Math::Max( Pt1.x, Pt2.x ) - 1;
	int Top		= Math::Min( Pt1.y, Pt2.y ) + 1;
	int Bottom	= Math::Max( Pt1.y, Pt2.y ) - 1;


	const float MinPickDistance = 3.0f;

	const float MaxPickDistance = 20.0f;

	const int MinAreaSelect = 4;
	if ( ( Right - Left ) <= MinAreaSelect || ( Bottom - Top ) <= MinAreaSelect )
		return false;

	SceneView* View = GEditorFrame->GetScenePanel()->GetRenderWindow()->GetView( 0 );

	PlaneBoundedVolume BoundVolume( View->CreateRay( Left, Top ), 
		View->CreateRay( Right, Top), 
		View->CreateRay( Left, Bottom), 
		View->CreateRay( Right, Bottom ),
		MinPickDistance,
		MaxPickDistance
		);

	GameWorld* World = GEditorFrame->GetScenePanel()->GetWorld();

	WorldPick Pick( World );

	if ( !Pick.Pick( BoundVolume ) )
		return true;

	FRect ScreenArea( (float)Left / View->GetWidth(), (float)Top / View->GetHeight(), (float)Right / View->GetWidth(), (float)Bottom/ View->GetHeight() );


	SelectedActorArray SelectedArray;

	// �����󶨺�ʰȡ���
	for( dword i = 0;i < Pick.GetCount(); i++)
	{
		Actor* A = Pick.GetActor(i);

		// ����ʰȡ�༭�����
		if ( A->HasFlag( EAF_Utility) )
			continue;

		// Mesh��ȷʰȡ
		if (!A->Pick( View, ScreenArea ))
			continue;

		SelectedArray.push_back( A );
	}

	IInputDriver* InputDrv = GEditorFrame->GetScenePanel()->GetRenderWindow()->GetInputDriver();

	CmdSetSelection(	SelectedArray, 
		InputDrv->IsKeyDown(KB_LeftControl),
		InputDrv->IsKeyDown(KB_LeftAtl) );

	return true;
}