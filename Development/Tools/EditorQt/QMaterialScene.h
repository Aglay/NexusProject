#pragma once

class QMaterialPanel;
class QMaterialSlot;
class QMaterialNode;
class QMaterialConnection;

/**
	���ʱ༭�Ĺ۲�View
*/
class QMaterialGraphicesView : public QGraphicsView
{
	Q_OBJECT
public:
	QMaterialGraphicesView( QMaterialPanel* Panel );

	QMaterialSlot* GetMouseHoverSlot(){ return mMouseHoverSlot;}

	const QBrush& GetElementBGBrush( ){ return mBrushElementBG; }

protected:
	virtual void wheelEvent(QWheelEvent *event);

	virtual void mouseMoveEvent(QMouseEvent *event);


private:
	void scaleView(qreal scaleFactor);
	
	QMaterialPanel* mPanel;

	QMaterialSlot* mMouseHoverSlot;

	QBrush mBrushElementBG;
};


/**
	���ʱ༭����
*/
class QMaterialScene : public QGraphicsScene
{
	Q_OBJECT
public:

	QMaterialScene( QMaterialPanel* Parent );

	virtual ~QMaterialScene( );

	/**
		�Ϸŵ�QGraphicsItemʱ���µ��ô˺���
	*/
	virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event );


	virtual void dropEvent( QGraphicsSceneDragDropEvent *event );

	/**
		�϶�ʱ,�����϶��¼�
		@remark
			����¼����봦��, ����, ֻ���϶���QGraphicsItem�ϲ���ͼ��仯
	*/
	virtual void dragMoveEvent( QGraphicsSceneDragDropEvent *evt );

	/// ��갴���¼�
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

	/// ����ƶ��¼�
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *evt);

	/// ����ͷ��¼�
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *evt);

	/// �Ҽ��˵�
	virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

	/// ���Ը����/����۽��жϿ�����
	void DisconnectSlot( QMaterialSlot* Slot );

	/// ��һ���ڵ�ӳ����ж������Ͽ�����Ҫ�Լ������ڴ�
	void DetachNode( QMaterialNode* Node );

	/// ����������
	void ConnectSlot( QMaterialSlot* OutputSlot, QMaterialSlot* InputSlot );

	/// ����һ������
	QMaterialConnection* AllocConnection( );

	/// �ͷ�һ���۶�Ӧ������
	void FreeConnection( QMaterialSlot* Slot );

	/// ���½ڵ��Ӧ��
	void UpdateNodeConnections( QMaterialNode* Node );

	/// ��ȡ�ڵ��Ӧ�����Ӷ���
	QList<QMaterialConnection*> GetNodeConnections( QMaterialNode* Node );

	QMaterialNode* CreateNode( RTTIClass* NodeType );

	/// �������ڵ�,���ڵ㲻�ܵ�Cmd����
	void CreateRoot( );

	QMaterialNode* GetRoot( ){ return mRoot;}

	void SaveMaterial( const WString& Name );

	void LoadMaterial( const WString& Name );

private:	
	void FindCoreConnections( MaterialNode* Node, QMap<MaterialNode*, QMaterialNode*>& CoreToQNodeMap );

private Q_SLOTS:

	void OnActionDisconnect( );

	void OnActionDeleteNode( );


private:
	QMaterialPanel* mPanel;

	QList<QMaterialConnection*> mPickedNodeConnections;
	QMaterialNode* mPickedNode;
	QPointF mSavedPos;
	QGraphicsLineItem* mConnectLine;
	QMaterialSlot* mSourceSlot;

	QAction* mActionDisconnect;
	QAction* mActionDeleteNode;

	QMaterialSlot* mSelectedSlot;
	QMaterialNode* mSelectedNode;

	QList<QMaterialConnection*> mConnectionList;
	QList<QMaterialConnection*> mFreeConnectionList;

	QMaterialNode* mRoot;
};
