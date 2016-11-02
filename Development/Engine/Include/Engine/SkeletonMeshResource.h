#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Model
	*  @{
	*/

	struct BoneContent;

	typedef std::vector< BoneContent* > BoneArray;
	typedef std::vector<dword> MappingArray;

	/** 
		��ͷ
	*/
	struct BoneContent
	{
		WString			mName;
		int 			mParentID;
		MappingArray	mChildArray;

		Vector3			mRelativeTranslation;
		Quaternion		mRelativeRotation;
		Vector3			mAbsoluteTranslation;
		Quaternion		mAbsoluteRotation;

		Vector3			mRelativeTranslationInit;
		Quaternion		mRelativeRotationInit;

		Vector3			mLocalTranslationBoneSpace;
		Quaternion		mLocalRotationBoneSpace;
		Vector3			mLocalTranslation;
		Quaternion		mLocalRotation;

		friend BinarySerializer& operator <<( NekoEngine::BinarySerializer& Ser, BoneContent*& Data )
		{
			if ( Ser.IsLoading() )
			{
				Data = new BoneContent;
			}

			Ser << Data->mName 
				<< Data->mParentID
				<< Data->mRelativeTranslation
				<< Data->mRelativeRotation
				<< Data->mLocalTranslationBoneSpace
				<< Data->mLocalRotationBoneSpace;				

			if ( Ser.IsLoading() )
			{
				Data->mRelativeTranslationInit = Data->mRelativeTranslation;
				Data->mRelativeRotationInit = Data->mRelativeRotation;
			}

			return Ser;
		}
	};

	/** 
		�����Shader�ģ���һ��һ���ֲ�Skin��Ҫ�õ��Ĺ�������
	*/
	struct BoneShaderData
	{
		typedef std::vector<Matrix4> BoneLocalMatrix;

		dword					mSharedBoneCount;
		BoneLocalMatrix			mBoneLocalMatrixArray;
	};

	typedef std::vector<BoneShaderData> BoneShaderBuffer;

	/// ��ƤҪʹ�õ��Ĺ�������
	typedef std::vector<dword> BoneIndexArray;			// ��¼ÿ����ģ��ʹ�õĹ�����Ϣ

	/// ����ģ�Ͷ�������
	class SkeletonMeshVertexFactory : public MeshVertexFactory
	{
		DECLARE_RTTI_CLASS( SkeletonMeshVertexFactory, MeshVertexFactory, ClassFlag_Intrinsic )

	public:
		BoneIndexArray		mBoneIndices;
	};
	
	/** 
		����ģ����Դʵ��
	*/
	class SkeletonMeshResource : public MeshResource
	{
		DECLARE_RTTI_CLASS( SkeletonMeshResource, MeshResource, ClassFlag_Intrinsic|ClassFlag_Serializable )
	public:
		SkeletonMeshResource( );

		virtual ~SkeletonMeshResource( );

		/// ��ӹ�ͷ
		dword AddBone( BoneContent* Bone );

		/// ��ȡ��ͷ
		BoneContent* GetBone( dword boneid );

		/// ���ɹ�����Ƥ�Ĺ�������
		BoneShaderData* GenBoneIndexMatrix( BoneShaderBuffer& DataArray, SkeletonInstance* Skeleton, dword MeshContentIndex);

	public:
		virtual void Serialize( BinarySerializer& Ser );

	protected:
		void BuildBoneIndex( );
		
	private:
		friend class SkeletonInstance;
		BoneArray		mBoneArray;
		MappingArray	mRootArray;
	};

	typedef TRefPtr<SkeletonMeshResource> SkeletonMeshResourcePtr;

	/** @} */
	/** @} */
}

