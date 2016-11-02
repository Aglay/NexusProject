#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup System
	*  @{
	*/

	enum eMessageKeyState
	{
		MKS_None,
		MKS_Down,
		MKS_Up,
	};

	/** 
		ģ��DirectInput��Windows��Ϣӳ��
	*/
	class MessageInputDriver : public IInputDriver
	{
	public:
		/**
			���캯��
			@param
				window ���ھ��
		*/
		MessageInputDriver( handle window );

		virtual void		Tick( float elapse );

		/// �Ƿ�����갴������
		virtual bool		IsMouseDown(eMouseButton Button);

		/// �Ƿ��м��̰�������
		virtual bool		IsKeyDown(eKeyButton Button);

		/// �Ƿ�����갴������
		virtual bool		IsMouseUp(eMouseButton Button);

		/// �Ƿ��м��̰�������
		virtual bool		IsKeyUp(eKeyButton Button);

		/// ��ȡ���ƫ��
		virtual Point		GetMouseOffset( );

		/// ��ȡ������
		virtual int			GetMouseScroller( );

		/// ��ȡ����
		virtual Point		GetMousePoint( );

		/// ע�밴��״̬
		void NotifyKeyState( eKeyButton Button , eMessageKeyState State );

		/// ע�����λ����Ϣ
		void NotifyMousePos( const Point& Pos );

		/// ע�����̧����Ϣ
		void NotifyMouseState( eMouseButton Button, eMessageKeyState State );


		/// ע����������Ϣ
		void NotifyMouseScroll( int Deta );

		/// �����Ƿ��ڴ��ڼ���ʱ�Ż�ȡ��Ϣ
		void SetReceiveOnActive( bool Enable ){ mReceiveOnActive = Enable; }
		
		/// ��ȡ�Ƿ��ڴ��ڼ���ʱ�Ż�ȡ��Ϣ
		bool GetReceiveOnActive( ){ return mReceiveOnActive;}

		/// ������
		void Cleanup( bool Force );

	private:
		Point mLastMousePt;
		enum{ MAX_VIRUTAL_KEY = 0xFF };
		eMessageKeyState	mKeyState[MAX_VIRUTAL_KEY];// ���ﲻʹ��WM_KEYDOWN��¼�������ظ�����Ч������
		eMessageKeyState	mMouseState[3];
		Point			mMousePos;
		int				mMouseScroll;
		handle			mWindowHandle;

		bool			mReceiveOnActive;
	};

	/** @} */
	/** @} */
}
