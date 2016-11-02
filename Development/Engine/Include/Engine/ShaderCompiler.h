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
		Shader������Ӧ��
	*/
	class ShaderParameterMap
	{
	public:
		/** 
			����һ��Shader������Ӧ�ļĴ�����Ϣ
			@param
				ParameterName ��������
			@param
				OutBaseRegisterIndex ���صļĴ�����ʼ����
			@param
				OutNumRegisters ���صı���ռ�õļĴ�������
		*/
		bool FindParameterAllocation(const char* ParameterName,word& OutBaseRegisterIndex,word& OutNumRegisters) const;

		/** 
			D3D�ײ����Shaderʱ��ӵ�����
			@param
				ParameterName ��������
			@param
				OutBaseRegisterIndex �Ĵ�����ʼ����
			@param
				OutNumRegisters ����ռ�õļĴ�������
		*/
		void AddParameterAllocation(const char* ParameterName,word BaseRegisterIndex,word NumRegisters);

	private:
		struct ParameterAllocation
		{
			word BaseRegisterIndex;
			word NumRegisters;
		};
		dynamic_hash<AString,ParameterAllocation> ParameterMap;
	};


	/** 
		Shader����
		@remark
			������һ��Shader�����������
	*/
	class ShaderParameter
	{
	public:
		ShaderParameter( );

		/** 
			��Shader�������в�ѯ��������,���Ĵ��������ڱ�����
			@param
				ParameterMap ������
			@param
				ParameterName ������
		*/
		void Bind(const ShaderParameterMap& ParameterMap,const char* ParameterName );

		/** 
			�Ƿ��Ѿ���
		*/
		bool IsBound() const { return mNumRegisters > 0; }

		/** 
			ȡ�û����Ĵ�������
		*/
		dword GetBaseRegisterIndex() const { return mBaseRegisterIndex; }

		/** 
			��ñ���ռ�õļĴ�����
		*/
		dword GetNumRegisters() const { return mNumRegisters; }

		/// ���������л�����������
		friend BinarySerializer& operator <<( NekoEngine::BinarySerializer& Ser, ShaderParameter& Data )
		{
			Ser << Data.mBaseRegisterIndex
				<< Data.mNumRegisters;

			return Ser;
		}

	private:
		word mBaseRegisterIndex;
		word mNumRegisters;
	};


	/** 
		Shader���뻷��
	*/
	struct ShaderCompilerEnvironment
	{
		// IncludeFileName, FileContent
		typedef dynamic_hash<AString,AString> StringPair;

		/** 
			�����ļ��б�
		*/
		StringPair mIncludeFileMap;

		/** 
			��ӳ��
		*/
		StringPair mMacroDefineMap;
	};

	/** @} */
	/** @} */
}
