#pragma once



class Vector2Manager;
class Vector3Manager;	
class Vector4Manager;	


class QPropertyGrid : public QWidget
{
	Q_OBJECT;
public:
	QPropertyGrid( QWidget* parent, bool MarginSide = true );

	virtual ~QPropertyGrid( );

	QtVariantPropertyManager* GetVarManager( ){ return mVariantManager; }
	Vector2Manager* GetVar2Manager( ){ return mVector2Manager; }
	Vector3Manager* GetVar3Manager( ){ return mVector3Manager; }
	Vector4Manager* GetVar4Manager( ){ return mVector4Manager; }

	QtAbstractPropertyBrowser* GetBrowser( ){ return mPropertyBrowser; }
	
	void ClearProperties( );
	void ReflectProperties( ReflectionObject* Object );

public Q_SLOTS:

	void valueChanged(QtProperty* Prop, const QVariant& Value);
	void OnTestButtonClicked( );
private:
	QtVariantPropertyManager*	mVariantManager;
	QtVariantEditorFactory*		mVariantEditorFactory;
	QtAbstractPropertyBrowser*	mPropertyBrowser;
	QPushButton*				mTestButton;

	QtGroupPropertyManager*		mGroupManager;

// ��չ���ͣ�Qt�����
	Vector2Manager*			mVector2Manager;
	Vector3Manager*			mVector3Manager;
	Vector4Manager*			mVector4Manager;

	bool mNeedClear;
	bool mEnableValueChangeNotify;

	//////////////////////////////////////////////////////////////////////////
	// ΪRTTIObject׼��������valueӳ��
	//////////////////////////////////////////////////////////////////////////

	friend dword GetTypeHash( QtVariantProperty* s )
	{
		return PointerHash( s );
	}
	

	struct MappedData 
	{
		PropertyValue* mValue;
		RTTIObject* mInstance;

		MappedData( )
			: mValue( null )
			, mInstance( null )
		{

		}

		MappedData( PropertyValue* Value, RTTIObject* Ins )
			: mValue( Value )
			, mInstance( Ins )
		{

		}
	};

	typedef dynamic_hash<QtVariantProperty*, MappedData > PropertyMapper;
	PropertyMapper mPropertyMapper;
};

 