#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Render
	*  @{
	*/


	/** 
		ȫ��Shader���Զ�����ʶ��ָ��
		@remark
			����һ�������ָ��,�����ظ���������
			GlobalShaderRef<ElementVertexShader> VertexShaderRef;
			VertexShaderRef->SetParameter( Transform.Transpose() );
	*/
	template<typename TShaderType>
	class GlobalShaderRef
	{
	public:
		GlobalShaderRef( )
		{
			GlobalShaderFactory* Factoy = GShaderMaster->GetFactory<GlobalShaderFactory>( );

			Shader = (TShaderType*)Factoy->Find( RTTI_CLASS_INFO(TShaderType) );
		}

		TShaderType* operator->() const
		{
			return Shader;
		}

		TShaderType* operator*() const
		{
			return Shader;
		}

	private:
		TShaderType* Shader;
	};

	/** 
		ȫ��Shader����
		@remark
			����ȫ��Shader�ı��뼰Ѱ��
	*/
	class GlobalShaderFactory : public ShaderFactory
	{
		DECLARE_RTTI_CLASS( GlobalShaderFactory, ShaderFactory, ClassFlag_Intrinsic| ClassFlag_Serializable )
	public:
		virtual ~GlobalShaderFactory( );

		virtual dword Compile( );

		virtual void Serialize( BinarySerializer& Ser );

		virtual void Clear( );
		
		virtual void LoadCache( );

		virtual void SaveCache( );

		/** 
			����ȫ��Shader�����Ͳ鵽�������
		*/
		RenderShader* Find( RTTIClass* ClassInfo );

		
	private:
		typedef dynamic_hash<RTTIClass*, RenderShader*> GlobalShaderMap;

		bool CompileGlobalShader( RenderShader* Binder, ShaderCompilerEnvironment& CompilerEnvironment );
		

		GlobalShaderMap mGlobalShaderMap;
	};

	/** @} */
	/** @} */
}
