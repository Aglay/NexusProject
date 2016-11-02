#include "EditorPCH.h"
#include "PrivateInclude.h"

//////////////////////////////////////////////////////////////////////////
// ActorFactoryEditor
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_RTTI_CLASS( ActorFactoryEditor )
Actor* ActorFactoryEditor::CreateActor( const WString& Name, void* Parameter )
{
	Actor* NewActor = GObjectManager->ConstructObject<Actor>( Name );

	NewActor->AddComponent<EditorDrawUtilityComponent>();
	NewActor->SetBoundingBox( AABB::cMaxBox );
	NewActor->SetFlag( EAF_Utility );

	return NewActor;
}



//////////////////////////////////////////////////////////////////////////
// EditorDrawUtilityComponent
//////////////////////////////////////////////////////////////////////////


IMPLEMENT_RTTI_CLASS( EditorDrawUtilityComponent)
EditorDrawUtilityComponent::EditorDrawUtilityComponent( )
{
	SetRenderQueueGroup( RQF_Overlay );
}
void EditorDrawUtilityComponent::Draw(SceneView* RV)
{
	ObjectModifier* Modifier = GEditorFrame->GetScenePanel()->GetObjectModifier();

	EditorObject* Obj = Modifier->GetSelectedObject();

	Canvas* Painter = RV->GetCanvas();

	// ѡ������ʱ����
	if ( Obj != null )
	{
		Camera* Cam = RV->GetCamera();

		for ( Actor* A = Obj->GetFirstActor();
			A != null;
			A = Obj->GetNextActor() )
		{
			Painter->PushTransform(A->GetFullTransform() * Cam->GetViewMatrix() * Cam->GetProjectMatrix());

			// �������СVectorתΪ�߽ǵ�
			Box BoxData( A->GetBoundingBox() );

			// ���Ʊ߽�Ч���İ󶨺�
			const float CornerLengthRate = 0.2f;
			for( dword SidePoint = 0;SidePoint < Box::MaxPoints;SidePoint++ )
			{
				const Box::NeighbourIndex& NBIndexArray = BoxData.GetNeighbourIndex( SidePoint );

				for ( dword NBIndex = 0; NBIndex < Box::MaxPointConnectSide; NBIndex++)
				{
					const Vector3& BasePoint = BoxData.mCornerPoint[SidePoint];

					Vector3 VecShort = ( BoxData.mCornerPoint[NBIndexArray.mNeighbourPoint[NBIndex]] - BasePoint ) * CornerLengthRate;

					Painter->DrawLine( BasePoint, BasePoint + VecShort, Color::cYellow );
				}
			}

			Painter->PopTransform();

		}
	}
	

	if ( Modifier->mIsVolumeSelecting )
	{
		// Ͷ�䷽ʽ����

		Vector2 P1( (float)Modifier->mVolumeSelectPt1.x, (float)Modifier->mVolumeSelectPt1.y );
		Vector2 P2( (float)Modifier->mVolumeSelectPt2.x, (float)Modifier->mVolumeSelectPt2.y );

		Painter->DrawTile( P1, P2 - P1, Vector2::cZero, Vector2::cOne, Color( 0.2f, 0.49f, 0.52f,0.86f ), GWhiteTexture, 	BLEND_Translucent );
		Painter->DrawRect2D( P1, P2, Color( 1.0f, 0.49f, 0.52f,0.86f ) );
	}
}

//void EditorDrawUtilityComponent::Tick( float Elapse )
//{
//
//}
