#pragma once

namespace NekoEngine
{
	/// ���ʾ�̬��������
	#define DECLARE_MATERIAL_STATIC_PROPERTY( TClass ) \
		public:\
			static void StaticInitProperty( ); \
			static void OnPropertyName( TClass*, WString* Value, bool IsGet); \
			static void OnPropertyDesc( TClass*, WString* Value, bool IsGet);

	// ����������ڵ�
	class MaterialNodeTextureSampler : public MaterialNode
	{
	DECLARE_RTTI_CLASS( MaterialNodeTextureSampler, MaterialNode, ClassFlag_Intrinsic| ClassFlag_Serializable )

	public:
		MaterialNodeTextureSampler( );

		virtual ~MaterialNodeTextureSampler( );

		virtual void Init(  MaterialCompiler* Compiler, MaterialDescriptor* Mat  );

		virtual void Compile( MaterialCompiler* Compiler );

		virtual void Serialize( BinarySerializer& Ser );

		virtual WString GetName( ){ return L"Texture Sampler"; }

	public:
		MaterialParameter* mSampler;
		

		MaterialSlot mUV;
	};

	// �����ڵ�
	class MaterialNodeConstant : public MaterialNode
	{
	DECLARE_RTTI_CLASS( MaterialNodeConstant, MaterialNode, ClassFlag_Intrinsic| ClassFlag_Serializable )

	public:
		MaterialNodeConstant( );

		virtual void Compile( MaterialCompiler* Compiler );

		virtual void Serialize( BinarySerializer& Ser );

		virtual WString GetName( ){ return L"Constant"; }

	public:
		Color mData;
	};

	// �������ڵ�
	class MaterialNodeMathOperator : public MaterialNode
	{
	DECLARE_RTTI_CLASS( MaterialNodeMathOperator, MaterialNode, ClassFlag_Intrinsic| ClassFlag_Serializable )
	public:
		MaterialNodeMathOperator( );

		virtual void Compile( MaterialCompiler* Compiler );

		virtual void Serialize( BinarySerializer& Ser );

		virtual WString GetName( );

	public:
		eMaterialMathOperator mOperatorType;

		MaterialSlot mDataX;
		MaterialSlot mDataY;
	};

	// Bumpƫ�ƽڵ�
	class MaterialNodeBumpOffset : public MaterialNode
	{
	DECLARE_RTTI_CLASS( MaterialNodeBumpOffset, MaterialNode, ClassFlag_Intrinsic| ClassFlag_Serializable )
	public:
		MaterialNodeBumpOffset( );

		virtual void Compile( MaterialCompiler* Compiler);

		virtual WString GetName( ){ return L"Bump Offset"; }


	public:		
		MaterialSlot mUV;
	};

	// �������ڵ�
	class MaterialNodeNormalize : public MaterialNode
	{
		DECLARE_RTTI_CLASS( MaterialNodeNormalize, MaterialNode, ClassFlag_Intrinsic| ClassFlag_Serializable )
	public:
		MaterialNodeNormalize( );

		virtual void Compile( MaterialCompiler* Compiler);

		virtual WString GetName( ){ return L"Normalize"; }

	public:		
		MaterialSlot mData;
	};


	// �ɹ����ⲿ���õı���
	class MaterialNodeUniformVector : public MaterialNode
	{
		DECLARE_RTTI_CLASS( MaterialNodeUniformVector, MaterialNode, ClassFlag_Intrinsic| ClassFlag_Serializable )
	public:
		MaterialNodeUniformVector( );

		virtual ~MaterialNodeUniformVector( );

		virtual void Init(  MaterialCompiler* Compiler, MaterialDescriptor* Mat  );

		virtual void Compile( MaterialCompiler* Compiler);

		virtual void Serialize( BinarySerializer& Ser );

		virtual WString GetName( ){ return L"Uniform Vector"; }

	public:
		MaterialParameter* mParameterData;
	};

	// �ս��,�����ص����ģ��
	class MaterialNodePointLight : public MaterialNode
	{
	DECLARE_RTTI_CLASS( MaterialNodePointLight, MaterialNode, ClassFlag_Intrinsic| ClassFlag_Serializable )
	public:
		MaterialNodePointLight( );

		virtual void Compile( MaterialCompiler* Compiler);

		virtual void CombineCode(MaterialCompiler* Compiler);

		virtual bool IsTerminateNode( ){ return true; }

		virtual WString GetName( ){ return L"Point Light Model"; }

	public:
		MaterialSlot mEmissive;
		MaterialSlot mDiffuse;
		MaterialSlot mNormal;
		MaterialSlot mSpecular;
		MaterialSlot mSpecularPow;
		MaterialSlot mOpacity;		
	};

}
