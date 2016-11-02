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
		Shader�����Ϣ
	*/
	struct ShaderMetaInfo 
	{
		/// ����
		eShaderType mType;

		/// ShaderԴ��λ��
		const wchar* mSourceFile;

		/// Դ�����
		const wchar* mEntryName;
		

		ShaderMetaInfo(eShaderType Type, const wchar* SourceFile, const wchar* EntryName )
			: mType( Type )
			, mSourceFile( SourceFile )
			, mEntryName( EntryName )
		{
			
		}

	};


	/** 
		RHIShader��װ��
		@remark
			����Ⱦ�߳�ʹ�õ�Shader��
	*/
	class RenderShader : public RTTIObject
	{
	public:
		DECLARE_RTTI_CLASS( RenderShader, RTTIObject,ClassFlag_Intrinsic| ClassFlag_Serializable )
		RenderShader( );

		virtual ~RenderShader( );

		/** 
			�ύShader
		*/
		virtual void Commit( );		

		/** 
			��ȡShader�����Ϣ
		*/
		virtual ShaderMetaInfo* GetShaderMetaInfo( ){ return null;}

		/** 
			�Ƿ���ʾ�����
		*/
		virtual bool ShowDisassembleCode( ){ return false; }

		/// ���������л�
		virtual void Serialize( BinarySerializer& Ser );

		/** 
			�Ƿ����Shader
		*/
		virtual bool IsMaterialShader( ){ return false; }

		/** 
			��ȡRHIShader
		*/
		RHIShader* GetRHIShader( ){ return mShaderRHI; }

	protected:
		/** 
			Ԥ�����ص�
		*/
		virtual void PreprocessMacro( ShaderCompilerEnvironment& CompilerEnvironment ){ }

		/** 
			��Shader����
		*/
		virtual void BindShaderParameter( eShaderType ShaderType, const ShaderParameterMap& ParameterMap ){}	


	protected:
		friend class GlobalShaderFactory;
		RHIShaderRef mShaderRHI;
		FileTime	 mModifyTime;
	};

	/// ��Shader��Ϣ����
	#define DECLARE_SHADER_METAINFO( ShaderType, SourceFile, EntryName ) \
	public:\
	virtual ShaderMetaInfo* GetShaderMetaInfo( ) \
	{ static ShaderMetaInfo metainfo( ShaderType, SourceFile, EntryName ); return &metainfo; }
		
	
	/** 
		Shader����
	*/
	class ShaderFactory : public RTTIObject
	{
		DECLARE_RTTI_ABSTRACT( ShaderFactory, RTTIObject, ClassFlag_Intrinsic|ClassFlag_Serializable )

	public:
		ShaderFactory( );
		virtual ~ShaderFactory( );

		/** 
			����Shader
		*/
		virtual dword Compile( ) = 0;

		/// ���������л�
		virtual void Serialize( BinarySerializer& Ser ) = 0;

		/// �������Shader
		virtual void Clear( ) = 0;

		/// ����
		virtual void Tick( float Elapse ){ }

		/// ���ػ���
		virtual void LoadCache( ) = 0;

		/// ���滻��
		virtual void SaveCache( ) = 0;

		void InitLog( );

		/// ����Ⱦ�߳���ɾ��RHIShader
		void DeleteShader_RenderThread( RenderShader* Binder );

	protected:
		Logger* mLogger;
	};

	/** 
		Shader������
	*/
	class ShaderMaster
	{
	public:
		ShaderMaster( );

		virtual ~ShaderMaster();

		/** 
			��ʼ��Shader��
			@param
				UseShaderCache �Ƿ����Shader�󻺳嵽���������´μ����ٶ�
		*/
		void InitializeShaderLibrary( bool UseShaderCache );		

		/// �ر���
		void Rebuild( );

		/// ɾ������Shader����
		void Clear(  );

		/// ����
		void Tick( float elapse );

		/** 
			��ȡһ��Shader����
			@param
				��������Ϣ
			@return
				Shader����
		*/
		ShaderFactory* GetFactory( RTTIClass* ClassInfo );

		template<typename TClass>
		TClass* GetFactory( )
		{
			return RTTI_CAST(TClass, GetFactory( RTTI_CLASS_INFO( TClass) ) );
		}

		
	private:
		bool mUseShaderCache;
		typedef dynamic_hash<RTTIClass*, ShaderFactory*> ShaderFactoryMap;
		ShaderFactoryMap mShaderFactoryMap;
	};


	extern ShaderMaster* GShaderMaster;

	/** @} */
	/** @} */
}
