#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup System
	*  @{
	*/


	/** 
		��Ϸ����, ��Actor���й���, Actor��ʹ����������
	*/
	class GameWorld : public RTTIObject
	{
		DECLARE_RTTI_CLASS( GameWorld, RTTIObject, ClassFlag_Intrinsic| ClassFlag_Serializable )
	public:
		GameWorld( ){}

		GameWorld( dword Index );

		virtual ~GameWorld( );

		/**
			����һ����ɫ
			@param
				FactoryClass ������
			@param
				Name ��ɫ��
			@param
				Parent ����
			@return
				�����õĽ�ɫ
		*/
		Actor* SpawnActor( RTTIClass* FactoryClass , const WString& Name , Actor* Parent = null, void* Parameter = null );
		

		/**
			��ȡ��ɫ����ʵ��
			@param
				FactoryClass ��������
			@return
				������
		*/
		ActorFactory* GetActorFactory( RTTIClass* FactoryClass )
		{
			ActorFactory** FactoryRef = mActorFactoryMap.find( FactoryClass );

			if ( FactoryRef == null )
				return null;

			return *FactoryRef;
		}

		/// ��ȡ��ɫ����ʵ��,ģ���Զ����
		template<typename TClass>
		TClass* GetActorFactory( )
		{
			return RTTI_CAST( TClass, GetActorFactory( RTTI_CLASS_INFO(TClass) ) );
		}

	
		/// ��ȡ����ɫ
		Actor* GetRootActor( ){ return mRootActor; }

		/// ��ȡ��Ⱦ�б�
		RenderQueue* GetRenderQueue( ){ return mRenderQueue; }

		/// ��ȡ�����
		Camera* GetCamera( const WString& Name );

		// ɾ�����󣬿���ָ��ĳ������
		void Kill( const WString& Name, RTTIClass* ClassInfo = RTTI_CLASS_INFO( Actor ) );

		/// ɾ��һ��Actor����������Actor
		void Kill( Actor* A );

		Actor* GetActor( const WString& Name, RTTIClass* ClassInfo = RTTI_CLASS_INFO( Actor )  );

		/// ���л�Actor
		void SerializeActors( BinarySerializer& Ser, Actor* Parent, dword IncludeFlag = 0, ActorArray* RootChildActors = null );		

		/// ����һ������,��������ڶ������ϵͳ
		static void IsolateFromSystem( Actor* A );

		/// �ָ�������Ķ���
		static void RestoreFromSystem( Actor* A );

	public:

		void Draw( SceneView* RV );

		virtual void Serialize( BinarySerializer& Ser );
		


	private:
		

	private:
		typedef dynamic_hash<RTTIClass*, ActorFactory*> ActorFactoryMap;
		ActorFactoryMap mActorFactoryMap;

		Actor* mRootActor;

		RenderQueue* mRenderQueue;
	};

	/** @} */
	/** @} */
}
