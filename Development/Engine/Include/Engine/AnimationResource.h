#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Model
	*  @{
	*/

	/** 
		���������ؼ�֡
	*/
	struct SkeletonAnimKeyframe
	{
		// ʱ���
		float		mTime;

		// λ��
		Vector3		mTranslation;

		// ��ת
		Quaternion	mRotation;

		friend BinarySerializer& operator <<( NekoEngine::BinarySerializer& Ser, SkeletonAnimKeyframe*& Data )
		{
			if ( Ser.IsLoading() )
			{
				Data = new SkeletonAnimKeyframe;
			}

			Ser << Data->mTime
				<< Data->mTranslation
				<< Data->mRotation;

			return Ser;
		}
	};

	typedef std::vector< SkeletonAnimKeyframe* > SkeletonAnimKeyframeArray;

	/** 
		�����������,��Ӧ��ͷ
	*/
	struct SkeletonAnimTrack
	{
		// ��ͷ
		int							mBoneID;

		// �ؼ�֡����
		SkeletonAnimKeyframeArray	mKeyframeArray;

		virtual ~SkeletonAnimTrack( );

		friend BinarySerializer& operator <<( NekoEngine::BinarySerializer& Ser, SkeletonAnimTrack*& Data )
		{
			if ( Ser.IsLoading() )
			{
				Data = new SkeletonAnimTrack;
			}

			Ser << Data->mBoneID
				<< Data->mKeyframeArray;

			return Ser;
		}
	};

	
	/** 
		����������Դ
	*/
	class SkeletonAnimResource : public ManagedObject
	{
		DECLARE_RTTI_CLASS( SkeletonAnimResource, ManagedObject, ClassFlag_Intrinsic| ClassFlag_Serializable )
	public:
		SkeletonAnimResource();
		virtual ~SkeletonAnimResource( );
		
		/// ���ö�������,�������ʱ��
		void SetDuration( float Duration ){ mDuration = Duration; }

		/// ��ö�������
		float GetDuration( ){ return mDuration; }

		/// ��ù������(��Ӧ��ͷ��)
		dword GetTrackCount( ){ return mTrackArray.size(); }

		/// ��ӹ��
		dword AddTrack( SkeletonAnimTrack* Track );

		virtual void Serialize( BinarySerializer& Ser );		

	private:
		friend class SkeletonAnimController;


		typedef std::vector< SkeletonAnimTrack* > SkAnimTrackArray;


		SkAnimTrackArray	mTrackArray;
		float		mDuration;

		void GetKeyframe( SkeletonAnimTrack* track, float time, SkeletonAnimKeyframe& frame1, SkeletonAnimKeyframe& frame2 );
		void SetKeyframe( SkeletonAnimTrack* track, float time, Vector3& translation, Quaternion& rotation );
	};

	typedef TRefPtr<SkeletonAnimResource> SkeletonAnimResourcePtr;
}
