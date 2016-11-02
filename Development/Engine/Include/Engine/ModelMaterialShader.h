#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Model
	*  @{
	*/


	/** 
		ģ���ò��ʶ���Shader
	*/
	class ModelMaterialVertexShader : public MaterialVertexShader
	{
		DECLARE_RTTI_CLASS( ModelMaterialVertexShader, MaterialVertexShader, ClassFlag_Intrinsic| ClassFlag_Serializable )
		DECLARE_SHADER_METAINFO(ST_VertexShader, L"EngineShader.ModelMaterialVertexShader.SF",L"Main")
	public:

		/**
			����Shader����
			@param
				LocalToScreen Ͷ�����
			@param
				LocalToWorld �������
			@param
				ViewPosition �����λ��
			@param
				WorldToLocal ���������
			@return
				
		*/
		void SetParameter( const Matrix4& LocalToScreen, const Matrix4& LocalToWorld, const Vector3& ViewPosition, const Matrix4& WorldToLocal  );

		/// �����任����
		void SetBoneLocalTransform( const Matrix4* BoneLocalTransform, dword NumBone );

		virtual void Serialize( BinarySerializer& Ser );

	protected:
		/// Ԥ����Shader��
		virtual void PreprocessMacro( MaterialInstance* Instance , ShaderCompilerEnvironment& CompilerEnvironment);

		/// ��ģ�Ͳ��ʲ���
		virtual void BindMaterialParameter(  MaterialInstance* Instance, eShaderType ShaderType, const ShaderParameterMap& ParameterMap );

	private:
		ShaderParameter mTransform;
		ShaderParameter mViewPosition;
		ShaderParameter mLightPosition;
		ShaderParameter mWorldTransform;
		ShaderParameter mBoneLocalTransform;
	};

	/** @} */
	/** @} */	
}
