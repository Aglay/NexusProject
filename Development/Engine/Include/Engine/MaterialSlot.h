#pragma once

namespace NekoEngine
{
	class MaterialNode;
	class MaterialDescriptor;

	/** 
		���ʽڵ����Ӳ�
	*/
	class MaterialSlot
	{
	public:
		MaterialSlot( );

		/// ��ȡ�۰󶨵Ľڵ�
		MaterialNode* GetNode( ){ return mNode; }

		/// ��ȡ�۵�����
		const wchar* GetName( ){ return mName; }

		/// �����û�������κνڵ㣬ʹ��Ĭ��ֵ
		bool IsFree( );	


		/**
			��������ʽڵ��
			@param
				Name ������
			@param
				Node �󶨵Ľڵ�
			@param
				Type ��Shaderֵ����
			@param
				DefaultValue Ĭ�����ɴ���
		*/
		void Bind( const wchar* Name, MaterialNode* Node, eMaterialValueType Type = MVT_None, const char* DefaultValue = "None" );

		/// ���뱾��
		void Compile(MaterialCompiler* Compiler);

		/// �ϲ�����
		void CombineCode( MaterialCompiler* Compiler );

		/// ȡ�ý��
		MaterialMaskedValue GetResult( );

		/// ��ȡ�ϲ���Ľ��ֵ
		const char* GetCombinedCodeResult( ){ return mCodeResult.c_str(); }

		/// ��ȡ�ϲ���Ĵ�����
		const char* GetCombinedCodeBody( ){ return mCodeBody.c_str(); }

		
		/**
			���ӵ����ʽڵ�
			@param
				NodeID Ҫ���ӵĲ��ʽڵ�
			@param
				Mask ���ӷ���
			@remark
				ֻ֧��1������ڵ�,����ж������,��ʹ��Add����
		*/
		void Connect( dword NodeID , eMaterialValueMask Mask = MVM_RGB );

		/// ������ֵ��Ϊֵ����
		void SolveInputMaskAsValueType( );

		/// �Ͽ���ڵ�����
		void Disconnect( MaterialNode* NodeDeleteSource );

		friend BinarySerializer& operator <<( NekoEngine::BinarySerializer& Ser, MaterialSlot*& Data )
		{			
			Ser << Data->mLinkedNodeID
				<< Data->mInputMask;

			return Ser;
		}

		/// ��ȡ����������ӵĽڵ�
		MaterialNode* GetLinkedNode( );
		
	private:
		friend class MaterialNode;

		// ���Լ�
		const wchar*		mName;	
		eMaterialValueType	mValueType;
		const char*			mDefaultValue;
		AString				mCodeBody;
		AString				mCodeResult;
		bool				mCompileFinish;
		MaterialNode*		mNode;

		// �������ڵ����
		dword				mLinkedNodeID;
		eMaterialValueMask	mInputMask;
		dword				mInputResult;
		MaterialDescriptor*			mMaterial;

	};


	/** 
		���ʽڵ�
	*/
	class MaterialNode : public RTTIObject
	{
		DECLARE_RTTI_CLASS( MaterialNode, RTTIObject, ClassFlag_Intrinsic| ClassFlag_Serializable )

	public:
		MaterialNode( );

		virtual ~MaterialNode( );

		/// ��ȡ����Ĵ�������
		dword GetOutputCodeIndex( ) { return mOutputResult; }

		/// �������,�������е������
		virtual void Compile( MaterialCompiler* Compiler );	

		/// �ϲ�����
		virtual void CombineCode( MaterialCompiler* Compiler);

		/// �Ƿ�Ϊ���սڵ�
		virtual bool IsTerminateNode( ){ return false; }

		/// ���ʽڵ������
		virtual WString GetName( ){ return L"MaterialNode"; }

		/// ��ȡ�ڵ�ID
		dword GetID( ){ return mID; }

		/// �����ڵ��ϵĲ�
		MaterialSlot* GetSlot( dword Index );

		/// ��ȡ�۵�����
		dword GetSlotCount( );

		/// �Ͽ�����ڵ����������
		void Disconnect( );

		/// ͨ���۰󶨵�Nodeʱ�������ҵ�ʵ��
		MaterialSlot* GetSlotByName( const wchar* Name );

	public:
		/// �ڵ��ʼ��
		virtual void Init(  MaterialCompiler* Compiler, MaterialDescriptor* Mat  );

		virtual void Serialize( BinarySerializer& Ser );

		void AddOutputSlot( MaterialSlot* Slot );

		void RemoveOutputSlot( MaterialSlot* Slot );

		static void StaticInitProperty( );

	private:
		friend class MaterialSlot;

		void AddSlot( MaterialSlot* Slot );
		

	protected:
		friend class MaterialDescriptor;
		dword mID;

		typedef std::vector<MaterialSlot*> SlotArray;
		SlotArray			mSlotArray;
		dword				mOutputResult;// ����������Compile�о���������������
		bool				mCompileFinish;
		MaterialDescriptor*	mMaterial;

		typedef std::list<MaterialSlot*> SlotList;

		// �������ӵĲ�
		SlotList			mOutputSlotList;

		/// Ϊ�༭������׼��
		Vector2				mScenePos;

	};

}
