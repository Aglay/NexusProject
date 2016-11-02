#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Model
	*  @{
	*/

	struct BoneShaderData;
	class MeshResource;

	/** 
		ͨ��ģ�����
	*/
	class MeshComponent : public GeometryComponent
	{
	DECLARE_RTTI_ABSTRACT( MeshComponent, GeometryComponent, ClassFlag_Intrinsic )
	public:
		MeshComponent( );

		virtual ~MeshComponent( );

		/// ����ģ�͵Ĳ��ʶ���
		void SetMaterialInstance( MaterialInstance* MatIns );

		MaterialInstancePtr GetMaterial( );

		/// ��Ҫʵ��:��ȡģ����Դ��
		virtual MeshResource* GetMeshResource( ) = 0;

		/// ����
		virtual void Draw( SceneView* RV );

		/// ��Ҫʵ��:ʰȡ
		virtual bool Pick( const Ray& PickRay, float& Distance ){ return false; }

		/// ��Ҫʵ��:ʰȡ
		virtual bool Pick( SceneView* RV, const FRect& ScreenArea ){ return false; }

		virtual bool IsTransparent( );

		virtual bool IsEnableDepthWrite( );

		virtual float GetViewDepthSquared(Camera* C  );

		static void StaticInitProperty();

		virtual void Serialize( BinarySerializer& Ser );

	protected:

		struct MeshRenderParameter 
		{
			Matrix4					mLocalToScreen; // ת������Ļ
			Matrix4					mLocalToWorld;	// ����ת��
			Matrix4					mWorldToLocal;	// ����ת����
			MaterialInstance*		mMaterialInstance;
			VertexFactory*			mVertexFactory;			
			BoneShaderData*			mBoneData;
			dword					mPickID;
			SceneView*				mRenderView;
		};

		virtual void CheckResourceStage( );

		virtual bool IsResourceReady( ) = 0;

		/// ����ǰ��Ҫ������Ⱦ����
		virtual void OnRenderParameter( dword Index, MeshRenderParameter& Parameter ){ }

	protected:
		ResourcePtrMarker<MaterialInstancePtr>		mMaterialInstance;

		/// ��Ⱦ�̻߳���ģ��
		static void DrawMesh_RenderThread( MeshRenderParameter& Parameter );

		/// ����ϵͳ����ģ�ͻص�
		void OnPropertyMaterial( WString* Value, bool IsGet );

	};
}
