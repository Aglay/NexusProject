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
		��Ⱦ����
	*/
	class PresentWindow : public RenderTarget
	{
	public:
		PresentWindow( );

		virtual ~PresentWindow( );

		virtual dword GetWidth( );

		virtual dword GetHeight( );

		virtual void Draw( );

		virtual dword GetPriority( ){ return 0;}

		/** 
			��ȡRHI�豸
		*/
		RHIVideoDevice* GetRHIVideoDevice( ){ return mRHIVideoDevice;}

		/** 
			�������ô�С
		*/
		void Resize( dword Width, dword Height );

		/** 
			ȡ�ô��ھ��
		*/
		handle GetWindowHandle( );

		/// ��������豸
		IInputDriver* GetInputDriver( ){ return mInputDriver; }

	private:
		static void DrawDebugStatus_RenderThread( PresentWindow* RW );

	protected:
		RHIVideoDevice*	mRHIVideoDevice;
		MessageInputDriver* mInputDriver;
	};

	
	/** 
		�ṩ���ھ�����ⲿ���ڻ�����
	*/
	class ExternWindow : public PresentWindow
	{
	protected:
		friend class GameEngine;

		/** 
			���캯��
			@param
				Window ���ھ��
			@param
				IsFullScreen �Ƿ�ȫ��
		*/
		ExternWindow( void* Window, bool IsFullScreen );

		virtual ~ExternWindow( );
	};


	/** 
		�Զ������Ĵ���
		@remark
			���ڸ���RenderTarget��GEngine����,�Զ�ɾ��,���new�˲��ù�
	*/
	class GameWindow : public PresentWindow
					 , public WinFormListener
	{
	public:
		/** 
			���д��ڵ���Ϣѭ��,ֱ�����ڹر�
			@remark
				��GameEngine�������ں�
		*/
		void Go( );

	protected:
		friend class GameEngine;
		GameWindow( const wchar* Title, dword Width, dword Height, bool IsFullScreen , dword IconID  );

		virtual ~GameWindow( );

		virtual void OnMouseUp(int x,int y,eMouseButton button);

		virtual void OnMouseDown(int x,int y,eMouseButton button);

		virtual void OnKeyUp(eKeyButton button);

		virtual void OnKeyDown(eKeyButton button);

		virtual void OnMouseMove(int x,int y,eMouseButton button);

		virtual void OnWindowSizeChanged(Point beforeSize,Point afterSize);

		virtual	void OnWindowStateChanged( );

		virtual bool OnFormClose( );

		virtual void OnMouseWheel(int z ,eMouseButton button);

		bool IsWindowFocus( );

	private:
		WinForm*		mForm;
	};


	/** @} */
	/** @} */
}
