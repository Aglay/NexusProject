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
		�����������ʵ��
	*/
	class SkeletonMeshComponent : public MeshComponent
	{
		DECLARE_RTTI_CLASS( SkeletonMeshComponent, MeshComponent, ClassFlag_Intrinsic )
	public:
		SkeletonMeshComponent( );

		virtual ~SkeletonMeshComponent( );

		/// ������Ƥ��Դ
		void SetSkin( const SkeletonMeshResourcePtr& Skin );

		/// ���ö�����Դ
		void SetAnimation( const SkeletonAnimResourcePtr& Anim );

		/// ��ù���
		SkeletonInstance* GetSkeleton( ){ return mSkeletonInstance; }

		/// ��ȡ����������
		SkeletonAnimController* GetAnimationController( ){ return mSkeletonAnimController; }

	public:
		virtual bool IsResourceReady( );

		virtual MeshResource* GetMeshResource( );

		virtual void OnRenderParameter( dword Index, MeshRenderParameter& Parameter );

		virtual bool Pick( SceneView* RV, const FRect& ScreenArea );

		virtual bool Pick( const Ray& PickRay, float& Distance );

		static void StaticInitProperty();

		virtual void Tick( float elapse );

		virtual void Serialize( BinarySerializer& Ser );

	protected:
		virtual void CheckResourceStage( );

		void OnPropertySkin( WString* Value, bool IsGet );

		void OnPropertyAnimation( WString* Value, bool IsGet );
		

	private:
		enum {

			SM20_MAX_BONE_MATRIX = 50,		// 256 / 4 = 64 ~= 50
		};



	private:
		ResourcePtrMarker<SkeletonMeshResourcePtr>			mSkin;
		ResourcePtrMarker<SkeletonAnimResourcePtr>	mAnimation;
		SkeletonInstance*						mSkeletonInstance;
		SkeletonAnimController*					mSkeletonAnimController;

		BoneShaderBuffer						mBoneShaderBuffer;// Ϊÿ��Meshʵ��׼���Ĺ�����Ƥ����
	};

	/** @} */
	/** @} */	
}
