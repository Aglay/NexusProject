#pragma once

class QPropertyGrid;

// ʵ���������Ե�Qt���Ե�ת����װ
class QTypeMapper
{
public:
	// ӳ�����������
	virtual const wchar* GetTypeName( ) = 0;

	// ��ʼ��������
	virtual QtVariantProperty* InitProperty( RTTIObject* Instance, PropertyValue* PV, QPropertyGrid* PGrid  ) = 0;

	// �������Ե�Qt��������
	virtual bool LoadProperty( RTTIObject* Instance, PropertyValue* PV, QPropertyGrid* PGrid, QtVariantProperty* Prop ) = 0;

	// Qt�������õ���������
	virtual bool SaveProperty( RTTIObject* Instance, PropertyValue* PV, QPropertyGrid* PGrid, const QVariant& Value) = 0;
};



// ����ӳ����������
class QTypeMapperManager
{
public:
	QTypeMapperManager( );
	virtual ~QTypeMapperManager( );

	// ע������ӳ����
	void RegisterMapper( QTypeMapper* Mapper );

	// ��ѯ����ӳ����
	QTypeMapper* QueryMapper( const wchar* TypeName );

	// ��ʼ��������
	QtVariantProperty* InitValue( RTTIObject* Instance, PropertyValue* PV, QPropertyGrid* PGrid  );

	// Qt�������õ���������
	bool SaveProperty( RTTIObject* Instance, PropertyValue* PV, QPropertyGrid* PGrid, const QVariant& Value );

private:
	typedef dynamic_hash<WString, QTypeMapper*> MapperMap;

	// �����������͵�Qt���͵�ӳ��
	MapperMap mMapperMap;

};

extern QTypeMapperManager* GTypeMapperManager;