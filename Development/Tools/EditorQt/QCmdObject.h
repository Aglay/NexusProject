#pragma once



class CmdActorAdd : public CmdBase
{
public:
	/// ���洴����Actor,������Undoʱɾ��
	CmdActorAdd( const ActorArray& SavedActors );

	virtual void OnHistoryChanged( );

	virtual void Execute( );

private:
	ActorArray mSavedActors;
};

class CmdActorRemove : public CmdBase
{
public:
	CmdActorRemove( const ActorArray& SavedActors );

	virtual void OnHistoryChanged( );

	virtual void Execute( );

private:
	ActorArray mSavedActors;
	ActorArray mSavedParents;
};


class CmdActorSelect : public CmdBase
{
public:
	CmdActorSelect( EditorObject* Selection );


	virtual void Execute( );

private:
	SelectedActorArray mSelectedArray;

};


class CmdSetObjProperty : public CmdBase
{
public:
	CmdSetObjProperty( const WString& PropertyName, const WString& PropertyValue );

	virtual void Execute( );

private:
	WString mPropertyName;
	WString mPropertyValue;
};

class CmdActorChangeParent : public CmdBase
{
public:
	CmdActorChangeParent( Actor* A , Actor* PrevParent );

	virtual void Execute( );

private:
	Actor* mActor;
	Actor* mPrevParent;
};


class CmdActorClear : public CmdBase
{
public:
	CmdActorClear( const ActorArray& SavedActors, Actor* Root );


	virtual void Execute( );

	virtual void OnHistoryChanged();
	
private:
	Actor* mRoot;
	ActorArray mSavedActors;
};


class CmdActorRestore : public CmdBase
{
public:
	CmdActorRestore( Actor* Root );

	virtual void Execute( );

	virtual void OnHistoryChanged();

private:
	Actor* mRoot;
	ActorArray mSavedActors;
};




/**
	����Node����Ҫʹ�����Cmd����Node������֮��Ĳ���
*/
class CmdMaterialNodeCreate : public CmdBase
{
public:
	CmdMaterialNodeCreate( const QMaterialNodeList& NodeArray );

	virtual void OnHistoryChanged( );

	virtual void Execute( );

private:
	QMaterialNodeList mNodeList;
};


// ��Ҫ���������
struct BackupSlotConnection
{
	QMaterialSlot* mOutputSlot;
	QMaterialSlot* mInputSlot;

	BackupSlotConnection( QMaterialSlot* OutputSlot, QMaterialSlot* InputSlot )
		: mInputSlot( InputSlot )
		, mOutputSlot( OutputSlot )
	{

	}
};


/**
	ɾ��Nodeǰ����Ҫ������ЩNode��Ҫɾ��
*/
class CmdMaterialNodeDelete : public CmdBase
{
public:
	CmdMaterialNodeDelete( const QMaterialNodeList& NodeArray );

	virtual void OnHistoryChanged( );

	virtual void Execute( );

private:
	// �ڵ���Ϣ
	QMap<QMaterialNode*, QList<BackupSlotConnection> > mSavedNodeInfo;

	QMaterialNodeList mNodeArray;
};

/**
	�ڵ��ƶ�����¼�ƶ�ǰλ��
*/
class CmdMaterialNodeMove : public CmdBase
{
public:
	CmdMaterialNodeMove( const QMaterialNodeList& NodeArray );

	virtual void OnHistoryChanged( );

	virtual void Execute( );

private:
	QMaterialNodeList mNodeArray;
	QVector<QPointF> mNodePositions;
};


/**
	����һ���ۣ���¼�Ͽ�ǰ������
*/
class CmdMaterialSlotConnect : public CmdBase
{
public:
	CmdMaterialSlotConnect( QMaterialSlot* InputSlot );

	virtual void OnHistoryChanged( ){}

	virtual void Execute( );

private:
	QMaterialSlot* mInputSlot;
};


/**
	�Ͽ�һ���ۣ���¼�Ͽ�ǰ������
*/
class CmdMaterialSlotDisconnect : public CmdBase
{
public:
	CmdMaterialSlotDisconnect( QMaterialSlot* SlotToDisconnect );

	virtual void OnHistoryChanged( ){}

	virtual void Execute( );

private:
	QList<BackupSlotConnection> mConnections;
};