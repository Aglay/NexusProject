#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Render
	*  @{
	*/

	class RenderTarget;
	class RenderTargetableSurface;
	class SceneViewListener;

	/** 
		��Ⱦ��ͼ
	*/
	class SceneView
	{
	public:
		/** 
			���캯��,ֻ����RenderTarget����
			@param
				World ������SceneView����������
			@param
				Owner ��ȾĿ��
			@param
				Cam	������SceneView�����������
			@param
				ZOrder ������View�Ļ����Ⱥ��ϵ
			@param
				Left,Top,Right,Bottom SceneView����Ļ�ϵ����λ��,������Χ(0~1)
		*/
		SceneView( GameWorld* World, RenderTarget* Owner, Camera* Cam, dword ZOrder = 0, float Left = 0.0f, float Top = 0.0f, float Width = 1.0f, float Height = 1.0f );

		/** 
			��ùҽӵ������
		*/
		Camera* GetCamera( ){ return mCamera; }

		/** 
			�趨�󶨵������
		*/
		void SetCamera( Camera* Cam ){ mCamera = Cam ;}

		/// ��VPΪ��ͼ���򣬸������������֪ͨWorld��ʼ����
		void Draw( SceneViewListener* Listener );

		/// ����View��RT�ı���
		void SetDimension( float Left = 0.0f, float Top = 0.0f, float Width = 1.0f, float Height = 1.0f );

		/// VP������
		const Viewport& GetViewport( ) const{ return mViewport; }

		/// ��ȡ���View������RT
		RenderTarget* GetRenderTarget( ){ return mOwner;}

		/// ZԽС��Խ�Ȼ���
		dword GetZOrder( ){ return mZOrder; }

		/// �󶨺��Ƿ�����׶�ڿɼ�
		bool IsInFrustum( const AABB& BoundingBox );

		/// ���
		dword GetWidth( ){ return mViewport.Width; }

		/// �߶�
		dword GetHeight( ){ return mViewport.Height; }
		
		/// ��ʼ��ѯView�ϵ����ص�,����Ч������,�Ѿ��ϳ�
		void StartQueryPixel( int X, int Y );

		/// ��ȡ���ص���ɫ
		bool GetPixel( dword& ColorResult, bool Wait /*= true */ );

		/// ��Ļ����
		Ray CreateRay( int X, int Y );

		/// ��Ļ���λ��(����������Ͻ�Ϊ0)
		Ray CreateRay( const Vector2& ScreenPos );

		/** 
			���View�ϵĻ���
			@return
				�����ڻ�����ʱ,�����ؿ�
		*/
		Canvas* GetCanvas( ){ return mCanvas;}

	private:
		friend class RenderTarget;
		
		// ���±�����Viewport
		void UpdateDimension( );
		
	protected:
		RenderTarget*	mOwner;
		Viewport		mViewport;
		dword			mZOrder;
		float			mRelativeLeft;
		float			mRelativeTop;
		float			mRelativeWidth;
		float			mRelativeHeight;
		Camera*			mCamera;
		Frustum			mFrustum;
		GameWorld*		mWorld;
		Canvas*			mCanvas;

	private:
		// HitProxy
		RenderTargetableSurface*	mHitProxyRT;
		struct QueryPixelParameter
		{
			int				X, Y;			
			SceneView* ClassPtr;
		};


		static void QueryPixel_RenderThread( QueryPixelParameter& Parameter );
		

	public:		

		volatile dword mColorQueryResult;
		volatile dword mNumPendingFences;
	};


	/** @} */
	/** @} */	
}


