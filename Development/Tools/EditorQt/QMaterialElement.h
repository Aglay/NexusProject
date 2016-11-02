#pragma once

class QMaterialGraphicesView;
class QMaterialSlot;
class QMaterialConnection;
class QMaterialNode;
class QMaterialPanel;


/*
	��νṹ
	QMaterialNodeGroup	<-����QMaterialScene��
		QMaterialNode	��Group����,ͨ��group���Group����
		QMaterialSlot	��Node�������

	QMaterialConnection <-����QMaterialScene��

*/


/**
	���ʽڵ��װ��
*/
class QMaterialNodeGroup : public QGraphicsItemGroup
{
public:
	QMaterialNodeGroup( QMaterialNode* Node )
		: mNode( Node )
	{

	}

	QMaterialNode* GetNode( ){ return mNode; }

private:
	QMaterialNode* mNode;
};

/**
	���ʽڵ������ľ��ο�
*/
class QMaterialNode : public QGraphicsItem
{

public:
	enum ElementSize
	{
		NodeWidth = 100,
		NameHeight = 15,
		NameWidthMargin = 10,

		SlotGap = 5,		
	};

	QMaterialNode( RTTIClass* NodeClass, QMaterialGraphicesView* View  );

	virtual ~QMaterialNode();

	void InitializeMembers( QGraphicsScene* Scene );

	/// ��Node��Groupɾ����Ȼ��ɾ��Groupʱ���Զ�ɾ��Node
	void ReleaseMembers( QGraphicsScene* Scene );

	const QRectF& GetLogicBound( ){ return mLogicBound; }

	/// ��ȡ�����
	QMaterialSlot* GetOutputSlot( ){ return mOutputSlot; }

	/// ��ȡ����ۼ���
	QList<QMaterialSlot*>& GetInputSlots( ){ return mInputSlots; }

	RTTIClass* GetMataerialNodeClass( ){ return mCoreNode->GetClass(); }

	/// ͨ�����ƻ�ò�
	QMaterialSlot* GetSlotByName( const QString& Name );

	dword mIDForSave;

protected:
	virtual QRectF boundingRect() const;

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	



private:
	QString mName;

	QMaterialGraphicesView* mView;

	QRectF mLogicBound;

	QRectF mSafeBound;

	QMaterialSlot* mOutputSlot;
	
	MaterialNode* mCoreNode;			

	QGraphicsItemGroup* mGroupItem;

	QList<QMaterialSlot*> mInputSlots;

};


typedef QList<QMaterialNode*> QMaterialNodeList;

/**
	���ʲ��
*/
class QMaterialSlot : public QGraphicsItem
{

public:
	enum ElementSize
	{
		SlotWidth = 15,

		SlotHeight = 15,
	};

	QMaterialSlot( QMaterialGraphicesView* View,  QMaterialNode* Parent, const QString& Name );

	/// �Ƿ�Ϊ����ڵ�
	bool IsOutputSlot( ){ return mParent->GetOutputSlot() == this; }

	/// ��Ӳ۶Բ�����
	void AddSlotConnection( QMaterialSlot* Slot );

	/// ɾ���۶Բ�����
	void RemoveSlotConnection( QMaterialSlot* Slot );

	/// ��ȡ�����ڵ�
	QMaterialNode* GetMaterialNode( ){ return mParent; }

	/// ��ò۵����Ӳۼ���
	QList<QMaterialSlot*>& GetSlotConnections( ) { return mSlotConnection;}

	QMaterialSlot* GetOneSlotConnection( );

	/// ��ȡ����
	QString GetName( ){ return mName; }

public:
	virtual QRectF boundingRect() const;

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);	
	

private:
	QString mName;

	QMaterialGraphicesView* mView;

	QMaterialNode* mParent;

	QRectF mBound;

	QList<QMaterialSlot*> mSlotConnection;	
};

/**
	��������
*/
class QMaterialConnection : public QGraphicsLineItem
{
public:
	enum ElementSize
	{
		SlotWidth = 15,

		SlotHeight = 15,
	};

	QMaterialConnection(  QMaterialGraphicesView* View );

	/// �����������ӵ����˲�
	void Reset( QMaterialSlot* OutputSlot, QMaterialSlot* InputSlot );

	/// ��������
	void UpdateGraphics( );

	/// ��ȡ�����
	QMaterialSlot* GetOutputSlot( ){return mOutputSlot; }

	/// ��ȡ�����
	QMaterialSlot* GetInputSlot( ){return mInputSlot; }

	/// ��������Ƿ��Node���
	bool IsRelateTo( QMaterialNode* Node );

private:
	QMaterialGraphicesView* mView;

	QMaterialSlot* mOutputSlot;
	QMaterialSlot* mInputSlot;

	QPointF mOutputPoint;
	QPointF mInputPoint;

	QRectF mBound;	

	QList<QMaterialNode*> mNodes;
};

