#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup System
	*  @{
	*/


	class RenderQueue;

	class Actor;

	typedef TRefPtr<Actor> ActorPtr; 

	/** 
		��ɫ��
		��װ��Ϸ������
		@remark
			֧�������չ����
			���ӹ�ϵ����
	*/
	class Actor	: public ManagedObject
				, public Tickable
				, public MovableObject
	{
		DECLARE_RTTI_CLASS( Actor, ManagedObject, ClassFlag_Intrinsic| ClassFlag_Serializable )

	public:
		Actor();

		virtual ~Actor( );

		//////////////////////////////////////////////////////////////////////////
		// ���
		//////////////////////////////////////////////////////////////////////////

		/// ���һ�����
		template<typename TClass>
		TClass* AddComponent( )
		{
			return RTTI_CAST(TClass, AddComponent( RTTI_CLASS_INFO(TClass) ) );
		}

		/// ��ȡ���
		template<typename TClass>
		TClass* GetComponent( )
		{
			return RTTI_CAST(TClass, GetComponent( RTTI_CLASS_INFO(TClass) ) );
		}

		/**
			������
			@param
				Class �������
			@param
				Index ͬ���͵�����
			@return
				���
		*/
		ActorComponent*		AddComponent( RTTIClass* Class, dword Index = 0 );

		/// ����������
		void				ClearComponent();

		
		/**
			��ȡ���
			@param
				Class �������
			@param
				Index ͬ���͵�����
			@return
				���
		*/
		ActorComponent*		GetComponent( RTTIClass* Class, dword Index = 0 );

		/// ������һ�����
		ActorComponent* 	GetFirstComponent( );

		/// ��ȡ��һ�����
		ActorComponent* 	GetNextComponent();

		/**
			�Ƴ����
			@param
				Class �������
			@param
				Index ͬ���͵�����
		*/
		void				RemoveComponent( RTTIClass* Class, dword Index = 0 );

		/**
			�����������
			@param
				Class �������
			@param
				Name ������
			@param
				Value ����ֵ
			@return
				�Ƿ����óɹ�
		*/
		bool				SetComponentPropertyByString( RTTIClass* Class, const wchar* Name, const wchar* Value );

		/**
			��ȡ�������
			@param
				Class �������
			@param
				Name ������
			@param
				Value ����ֵ
			@return
				�Ƿ��ȡ�ɹ�
		*/
		bool				GetComponentPropertyAsString( RTTIClass* Class, const wchar* Name, WString& Value );

		/// �������Ե�ģ�������Զ����
		template<typename TClass>
		bool SetPropertyByString( const wchar* Name, const wchar* Value )
		{
			return SetComponentPropertyByString( RTTI_CLASS_INFO( TClass ), Name, Value );
		}

		/// ��ȡ���Ե�ģ�������Զ����
		template<typename TClass>
		bool GetPropertyAsString( const wchar* Name, WString& Value )
		{
			return GetComponentPropertyAsString( RTTI_CLASS_INFO( TClass ), Name, Value );
		}

		//////////////////////////////////////////////////////////////////////////
		// ��������
		//////////////////////////////////////////////////////////////////////////

		/// �����Ƿ�ɼ�
		void SetVisible( bool Visible ){ mVisible = Visible; }

		/// ��ȡ�Ƿ�ɼ�
		bool GetVisible( ){ return mVisible; }

		void SetPickable( bool Pickable );

		bool GetPickable( );

		dword GetUserData( ){ return mUserData; }

		void SetUserData( dword UserData ){ mUserData = UserData; }

		/// ��ȡ����
		Actor* GetParent( );

		/// ����ӽ�ɫ
		void AddChild( Actor* A );

		/// �ӽ�ɫ�Ƿ�
		bool ExistChild( Actor* A );

		/// ��ȡ�ӽ�ɫ����
		dword GetChildCount( ){ return mChildActorList.size(); }

		/// �Ƴ�����
		void RemoveChild( Actor* A );

		/// �Ƴ����е��ӽ�ɫ
		void RemoveAllChild( );

		/// ������һ���ӽ�ɫ
		Actor* GetChildFirst( );

		/// ������һ���ӽ�ɫ
		Actor* GetChildNext( );

		/// ��ȡ�Լ��ı��ذ󶨺�
		const AABB& GetBoundingBox( ){ return mSelfAABB; }

		/// ��ȡ�Լ����ӽڵ������󶨺�
		AABB GetComboWorldBoundingBox( );

		/// ��ȡ�Լ�������󶨺�
		AABB GetWorldBoundingBox();

		/// ���ð󶨺�
		void SetBoundingBox( const AABB& BoundingBox ){ mSelfAABB = BoundingBox; }

		void SetTestColor( dword Color );

		/**
			ʰȡ�ж�
			@param
				PickRay ����
			@param
				Distance ʰȡ���ľ���
			@return
				�Ƿ�ʰȡ��
		*/
		bool Pick( const Ray& PickRay, float& Distance );

		/**
			�ж���ɫ�Ƿ�����Ļ��Χ��
			@param
				RV ʰȡ���ӿ�
			@param
				ScreenArea ��Ļ��Χ
			@return
				�Ƿ�����Ļ��Χ��
		*/
		bool Pick( SceneView* RV, const FRect& ScreenArea );

		//////////////////////////////////////////////////////////////////////////
		// �ڲ�ʹ��
		//////////////////////////////////////////////////////////////////////////
		virtual void Tick( float Elapse );

		virtual void Serialize( BinarySerializer& Ser );

		void SetDebugName( const WString& Name ){ mDebugName = Name; }

		WString GetDebugName( );

		void SetFlag( dword Flag );

		dword GetFlag( );

		bool HasFlag( dword Mask );

	private:
		friend class GameWorld;

		/// ���ҿɻ��������䵽��Ⱦ�б���
		void FindDrawableComponent( RenderQueue* Queue );

		/// ���ɼ����������Ⱦ����
		void FindVisibleObject( SceneView* RV, RenderQueue* Queue );

		/// ���ӽڵ�İ󶨺кϲ�����
		void RefreshCombineBoundingBox( );

		virtual MovableObject*	GetParentMovable( );

		virtual MovableObject* GetFirstMovable( );

		virtual MovableObject* GetNextMovable( );

		virtual void BeginDispose(  );

		void SetParent( Actor* A );

	
	private:
		friend class WorldPick;
		WString			mDebugName;
		Actor*			mParent;
		GameWorld*		mWorld;		// �����ĸ�����
		RTTIClass*		mFactoryClass;

		// Component = Front { NormalComponent...| ... DrawableComponent } Back
		typedef std::list<ActorComponent*> ComponentList;
		ComponentList mComponentList;
		ComponentList::iterator mFirstGeometryComponent;
		ComponentList::iterator mComponentIterator;


		bool		mVisible;


		dword		mUserData;
		bool		mPickable;// 0: ��ʰȡ��1:����ʰȡ���ȴ�������ɫ,����:ʰȡ��ɫ

		friend dword GetTypeHash( Actor* A )
		{
			return PointerHash(A);
		}
		

		typedef std::list<Actor*> ChildActorList;

		ChildActorList mChildActorList;

		ChildActorList::iterator mChildIterator;


		AABB		mChildAABB;			// �����ӳ�Ա�ϲ���İ󶨺�
		AABB		mSelfAABB;			// ͨ��������µ�����󶨺�

		dword		mFlag;
	};


	typedef std::vector<Actor*> ActorArray;

	/** @} */
	/** @} */
}
