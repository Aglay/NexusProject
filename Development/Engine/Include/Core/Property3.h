#pragma once


namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Reflection
	*  @{
	*/

	class RTTIObject;
	class PropertyCollection;
	class PropertyValue;

	/**
		������
	*/

	class PropertyGroup
	{
	public:
		explicit PropertyGroup( const WString& Name ) : mGroupName( Name ){ }

		/** 
			����������
			@return
				������׺���ʽ
		*/
		PropertyGroup& SetName( const WString& Name ){ mGroupName = Name; return *this;}

		/// ��ȡ��������
		const WString& GetName( ){ return mGroupName; }

		/// ��ȡ�����ڵ�����
		PropertyValue* GetPropery( dword Index ){ return mPropertyValueArray[Index]; }

		/// ��ȡ�����ڵ���������
		dword GetPropertyCount( ){ return mPropertyValueArray.size(); }

		/// ������Ե�����
		void AddProperty( PropertyValue* PV ){ mPropertyValueArray.push_back( PV ); }

	private:
		WString mGroupName;

		typedef std::vector<PropertyValue*> PropertyValueArray;
		PropertyValueArray mPropertyValueArray;		
	};

	/** 
		����ֵ
	*/
	class PropertyValue
	{
	public:
		PropertyValue( )			
			: mReadOnly( false )
			, mGroup( null )
		{

		}

		virtual ~PropertyValue( ){ }


		/** 
			���û��߻�ȡһ������ֵ
			@param
				Instance ʵ��
			@param
				PV ����
			@param
				IsGet �Ƿ�Ϊ��ȡ����/��������
		*/
		virtual bool AccessValue( RTTIObject* Instance, PropertyValue* PV, bool IsGet ) = 0;

		/** 
			����һ������ֵ
			@param
				Instance ʵ��
			@param
				PV ����
		*/
		inline bool Set( RTTIObject* Instance, PropertyValue* PV)
		{
			return AccessValue( Instance, PV, false );
		}

		/** 
			��ȡһ������ֵ
			@param
				Instance ʵ��
			@param
				PV ����
		*/
		inline bool Get( RTTIObject* Instance, PropertyValue* PV)
		{
			return AccessValue( Instance, PV, true );
		}

		/**
			ʹ���������л������л�����
			@param
				Instance ʵ��
			@param
				Ser	�������л���
			@return
				�����л����󶨴���׽������Ի����ȷ����ֵ.����ʼ��Ϊtrue
		*/
		virtual bool SerializeConfig( RTTIObject* Instance, PropertySerializer& Ser, bool UseGroupAsSection ) = 0;

		/** 
			ȡ����������
		*/
		virtual const wchar* GetName( ){ return mName; }

		/** 
			�����Ƿ�Ϊ����
		*/
		virtual bool IsConstant( ) = 0;

		/** 
			��������תΪ�ַ���
		*/
		bool ToString( RTTIObject* Instance, WString& Value );

		/** 
			�����ַ�������������
		*/
		bool Parse( RTTIObject* Instance, const wchar* Value );

		/** 
			�Ƿ�ƥ����������
		*/
		bool MatchType( PropertyValue* PV );

		/** 
			��������ֻ��
			@return
				������׺���ʽ
		*/
		PropertyValue& SetReadOnly( bool Value ){ mReadOnly = Value; return *this; }

		/** 
			��ȡ����ֻ��
		*/
		bool GetReadOnly( ){ return mReadOnly; }

		/** 
			ȡ������������
		*/
		const wchar* GetTypeName( ){ return mTypeName; }

		/// ����������
		PropertyValue& SetGroup( PropertyGroup* Group ){ mGroup = Group;  return *this; }

		/// ��ȡ������
		PropertyGroup* GetGroup( ){ return mGroup; }

	protected:
		const wchar* mTypeName;

		const wchar* mName;

		PropertyGroup* mGroup;

		bool mReadOnly;

		friend class PropertyCollection;
		PropertyCollection* mCollection;
	};



	/** 
		ֵ���ͻ���
	*/
	template<typename TType>
	class TPropertyValueBase : public PropertyValue
	{
	public:
		virtual void OnSetValue( RTTIObject* Instance, const TType& Value ) = 0;

		virtual void OnGetValue( RTTIObject* Instance, TType& Value ) = 0;

		virtual bool SerializeConfig( RTTIObject* Instance, PropertySerializer& Ser, bool UseGroupAsSection )
		{
			if ( UseGroupAsSection && mGroup != null )
			{
				// �л�section
				if ( Ser.GetSection( ) != mGroup->GetName() )
					Ser.SerializeSection( mGroup->GetName() );
			}
			

			if ( Ser.IsLoading() )
			{
				if ( !IsConstant() )
				{
					TType Value;

					// ����key
					Ser << mName << Value;

					OnSetValue( Instance , Value );
				}
			}
			else
			{
				TType Value;

				OnGetValue( Instance, Value );

				Ser << mName << Value;
			}

			// �����Ҫ����ֵ����,��ҪΪSerializer��һ��Error����
			PropertySerializerErrorCatcher* ErrorObj = Ser.GetErrorObject();
			
			if ( ErrorObj == null )
				return true;

			return ErrorObj->GetErrorCount() == 0;
		}

		virtual bool AccessValue( RTTIObject* Instance, PropertyValue* PV, bool IsGet )
		{
			if ( IsGet && PV->IsConstant() )
				return false;

			if ( !IsGet && IsConstant() )
				return false;

			// ���ⲿ�ַ������ͽ���Ϊ������
			PropertyStringValue* PStr = dynamic_cast<PropertyStringValue*>( PV );
			if ( PStr != null )
			{
				if ( IsGet )
				{
					TType Value;
					OnGetValue( Instance, Value );

					PStr->mStringRef = value_tostringW( Value  );
				}
				else
				{
					TType NewValue;
					if ( !value_parse( PStr->GetString(), NewValue ) )
						return false;

					OnSetValue( Instance, NewValue );

				}
				
				return true;
			}


			Assert( PV->MatchType( this ) );
			if ( !PV->MatchType( this ) )
				return false;

			// ��ֵ���ⲿֵ����/ ���ⲿֵ��������
			TPropertyValueRef<TType>* PVRef = dynamic_cast<TPropertyValueRef<TType>*>( PV );
			if ( PVRef != null )
			{
				if ( IsGet )
				{
					TType Value;
					OnGetValue( Instance, Value );

					*PVRef->mValueRef = Value;
				}
				else
				{
					OnSetValue( Instance , *PVRef->mValueRef );
				}
				
				return true;
			}

			return false;
		}
	};

	/** 
		���Ա����
	*/
	template<typename TType>
	class TPropertyMember : public TPropertyValueBase<TType>
	{
	public:
		TPropertyMember( const wchar* TypeName, const wchar* Name, dword Offset, dword Size )
		{
			mOffset		= Offset;
			mSize		= Size;
			mTypeName	= TypeName;
			mName		= Name;
		}

		virtual const wchar* GetName( ){ return mName; }

		// ���ĳ��ʵ��������ָ��
		TType* GetPropertyAddress( RTTIObject* Instance )
		{
			return (TType*)(dword(Instance) + mOffset);
		}

		virtual bool IsConstant( ){ return false; }


		virtual void OnSetValue( RTTIObject* Instance, const TType& Value )
		{
			*GetPropertyAddress( Instance ) = Value;
		}

		virtual void OnGetValue( RTTIObject* Instance, TType& Value )
		{
			Value = *GetPropertyAddress( Instance );
		}

	private:
		dword	mOffset;
		dword	mSize;
	};

	extern WString GPropertyNullString;

	/** 
		�ַ�������,����ToString��Parse
	*/
	class PropertyStringValue : public PropertyValue
	{
	public:
		PropertyStringValue( WString& Value )
			: mStringRef( Value )
			, mConstString( null )
		{
			mTypeName = L"#RefString";
			mName = L"#RefString";
		}

		PropertyStringValue( const wchar* Value )
			: mStringRef( GPropertyNullString )
			, mConstString( Value )
		{
			mTypeName = L"#ConstString";
			mName = L"#ConstString";
		}

		virtual bool IsConstant( ){ return mConstString != null; }

		virtual bool SerializeConfig( RTTIObject* Instance, PropertySerializer& Ser, bool UseGroupAsSection )
		{
			if ( UseGroupAsSection && mGroup != null )
			{
				// �л�section
				if ( Ser.GetSection( ) != mGroup->GetName() )
					Ser.SerializeSection( mGroup->GetName() );
			}


			if ( Ser.IsLoading() )
			{
				if ( IsConstant() )
					return false;
			
				// ����key
				Ser << mName << mStringRef;
			}
			else
			{								
				Ser << mName << GetString();
			}

			// �����Ҫ����ֵ����,��ҪΪSerializer��һ��Error����
			PropertySerializerErrorCatcher* ErrorObj = Ser.GetErrorObject();

			if ( ErrorObj == null )
				return true;

			return ErrorObj->GetErrorCount() == 0;
		}


		virtual bool AccessValue( RTTIObject* Instance, PropertyValue* PV, bool IsGet )
		{
			if ( IsGet && PV->IsConstant() )
				return false;

			if ( !IsGet && IsConstant() )
				return false;

			// ����Ϊ�ַ�������
			Assert( PV->MatchType( this ) );
			if ( !PV->MatchType( this ) )
				return false;

			// �ַ�������
			PropertyStringValue* PStr = dynamic_cast<PropertyStringValue*>( PV );
			if ( PStr != null )
			{
				if ( IsGet )
				{
					if ( IsConstant() )
						PStr->mStringRef = mConstString;
					else
						PStr->mStringRef = mStringRef;
				}
				else
				{
					mStringRef = PStr->GetString();
				}
				

				return true;
			}

			return false;
		}

		const wchar* GetString( )
		{
			if ( mConstString )
				return mConstString;

			return mStringRef.c_str();
		}

	public:
		WString& mStringRef;
		const wchar* mConstString;		
	};


	/** 
		��������Я����Ϣ
	*/
	template<typename TType>
	class TPropertyValueRef : public TPropertyValueBase<TType>
	{
	public:
		// ��������
		TPropertyValueRef( TType& Value, const wchar* TypeName )
			: mValueRef( &Value )
			, mConstant( false )
		{
			mTypeName = TypeName;
			mName = L"#Value";
		}

		// ������������
		TPropertyValueRef( const TType& Value, const wchar* TypeName )
			: mValueRef( (TType*)&Value )
			, mConstant( true )
		{

			mTypeName = TypeName;
		}

		virtual bool IsConstant( ){ return mConstant; }
		
		virtual void OnSetValue( RTTIObject* Instance, const TType& Value )
		{
			*mValueRef = Value;
		}

		virtual void OnGetValue( RTTIObject* Instance, TType& Value )
		{
			Value = *mValueRef;
		}


	public:
		TType* mValueRef;
		bool mConstant;
	};

	
	/** 
		���Ա��������
	*/
	template<typename TType, typename TClass, typename TFuncType>
	class TPropertyDelegate : public TPropertyValueBase<TType>
	{
	public:
		// ��������
		TPropertyDelegate( const wchar* TypeName, const wchar* Name, TFuncType Func )
			: mFunc( Func )
		{
			mTypeName = TypeName;
			mName = Name;
		}



		virtual bool IsConstant( ){ return false; }

		virtual void OnSetValue( RTTIObject* Instance, const TType& Value )
		{			
			TClass* Callee = RTTIObject::Cast<TClass>( Instance );
			Assert( Callee != null );
			if ( Callee == null )
				return;

			( Callee->*mFunc)( (TType*)&Value, false );
		}

		virtual void OnGetValue( RTTIObject* Instance, TType& Value )
		{
			TClass* Callee = RTTIObject::Cast<TClass>( Instance );
			Assert( Callee != null );
			if ( Callee == null )
				return;

			( Callee->*mFunc)( &Value, true );
		}

	private:
		TFuncType mFunc;
	};

	/** 
		�ص�����
	*/
	template<typename TType, typename TClass, typename TFuncType >
	class TPropertyCallback : public TPropertyValueBase<TType>
	{
	public:
		// ��������
		TPropertyCallback( const wchar* TypeName, const wchar* Name, TFuncType Func )
			: mFunc( Func )
		{
			mTypeName = TypeName;
			mName = Name;
		}

		virtual bool IsConstant( ){ return false; }

		virtual void OnSetValue( RTTIObject* Instance, const TType& Value )
		{			
			TClass* Callee = RTTIObject::Cast<TClass>( Instance );
			
			Assert( Callee != null );
			if ( Callee == null )
				return;

			mFunc( Callee, (TType*)&Value, false );
		}

		virtual void OnGetValue( RTTIObject* Instance, TType& Value )
		{
			TClass* Callee = RTTIObject::Cast<TClass>( Instance );

			mFunc( Callee, &Value, true );
		}

	private:
		TFuncType mFunc;
	};


	/// ֵ����
	#define PROPERTY_VALUE(TType, TValue ) TPropertyValueRef<TType>( TValue, UTEXT(#TType) )

	/// �࣬�ṹ��ĳ�Ա����
	#define PROPERTY_MEMBER_VAR( TClass, TType, TValue) new TPropertyMember<TType>( UTEXT(#TType),UTEXT(#TValue) + 1,StructOffset(TClass,TValue), sizeof(TType) )

	/// ���Ա����
	#define PROPERTY_DELEGATE( TClass, TType, ValueName,Func ) PropertyCollection::NewDelegateProperty<TType>( (TClass*)null, UTEXT(#TType), ValueName, Func )

	/// ��̬����
	#define PROPERTY_CALLBACK( TClass, TType, ValueName,Func ) PropertyCollection::NewCallbackProperty<TType>( (TClass*)null, UTEXT(#TType), ValueName, Func )	

	

	class PropertyActionListener
	{
	public:
		virtual bool OnPropertyGet( PropertyCollection* PC, RTTIObject* Instance, PropertyValue* PV ) = 0; 

		virtual bool OnPropertySet( PropertyCollection* PC, RTTIObject* Instance, PropertyValue* PV ) = 0; 
	};

	class PropertyCollection
	{
	public:
		PropertyCollection( );

		virtual ~PropertyCollection( );

		/// ���������Ϣ
		PropertyValue* Add( PropertyValue* Property, PropertyGroup* Group = null );
		
		/// ��������ֵ
		bool Set( RTTIObject* Instance, const wchar* Name, PropertyValue& PV );

		/// ��ȡ����ֵ
		bool Get( RTTIObject* Instance, const wchar* Name, PropertyValue& PV );

		/// ����ֵתΪ�ַ���
		bool ToString( RTTIObject* Instance, const wchar* Name,WString& Value );

		/// �ַ�����������ֵ
		bool Parse( RTTIObject* Instance, const wchar* Name,const wchar* Value );

		/// ��������һ������ֵ
		PropertyValue* GetFirstProperty( );

		/// ��������һ������ֵ
		PropertyValue* GetNextProperty( );

		/// ����ĳ���ض�����ֵ
		PropertyValue* Query( const wchar* Name );


		/**
			ʹ���������л������л����е�����
			@param
				Instance ʵ��
			@param
				Ser	�������л���			
		*/
		void SerializeConfig( RTTIObject* Instance, PropertySerializer& Ser );

		/// Я��TClass���ͼ�TFuncType��Dummy����
		template<typename TType, typename TClass, typename TFuncType >
		static PropertyValue* NewDelegateProperty( TClass* TemplateDummy, const wchar* TypeName, const wchar* Name, TFuncType Func)
		{
			return new TPropertyDelegate<TType,TClass, TFuncType>( TypeName, Name, Func );
		}

		/// Я��TClass���ͼ�TFuncType��Dummy����
		template<typename TType, typename TClass, typename TFuncType >
		static PropertyValue* NewCallbackProperty( TClass* TemplateDummy, const wchar* TypeName, const wchar* Name, TFuncType Func)
		{
			return new TPropertyCallback<TType,TClass, TFuncType>( TypeName, Name, Func );
		}

		/// ���һ��������
		PropertyGroup* AddGroup( const WString& Name );

		/// ����������
		PropertyGroup* GetGroup( dword Index );

		/// ��ȡ����������
		dword GetGroupCount( ){ return mGroupArray.size(); }
	
		/// �������������Ʋ�ѯ
		PropertyGroup* QueryGroup( const WString& Name );

	private:
		bool DoAction( RTTIObject* Instance, const wchar* Name, PropertyValue* PV, bool IsGet );		
		
	private:
		typedef dynamic_hash<WString, PropertyValue*> PropertyMap;
		PropertyMap mPropertyMap;
		PropertyMap::iterator* mIterator;

		typedef std::vector<PropertyGroup*> GroupArray;
		GroupArray mGroupArray;
	};


	/** @} */
	/** @} */
}

//struct MyClass 
//{
//	bool Value1;
//	Vector3 Value2;
//
//	const Vector3& GetValue2( )
//	{
//		return Value2;
//	}
//
//	void SetValue2( const Vector3& v )
//	{
//		Value2 = v;
//	}
//
//
//	void OnValueChange( Vector3* Value, bool IsGet )
//	{
//		if ( IsGet )
//		{
//			*Value = GetValue2();
//		}
//		else
//		{
//			SetValue2( *Value );
//		}
//
//	}
//
//	static void OnChange( MyClass* Instance, Vector3* Value, bool IsGet )
//	{
//
//	}
//};
//
//MyClass b;
//b.Value1 = false;
//b.Value2 = Vector3( 4,5,6);
//
//PropertyCollection PS;
//PS.Add( CLASS_PROPERTY(MyClass,bool, Value1) );
////PS.Add( CLASS_PROPERTY(MyClass,Vector3, Value2) );
//
//
//PS.Add( CALLBACK_PROPERTY( MyClass, Vector3, L"Value3", &MyClass::OnChange ) );
//PS.Add( DELEGATE_PROPERTY( MyClass, Vector3, L"Value2", &MyClass::OnValueChange ) );
//
//PS.Parse( &b, L"Value3",L"a");
//
//PS.Parse( &b, L"Value1", L"true");
//
//PS.Set( &b, L"Value2", PROPERTY_VALUE( Vector3, Vector3(1,2,3) ));
//
//WString a;
//PS.ToString(&b,L"Value2", a );
//
//Vector3 d;
//PS.Get(&b,L"Value2", PROPERTY_VALUE(Vector3, d ));
//
//
//SimpleLog log;
//for ( PropertyValue* MV = PS.GetFirstProperty();
//	 MV != null;
//	 MV = PS.GetNextProperty() )
//{
//	WString str;
//	MV->ToString( &b, str );
//	log.Debug(L"%s = %s", MV->GetName(),  str.c_str());
//}