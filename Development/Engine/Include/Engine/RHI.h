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
		��������˽ṹ
	*/
	enum ePrimitiveTopology
	{
		PT_PointList = 1,
		PT_LineList,
		PT_LineStrip,
		PT_TriangleList,
		PT_TriangleStrip,
	};

	/** 
		��Ⱦ���
	*/
	struct RenderStatus 
	{
		dword mNumPrimitives;
		dword mNumVertices;
	};


	/** 
		���ظ�ʽ
	*/
	enum ePixelFormat
	{
		PF_Unknown				= 0,
		PF_R8G8B8               = 20,
		PF_A8R8G8B8             = 21,
		PF_X8R8G8B8             = 22,
		PF_A8L8					= 51,
	};

	/** 
		RHI�������
	*/
	class RHISurfaceBase : public RefObject
	{
	public:
		virtual ~RHISurfaceBase( ){ }

		/** 
			�������Ϊ�ļ�
		*/
		virtual void Save( const wchar* FileName ) = 0;

		/** 
			�������ύΪ��ȾĿ��
		*/
		virtual void CommitAsRenderTarget( dword Index ) = 0;

		/** 
			��ȡ���
		*/
		virtual dword GetWidth( ) = 0;

		/** 
			��ȡ�߶�
		*/
		virtual dword GetHeight( ) = 0;
	};

	/** 
		RHI����
	*/
	class RHISurface : public RHISurfaceBase
	{
	public:
		virtual ~RHISurface( ){ }

		/** 
			������������
			@param
				DestStride ���ؿ��
			@param
				RectToLock ��Ҫ�����ķ�Χ
		*/
		virtual void* Lock( dword& DestStride, Rect* RectToLock ) = 0;

		/** 
			��������
		*/
		virtual void Unlock( ) = 0;
	};

	typedef TRefPtr<RHISurface> RHISurfaceRef;

	/** 
		RHI����
	*/
	class RHITexture : public RHISurfaceBase
	{
	public:
		virtual ~RHITexture( ){ }

		/** 
			�ύ��GPU
		*/
		virtual void Commit( dword SamplerIndex ) = 0;

		/** 
			��������
			@param
				MipIndex �������
			@param
				NeedWriteData ��������Ҫд������
			@param
				DestStride ���ؿ��
			@param
				RectToLock ��Ҫ�����ķ�Χ	
		*/
		virtual void* Lock( dword MipIndex,bool NeedWriteData,dword& DestStride, const Rect* RectToLock = null ) = 0;

		/** 
			��������
		*/
		virtual void Unlock( dword MipIndex ) = 0;
	};

	typedef TRefPtr<RHITexture> RHITextureRef;


	/** 
		RHI�����ʽ
	*/
	class RHIVertexFormat : public RefObject
	{
	public:
		virtual ~RHIVertexFormat( ){ }

		/** 
			�ύ
		*/
		virtual void Commit() = 0;
	};
	typedef TRefPtr<RHIVertexFormat> RHIVertexFormatRef;


	/** 
		RHI���㻺��
	*/
	class RHIVertexBuffer : public RefObject
	{
	public:
		virtual ~RHIVertexBuffer( ){ }

		/** 
			�ύ
			@param
				StreamIndex ������
			@param
				Stride �����С
		*/
		virtual void Commit( dword StreamIndex, dword Stride  ) = 0;

		/** 
			����
			@param
				Offset ƫ��
			@param
				Size ������С
		*/
		virtual void* Lock( dword Offset, dword Size ) = 0;

		/** 
			����
		*/
		virtual void Unlock( ) = 0;

		/** 
			��û����С
		*/
		virtual dword GetSize( ) = 0;
	};

	typedef TRefPtr<RHIVertexBuffer> RHIVertexBufferRef;

	/** 
		RHI��������
	*/
	class RHIIndexBuffer : public RefObject
	{
	public:
		virtual ~RHIIndexBuffer( ){ }

		/** 
			�ύ
			@param
				StreamIndex ������
			@param
				Stride �����С
		*/
		virtual void Commit(  ) = 0;

		/** 
			����
			@param
				Offset ƫ��
			@param
				Size ������С
		*/
		virtual void* Lock( dword Offset, dword Size ) = 0;

		/** 
			����
		*/
		virtual void Unlock( ) = 0;

		/** 
			��û����С
		*/
		virtual dword GetSize( ) = 0;
	};

	typedef TRefPtr<RHIIndexBuffer> RHIIndexBufferRef;

	/** 
		RHI��Ⱦ״̬
	*/
	class RHIRenderState : public RefObject 
	{
	public:
		/** 
			�ύ
		*/
		virtual void Commit( ) = 0;
	};

	/** 
		RHI������״̬
	*/
	class RHISamplerState: public RHIRenderState
	{
	public:
		virtual void Commit( dword SamplerIndex ) = 0;
	};
	typedef TRefPtr<RHISamplerState> RHISamplerStateRef;

	/** 
		RHI��դ��״̬
	*/
	class RHIRasterizerState: public RHIRenderState{};
	typedef TRefPtr<RHIRasterizerState> RHIRasterizerStateRef;

	/** 
		RHI���״̬
	*/
	class RHIDepthState: public RHIRenderState {};
	typedef TRefPtr<RHIDepthState> RHIDepthStateRef;

	/** 
		RHIģ��״̬
	*/
	class RHIStencilState: public RHIRenderState{};
	typedef TRefPtr<RHIStencilState> RHIStencilStateRef;

	/** 
		RHI���״̬
	*/
	class RHIBlendState : public RHIRenderState{};
	typedef TRefPtr<RHIBlendState> RHIBlendStateRef;


	/** 
		Shader����
	*/
	enum eShaderType
	{
		ST_VertexShader,
		ST_PixelShader,
		ST_Max,
	};

	class RenderTexture;

	/** 
		RHI��Ƶ�豸
	*/
	class RHIVideoDevice 
	{
	public:
		/// �ͷ�
		virtual void Release( ) = 0;

		/// ��ȡ���ھ��
		virtual handle GetWindowHandle() = 0;

		/// ���ڿ��
		virtual dword GetWidth( ) = 0;

		/// ���ڸ߶�
		virtual dword GetHeight( ) = 0;

		/// �����޸Ĵ�С
		virtual void Resize( dword Width, dword Height, bool bInIsFullscreen, void* NewWindowHandle = null ) = 0;		

		/// ���Ƶ���Ļ
		virtual void Present( ) = 0;

		/// �����豸
		virtual void UpdateDevice( ) = 0;
	};

	
	/** 
		RHI Shader
	*/
	class RHIShader : public RefObject
	{
	public:
		virtual ~RHIShader( ){ }

		/** 
			�ύ
			@remark
				��������Ⱦ�̵߳���
		*/
		virtual void Commit() = 0;

		/** 
			����Shader����
			@param
				Parameter �����мĴ�����������
			@param
				NewValue ����ָ��
			@param
				NumVector4 �ж��ٸ�Vector4
		*/
		virtual void SetContantParameter( const ShaderParameter& Parameter, const float* NewValue, dword NumVector4 ) = 0;

		/** 
			��ȡShader����
		*/
		eShaderType GetType( ){ return mShaderType; }

		/// ģ���Զ�ƥ������Shader����
		template<class TParameterType>
		void SetContantParameter( const ShaderParameter& Parameter, const TParameterType& Value )
		{
			if ( Parameter.IsBound() )
			{
				enum { RegisterSize = sizeof(float) * 4 };
				enum { NumRegistersPerElement = (sizeof(TParameterType) + RegisterSize - 1) / RegisterSize };
				Assert(NumRegistersPerElement <= Parameter.GetNumRegisters());

				SetContantParameter( Parameter, (float*)&Value, NumRegistersPerElement );
			}
		}

		/** 
			��������������
			@param
				Parameter �����мĴ�����������
			@param
				NewSamplerState ������״̬
			@param
				NewTexture ����
		*/
		virtual void SetTextureParameter( const ShaderParameter& Parameter, RHISamplerState* NewSamplerState, RHITexture* NewTexture ) = 0;

		/** 
			��������
			@param
				Parameter �����мĴ�����������
			@param
				NewTexture ����
			@remark
				û������ʱʹ�ð�������Ӧ������
		*/
		virtual void SetTextureParameter( const ShaderParameter& Parameter, RenderTexture* NewTexture );

		/** 
			�����Ĵ���ָ��
		*/
		virtual _byte* GetCodePointer( );

		/** 
			�����Ĵ����С
		*/
		virtual dword GetCodeSize( );

	protected:
		eShaderType			mShaderType;

		typedef std::vector<_byte> ShaderCodeBuffer;
		ShaderCodeBuffer	mCodeBuffer;
	};


	typedef TRefPtr<RHIShader> RHIShaderRef;

	/** 
		Shader�������
	*/
	struct ShaderCompilerOutput
	{
		/// ���ƶ�Ӧ�Ĵ���
		ShaderParameterMap	mParameterMap;

		/// �����з����Ĵ���
		WString				mErrors;

		/// ��������ɵ�Shader����
		RHIShaderRef		mShaderRHI;
	};


	class TextureMipMap;

	extern RenderStatus GRenderStatus;

	/** 
		��ȾӲ������ӿ�
		@remark
			���½ӿڱ��뱣֤ʼ������Ⱦ�߳�ʹ��
	*/
	class IRenderHardware
	{
	public:
		/** 
			����һ��Ӳ����Ƶ�豸
			@param
				window ���ھ��
			@param
				Width,Height ���ڳߴ�
			@param
				isfullscn �Ƿ�ȫ��
			@return
				�����õ���Ƶ�豸���
		*/
		virtual RHIVideoDevice*			CreateVideoDevice( void* window, dword Width, dword Height, bool isfullscn ) = 0;

		/** 
			���Ƶ����������,û�д����ι�ϵ
		*/
		virtual void					DrawDebugText(int x, int y, dword color,const wchar* format,...) = 0;

		/** 
			����ǰ����Ŀ��
			@param
				bClearColor �Ƿ�ʹ�������ɫ
			@param
				c �����ɫ
			@param
				bClearDepth �Ƿ������Ȼ���
			@param
				Depth ���
			@param
				bClearStencil �Ƿ�����ģ�建��
			@param
				Stencil ģ��
		*/
		virtual void					Clear(	bool bClearColor,
												dword c,
												bool bClearDepth,
												float Depth,
												bool bClearStencil,
												dword Stencil) = 0;

		/** 
			���ݵ�ǰ���õĶ��㻺��,����ͼԪ
			@param
				PrimitiveType ͼԪ��������
			@param
				IndexBuffer ��������,����Ϊ��
			@param
				NumVertices ������
		*/
		virtual void					Draw(	ePrimitiveTopology PrimitiveType, 
												RHIIndexBuffer* IndexBuffer, 
												dword NumVertices ) = 0;

		/** 
			ʹ�ô��������û��������ͼԪ����
			@param
				PrimitiveType ͼԪ��������
			@param
				NumPrimitives �������
			@param
				NumVertices ������
			@param
				UserVertexStream �û����㻺���ڴ�
			@param
				VertexStreamStride �û����㻺�嶥���С
			@param
				UserIndexBuffer �û���������
			@param
				IndexStreamStride ����������
		*/
		virtual void					DrawIndexedUserBuffer(  ePrimitiveTopology PrimitiveType, 
																dword NumPrimitives, 
																dword NumVertices, 
																const void* UserVertexStream, 
																dword VertexStreamStride, 
																const void* UserIndexBuffer, 
																dword IndexStreamStride ) = 0;

		/** 
			ʹ���û��������ͼԪ����
			@param
				PrimitiveType ͼԪ��������
			@param
				NumPrimitives �������
			@param
				UserVertexStream �û����㻺���ڴ�
			@param
				VertexStreamStride �û����㻺�嶥���С
		*/
		virtual void					DrawUserBuffer( ePrimitiveTopology PrimitiveType,
														dword NumPrimitives, 
														const void* UserVertexStream, 
														dword VertexStreamStride ) = 0;

		/** 
			����2D����
			@param
				SizeX,SizeY ����ߴ�
			@param
				MipCount ���
			@param
				Format ��ʽ
			@return
				�����õ�����
		*/
		virtual RHITextureRef			CreateTexture2D( dword SizeX, dword SizeY, dword MipCount, ePixelFormat Format) = 0;

		/** 
			���������ʽ����
			@param
				Parameter ��������
			@return
				�����õĶ����ʽ
		*/
		virtual RHIVertexFormatRef		CreateVertexFormat( const VertexFormat& Parameter ) = 0;


		/** 
			�������㻺��
			@param
				Size �����С
			@param
				IsDynamic �Ƿ�̬
			@return
				�����õĶ��㻺��
		*/
		virtual RHIVertexBufferRef		CreateVertexBuffer(dword Size,bool IsDynamic) = 0;

		/** 
			������������
			@param
				Size �����С
			@param
				Stride ��ȴ�С(ʹ��sizeof(word)����dword)
			@param
				IsDynamic �Ƿ�̬
			@return
				�����õ���������
		*/
		virtual RHIIndexBufferRef		CreateIndexBuffer(dword Size,dword Stride, bool IsDynamic) = 0;

		/// ������դ��״̬
		virtual RHIRasterizerStateRef	CreateRasterizerState(const RasterizerStateInitializer& Initializer) = 0;

		/// �������״̬
		virtual RHIDepthStateRef		CreateDepthState(const DepthStateInitializer& Initializer) = 0;

		/// ����ģ��״̬
		virtual RHIStencilStateRef		CreateStencilState(const StencilStateInitializer& Initializer) = 0;

		/// �������״̬
		virtual RHIBlendStateRef		CreateBlendState(const BlendStateInitializer& Initializer) = 0;

		/// ����������״̬
		virtual RHISamplerStateRef		CreateSamplerState(const SamplerStateInitializer& Initializer) = 0;

		/** 
			����ShaderԴ��
			@param
				SourceFile Դ�ļ�λ��
			@param
				EntryName ��ں�����
			@param
				ShaderType ����
			@param
				Environment ����ʱʹ�õĺ�
			@param
				CompileOutput �������
			@return
				�����Ƿ�ɹ�
			@remark
				��������Ⱦ�̵߳���
		*/
		virtual bool					CompileShader(  const wchar* SourceFile, 
														const wchar* EntryName,	
														eShaderType ShaderType,	
														ShaderCompilerEnvironment& Environment,	
														ShaderCompilerOutput& CompileOutput ) = 0;

		/** 
			�ӱ���õ�Shader���崴��Shader����
			@param
				ShaderType ����
			@param
				Code ���뻺��
			@param
				CodeSize �����С
			@return
				�����õ�Shader����
			@remark
				��������Ⱦ�̵߳���
		*/
		virtual RHIShaderRef			CreateShader( eShaderType ShaderType, void* Code, dword CodeSize ) = 0;

		/** 
			������Shader����
		*/
		virtual AString					DisassembleCode( void* Code ) = 0;

		/** 
			���û�������,ͬSetViewport
		*/
		virtual void					SetDrawArea( dword X, dword Y, dword Width, dword Height ) = 0;

		/** 
			����������ΪĿ�������
			@param
				SizeX,SizeY ����ߴ�
			@param
				Format ��ʽ
			@return
				�����õ�����
		*/
		virtual RHITextureRef			CreateTargetableTexture2D( dword SizeX, dword SizeY, ePixelFormat Format) = 0;

		/** 
			������ָ����Ŀ��������Ϊ�󱸻���
			@param
				Index ��ȾĿ������
		*/
		virtual void					RestoreRenderTarget( dword Index ) = 0;

		/// ��ʼ����
		virtual void					BeginDraw( ) = 0;

		/// ��������
		virtual void					EndDraw( ) = 0;

		/** 
			������ȾĿ�����
			@remark
				����������
		*/
		virtual void*					LockRenderTargetSurface( dword& DestStride, Rect* RectToLock = null ) = 0;

		/// ��������
		virtual void					UnlockRenderTargetSurface( ) = 0;

		virtual RHISurfaceRef			CreateTargetableSurface( dword SizeX, dword SizeY, ePixelFormat Format, bool Readable ) = 0;

		virtual dword					GetBitsPerPixel( ePixelFormat Format ) = 0;
	};

	/// RHI���ʼ��
	extern void RHIInitialize( );

	/// RHI������
	extern void RHIFinalize( );

	extern IRenderHardware* RHI;

	/** 
		DDS�����ļ�����
	*/
	struct DDSTextureParameter 
	{
		dword			mSizeX;
		dword			mSizeY;
		ePixelFormat	mPixelFormat;

		DDSTextureParameter( )
			: mSizeX( 0 )
			, mSizeY( 0 )
			, mPixelFormat( PF_Unknown )
		{

		}
	};

	/** 
		����һ��DDS�ļ�������
		@param
			FileName �ļ���
		@param
			MipData ����
		@param
			Parameter ��ȡ��Ĳ���
		@return
			�Ƿ��ȡ�ɹ�
	*/
	extern bool	DDSCodec_Load( const wchar* FileName, TextureMipMap& MipData, DDSTextureParameter& Parameter );

	/** 
		��DataStream����DDS������
		@param
			Stream ��
		@param
			MipData ����
		@param
			Parameter ��ȡ��Ĳ���
		@return
			�Ƿ��ȡ�ɹ�
	*/
	extern bool DDSCodec_Load( DataStream* Stream, TextureMipMap& MipData, DDSTextureParameter& Parameter );

	/** @} */
	/** @} */
}
