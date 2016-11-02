#include "EnginePCH.h"
#include "NekoEngine_System.h"

namespace NekoEngine
{
	MovableObject::MovableObject()
		: mNeedRebuildMatrix( true )
		, mPosition( Vector3::cZero )
		, mScale( Vector3::cOne )
		, mRotation( Quaternion::cIdentity )
		, mInheritRotate( true )
		, mInheritScale( true )
		, mDerivedPosition( Vector3::cZero )
		, mDerivedRotation( Quaternion::cIdentity )
		, mDerivedScale( Vector3::cOne )
		, mNeedParentUpdateType( TT_None )
		, mNotifyTransform( false )
	{
	}

	MovableObject::~MovableObject()
	{


	}


	void MovableObject::Translate( const Vector3& Value, eTransformSpace Space )
	{
		switch ( Space )
		{
		case TS_Local:
			// �ڸ�������ת��,�ٵ����Լ�����ת
			mPosition += mRotation * Value;
			break;
		case TS_World:
			// position is relative to parent so transform upwards
			if (GetParentMovable())
			{
				mPosition += (GetParentMovable()->GetDerivedRotation().Inverse() * Value )
					/ GetParentMovable()->GetDerivedScale();
			}
			else
			{
				mPosition += Value;
			}

			break;
		case TS_Parent:
			mPosition += Value;
			break;
		}

		NeedUpdateTransform( TT_Position );

	}	
	void MovableObject::Rotate( const Quaternion& Value, eTransformSpace Space )
	{
		Quaternion NormalizedRot = Value;
		NormalizedRot.Normalize();

		switch ( Space )
		{
		case TS_Local:
			// �ڸ�������ת��,�ٵ����Լ�����ת
			mRotation = NormalizedRot * mRotation;
			break;
		case TS_World:
			mRotation = mRotation * GetDerivedRotation().Inverse()
				* NormalizedRot * GetDerivedRotation();
			break;
		case TS_Parent:
			mRotation *= NormalizedRot;
			break;
		}

		NeedUpdateTransform( TT_Rotation );		
	}


	void MovableObject::Scale( const Vector3& Value )
	{
		mScale *= Value;

		NeedUpdateTransform( TT_Scale );
	}



	void MovableObject::SetPosition( const Vector3& Value )
	{
		mPosition = Value;

		NeedUpdateTransform( TT_Position );
	}

	void MovableObject::SetRotation( const Quaternion& Value )
	{
		mRotation = Value;

		NeedUpdateTransform( TT_Rotation );
	}

	void MovableObject::SetScale( const Vector3& Value )
	{
		mScale = Value;		

		NeedUpdateTransform( TT_Scale );
	}

	const Vector3& MovableObject::GetPosition()
	{
		return mPosition;
	}

	const Quaternion& MovableObject::GetRotation()
	{
		return mRotation;
	}

	const Vector3& MovableObject::GetScale()
	{
		return mScale;
	}

	void MovableObject::SetInheriteScale( bool IsInherite )
	{
		mInheritScale = IsInherite;

		NeedUpdateTransform( TT_InheritScale );
	}

	bool MovableObject::GetInheriteScale( )
	{
		return mInheritScale;
	}

	void MovableObject::SetInheriteRotate( bool IsInherite )
	{
		mInheritRotate = IsInherite;

		NeedUpdateTransform( TT_InheritRotate );
	}

	bool MovableObject::GetInheriteRotate( )
	{
		return mInheritRotate;
	}

	void MovableObject::ResetRotation()
	{
		mRotation = Quaternion::cIdentity;

		NeedUpdateTransform( TT_Rotation );
	}

	const Matrix4& MovableObject::GetFullTransform()
	{
		if ( mNeedParentUpdateType || mNeedRebuildMatrix )
		{
			mFullTransform.FromTransform( GetDerivedPosition(), GetDerivedRotation(), GetDerivedScale() );			
			mNeedRebuildMatrix = false;
		}

		return mFullTransform;
	}

	void MovableObject::NeedUpdateTransform( dword TransformType )
	{
		mNeedParentUpdateType |= TransformType;
	}

	void MovableObject::UpdateFromParent( )
	{
		if ( GetParentMovable() != null )
		{
			// ������ת
			const Quaternion& ParentRotation = GetParentMovable()->GetDerivedRotation();
			if (mInheritRotate)
			{
				// �ϲ�������ת
				mDerivedRotation = ParentRotation * mRotation;
			}
			else
			{
				// ������������ת
				mDerivedRotation = mRotation;
			}

			// ��������
			const Vector3& ParentScale = GetParentMovable()->GetDerivedScale();
			if (mInheritScale)
			{
				mDerivedScale = ParentScale * mScale;
			}
			else
			{
				// ������������ת
				mDerivedScale = mScale;
			}

			// ���ڸ���������ϵ����ת�ı��Լ���λ��
			mDerivedPosition = ParentRotation * (ParentScale * mPosition);

			// �ٵ��Ӹ���λ��
			mDerivedPosition += GetParentMovable()->GetDerivedPosition();

			for ( MovableObject* A = GetFirstMovable();
				A != null; 
				A = GetNextMovable() )
			{
				A->NeedUpdateTransform( TT_All );
			}
		}
		else
		{
			mDerivedPosition = mPosition;
			mDerivedRotation = mRotation;
			mDerivedScale	 = mScale;
		}

		if ( !mNotifyTransform )
		{
			mNotifyTransform = true;
			OnObjectTransformed( mNeedParentUpdateType );
			mNotifyTransform = false;
		}
		

		mNeedParentUpdateType = TT_None;

		// �����ؽ�
		mNeedRebuildMatrix = true;
	}

	const Quaternion& MovableObject::GetDerivedRotation( )
	{
		if ( mNeedParentUpdateType )
		{
			UpdateFromParent();
		}

		return mDerivedRotation;
	}

	const Vector3& MovableObject::GetDerivedPosition( )
	{
		if ( mNeedParentUpdateType )
		{
			UpdateFromParent();
		}

		return mDerivedPosition;
	}

	const Vector3& MovableObject::GetDerivedScale( )
	{
		if ( mNeedParentUpdateType )
		{
			UpdateFromParent();
		}

		return mDerivedScale;
	}

	Vector3 MovableObject::WorldToLocalPosition( const Vector3 &WorldPos )
	{
		if (mNeedParentUpdateType)
		{	
			UpdateFromParent();
		}
		return mDerivedRotation.Inverse() * (WorldPos - mDerivedPosition) / mDerivedScale;
	}
	//-----------------------------------------------------------------------
	Vector3 MovableObject::LocalToWorldPosition( const Vector3 &LocalPos )
	{
		if (mNeedParentUpdateType)
		{
			UpdateFromParent();
		}
		return (mDerivedRotation * LocalPos * mDerivedScale) + mDerivedPosition;
	}
	//-----------------------------------------------------------------------
	Quaternion MovableObject::WorldToLocalRotation( const Quaternion &WorldRotation )
	{
		if (mNeedParentUpdateType)
		{
			UpdateFromParent();
		}
		return mDerivedRotation.Inverse() * WorldRotation;
	}
	//-----------------------------------------------------------------------
	Quaternion MovableObject::LocalToWorldRotation( const Quaternion &LocalRotation )
	{
		if (mNeedParentUpdateType)
		{
			UpdateFromParent();
		}
		return mDerivedRotation * LocalRotation;

	}


	void MovableObject::SetDerivedPosition( const Vector3& Value )
	{
		//SetPosition( WorldToLocalPosition( Value ) );

		MovableObject* Parent = GetParentMovable();

		if ( Parent )
		{
			Quaternion Rot = Parent->GetDerivedRotation().Inverse();


			Vector3 NewPos = ( Value - Parent->GetDerivedPosition() ) / Parent->GetDerivedScale();

			SetPosition( Rot *NewPos   );
		}
		else
		{
			SetPosition( Value );
		}
	}

	void MovableObject::SetDerivedRotation( const Quaternion& Value )
	{
		//SetRotation( WorldToLocalRotation( Value ) );

		MovableObject* Parent = GetParentMovable();
		if ( Parent )
		{
			SetRotation( Parent->GetDerivedRotation().Inverse() * Value );
		}
		else
		{
			SetRotation( Value );
		}	
	}

	void MovableObject::SetDerivedScale( const Vector3& Value )
	{
		MovableObject* Parent = GetParentMovable();
		if ( Parent )
		{
			const Vector3& ParentScale = Parent->GetDerivedScale();

			Vector3 Final;
			if ( ParentScale.x != 0.0f )
				Final.x = Value.x / ParentScale.x;
			if ( ParentScale.y != 0.0f )
				Final.y = Value.y / ParentScale.y;
			if ( ParentScale.z != 0.0f )
				Final.z = Value.z / ParentScale.z;

			SetScale( Final );
		}
		else
		{
			SetScale( Value );
		}
	}

	void MovableObject::SetViewTarget( const Vector3& Value, bool UpFixed )
	{
		Vector3 ViewDir = ( Value - GetDerivedPosition() ).Normalize();

		if ( UpFixed )
		{
			// ����ViewDirͶӰ�������ʸ��
			Vector3 GroundVector( ViewDir.x, ViewDir.y, 0.0f );

			// ����ǰ������Ҫ��ת��ˮƽ��ת��
			Quaternion RotZ;
			RotZ.Rotation( Vector3::cXAxis, GroundVector );

			// ����Ͷ�䵽����ʸ����ViewDir�Ĵ�ֱ��ת��
			Quaternion RotY;
			RotY.Rotation( GroundVector, ViewDir );

			// �ϲ���ת
			SetDerivedRotation( RotY * RotZ );
		}
		else
		{
			Quaternion Rot;
			Rot.Rotation( Vector3::cXAxis,  ViewDir );

			SetDerivedRotation( Rot );
		}
	}

	Vector3 MovableObject::GetViewDir( )
	{
		return GetDerivedRotation().GetXAxis();
	}

	void MovableObject::Serialize( BinarySerializer& Ser )
	{
		Ser << mPosition 
			<< mScale 
			<< mRotation
			<< mInheritScale
			<< mInheritRotate;
	}

}