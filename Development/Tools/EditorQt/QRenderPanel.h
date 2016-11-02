#pragma once



/**
	��Ҫʹ��������Ⱦ����Ĵ��ڻ���
*/
class QRenderPanel : public QWidget
{
	Q_OBJECT
public:
	QRenderPanel( QWidget* Parent = NULL );

	virtual ~QRenderPanel();

	virtual void Initialize( RTTIClass* CameraControllerType );

	PresentWindow* GetRenderWindow( );

	GameWorld* GetWorld( ){ return mWorld;}

	void NotifyMouseEvent( QMouseEvent *evt, eMessageKeyState MKS );

protected:
	virtual void resizeEvent(QResizeEvent* evt);

	virtual QPaintEngine* paintEngine() const{ return NULL;}

	virtual void mouseMoveEvent(QMouseEvent *evt);

	virtual void mousePressEvent(QMouseEvent *evt);

	virtual void wheelEvent(QWheelEvent *evt);

	virtual bool event(QEvent *evt);

	virtual void focusOutEvent(QFocusEvent *);

public Q_SLOTS:

protected:
	PresentWindow*		mRenderWindow;
	MessageInputDriver* mInputDriver;
	CameraActor*		mCameraActor;
	GameWorld*			mWorld;
};