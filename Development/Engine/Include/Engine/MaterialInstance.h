#pragma once

namespace NekoEngine
{
	
	/**
		����ʵ��
		@remark
			MaterialInstance��������ʱʹ��,�༭����ʹ��\
			MaterialInstance����Ⱦ״̬���з�װ,����
			MaterialInstance��Ҫ����MaterialDescriptor�����Ƽ�MaterialParameter��������������
			MaterialInstanceʹ��ʱ,ͨ�����������ҵ���Ӧ��Pixel Shader�ļ����б���,����������ʱ������Ҫ��MaterialParameter����ʹ��
			��MaterialDescriptor���º�,MaterialInstance��Ҫ���йҽӸ���
	*/
	class MaterialInstance : public ManagedObject
	{
		DECLARE_RTTI_CLASS( MaterialInstance, ManagedObject, ClassFlag_Intrinsic| ClassFlag_Serializable )
	public:
		MaterialInstance();

		virtual ~MaterialInstance( );

		virtual void Serialize( BinarySerializer& Ser );

		void SetVector4( const wchar* Name, const Vector4& Value );

		void SetColor( const wchar* Name, const Color& C );

		MaterialParameter* GetShaderParameter( dword UniformIndex );

		dword GetShaderParameterCount( );

		MaterialParameter* SearchParameter( const wchar* Name  );

		// ��Material��Compiler������Ĳ����б����õ�MI��������������
		void LinkMaterial( MaterialDescriptor* Mat );

		// �ṩһ��VS���࣬�����ݲ������ƴ�MaterialShaderFactory����Shader
		void LoadShader( RTTIClass* VertexShaderProvider );

		// ����Shader�������ύVS,PS
		void CommitShader( bool VertexShaderOnly );

		void CommitRenderState( );

		// �ⲿ����VS����
		MaterialVertexShader* GetVertexShader( ){ return mShaderCollection.mVertexShader; }

		template<typename TClass>
		TClass* GetVertexShader( )
		{
			return RTTI_CAST(TClass, GetVertexShader() );
		}

		static void StaticInitProperty();

		bool IsTransparent() { return mBlendMode == BLEND_Translucent; }

		bool IsEnableDepthWrite() { return mEnableDepthWrite; }


	protected:
		virtual void PostLoad( );

		virtual bool IsManualResourceReady( );
		
	private:
		friend class MaterialDescriptor;
		WString						mMaterialName;

		// ����Shader����Ĳ����б�
		MaterialParameterArray		mShaderParameterArray;
	
		// Shaderָ��
		MaterialShaderCollection	mShaderCollection;


		RenderCommandFence mParamterResourceFence;

		bool		mUseTangentSpace;
		bool		mUseSkeletonMesh;
		eBlendMode	mBlendMode;
		bool		mWireframe;
		bool		mTwoSided;
		bool		mEnableDepthWrite;
	};

	typedef TRefPtr<MaterialInstance> MaterialInstancePtr;

	
}
