#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Render
	*  @{
	*/

	/// ���ģʽ
	enum eBlendMode
	{
		BLEND_Opaque            =0,		///< ��͸��
		BLEND_Masked            =1,		///< �ɰ�
		BLEND_Translucent       =2,		///< ͸��
		BLEND_Additive          =3,		///< ����
		BLEND_Modulate          =4,		///< ���
		BLEND_MAX               =5,
	};

	/** 
		Element�Ķ��㴦��
	*/
	class ElementVertexShader : public RenderShader
	{
		DECLARE_RTTI_CLASS( ElementVertexShader, RenderShader, ClassFlag_Intrinsic| ClassFlag_Serializable )
		DECLARE_SHADER_METAINFO(ST_VertexShader, L"EngineShader.SimpleElementVertexShader.SF",L"Main")

	public:

		virtual void BindShaderParameter( eShaderType ShaderType, const ShaderParameterMap& ParameterMap );

		void SetParameter( const Matrix4& mat );

		virtual void Serialize( BinarySerializer& Ser );

	private:
		ShaderParameter mTransform;
	};

	/** 
		Element�����ش���
	*/
	class ElementPixelShader : public RenderShader
	{
		DECLARE_RTTI_CLASS( ElementPixelShader, RenderShader, ClassFlag_Intrinsic| ClassFlag_Serializable )
		DECLARE_SHADER_METAINFO(ST_PixelShader, L"EngineShader.SimpleElementPixelShader.SF",L"Main")

	public:

		virtual void BindShaderParameter( eShaderType ShaderType, const ShaderParameterMap& ParameterMap );

		void SetTexture( RenderTexture* NewTexture );

		virtual void Serialize( BinarySerializer& Ser );

	private:
		ShaderParameter mTexture;
	};


	/** 
		����Ԫ�ش�����
		@remark
			����ּ�ںϲ�DrawCall,���ٶ����ύ����.��Ҫ��������Ⱦ�߳�
	*/
	class BatchedElements 
	{
	public:
		BatchedElements( );

		/** 
			���һ��3D��
			@param
				P1 ����1
			@param
				P2 ����2
			@param
				C ��ɫ
		*/
		void AddLine( const Vector3& P1, const Vector3& P2, const Color& C );

		/** 
			���һ��3D��,ͨ��Ӳ����C1��C2��ɫ���ֵ
			@param
				P1 ����1
			@param
				P2 ����2
			@param
				C1 ��ɫ1
			@param
				C2 ��ɫ2
		*/
		void AddLine( const Vector3& P1, const Vector3& P2, const Color& C1, const Color& C2 );

		/** 
			���һ������ζ���
			@param
				Pos ����λ��
			@param
				UV �����UV
			@param
				C ������ɫ
			@return
				���ض�������
		*/
		int AddTriangleVertex( const Vector3& Pos,const Vector2& UV , const Color& C );

		/** 
			���һ������ζ�������
			@param
				V0,V1,V2 3��������
			@param
				TextureRes ����
			@param
				BlendMode ���ģʽ
		*/
		void AddTriangleIndex( int V0, int V1, int V2, RenderTexture* TextureRes, eBlendMode BlendMode );

		/** 
			���ƻ����и���ͼԪ
			@param
				Transform �任
		*/
		void Draw( Matrix4& Transform );

		static void StaticInit( );
	private:
		struct SimpleElementVertex	
		{
			Vector3 mPosition;
			Vector2 mTextureCoordinate;
			dword	mColor;
			SimpleElementVertex( )
			{

			}

			SimpleElementVertex( const Vector3& Pos, dword C )
				: mPosition( Pos )
				, mColor( C )
			{

			}

			SimpleElementVertex( const Vector3& Pos, const Vector2& UV, dword C )
				: mPosition( Pos )
				, mTextureCoordinate( UV )
				, mColor( C )
			{

			}
		};

		struct BatchedMeshElement
		{
			int mMinVertex;
			
			int mMaxVertex;
			
			typedef growable_buffer<int,8> IndexBuffer;
			IndexBuffer mIndexData;

			RenderTexture* mTexture;
			eBlendMode mBlendMode;
		};

		// Line
		typedef growable_buffer<SimpleElementVertex,100> BatchedLineBuffer;
		BatchedLineBuffer mBatchedLineBuffer;	

		// Mesh
		typedef growable_buffer<SimpleElementVertex,100> BatchedMeshVertexBuffer;
		BatchedMeshVertexBuffer mBatchedMeshVertexBuffer;	

		typedef growable_buffer<BatchedMeshElement,100> BatchedMeshIndexBuffer;
		BatchedMeshIndexBuffer mBatchedMeshIndexBuffer;	

	};

	/** @} */
	/** @} */
}
