#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup System
	*  @{
	*/

	/// �йܶ����������ղ���
	enum eGarbageCollectPolicy
	{		
		GCP_Full,				///< ��ȫɨ�����
		GCP_Finalize,			///< ��������
	};

	class ManagedObject;


	/** 
		��Դ���صĹ۲���
	*/
	class ObjectSerializeObserver : public AsyncTask
	{
	public:
		ObjectSerializeObserver(  ManagedObject* Obj, BinarySerializer* Ser  );

		virtual ~ObjectSerializeObserver( );

		/// �����̴߳�����
		virtual void OnAsyncTaskProcess();

		/// ��Ϸ�̴߳������
		virtual void OnAsyncTaskFinished( );

		/// ��Դ�Ƿ���ؽ���
		bool IsFinished( );

		/// ͬ����ʽ�������,��ɾ���Լ�
		void StartSync( );

		/// �첽Ͷ������
		void PostAsync( );
	private:
		ManagedObject*		mObject;	
		BinarySerializer*	mSerializer;
	};

	enum eObjectSpawnType
	{
		OST_Unknown,
		OST_Constructed,
		OST_Loaded,
		OST_Savable,
	};
	
	/** 
		�йܶ���
		֧�ֺ�̨��Դ����,ж�ؿ���
		@remark
			ManagedObject����Ҫ����Dispose,ԭ��:�����˻�������ʱ,��Դɾ��Ҳ�ǲ������
	*/
	class ManagedObject	: public RTTIObject
						, public RefObject
	{
	public:
		ManagedObject( );

		DECLARE_RTTI_CLASS( ManagedObject, RTTIObject, ClassFlag_Intrinsic )

		virtual ~ManagedObject( );

		/// ����Դ����OK,�˱�־��ϵͳ�Զ����
		bool IsPackageResourceReady( );

		/// ����Դ������Ϻ����,������������о����Ƿ���Ҫ��ManualResource���ع���,����GPU��Դ
		virtual void PostLoad( ){ }

		/// �ֶ���Դ�����Ƿ�OK, ���������ṩ,����GPU��Դ
		virtual bool IsManualResourceReady( ){ return true; }

		/// ����Դ���ֶ���Դ��׼������
		virtual bool IsResourceReady( ){ return IsManualResourceReady() && IsPackageResourceReady(); }

		/// ����û���ⲿ����ʱ,������Դ����
		virtual void BeginDispose( ){}

		/// �����Ƿ�����Dispose
		bool IsDisposing( ){ return mIsDisposing; }

		/// ����Dispose�Ķ����Ƿ��Ѿ�ж������Դ����ɾ��?
		virtual bool CanDestroyNow( ){ return true; }

		/// ��������
		void SetName( const WString& Name );

		/// ��ȡ����
		const WString& GetName( ){ return mName; }

		/// ʹ��ConstructObject����Ķ�������Դʱ,������ô˺����Ա�����ԴOK
		void MarkPackageResourceReady( ){ mPackageResourceReady = true; }


	
	private:
		friend class ObjectSerializeObserver;
		friend class ObjectManager;
		WString					mName;
		dword					mObjectIndex;
		ManagedObject*			mHashNext;
		bool					mIsDisposing;

		// ��Դ���ؽ׶��Ƿ����
		bool					mPackageResourceReady;		

		// ����ʱ������
		eObjectSpawnType		mSpawnType;
	};


	/**
		�йܶ��������
	*/
	class ObjectManager : public RTTIObject
	{
	public:
		DECLARE_RTTI_CLASS( ObjectManager, RTTIObject, ClassFlag_Intrinsic )

		enum{ OBJECT_HASH_BINS = 4096 };

		ObjectManager( );

		virtual ~ObjectManager( );

		/**
			����һ���Զ��������	
			@param
				ClassInfo ���������
			@param
				Name ��������
			@return
				�����õĶ���
			@remark
				����Ϊ��ʱ�Զ���������ȷ������
		*/
		ManagedObject* ConstructObject( RTTIClass* ClassInfo, const WString& Name );

	
		/**
			����һ���Զ��������,ģ���������
			@param
				Name ��������
			@return
				�����õĶ���
			@remark
				����Ϊ��ʱ�Զ���������ȷ������
		*/
		template<typename TClass>
		TClass* ConstructObject( const WString& Name )
		{
			return RTTI_CAST(TClass, ConstructObject( RTTI_CLASS_INFO(TClass), Name ) );
		}

		
		/**
			���ٶ���
			@param
				Obj ����
		*/
		void DestructObject( ManagedObject* Obj );

		/**
			��������ӵ�������
			@param
				Obj ����
			@param
				Name ����
			@return
				
		*/
		bool LinkObject( ManagedObject* Obj, const WString& Name );
		
		/**
			���Ҷ���
			@param
				ClassInfo ���������
			@param
				Name ��������
			@return
				���ҵ��Ķ���
		*/
		ManagedObject* FindObject( RTTIClass* ClassInfo, const WString& Name );

		/**
			���Ҵ������еĵ�һ������
			@param
				ClassInfo ���������
			@param
				Name ��������
			@return
				���ҵ��Ķ���
		*/
		ManagedObject* FindFirstObjectByKind( RTTIClass* ClassInfo, const WString& Name );

		/**
			���Ҵ������е���һ������
			@param
				ClassInfo ���������
			@param
				Name ��������
			@return
				���ҵ��Ķ���
		*/
		ManagedObject* FindNextObjectByKind( RTTIClass* ClassInfo, ManagedObject* KindOfObject );


		/// ��ȡ�������־��
		Logger* GetLogger( ){ return GObjectLogger; }

		
		/**
			���ض���
			@param
				Name ��Դ��/������
			@return
				���غõĶ���
		*/
		template<typename TClass>
		TClass* LoadObject( const WString& Name, bool Background = true )
		{
			return RTTI_CAST(TClass, LoadObject(  RTTI_CLASS_INFO(TClass), Name, Background  ) );
		}

		/**
			���ض���
			@param
				ClassInfo ���������
			@param
				Name ��Դ��/������
			@return
				����
		*/
		ManagedObject* LoadObject( RTTIClass* ClassInfo, const WString& Name, bool Background );


		/// �ֶ������������������
		void AddNamedObject( ManagedObject* MO);

		/// �Ͽ��������,��ʱ�����޷�����,��Ҫ�Լ������ڴ�
		void RemoveNamedObject( ManagedObject* MO);



		/// д����Դ	
		bool SaveToFile( ManagedObject* MO, dword FileVersion );

		/// ��ȡ��Դ·��
		const WString& GetContentPath( ){ return mContentPath; }
		
		/**
			������Դ·��
			@param
				Value ����ڿ�ִ���ļ���·��
		*/
		void SetContentPath( const WString& Value );

		/// ���ö�ȡ
		virtual void SerializeConfig( PropertySerializer& Ser );

		/// �����Դ����
		void CheckResourceProcessing( );

		/**
			������������
			@param
				Policy ���ղ���
		*/
		void CollectGarbage( eGarbageCollectPolicy Policy );

		static void StaticInitProperty( );

	private:
		WString MakeUniqueObjectName( RTTIClass* ClassInfo );
		

	private:
		
		typedef std::vector<ManagedObject*> ObjectArray;
		typedef std::vector<dword>	   FreeObjectArray;
		typedef std::list<ManagedObject*>	ObjectList;
		
		WString			mContentPath;

		// �����Hash��,������Key
		ManagedObject*		GObjectHash[OBJECT_HASH_BINS];

		// �����,��������,�п�λ
		ObjectArray		GObjects;

		// ����ʵ������
		dword			GObjectCount;

		// �������λ
		FreeObjectArray	GFreeObjectArray;


		Logger*			GObjectLogger;

		// ��������
		ObjectList		GDisposingList;

		// �����������ս���
		dword			GPurgeObjectIndex;

		typedef std::set<ObjectSerializeObserver*> ObjectSerializeList;

		ObjectSerializeList		GLoadingList;
	};

	extern ObjectManager* GObjectManager;

	/** @} */
	/** @} */	
}
