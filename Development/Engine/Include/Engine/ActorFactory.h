#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup System
	*  @{
	*/


	class GameWorld;

	/** 
		��ɫ����
	*/
	class ActorFactory : public RTTIObject
	{
	DECLARE_RTTI_ABSTRACT(ActorFactory, RTTIObject, ClassFlag_Intrinsic )
	public:
		/// ��Ҫʵ��,������ɫ�����������,������
		virtual Actor* CreateActor( const WString& Name, void* Parameter ) = 0;

	protected:
		friend class GameWorld;
		GameWorld* mOwner;
	};

	/** 
		��̬ģ�ͽ�ɫ����
	*/
	class ActorFactoryStaticMesh : public ActorFactory
	{
	DECLARE_RTTI_CLASS( ActorFactoryStaticMesh, ActorFactory, ClassFlag_Intrinsic )

	public:
		virtual Actor* CreateActor( const WString& Name, void* Parameter );	
	};

	/** 
		����ģ�ͽ�ɫ����
	*/
	class ActorFactorySkeletonMesh : public ActorFactory
	{
	DECLARE_RTTI_CLASS( ActorFactorySkeletonMesh, ActorFactory, ClassFlag_Intrinsic )

	public:
		virtual Actor* CreateActor( const WString& Name, void* Parameter );	
	};

	/** 
		�༭���������
	*/
	class ActorFactoryArcBallCamera: public ActorFactory
	{
		DECLARE_RTTI_CLASS( ActorFactoryArcBallCamera, ActorFactory, ClassFlag_Intrinsic )

	public:
		virtual Actor* CreateActor( const WString& Name, void* Parameter );	
	};

	/** 
		��һ�˳Ʒ�ʽ���������
	*/
	class ActorFactoryFPSCamera: public ActorFactory
	{
		DECLARE_RTTI_CLASS( ActorFactoryFPSCamera, ActorFactory, ClassFlag_Intrinsic )

	public:
		virtual Actor* CreateActor( const WString& Name, void* Parameter );	
	};

		/** 
		��һ�˳Ʒ�ʽ���������
	*/
	class ActorFactoryFocusCamera: public ActorFactory
	{
		DECLARE_RTTI_CLASS( ActorFactoryFocusCamera, ActorFactory, ClassFlag_Intrinsic )

	public:
		virtual Actor* CreateActor( const WString& Name, void* Parameter );	
	};

	/** @} */
	/** @} */
}
