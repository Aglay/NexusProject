#include "EnginePCH.h"
#include "NekoEngine_Model.h"

namespace NekoEngine
{
	IMPLEMENT_RTTI_CLASS( SkeletonMeshVertexFactory)
	IMPLEMENT_RTTI_CLASS( SkeletonMeshResource)

	#define USE_SHARE_BONE_ARRAY

	SkeletonMeshResource::SkeletonMeshResource()
	{

	}

	SkeletonMeshResource::~SkeletonMeshResource()
	{
		// �ͷŹ���
		for ( dword i = 0; i < (dword)mBoneArray.size(); i ++ )
			delete mBoneArray[i];

		mRootArray.clear( );
		mBoneArray.clear( );

	}

	void SkeletonMeshResource::Serialize( BinarySerializer& Ser )
	{
		Super::Serialize( Ser );

		Ser << mBoneArray;

		if ( Ser.IsLoading() )
		{
			// ������ι�ϵ
			for ( dword BoneID = 0;BoneID < mBoneArray.size() ;BoneID++ )
			{
				BoneContent* ParentBone = GetBone( mBoneArray[BoneID]->mParentID );
				if ( ParentBone != null )
					ParentBone->mChildArray.push_back( BoneID );
				else
					mRootArray.push_back( BoneID );
			}

#ifdef USE_SHARE_BONE_ARRAY
			BuildBoneIndex();
#endif
		}
	}

	dword SkeletonMeshResource::AddBone( BoneContent* Bone )
	{
		mBoneArray.push_back( Bone );

		return mBoneArray.size() - 1;
	}

	BoneContent* SkeletonMeshResource::GetBone( dword boneid )
	{
		if ( boneid < mBoneArray.size())
			return mBoneArray[ boneid ];

		return  null;
	}


	void SkeletonMeshResource::BuildBoneIndex( )
	{
		dword BlendIndicesOffset = mVertexFormat.GetElementOffset( VU_Blend_Indices );
		dword TotalStride = mVertexFormat.GetTotalStride( 0 );

		// ��̬ģ�ͻ���û�б���BlendIndices��Ϣ
		if ( BlendIndicesOffset == -1 )
			return;

		for ( dword FactoryIndex = 0; FactoryIndex < GetVertexFactoryCount(); FactoryIndex++)
		{
			// ÿ����ģ��
			SkeletonMeshVertexFactory* Factory = GetVertexFactory<SkeletonMeshVertexFactory>( FactoryIndex );

			for ( dword MeshVertexIndex = 0; MeshVertexIndex< Factory->GetVertexCount(); MeshVertexIndex++ )
			{
				// ÿ�����������
				_byte* VertexData = (_byte*)Factory->GetVertexStream()->GetBuffer() + MeshVertexIndex * TotalStride;


				for ( dword InfluenceIndex = 0; InfluenceIndex < 4; InfluenceIndex ++ )
				{
					// ÿ�������4��Ȩ��
					float* VertexBlendIndexPtr = (float*)( VertexData + BlendIndicesOffset) + InfluenceIndex;

					dword VertexBlendIndex = dword( *VertexBlendIndexPtr );

					// ûӰ��Ĺ���������
					if ( VertexBlendIndex == -1 )
						continue;

					// ��ԭ����VB����������Ϊ���ÿ����ģ��
					// �ڹ��������в���

				
					BoneIndexArray::iterator ExistBoneRef = std::find( Factory->mBoneIndices.begin(), Factory->mBoneIndices.end(), VertexBlendIndex );
					if ( ExistBoneRef == Factory->mBoneIndices.end() )
					{
						*VertexBlendIndexPtr = (float)Factory->mBoneIndices.size();

						Factory->mBoneIndices.push_back( VertexBlendIndex );
					}
					else
					{
						// �Ѿ����ڵ�����
						*VertexBlendIndexPtr = (float)(ExistBoneRef - Factory->mBoneIndices.begin() );
					}
				}
			}
		}
	}


	BoneShaderData* SkeletonMeshResource::GenBoneIndexMatrix( BoneShaderBuffer& DataArray, SkeletonInstance* Skeleton, dword MeshContentIndex)
	{
		Assert( IsInGameThread() );


		if ( DataArray.size() == 0   )
			DataArray.resize( GetVertexFactoryCount() );

		BoneShaderData& BoneData = DataArray[ MeshContentIndex ];

		SkeletonMeshVertexFactory* Factory = GetVertexFactory<SkeletonMeshVertexFactory>( MeshContentIndex );

#ifdef USE_SHARE_BONE_ARRAY
		// ��չ��������ռ�
		if ( BoneData.mBoneLocalMatrixArray.size() == 0 && Factory->mBoneIndices.size() )
			BoneData.mBoneLocalMatrixArray.resize( Factory->mBoneIndices.size() );

		// �����������
		for ( BoneData.mSharedBoneCount = 0;BoneData.mSharedBoneCount < Factory->mBoneIndices.size(); BoneData.mSharedBoneCount ++ )
		{
			BoneContent* Bone = Skeleton->GetBone( Factory->mBoneIndices[BoneData.mSharedBoneCount] );
			BoneData.mBoneLocalMatrixArray[BoneData.mSharedBoneCount] = BoneData.mBoneLocalMatrixArray[BoneData.mSharedBoneCount].FromTranslationRotation( Bone->mLocalTranslation, -Bone->mLocalRotation ).Transpose();
		}
#else
		BoneData.mSharedBoneCount = Skeleton->GetBoneCount();

		if ( BoneData.mBoneLocalMatrixArray.size() == 0 && Skeleton->GetBoneCount() > 0 )
			BoneData.mBoneLocalMatrixArray.resize( Skeleton->GetBoneCount() );

		for ( dword  i = 0;i< Skeleton->GetBoneCount();i++ )
		{
			BoneContent* Bone = Skeleton->GetBone( i );
			BoneData.mBoneLocalMatrixArray[i] = BoneData.mBoneLocalMatrixArray[i].FromTranslationRotation( Bone->mLocalTranslation, -Bone->mLocalRotation ).Transpose();
			
		}
#endif

		return &BoneData;
	}

}