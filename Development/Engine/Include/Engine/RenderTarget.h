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
		SceneView����������
	*/
	class SceneViewListener
	{
	public:
		/** 
			SceneView����֮ǰ
		*/
		virtual void PreSceneViewDraw( SceneView* RV ){}

		/** 
			SceneView ����֮��
		*/
		virtual void PostSceneViewDraw( SceneView* RV ){}
	};

	/** 
		��ȾĿ�����
	*/
	class RenderTarget
	{
	public:
		RenderTarget( );

		virtual ~RenderTarget( );

		/** 
			�����ȾĿ����
		*/
		virtual dword GetWidth( ) = 0;

		/** 
			�����ȾĿ��߶�
		*/
		virtual dword GetHeight( ) = 0;

		/** 
			��Ⱦ���ȶ�
			@remark
				�������Ǳ���Ļ�Ȼ���
		*/
		virtual dword GetPriority( ) = 0;

		/** 
			��ȾĿ��Ļ��Ʋ���
		*/
		virtual void Draw( ) = 0;

		// �����ΪSceneManager�����ģ�Ӧ����CameraActor������ʵ�壬�ɱ���Ⱦ����

		/** 
			����ȾĿ�������һ��SceneView,����ʵ�ַ���
			@param
				World ������SceneView����������
			@param
				Cam	������SceneView�����������
			@param
				ZOrder ������View�Ļ����Ⱥ��ϵ
			@param
				Left,Top,Right,Bottom SceneView����Ļ�ϵ����λ��,������Χ(0~1)
		*/
		virtual SceneView* AddSceneView( GameWorld* World, Camera* Cam, dword ZOrder = 0, float Left = 0.0f, float Top = 0.0f, float Width = 1.0f, float Height = 1.0f );

		/// ��ȡÿ��View
		SceneView* GetView( dword Index );

		/// ������е�View
		void ClearView();

		/// RenderTarget��Size�б仯ʱ�����������������View�Ĵ�С
		void UpdateViewDimension( );

		/// ����ÿ��View���µ�֪ͨ
		void AddListener( SceneViewListener* Listener );

		/// ȡ��Ŀ�������ɫ
		dword GetClearColor( ){ return mClearColor; }

		/// ����Ŀ�������ɫ
		void SetClearColor( const Color& C ){ mClearColor = C; }

		/// �Ƿ�������
		void SetEnableDraw( bool EnableDraw ) { mEnableDraw = EnableDraw; }

		/// ����Ƿ�������
		bool GetEnableDraw( ){ return mEnableDraw; }

	private:
		friend class GameEngine;

		void NotifyDestoryCamera(Camera* Cam );

	protected:
		// ����Viewport
		void DrawSceneView( );

	private:
		typedef std::map<dword, SceneView*, std::less<dword> > ViewMap;
		ViewMap mViewMap;

	protected:
		SceneViewListener* mListener;
		dword				mClearColor;
		bool				mEnableDraw;
	};

	/** 
		������ȾĿ�����Դ����
	*/
	class RenderTargetableResource : public RenderTarget
	{
	public:
		RenderTargetableResource( );

		virtual ~RenderTargetableResource( );

		virtual dword GetWidth( );

		virtual dword GetHeight( );

		virtual void Draw();

		virtual bool IsResourceReady( ) = 0;

		virtual void InitDynamicRHI();

		virtual RHISurfaceBase* GetSurfaceBase( ) = 0;

		virtual dword GetPriority( ){ return 1;}

		/** 
			��������
			
		*/
		void SetScaleSize( SceneView* View , float ScaleX = 1.0f, float ScaleY = 1.0f);

		void SetSize( dword Width, dword Height );

	protected:
		dword mWidth, mHeight;

		SceneView* mView;
		float mScaleX;
		float mScaleY;
	};

	class RenderTargetableTexture2D : public RenderTexture
									, public RenderTargetableResource
	{
	public:
		virtual ~RenderTargetableTexture2D( ){ }

	public:
		// �ر�Ĭ�ϵĳ�ʼ��
		virtual void InitRHI( ){ }

		// �ر�Ĭ�ϵ�����
		virtual void ReleaseRHI(){ }

		// ��̬��Դ�Ĵ���
		virtual void InitDynamicRHI();

		virtual void ReleaseDynamicRHI();


		virtual bool IsResourceReady( );

		virtual RHISurfaceBase* GetSurfaceBase( );
	
	};

	class RenderTargetableSurface : public RenderResource
								  , public RenderTargetableResource
	{
	public:
		virtual ~RenderTargetableSurface( ){ }

	public:
		// �ر�Ĭ�ϵĳ�ʼ��
		virtual void InitRHI( ){ }

		// �ر�Ĭ�ϵ�����
		virtual void ReleaseRHI(){ }

		// ��̬��Դ�Ĵ���
		virtual void InitDynamicRHI();

		virtual void ReleaseDynamicRHI();


		virtual bool IsResourceReady( );

		virtual RHISurfaceBase* GetSurfaceBase( );

		virtual void BeginReleaseResource();

		bool ReadyForDestory( );
		
	public:
		RHISurfaceRef mRHISurface;
		RenderCommandFence	mReleaseFence;// ��������ͬ����
	};

	/** @} */
	/** @} */
}
