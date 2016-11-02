#include "EnginePCH.h"
#include "NekoEngine_System.h"
#include "NekoEngine_Model.h"

namespace NekoEngine
{
	//////////////////////////////////////////////////////////////////////////
	// ActorComponent
	//////////////////////////////////////////////////////////////////////////

	IMPLEMENT_RTTI_CLASS( ActorComponent )
	ActorComponent::ActorComponent()
		: mIndex( 0 )
		, mOwner( null )
	{

	}

	void ActorComponent::Tick( float Elapse )
	{

	}


	//////////////////////////////////////////////////////////////////////////
	// GridAxisComponent
	//////////////////////////////////////////////////////////////////////////


	IMPLEMENT_RTTI_CLASS( GridAxisComponent)
	void GridAxisComponent::Draw(SceneView* RV)
	{

		if ( RV->GetCamera() != null )
		{
			RenderHelper::DrawAxisGrid( RV->GetCamera(),  RV->GetCanvas(), RV->GetViewport()  );
			RenderHelper::DrawAxisDirection( RV->GetCamera(), RV->GetCanvas(), RV->GetViewport() );
		}

	}


	//////////////////////////////////////////////////////////////////////////
	// ActorHelperComponent
	//////////////////////////////////////////////////////////////////////////
	IMPLEMENT_RTTI_CLASS( ActorHelperComponent)
	ActorHelperComponent::ActorHelperComponent( )
	: mBoundingBoxColor( Color::cGreen )
	, mShowBoundingBox( true )
	, mShowSkeleton( true )
	, mBoneStartColor( Color::cRed )
	, mBoneEndColor( Color::cWhite )
	{

	}

	void ActorHelperComponent::Draw( SceneView* RV )
	{
		Camera* Cam = RV->GetCamera();

		// Ͷ�䷽ʽ����
		RV->GetCanvas()->PushTransform( mOwner->GetFullTransform() * Cam->GetViewMatrix() * Cam->GetProjectMatrix() );
		

		if ( mShowBoundingBox )
		{
			// �������СVectorתΪ�߽ǵ�
			Box BoxData( mOwner->GetBoundingBox() );


			dword NoneSharedPoint = 0;

			// һ��12���ߣ�24����
			while( NoneSharedPoint < Box::MaxNoneSharedPoint )
			{
				// ������ȡ���߽ǵ�λ��
				Vector3& P1 = BoxData.mCornerPoint[ BoxData.GetSideIndex( NoneSharedPoint++ ) ];
				Vector3& P2 = BoxData.mCornerPoint[ BoxData.GetSideIndex( NoneSharedPoint++ ) ];
				RV->GetCanvas()->DrawLine( P1, P2 , mBoundingBoxColor );
			}

		}


		// ���ƹǼ�
		SkeletonMeshComponent* SMComponent = mOwner->GetComponent<SkeletonMeshComponent>( );
		if ( SMComponent != null && mShowSkeleton )
		{
			SkeletonInstance* Skeleton = SMComponent->GetSkeleton();

			DrawSkeleton( Skeleton, RV->GetCanvas()  );
		}

		RV->GetCanvas()->PopTransform();
	}


	void ActorHelperComponent::DrawSkeleton( SkeletonInstance* Skeleton, Canvas* Painter )
	{
		if ( Skeleton == null )
			return;

		for ( dword i = 0; i < Skeleton->mRootArray.size(); i ++ )
		{
			BoneContent* Bone = Skeleton->GetBone( Skeleton->mRootArray.at( i ) );

			DrawSkeleton( Skeleton, Painter , Bone );
		}

	}

	void ActorHelperComponent::DrawSkeleton( SkeletonInstance* Skeleton, Canvas* Painter, BoneContent* Bone )
	{
		BatchedElements Batcher;

		for ( dword i = 0; i < (dword)Bone->mChildArray.size(); i ++ )
		{
			BoneContent* Child = Skeleton->GetBone( Bone->mChildArray[i] );

			if ( Child == null )
				continue;

			Painter->DrawLine( Bone->mAbsoluteTranslation,Child->mAbsoluteTranslation, mBoneStartColor, mBoneEndColor );			

			DrawSkeleton( Skeleton, Painter, Child );
		}
	}

	void ActorHelperComponent::StaticInitProperty()
	{
		// @TODO RTTIClass������һ��StaticConstruct����ʼ�����ԣ�Ҫ�����е��඼��ʵ��

		PropertyCollection* PC = RTTI_CLASS_INFO(ActorHelperComponent)->GetPropertyCollection( );
		PC->Add( PROPERTY_MEMBER_VAR( ActorHelperComponent,Color, mBoundingBoxColor ) );
		PC->Add( PROPERTY_MEMBER_VAR( ActorHelperComponent,Color, mBoneStartColor ) );
		PC->Add( PROPERTY_MEMBER_VAR( ActorHelperComponent,Color, mBoneEndColor ) );
		PC->Add( PROPERTY_MEMBER_VAR( ActorHelperComponent,bool, mShowBoundingBox ) );
		PC->Add( PROPERTY_MEMBER_VAR( ActorHelperComponent,bool, mShowSkeleton ) );
	}


	//////////////////////////////////////////////////////////////////////////
	// GeometryComponent
	//////////////////////////////////////////////////////////////////////////
	IMPLEMENT_RTTI_CLASS( GeometryComponent)
	GeometryComponent::GeometryComponent()
		: mPickID( 0 )
		, mRenderQueueGroup( RQF_Default )
	{

	}








}