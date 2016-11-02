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
		��̬ģ�����ʵ��
	*/
	class StaticMeshComponent : public MeshComponent
	{
		DECLARE_RTTI_CLASS( StaticMeshComponent, MeshComponent, ClassFlag_Intrinsic )
	public:
		
		/// ����ģ����Դ
		void SetMesh( const StaticMeshResourcePtr& Mesh );

	public:
		virtual MeshResource* GetMeshResource( );

		virtual bool Pick( const Ray& PickRay, float& Distance );

		virtual bool Pick( SceneView* RV, const FRect& ScreenArea );

		static void StaticInitProperty();

		virtual void Tick( float elapse );

		virtual void Serialize( BinarySerializer& Ser );

	private:
		virtual bool IsResourceReady();

		virtual void CheckResourceStage( );
		
		void OnPropertyMesh( WString* Value, bool IsGet );
		
	private:
		ResourcePtrMarker<StaticMeshResourcePtr> mMesh;
		
	};

	/** @} */
	/** @} */
}
