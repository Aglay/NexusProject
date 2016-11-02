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
		��̬ģ�Ͷ����ʽʵ��
	*/
	class StaticMeshVertexFactory : public MeshVertexFactory
	{
		DECLARE_RTTI_CLASS( StaticMeshVertexFactory, MeshVertexFactory, ClassFlag_Intrinsic )

	public:
		
	};

	/** 
		��̬ģ����Դʵ��
	*/
	class StaticMeshResource : public MeshResource
	{
		DECLARE_RTTI_CLASS( StaticMeshResource, MeshResource, ClassFlag_Intrinsic|ClassFlag_Serializable )
	public:
		StaticMeshResource( );

		virtual ~StaticMeshResource( );

		virtual void Serialize( BinarySerializer& Ser );
	};

	typedef TRefPtr<StaticMeshResource> StaticMeshResourcePtr;

	/** @} */
	/** @} */
}
