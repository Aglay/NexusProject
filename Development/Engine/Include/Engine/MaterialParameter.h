#pragma once

namespace NekoEngine
{
	


	class MaterialParameter : public RTTIObject
	{
	DECLARE_RTTI_ABSTRACT( MaterialParameter, RTTIObject, ClassFlag_Intrinsic|ClassFlag_Serializable )

	public:
		
		MaterialParameter( );

		virtual ~MaterialParameter( );

		// ���ɲ�����Ӧ��Shader������
		virtual AString MakeParameterName( ){ return ""; }// Option���Ͳ���ʵ��

		// ����Դ�࿪ʼ������Դ
		virtual void PrepareResource( ){ }

		virtual bool IsResourceReady( ){ return true; }

		virtual const char* MakeDefineType( ){ return ""; }

		//// ����ָ��Ĵ�����
		//friend BinarySerializer& operator <<( NekoEngine::BinarySerializer& Ser, MaterialParameterPtr& Data )
		//{	
		//	Ser.SerializeObject( Data.GetPtr() );

		//	if ( Ser.IsLoading() )
		//	{
		//		Data.GetPtr()->AddRef();
		//	}

		//	return Ser;
		//}

		virtual MaterialParameter* Clone( );

		virtual void Serialize( BinarySerializer& Ser );

		// �����ύ���ݵ�Shader
		virtual void Commit( RHIShader* Shader, const ShaderParameter& Parameter ){ }

		// �Ƿ�Shaderʹ�õı���
		virtual bool IsUniformParameter( ){ return true; }

		// ��������
		void SetName( const wchar* Name ){ mName = Name; }

		const wchar* GetName( ){ return mName.c_str(); }

		// ����ֵ���ڲ����Զ�Parse��Ϊָ��������
		virtual void SetValue( const wchar* Value ) = 0;

		virtual WString GetValue( ) = 0;

		// ��ӦShader�б��������
		dword GetUniformIndex( ){ return mUniformIndex; }
		
	protected:
		friend class MaterialCompiler;
		dword	mUniformIndex;		// ���������������������
		WString mName;
		
	};

	typedef std::vector<MaterialParameter*> MaterialParameterArray;
	
	

	

	class MaterialParameterTextureSampler : public MaterialParameter
	{
	public:
		DECLARE_RTTI_CLASS( MaterialParameterTextureSampler, MaterialParameter, ClassFlag_Intrinsic| ClassFlag_Serializable )

		virtual AString MakeParameterName( );

		virtual const char* MakeDefineType( ){ return "sampler2D"; }

		virtual void PrepareResource( );

		virtual bool IsResourceReady( );

		virtual void Commit( RHIShader* Shader, const ShaderParameter& Parameter );

		virtual void Serialize( BinarySerializer& Ser );

		virtual void SetValue( const wchar* Value );

		virtual WString GetValue( );

		virtual MaterialParameter* Clone( );

	protected:
		TextureResourcePtr	mTexture;
		WString				mResourceLocation;
	};

	class MaterialParameterVector : public MaterialParameter
	{
	public:
		DECLARE_RTTI_CLASS( MaterialParameterVector, MaterialParameter, ClassFlag_Intrinsic| ClassFlag_Serializable )

		MaterialParameterVector( );

		virtual AString MakeParameterName( );

		virtual const char* MakeDefineType( ){ return "float4"; }

		virtual void Commit( RHIShader* Shader, const ShaderParameter& Parameter );

		virtual void SetValue( const wchar* Value );

		virtual WString GetValue( );

		MaterialParameter* Clone();

	public:
		eMaterialValueType	mValueType;
		Vector4				mValue;
	};

	class MaterialParameterBool : public MaterialParameter
	{
	public:
		DECLARE_RTTI_CLASS( MaterialParameterBool, MaterialParameter, ClassFlag_Intrinsic| ClassFlag_Serializable )

		virtual void Serialize( BinarySerializer& Ser );

		virtual bool IsUniformParameter( ){ return false; }

		virtual void SetValue( const wchar* Value );

		virtual WString GetValue( );

		virtual MaterialParameter* Clone();

	public:
		bool mValue;
	};
}
