#include "EditorPCH.h"
#include "PrivateInclude.h"



//////////////////////////////////////////////////////////////////////////
// QMaterialScene
//////////////////////////////////////////////////////////////////////////


QMaterialScene::QMaterialScene( QMaterialPanel* Parent )
: QGraphicsScene( Parent )
, mPanel( Parent )
, mPickedNode( null )
, mConnectLine( null )
, mSourceSlot( null )
, mSelectedNode( null )
, mSelectedSlot( null )
, mRoot( null )
{	
	mActionDisconnect = new QAction(this);
	mActionDisconnect->setObjectName(QString::fromUtf8("Action.Material.Slot.Disconnect"));	
	mActionDisconnect->setText(QApplication::translate("this", "Disconnect", 0, QApplication::UnicodeUTF8));
	mActionDisconnect->setToolTip(QApplication::translate("this", "Disconnect the connection between node and slot", 0, QApplication::UnicodeUTF8));
	connect( mActionDisconnect,SIGNAL(triggered()), this, SLOT(OnActionDisconnect()) );

	mActionDeleteNode = new QAction(this);
	mActionDeleteNode->setObjectName(QString::fromUtf8("Action.Material.Node.Delete"));	
	mActionDeleteNode->setText(QApplication::translate("this", "Delete", 0, QApplication::UnicodeUTF8));
	mActionDeleteNode->setToolTip(QApplication::translate("this", "Delete the node", 0, QApplication::UnicodeUTF8));
	connect( mActionDeleteNode,SIGNAL(triggered()), this, SLOT(OnActionDeleteNode()) );
}

QMaterialScene::~QMaterialScene( )
{
	// ɾ��δ�йܵ�����
	foreach( QMaterialConnection* Connection, mFreeConnectionList )
	{
		delete Connection;
	}

	mFreeConnectionList.clear();
}


void QMaterialScene::OnActionDisconnect( )
{
	if( mSelectedSlot == null )
		return;

	mPanel->CmdDisconnectSlot( mSelectedSlot );
}


void QMaterialScene::OnActionDeleteNode( )
{
	if( mSelectedNode == null )
		return;

	mPanel->CmdDeleteNode( mSelectedNode );
}





void QMaterialScene::dragEnterEvent( QGraphicsSceneDragDropEvent *evt )
{
	// ���ʴ����Ϸ�
	if ( evt->mimeData()->hasFormat( cDragDropType_MaterialSpawn ) )
	{
		evt->accept( );
	}
	else
	{
		// ��ͨ�Ϸ�
		__super::dragEnterEvent( evt );
	}
}

void QMaterialScene::dragMoveEvent( QGraphicsSceneDragDropEvent *evt )
{
	// ���ʴ����Ϸ�
	if ( evt->mimeData()->hasFormat( cDragDropType_MaterialSpawn ) )
	{
		evt->accept( );
	}
	else
	{
		// ��ͨ�Ϸ�
		__super::dragMoveEvent( evt );
	}
}

void QMaterialScene::dropEvent( QGraphicsSceneDragDropEvent *evt )
{
	__super::dropEvent( evt );

	QByteArray exData = evt->mimeData()->data(cDragDropType_MaterialSpawn);

	QDataStream dataStream (&exData, QIODevice::ReadOnly);


	int Data;
	dataStream >> Data;

	QMaterialNode* Node = mPanel->CmdSpawnNode( (RTTIClass*)Data );

	const QRectF& Bound = Node->GetLogicBound();

	Node->group()->setPos( evt->scenePos() - QPointF( Bound.width() /2, Bound.height()/2) );	
}


void QMaterialScene::mousePressEvent( QGraphicsSceneMouseEvent *evt )
{
	__super::mousePressEvent( evt );

	switch ( evt->button() )
	{
	case Qt::LeftButton:
		{
			QGraphicsItem* PickedItem = itemAt( evt->scenePos() );

			if ( PickedItem == null )
				return;


			QMaterialNode* Node = dynamic_cast<QMaterialNode*>( PickedItem );

			// ʰȡ���ڵ�
			if ( Node != null )
			{
				// �ҵ������ڵ���
				QGraphicsItemGroup* Group = Node->group();

				if ( Group == null )
					return;

				// ��ʼ�ƶ���
				mPickedNode = Node;

				mPickedNodeConnections = GetNodeConnections( Node );


				mSavedPos = evt->scenePos() - Group->pos();

				// ��¼�ƶ��Ľڵ�
				QMaterialNodeList ToBeMovedNode;
				ToBeMovedNode.push_back( mPickedNode );

				GCommandManager->Add( new CmdMaterialNodeMove( ToBeMovedNode ) );

				return;
			}

			QMaterialSlot* Slot = dynamic_cast<QMaterialSlot*>( PickedItem );

			// ʰȡ����
			if ( Slot != null )
			{
				mConnectLine = new QGraphicsLineItem( QLineF( evt->scenePos(), evt->scenePos()) );
				mConnectLine->setPen( QPen(Qt::black, 2) );

				addItem( mConnectLine );

				mSourceSlot = Slot;
			}
		}
		break;
	case Qt::RightButton:
		{
			mSelectedNode = null;
			mSelectedSlot = null;
		}
		break;
	}

}

void QMaterialScene::mouseMoveEvent(QGraphicsSceneMouseEvent *evt)
{
	__super::mouseMoveEvent( evt );

	// �϶�������
	if ( mConnectLine != null )
	{
		QLineF Org = mConnectLine->line();
		mConnectLine->setLine( QLineF(Org.p1(), evt->scenePos()) );
	}


	// �϶��ڵ�
	if ( mPickedNode != null && mPickedNode->group() )
	{

		mPickedNode->group()->setPos( evt->scenePos() - mSavedPos );

		// ����Node�ϵ�����λ��
		// �����������ӣ��ҵ���˽ڵ���ص����ӽ��и���
		foreach( QMaterialConnection* Connecion, mPickedNodeConnections )
		{
			Connecion->UpdateGraphics();
		}
	}
}

void QMaterialScene::UpdateNodeConnections( QMaterialNode* Node )
{
	// �����������ӣ��ҵ���˽ڵ���ص����ӽ��и���
	foreach( QMaterialConnection* Connecion, GetNodeConnections( Node ) )
	{
		Connecion->UpdateGraphics();
	}
}

void QMaterialScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *evt)
{
	__super::mouseReleaseEvent( evt );

	switch ( evt->button() )
	{
	case Qt::LeftButton:
		{
			mPickedNode = null;

			if ( mConnectLine != null )
			{
				QList<QGraphicsItem *> PickedItem = items( evt->scenePos() );

				// ���ϵ���,�ҵ�һ�����ʵĲ�
				foreach( QGraphicsItem* Item, PickedItem )
				{
					QMaterialSlot* Slot = dynamic_cast<QMaterialSlot*>( Item );

					// �۲�����Դ��
					if ( Slot == null || mSourceSlot == Slot )
						continue;

					// ����Ϊ��ͬ���͵����Ӳ�
					if ( mSourceSlot->IsOutputSlot() == Slot->IsOutputSlot() )			
						break;

					if ( mSourceSlot->IsOutputSlot() )
					{
						Math::Swap( mSourceSlot, Slot );
					}


					mPanel->CmdConnectSlot( Slot, mSourceSlot );

					break;
				}


				this->removeItem( mConnectLine );
				delete mConnectLine;		
				mConnectLine = null;
			}
		}
		break;
	}


}

void QMaterialScene::contextMenuEvent( QGraphicsSceneContextMenuEvent *evt )
{
	QGraphicsItem* PickedItem = itemAt( evt->scenePos() );

	if ( PickedItem == null )
		return;

	QMaterialNode* Node = dynamic_cast<QMaterialNode*>( PickedItem );

	// ʰȡ���ڵ�
	if ( Node != null )
	{
		QMenu* PopupMenu = new QMenu( mPanel->GetGraphicsView() );
		PopupMenu->addAction( mActionDeleteNode );

		mSelectedNode = Node;

		PopupMenu->exec( QCursor::pos());		
	}

	QMaterialSlot* Slot = dynamic_cast<QMaterialSlot*>( PickedItem );

	if ( Slot != null )
	{
		QMenu* PopupMenu = new QMenu( mPanel->GetGraphicsView() );
		PopupMenu->addAction( mActionDisconnect );

		mSelectedSlot = Slot;

		PopupMenu->exec( QCursor::pos());		
	}
}

QMaterialNode* QMaterialScene::CreateNode( RTTIClass* NodeType ) 
{
	QMaterialNode* NewNode = new QMaterialNode( NodeType, mPanel->GetGraphicsView() );

	NewNode->InitializeMembers( this );

	return NewNode;
}

void QMaterialScene::CreateRoot( )
{
	mRoot = CreateNode( RTTI_CLASS_INFO(MaterialNodePointLight) );
}




void QMaterialScene::ConnectSlot( QMaterialSlot* OutputSlot, QMaterialSlot* InputSlot )
{
	Assert( OutputSlot->IsOutputSlot() );
	Assert( !InputSlot->IsOutputSlot() );

	QMaterialConnection* Connection = AllocConnection();

	Connection->Reset( OutputSlot, InputSlot );

	addItem( Connection  );
}

QList<QMaterialConnection*> QMaterialScene::GetNodeConnections( QMaterialNode* Node )
{
	QList<QMaterialConnection*> Connections;
	foreach( QMaterialConnection* Connecion, mConnectionList )
	{
		if ( Connecion->IsRelateTo( Node ) )
			Connections.push_back( Connecion );
	}

	return Connections;
}

QMaterialConnection* QMaterialScene::AllocConnection( )
{
	QMaterialConnection* Connection;

	if ( mFreeConnectionList.size() > 0 )
	{
		Connection = mFreeConnectionList.back();
		mFreeConnectionList.pop_back();		
	}
	else
	{
		Connection = new QMaterialConnection( mPanel->GetGraphicsView() );
	}

	mConnectionList.push_back( Connection );

	return Connection;
}

void QMaterialScene::FreeConnection( QMaterialSlot* Slot )
{
	for( QList<QMaterialConnection*>::iterator it = mConnectionList.begin();
		it != mConnectionList.end();
		)
	{
		QMaterialConnection* Connection = *it;

		bool NeedRemove = false;

		if ( Slot->IsOutputSlot() )
		{
			NeedRemove = (Connection->GetOutputSlot() == Slot );
		}
		else
		{
			NeedRemove = (Connection->GetInputSlot() == Slot );
		}

		if ( NeedRemove )
		{
			// �ӳ���ɾ��
			removeItem( Connection );

			// �����������ӱ�������
			mFreeConnectionList.push_back( Connection );

			it = mConnectionList.erase( it );
		}
		else
		{
			++it;
		}
	}
}

void QMaterialScene::DisconnectSlot( QMaterialSlot* Slot )
{
	// ������������
	foreach (QMaterialSlot *ConnectedSlot, Slot->GetSlotConnections())
	{
		// �����ӵ�������Ƴ������
		ConnectedSlot->RemoveSlotConnection( Slot );
	}

	// ��������ӵ����е��������
	Slot->GetSlotConnections().clear();

	// �������Ӷ���
	FreeConnection( Slot );
}
void QMaterialScene::DetachNode( QMaterialNode* Node )
{
	QGraphicsItemGroup* Group = Node->group();
	if ( Group == null )
		return;

	// �����ڵ������е�����ڵ㣬�Ͽ�
	foreach( QMaterialSlot* InputSlot, Node->GetInputSlots() )
	{
		DisconnectSlot( InputSlot );
	}

	// �Ͽ�����ڵ�
	DisconnectSlot( Node->GetOutputSlot() );

	removeItem( Group );
}


inline Vector2 ToVector2( const QPointF& Value )
{
	return Vector2( Value.x(), Value.y() );
}

inline QPointF ToPointF( const Vector2& Value )
{
	return QPointF( Value.x, Value.y );
}

void QMaterialScene::SaveMaterial( const WString& Name )
{
	Assert( mRoot != null );

	MaterialDescriptor* MatDesc = GObjectManager->ConstructObject<MaterialDescriptor>( Name );

	if ( MatDesc == null )
		return;


	// ��ӵ���������
	foreach( QGraphicsItem* Item, items() )
	{
		QMaterialNodeGroup* Group = dynamic_cast<QMaterialNodeGroup*>( Item );
		if ( Group == null )
			continue;

		QMaterialNode* Node = Group->GetNode();

		MaterialNode* CoreNode = MatDesc->AddNode( Node->GetMataerialNodeClass() );

		Node->mIDForSave = CoreNode->GetID();

		// ���ڵ�λ�ñ����ں��Ľڵ���
		CoreNode->SetObjectPropertyT<Vector2>(L"ScenePos", ToVector2( Node->scenePos() ) );
	}

	// ���Ӳ�
	foreach( QMaterialConnection* Connection, mConnectionList )
	{
		MaterialNode* InputCoreNode = MatDesc->GetNode( Connection->GetInputSlot()->GetMaterialNode()->mIDForSave );
		
		MaterialSlot* InputCoreSlot = InputCoreNode->GetSlotByName( Connection->GetInputSlot()->GetName().toStdWString().c_str() );

		InputCoreSlot->Connect( Connection->GetOutputSlot()->GetMaterialNode()->mIDForSave );
	}

	GObjectManager->SaveToFile( MatDesc, FILE_VER_MATERIAL_DESCRIPTOR );

	GObjectManager->DestructObject( MatDesc );
}

void QMaterialScene::FindCoreConnections( MaterialNode* Node, QMap<MaterialNode*, QMaterialNode*>& CoreToQNodeMap )
{
	for ( dword i = 0; i< Node->GetSlotCount(); i++)
	{
		MaterialSlot* Slot = Node->GetSlot( i );

		MaterialNode* LinkedNode = Slot->GetLinkedNode();

		if ( LinkedNode != null )
		{			
			mPanel->CmdConnectSlot( CoreToQNodeMap[LinkedNode]->GetOutputSlot(), CoreToQNodeMap[Node]->GetSlotByName( QString::fromWCharArray( Slot->GetName() ) ) );

			FindCoreConnections( LinkedNode, CoreToQNodeMap );
		}
	}
}

void QMaterialScene::LoadMaterial( const WString& Name )
{
	MaterialDescriptor* MatDesc = GObjectManager->LoadObject<MaterialDescriptor>( Name, false );

	if ( MatDesc == null )
		return;

	QMap<MaterialNode*, QMaterialNode*> CoreToQNodeMap;

	QMaterialNodeList CreatedNodes;
	
	for ( MaterialNode* Node = MatDesc->GetFirstNode();
		 Node != null;
		 Node = MatDesc->GetNextNode() )
	{
		QMaterialNode* NewNode;

		// Root�ڵ㲻�ô���
		if ( Node->GetClass() != mRoot->GetMataerialNodeClass() )
		{
			NewNode = CreateNode( Node->GetClass() );
			CreatedNodes.push_back( NewNode );
		}
		else
		{
			NewNode = mRoot;
		}

		CoreToQNodeMap[Node] = NewNode;

		// �ָ�����λ��
		Vector2 ScenePos;
		if ( Node->GetObjectPropertyT<Vector2>( L"ScenePos", ScenePos ) )
		{
			NewNode->group()->setPos( ToPointF(ScenePos) );
		}
	}

	GCommandManager->Add( new CmdMaterialNodeCreate( CreatedNodes ) );

	MaterialNode* CoreTerminateNode = MatDesc->GetTerminateNode();
	if ( CoreTerminateNode == null )
		return;

	FindCoreConnections( CoreTerminateNode, CoreToQNodeMap );
}