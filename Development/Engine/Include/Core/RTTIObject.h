#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Reflection
	*  @{
	*/

	typedef class RTTIObject* (*ClassConstructor)( );

	#define RTTIOBJECT_HASHBOUND 4096
	#define RTTIPACKAGE_HASHBOUND 32

	class RTTIClass;

	/** 
		RTTI��
	*/
	class RTTIGroup
	{
	public:
		RTTIGroup( );

		/** 
			������һ��������
		*/
		RTTIClass* GetFirstClass( );

		/** 
			������һ��������һ����
		*/
		RTTIClass* GetNextClass( );

		/** 
			��ȡ������������
		*/
		dword GetClassCount( );

		/** 
			���һ����
		*/
		void AddClass( RTTIClass* ClassInfo );

		/** 
			���Ƿ����
		*/
		bool ClassExist( RTTIClass* ClassInfo );

	private:
		typedef std::vector<RTTIClass*> ClassArray;
		ClassArray mClassArray;
		dword	   mIterator;
	};

	/** 
		�ྲ̬��ʾ
	*/
	enum eClassFlag
	{
		ClassFlag_None			= 0x00000000,	///< ����C++��
		ClassFlag_Serializable	= 0x00000001,	///< �������л�
		ClassFlag_Abstract		= 0x00000002,	///< ������
		ClassFlag_HasProperty	= 0x00000004,	///< ӵ�����ԣ��Զ���ʼ������
		ClassFlag_Intrinsic		= 0x10000000,	///< �ڽ��࣬�ǽű���
	};

	/** 
		RTTI����Ϣ
	*/
	class RTTIClass
	{
	public:
		/// ������
		NameRef			mClassName;

		/// ���䵽�ĸ��������ڱ�������ʶ��
		NameRef			mPackageName; 

		/// �����ʵ���Ĳο�����
		dword			mClassUnique;

		/// ����
		RTTIClass*		mParentClass; 

		/// ��һ������
		RTTIClass*		mChildClass;  

		/// ͬ��������
		RTTIClass*		mNextClass;	  

		/// �����ĸ���
		RTTIGroup*		mGroup;

		/// ������
		dword			mClassFlag;	  

		/// ������ʵ��
		RTTIObject* CreateInstance(  );

		/** 
			���캯��
			@param
				ClassName ����
			@param
				CreateFunc �ഴ������
			@param
				ParentClass ����
			@param
				ClassFlag ���ʾ

		*/
		RTTIClass(	const NameRef& ClassName, 
					ClassConstructor CreateFunc, 
					RTTIClass* ParentClass, dword ClassFlag );

		virtual ~RTTIClass( );

		/** 
			ȡHashֵ
		*/
		dword GetHash( ) const { return mClassName.GetIndex(); }

		/** 
			ȡRTTI�������ַ���
		*/
		const wchar* GetRTTIClassString( );

		/** 
			ȡRTTI������
		*/
		const NameRef& GetRTTIClassName( );

		/** 
			�ж������
		*/
		bool IsA( RTTIClass* ClassInfo );

		/** 
			�ж������
		*/
		bool IsA( const NameRef& ClassName );

		/** 
			�ж�����ĳһ������
		*/
		bool IsKindOf( RTTIClass* ClassInfo );

		/** 
			�����Ƿ�ӵ��ĳ�����ʾ
		*/
		bool HasFlag( dword ClassFlag );

		friend dword GetTypeHash( RTTIClass* A )
		{
			return PointerHash(A);
		}

		/** 
			ȡ�������Խӿ�
		*/
		PropertyCollection* GetPropertyCollection( );

	private:
		friend class RTTIObject;

		ClassConstructor mCreateEntry;
		PropertyCollection*	mPropertyCollection;
	};



	class BinarySerializer;

	/** 
		RTTI�������
		@remark
			��Ϻ�,�����Զ�ע�ᶯ̬����ʶ����
	*/
	class RTTIObject
	{
	public:
		/** 
			ȡ����Ϣ
		*/
		virtual RTTIClass* GetClass( ){ Assert( sRTTIInfo != null && "RTTIObject not initialized, call Object::StaticInit first"); return sRTTIInfo; } 

		static RTTIClass* StaticClass( );
		static RTTIObject* StaticConstruct( ){ return new RTTIObject;}

		/** 
			���������л�
		*/
		virtual void Serialize( BinarySerializer& Ser ){}

		/**
			�������л�
		*/
		virtual void SerializeConfig( PropertySerializer& Ser );

		/** 
			�������������
		*/
		friend BinarySerializer& operator << ( BinarySerializer& Ser, RTTIObject*& Obj );
		friend BinarySerializer& operator << ( BinarySerializer& Ser, RTTIObject& Obj ); 
		static RTTIClass* sRTTIInfo;
	public:
		virtual ~RTTIObject( ){}
		//////////////////////////////////////////////////////////////////////////
		// Class Instance Function
		//////////////////////////////////////////////////////////////////////////

		/** 
			��ʵ�����
		*/
		bool EqualTo( RTTIObject* ClassObj );

		/** 
			�����
		*/
		bool IsA( RTTIClass* ClassInfo );

		/** 
			�����
		*/
		bool IsA( const NameRef& rttitype );

		/** 
			������ͬ
		*/
		bool IsKindOf( RTTIClass* ClassInfo );

		/** 
			����ת��
		*/
		template<typename TClass>
		TClass* Cast( )
		{
			return IsKindOf( TClass::StaticClass() ) ? (TClass*)this:null;
		}

		/** 
			��̬����ת��
		*/
		template<typename TClass>
		static TClass* Cast( RTTIObject* Obj )
		{
			if( Obj == null )
				return null;

			return Obj->IsKindOf( TClass::StaticClass() ) ? (TClass*)Obj:null;
		}


		//////////////////////////////////////////////////////////////////////////
		// Property Access
		//////////////////////////////////////////////////////////////////////////

		bool SetObjectPropertyByString( const wchar* Name, const WString& Value, bool SeekWholeFamily = true );

		bool SetObjectProperty( const wchar* Name, PropertyValue& PV, bool SeekWholeFamily = true );

		bool GetObjectPropertyAsString( const wchar* Name, WString& Value, bool SeekWholeFamily = true );

		bool GetObjectProperty( const wchar* Name, PropertyValue& PV, bool SeekWholeFamily = true );

		template<typename TOptionType>
		bool GetObjectPropertyT( const wchar* Name, TOptionType& Value, bool SeekWholeFamily = true )
		{
			return GetObjectProperty( Name, TPropertyValueRef<TOptionType>( Value, typeconv<TOptionType>().value_typenameW() ), SeekWholeFamily );
		}

		/// ������ֵ�Ƿ����������
		template<typename TOptionType>
		bool CheckObjectPropertyT( const wchar* Name, TOptionType Value, bool SeekWholeFamily = true )
		{
			TOptionType Ret;
			if ( !GetObjectPropertyT( Name, Ret, SeekWholeFamily ) )
				return false;

			return Value == Ret;
		}

		/// �Զ�ģ��ƥ������
		template<typename TOptionType>
		bool SetObjectPropertyT( const wchar* Name, TOptionType Value, bool SeekWholeFamily = true )
		{	
			return SetObjectProperty( Name, TPropertyValueRef<TOptionType>( Value, typeconv<TOptionType>().value_typenameW() ), SeekWholeFamily );
		}
		//////////////////////////////////////////////////////////////////////////
		// RTTI Object Management
		//////////////////////////////////////////////////////////////////////////

		// Private Usage
		static void StaticInit( );

		static void StaticExit( );

		static void Dump( Logger* logger );

		/// ������ʵ��
		static RTTIObject*	CreateInstance( const wchar* ClassName );

		/// ������ʵ��
		static RTTIObject*	CreateInstance( const NameRef& ClassName );

		/// ע������Ϣ
		static void			Register( RTTIClass* ClassInfo );

		/// ��ע������Ϣ
		static void			UnRegister( RTTIClass* ClassInfo );

		/// ��������Ϣ
		static RTTIClass*	FindClass( const NameRef& ClassName );

		/// �����������Ϣ
		static void			ClearClass( );	

		/// ������һ������Ϣ
		static RTTIClass*	GetFirstClass( );

		/// ������һ������Ϣ
		static RTTIClass*	GetNextClass( );

		/// ��ȡ������
		static dword		GetClassCount( );

		/// ȡ������
		static RTTIGroup*	GetGroup( const NameRef& Name );

		/// �����������
		static void			ClearGroup( );

		/// ���ൽ����
		static void			BindGroup( RTTIClass* ClassInfo, RTTIGroup* Group );

		/// �����������м̳в�η�������
		bool SeekAccessObjectProperty( const wchar* Name, PropertyValue* PV, bool IsGet, bool SeekWholeFamily );

	private:
		
		struct RTTIObjectHashFunction
		{
			// ������Դid����
			dword operator()( const RTTIClass* key ) const
			{
				return key->GetHash( );
			}

			bool operator()(const RTTIClass* key1, const RTTIClass* key2 ) const
			{
				return key1->mClassName == key2->mClassName;
			}
		};

		typedef static_hash<RTTIClass*,RTTIClass*,RTTIObjectHashFunction, RTTIOBJECT_HASHBOUND> ClassInfoMap;

		static ClassInfoMap::iterator mIterator;
		static ClassInfoMap mClassInfoMap;

		typedef std::map<NameRef, RTTIGroup*> GroupMap;
		static GroupMap mGroupMap;
	};

	#define DECLARE_RTTI_BASE(TClass, TSuperClass, StaticClassFlag) \
		public:\
		typedef	TSuperClass Super;\
		enum { StaticClassFlags = StaticClassFlag };\
		virtual RTTIClass* GetClass( ){ Assert( sRTTIInfo != null && "RTTIObject not initialized, call Object::StaticInit first"); return sRTTIInfo; } \
		static RTTIClass* StaticClass( );\
		private:\
		static RTTIClass* sRTTIInfo;\
		friend BinarySerializer& operator << ( BinarySerializer& Ser, TClass*& Obj ) \
		{  return Ser.SerializeObject( Obj ); }\
		friend BinarySerializer& operator << ( BinarySerializer& Ser, TClass& Obj ) \
		{ Assert( Ser.IsSaving() ) \
		Ser.WriteObject( &Obj ); \
		Obj.Serialize( Ser );\
		return Ser;	} \
		public:

	/// ���� �࣬���࣬���־
	#define DECLARE_RTTI_CLASS( TClass, TSuperClass, StaticClassFlag ) \
			DECLARE_RTTI_BASE( TClass, TSuperClass, StaticClassFlag ) \
			static RTTIObject* StaticConstruct( ){ return new TClass;}\
			public:

	/// �������� �࣬���࣬���־
	#define DECLARE_RTTI_ABSTRACT( TClass, TSuperClass, StaticClassFlag  ) \
			DECLARE_RTTI_BASE(TClass, TSuperClass, StaticClassFlag | ClassFlag_Abstract ) \
			static RTTIObject* StaticConstruct( ){ return null;}\
			public:

	/// ��ʵ��
	#define IMPLEMENT_RTTI_CLASS( TClass )\
		RTTIClass* TClass::sRTTIInfo = null;\
		RTTIClass* TClass::StaticClass( )	\
		{if ( sRTTIInfo ) return  sRTTIInfo;\
		sRTTIInfo = new RTTIClass( UTEXT(#TClass), TClass::StaticConstruct, Super::StaticClass(), StaticClassFlags ); \
		RTTIObject::Register( sRTTIInfo ); \
		return sRTTIInfo;} \

	/// ע����
	#define RTTI_REGISTER( TClass ) TClass::StaticClass( );

	/// ע����,������
	#define RTTI_REGISTER_GROUP( TClass, GroupInstance ) RTTIObject::BindGroup( TClass::StaticClass( ), GroupInstance );

	/// ����ת��
	#define RTTI_CAST( TClass, TInstance ) RTTIObject::Cast<TClass>( TInstance )

	// ��̬RTTI
	#define RTTI_CLASS_NAME( TClass ) TClass::StaticClass()->mClassName
	#define RTTI_CLASS_INFO( TClass ) ( TClass::StaticClass() )

	// ʵ��RTTI
	#define RTTI_INSTANCE_STRING( TInstance ) ( TInstance->GetClass()->GetRTTIClassString() )
	#define RTTI_INSTANCE_NAME( TInstance ) ( TInstance->GetClass()->mClassName )
	#define RTTI_INSTANCE_CLASS( TInstance ) ( TInstance->GetClass() )


	// ��̬����
	// RTTIObject::StaticClass() ��ȡ��̬����Ϣ
	
	// ʵ������
	//class SomeClass : public RTTIObject
	//{
	//	DECLARE_RTTIOBJECT(SomeClass)
	//};

	//IMPLEMENT_RTTIOBJECT( SomeClass, "SomeClass", "SomeClass" )

	//SomeClass a;
	//a.GetObjectClassInfo();		// ��ȡʵ������Ϣ
	//a.GetObjectClassName();		// ��ȡʵ�������ַ���
	//a.GetObjectClassNameRef(); // ��ȡʵ����������


	/** @} */
	/** @} */
}