#include "EnginePCH.h"
#include "NekoEngine_Material.h"

namespace NekoEngine
{
	IMPLEMENT_RTTI_CLASS( MaterialShaderFactory );

	#define MATERIAL_SHADER_CACHE_FOLDERNAME L"MaterialShaderCache"

	#define MATERIAL_FILE( FileName ) UTEXT("MaterialShaderCache"####UTEXT(FileName))

	#define MATERIAL_SHADER_CACHE_INDEX_FILE MATERIAL_FILE("\\index.toc")

	MaterialShaderFactory::MaterialShaderFactory()
		: mNeedRebuildIndex( 0 )
	{
		// ����ʱ�����ļ���,�����ȡ����
		Directory::Create( MATERIAL_SHADER_CACHE_FOLDERNAME );
	}

	MaterialShaderFactory::~MaterialShaderFactory()
	{
		Clear();
	}


	MaterialShaderCollection MaterialShaderFactory::GetShader( MaterialInstance* Instance , const wchar* MaterialName, RTTIClass* VertexShaderClass )
	{
		MaterialShaderCollection Collection;

		bool NeedCreateVS = false;
		bool NeedCreatePS = false;

		// �ڿ����ҵ�Collection
		MaterialShaderCollection* Result = mMaterialShaderMap.find( MaterialName );
		if ( Result != null )
		{
			Collection = *Result;

			// ���Shader�ļ��Ƿ��и���
			if ( IsShaderOutofTime( Collection.mVertexShader ) )
			{
				// ���ϵ�Shaderɾ��
				DeleteShader_RenderThread( Collection.mVertexShader );
				Collection.mVertexShader = null;
				NeedCreateVS = true;	
			}

			if ( IsShaderOutofTime( Collection.mPixelShader ) )
			{
				DeleteShader_RenderThread( Collection.mPixelShader );
				Collection.mPixelShader = null;
				NeedCreatePS = true;	
			}
		}
		else
		{
			NeedCreateVS = true;
			NeedCreatePS = true;
		}

		// ������
		bool VSCompileOK = false;
		bool PSCompileOK = false;

		if ( NeedCreateVS)
		{
			// ���ݿ������ʹ���VertexShader
			Collection.mVertexShader = RTTI_CAST(MaterialVertexShader, VertexShaderClass->CreateInstance() );

			// ����VertexShader
			ShaderCompilerEnvironment Env;
			VSCompileOK = CompileMaterialShader( Instance, Collection.mVertexShader, Env );
		}

		if ( NeedCreatePS )
		{
			// ���ݸ����Ĳ������ƴ���PixelShader
			Collection.mPixelShader = new MaterialPixelShader;
			ResourceLocation::ModifyType( MaterialName, Collection.mPixelShader->mShaderSource, RFT_ShaderFile );
			Collection.mPixelShader->InitMetaData();

			// ����PixelShader
			ShaderCompilerEnvironment Env;
			PSCompileOK = CompileMaterialShader( Instance, Collection.mPixelShader, Env );
		}


		// ����OK�ſɼ����
		if ( VSCompileOK || PSCompileOK )
		{
			mMaterialShaderMap.set( MaterialName, Collection );
			mNeedRebuildIndex++;

			SerializeMaterialShaderCache( MaterialName, Collection, false );
		}
		

		return Collection;
	}

	void MaterialShaderFactory::Serialize( BinarySerializer& Ser )
	{
		//Ser << mMaterialShaderMap;
		if ( Ser.IsLoading() )
		{
			LoadCache();
		}
		else
		{
			SaveCache();
			RebuildMaterialIndex();
		}
	}



	bool MaterialShaderFactory::SerializeMaterialShaderCache( const wchar* MaterialName, MaterialShaderCollection& Collection, bool IsLoading )
	{
		// ���������ǻ����ļ���
		wchar Buffer[256];
		StringHelper::FormatBuffer( Buffer, 256, L"%s\\%s.cache", MATERIAL_SHADER_CACHE_FOLDERNAME, MaterialName );

		FileStream File( Buffer, IsLoading ? FAM_Read: FAM_Write );

		if ( !File.IsValid() )
			return false;

		BinarySerializer Ser( &File, IsLoading );
		Ser.SerializerFileHeader( FILE_VER_MATERIAL_SHADERCACHE );

		Ser << Collection;

		return true;
	}



	void MaterialShaderFactory::SaveCache( )
	{
		Directory::Create(MATERIAL_SHADER_CACHE_FOLDERNAME);

		dword Index = 0;
		for ( MaterialShaderMap::iterator it(mMaterialShaderMap);it;++it)
		{
			WString& MaterialName = it.get_key();

			MaterialShaderCollection& Collection = it.get_value();

			SerializeMaterialShaderCache( MaterialName.c_str(), Collection, false );
		}


	}

	void MaterialShaderFactory::RebuildMaterialIndex( )
	{
		Directory::Create( MATERIAL_SHADER_CACHE_FOLDERNAME );

		std::vector<WString> MaterialNameArray;

		MaterialNameArray.resize( mMaterialShaderMap.size() );

		dword Index = 0;
		for ( MaterialShaderMap::iterator it(mMaterialShaderMap);it;++it)
		{
			WString& MaterialName = it.get_key();

			MaterialNameArray[Index++] = MaterialName;
		}

		FileStream IndexFile( MATERIAL_SHADER_CACHE_INDEX_FILE, FAM_Write );

		// ���̲���д
		if ( !IndexFile.IsValid() )
			return;

		// ���л���������ͷ
		BinarySerializer Ser( &IndexFile, false );
		Ser.SerializerFileHeader( FILE_VER_MATERIAL_SHADERINDEX );

		Ser << MaterialNameArray;
	}

	void MaterialShaderFactory::LoadCache( )
	{
		FileStream IndexFile( MATERIAL_SHADER_CACHE_INDEX_FILE, FAM_Read );

		// �ļ�������
		if ( !IndexFile.IsValid() )
			return;

		// ���л���������ͷ
		BinarySerializer Ser( &IndexFile, true );
		Ser.SerializerFileHeader( FILE_VER_MATERIAL_SHADERINDEX );

		std::vector<WString> MaterialNameArray;

		Ser << MaterialNameArray;
		
		for ( dword i = 0;i< MaterialNameArray.size();i++)
		{
			MaterialShaderCollection Collection;
			WString& MaterialName = MaterialNameArray[i];
			if ( SerializeMaterialShaderCache(MaterialName.c_str(), Collection, true ) )
			{
				mMaterialShaderMap.set( MaterialName, Collection );
			}
		}
	}

	dword MaterialShaderFactory::Compile()
	{
		return 0;
	}

	bool MaterialShaderFactory::IsShaderOutofTime( MaterialShader* Binder )
	{
		ShaderMetaInfo* MetaInfo = Binder->GetShaderMetaInfo();

		if ( MetaInfo == null )
			return false;

		WString RealPath = ResourceLocation::Resovle( MetaInfo->mSourceFile );

		// �Ƚ��ļ��Ƿ����޸�
		FileTime ThisFileTime;
		if ( File::GetFileModifyTime( RealPath.c_str() , ThisFileTime ) )
		{
			if ( ThisFileTime == Binder->mModifyTime )
				return false;
		}
		else
		{
			return false;
		}

		return true;
	}


	bool MaterialShaderFactory::CompileMaterialShader( MaterialInstance* MatIns , MaterialShader* Binder, ShaderCompilerEnvironment& CompilerEnvironment  )
	{
		ShaderMetaInfo* MetaInfo = Binder->GetShaderMetaInfo();

		if ( MetaInfo == null )
			return false;

		WString RealPath = ResourceLocation::Resovle( MetaInfo->mSourceFile );

		// �Ƚ��ļ��Ƿ����޸�
		FileTime ThisFileTime;
		if ( File::GetFileModifyTime( RealPath.c_str() , ThisFileTime ) )
		{
			Binder->mModifyTime = ThisFileTime;
		}

		
		mLogger->Info( L"Recompile Material Shader file %s ...", RealPath.c_str() );


		// ����Shader��Ϣ����������ṹ
		ShaderCompilerOutput ShaderOutput;

		Binder->PreprocessMacro( MatIns, CompilerEnvironment );

		if ( RHI->CompileShader( RealPath.c_str(), MetaInfo->mEntryName, MetaInfo->mType, CompilerEnvironment, ShaderOutput ) )
		{
			Binder->mShaderRHI = ShaderOutput.mShaderRHI;

			Binder->BindMaterialParameter( MatIns, MetaInfo->mType, ShaderOutput.mParameterMap );
		}
		else
		{
			mLogger->Error( ShaderOutput.mErrors.c_str() );
			return false;
		}

		CompilerEnvironment.mMacroDefineMap.clear();	

		return true;
	}

	void MaterialShaderFactory::Clear()
	{
		for ( MaterialShaderMap::iterator it(mMaterialShaderMap);it;++it)
		{
			MaterialShaderCollection& Collection = it.get_value();

			DeleteShader_RenderThread( Collection.mPixelShader );
			DeleteShader_RenderThread( Collection.mVertexShader );			
		}

		mMaterialShaderMap.clear();
	}

	void MaterialShaderFactory::Tick( float Elapse )
	{
		if ( mNeedRebuildIndex > 0 )
		{
			RebuildMaterialIndex();

			mNeedRebuildIndex = 0;
		}
	}




}