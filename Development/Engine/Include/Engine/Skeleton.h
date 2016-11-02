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
		����
	*/
	class SkeletonInstance 
	{
	public:
		SkeletonInstance( SkeletonMeshResource* skeleton );
		virtual ~SkeletonInstance( );

		/// �������ƻ�ȡ����ID
		dword GetBoneID( const wchar* bonename );

		/// ��ȡ����
		BoneContent* GetBone( dword boneid );

		/// �������ƻ�ù�������
		BoneContent* GetBone( const wchar* bonename );

		/// ��ȡ��������
		dword GetBoneCount( );

		/// ����Ӱ���
		void SetInfluence( BoneContent* bone, const Vector3& translation, const Quaternion& rotation );

		/// ���Ӱ���
		void ClearInfluence( );

		/// ��������󶨺�
		AABB CaculateSkeletonBoundingBox( );

	public:
		virtual void Tick( float elapse );

	private:
		void CaculateSkeletonBoundingBox( AABB& BoneBox, BoneContent* Bone );
		


	private:
		void UpdateBone( BoneContent* bone );
		

		friend class SkeletonAnimController;
		friend class ActorHelperComponent;
		BoneContent*	mInfluenceBone;
		Vector3			mInfluenceTranslation;
		Quaternion		mInfluenceRotation;
		BoneArray		mBoneArray;
		MappingArray	mRootArray;
	};

	/** @} */
	/** @} */
}
