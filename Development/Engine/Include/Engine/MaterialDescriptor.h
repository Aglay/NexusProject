#pragma once

namespace NekoEngine
{
	/** 
		����������
		@remark
			��ƽ׶εĲ��ʽڵ�������
			����Ҫ�ĸ������ͽڵ���ӵ��������в��������Ǽȿ����ɶ�Ӧ��Pixel Shader�ļ�
	*/
	class MaterialDescriptor : public ManagedObject
	{
		DECLARE_RTTI_CLASS( MaterialDescriptor, ManagedObject, ClassFlag_Intrinsic| ClassFlag_Serializable )
	public:
		MaterialDescriptor( );

		virtual ~MaterialDescriptor( );

		/**
			��ӽڵ�
			@param
				ClassInfo �ڵ�����
			@return
				��Ӻ�Ľڵ�
		*/
		MaterialNode* AddNode( RTTIClass* ClassInfo );

		/// ��ӽڵ��ģ���װ
		template<typename TClass>
		TClass* AddNode( )
		{
			return RTTI_CAST(TClass, AddNode( RTTI_CLASS_INFO(TClass) ) );
		}

		/// ��ȡ���ʽڵ�
		MaterialNode* GetNode( dword ID );

		/// �Ƴ�һ�����ʽڵ�
		void RemoveNode( dword ID );

		/// ������в��ʽڵ�
		void Clear( );

		/// ���벢����Shader����
		void GenerateShaderFile( const wchar* FilenName );

		/// ��ȡ������
		MaterialCompiler* GetCompiler( ){ return mCompiler; }

		/// ������һ���ڵ�
		MaterialNode* GetFirstNode( );

		/// ������һ���ڵ�
		MaterialNode* GetNextNode( );

		/// ��ȡ�ն˽ڵ�
		MaterialNode* GetTerminateNode( );

	public:
		virtual void Serialize( BinarySerializer& Ser );

	private:
		typedef dynamic_hash<dword, MaterialNode*> NodeMap;
		NodeMap				mNodeMap;
		MaterialCompiler*	mCompiler;
		dword				mAccIDGen;
		NodeMap::iterator*	mIterator;
		
	};

	typedef TRefPtr<MaterialDescriptor> MaterialDescriptorPtr;
}
