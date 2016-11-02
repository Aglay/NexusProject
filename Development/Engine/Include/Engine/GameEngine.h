#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup System
	*  @{
	*/


	class RHIVideoDevice;
	class FrameSpeedUnit;
	class CameraController;

	class PresentWindow;
	class RenderTarget;
	class RenderTargetableTexture2D;
	class GameWindow;
	class ExternWindow;

	/** 
		�����¼�������
	*/
	class EngineEventListener
	{
	public:
		/// �������֡��ʼ
		virtual void OnEngineFrameBegin( float Elapsed ){ }

		/// �������֡����
		virtual void OnEngineFrameEnd( float Elapsed ){ }
	};

	/** 
		����
		@remark
			���Ϲ���������Ϸ������
	*/
	class GameEngine : public RTTIObject
	{
	public:
		DECLARE_RTTI_CLASS( GameEngine, RTTIObject, ClassFlag_Intrinsic )

		GameEngine( );

		virtual ~GameEngine( );

		/**
			��ʼ������
			@remark
				����Ĭ�������ʼ��,��˱����ڴ�֮�䴴��RHI�豸
		*/ 
		void Initialize( EngineEventListener* Listener );

		/// ֹͣ����, ж����Դ
		void Finalize( );

		/// ��������
		bool Tick( );
		
		/// ��ȡ������־��
		Logger* GetLogger( ){ return mLogger; }
		
		/**
			������Ϸ����
			@param
				Title ����
			@param
				Width ���
			@param
				Height �߶�
			@param
				IsFullScreen �Ƿ�ȫ������
			@param
				IconID ͼ����ԴID
			@return
				��Ϸ����
		*/
		GameWindow* CreateGameWindow( const wchar* Title, dword Width, dword Height, bool IsFullScreen, dword IconID = 0 );

		/**
			������Ϸ����
			@param
				WindowHandle ���ھ��
			@param
				IsFullScreen �Ƿ�ȫ������
			@return
				��Ϸ����
		*/
		ExternWindow* CreateGameWindow( void* WindowHandle, bool IsFullScreen );

		/** 
			������Ϸ����
		*/
		GameWorld* CreateWorld( );

		/** 
			��ȡ��Ϸ����
		*/
		GameWorld* GetWorld( dword Index );

		/// �����¼�������
		void SetEventListener( EngineEventListener* Listener ){ mListener = Listener; }

		/// ���湦�ܰ���ʰȡ
		void CheckEngineShortcut( );

		/// ���¸���RT
		void UpdateRenderTarget( );

		/// ��ȡRT����
		dword GetRenderTargetCount( );

		/// ��ȡRT,��������RT
		RenderTarget* GetRenderTarget( dword Index );

		/// ��ȡ����
		PresentWindow* GetWindow( dword Index );


		static void StaticInitProperty( );

	private:

		void DrawRenderTarget( );

		void ClearRenderTarget( );

		void AttachRenderTarget( RenderTarget* RT );

		void DetachRenderTarget( RenderTarget* RT);

		void SaveConfig( );

		void LoadConfig( );

		void SerializeConfig( PropertySerializer& Ser );

		void ClearWorld( );

		friend class GameWorld;
		void NotifyDestoryCamera(Camera* Cam );

		void OnPropertyUseParallelRendering( bool* Value, bool IsGet );

		void OnPropertyUseAsyncTask( bool* Value, bool IsGet );
		
	public:		
		FrameSpeedUnit*	mFPSUnit;
		
		//Camera mCamera;
		Vector3 mTestPoint;

	private:
		Logger* mLogger;
		
		//////////////////////////////////////////////////////////////////////////
		// ���԰�
		//////////////////////////////////////////////////////////////////////////
		bool mShowGrid;
		bool mUseThreadRendering;
		bool mUseAsyncTask;
		bool mUseShaderCache;


		bool mIsUpdate;		
		EngineEventListener* mListener;

		typedef std::vector<GameWorld*> GameWorldList;
		GameWorldList mGameWorldList;

		// RT����
		typedef std::vector<RenderTarget*> RenderTargetArray;
		RenderTargetArray mRenderTargetArray;

		// RTж��ʱ���ر�Detach��Ĵ��б�ɾ��
		bool mEnableDraw;
	};

	
	extern GameEngine*		GEngine;
	extern dword			GGameThreadID;

	/** @} */
	/** @} */
}
