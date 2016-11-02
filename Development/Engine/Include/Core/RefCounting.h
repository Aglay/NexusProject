#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Basic
	*  @{
	*/

	/**
		���ü�������
		@remark
			��Ҫ�������ü�����������������
	*/
	class RefObject
	{
	public:
		RefObject(): NumRefs(0) {}
		virtual ~RefObject() {  }

		/**
			��������
		*/
		void AddRef()
		{
			NumRefs++;
		}

		/** 
			�Ƴ�����
			@return
				�Ƴ����ú�ʣ�µ�����
		*/
		int RemoveRef()
		{
			--NumRefs;

			RefObject_OnDecrease( NumRefs );

			if( NumRefs == 0)
			{
				RefObject_OnDestroy( );

				return 0;
			}

			return NumRefs;
		}

		/** 
			��ȡ��������
			@return
				��������
		*/
		int GetRefCount( ){ return NumRefs; }

		/** 
			��������֪ͨ
			@remark
				���ش˺������ڶ��󼴽�����ǰ��֪ͨ
		*/
		virtual void RefObject_OnDestroy(  )
		{
			delete this;
		}

		/** 
			�������ü���֪ͨ
			@remark
				ʹ�ô˺������Ե����������մ���֪ͨ
			@param
				RefCount ʣ�µ����ü���
		*/
		virtual void RefObject_OnDecrease( int RefCount ){ }

	private:
		int NumRefs;
	};

	/** 
		����ָ�����
		@remark
			��ģ����ģ���������Ҫ����RefObject�����࣬����ʵ���Զ�AddRef/RemoveRef����
	*/
	template<typename ReferencedType>
	class TRefPtr
	{
		typedef ReferencedType* ReferenceType;
	public:

		TRefPtr():
			Reference(null)
		{}

		/** 
			���캯��
			@remark
				����������ָ��
		*/
		TRefPtr(ReferencedType* InReference,bool bAddRef = true)
		{
			Reference = InReference;
			if(Reference && bAddRef)
			{
				Reference->AddRef();
			}
		}

		/** 
			�������캯��
		*/
		TRefPtr(const TRefPtr& Copy)
		{
			Reference = Copy.Reference;
			if(Reference)
			{
				Reference->AddRef();
			}
		}

		/** 
			��������
		*/
		~TRefPtr()
		{
			if(Reference)
			{
				Reference->RemoveRef();
			}
		}

		/** 
			�ͷ�����ָ��Ķ�������
		*/
		void Release( )
		{
			*this = null;
		}

		/** 
			��֤����ָ����Ч��
			@return
				����ָ��������ʱ������true������false
		*/
		bool Valid( ) const
		{
			return Reference != null;
		}

		/** 
			��֤����ָ���Ƿ�Ϊ��
			@return
				����ָ��Ϊ��ʱ������true������false
		*/
		bool Empty( ) const
		{
			return Reference == null;
		}

		/** 
			����ָ�뿽������
			@param 
				InReference �������ö���ָ��
			@return
				���ر���������
		*/
		TRefPtr& operator=(ReferencedType* InReference)
		{
			ReferencedType* OldReference = Reference;
			Reference = InReference;
			if(Reference)
			{
				Reference->AddRef();
			}
			if(OldReference)
			{
				OldReference->RemoveRef();
			}
			return *this;
		}
		
		/** 
			����ָ�뿽������
			@param 
				InReference �������ö�������
			@return
				���ر���������

		*/
		TRefPtr& operator=(const TRefPtr& InPtr)
		{
			return *this = InPtr.Reference;
		}

		/** 
			����ָ��Ƚ�
			@param
				Other ����һ������ָ��
			@return
				����ָ���Ƿ����
		*/
		bool operator==(const TRefPtr& Other) const
		{
			return Reference == Other.Reference;
		}

		/** 
			����ָ��Ƚ�
			@param
				Other ����һ������ָ��ָ��
			@return
				����ָ���Ƿ����
		*/
		bool operator==(ReferencedType* Other) const
		{
			return Reference == Other;
		}

		/** 
			��ȡ���ö���
			@return
				������������
		*/
		ReferencedType* operator->() const{	return Reference;}

		/** 
			��ȡ���ö���
			@return
				������������
		*/
		ReferencedType* GetPtr( ) const{return Reference;}

		/** 
			��ȡ���ö���
			@return
				������������
		*/
		ReferencedType*& GetPtr( ){	return Reference;}

		/** 
			ת�����ö�������
			@return
				������������
		*/
		template<typename TClass>
		TClass* CastTo( ) const{return dynamic_cast<TClass*>( Reference );}

		/** 
			��ȡ���ö���
			@return
				������������
		*/
		operator ReferenceType() const{	return Reference;}

	private:
		ReferencedType* Reference;
	};

	/** @} */
	/** @} */
}