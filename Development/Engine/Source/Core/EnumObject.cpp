#include "CorePCH.h"
#include "NekoCore_Reflection.h"

namespace NekoEngine
{
	void EnumObject::AddMember( const char* k, dword v )
	{
		mValueMapping[NameRef(k)] = v;
	}

	bool EnumObject::GetValue( const char* k, dword& v )
	{
		ValueMapping::iterator it = mValueMapping.find( NameRef(k, NameBuild_Find ) );
		if ( it == mValueMapping.end() )
			return false;

		v = it->second;

		return true;
	}



	void EnumObject::StaticExit()
	{
		// ע�⣬���ö�ٶ�����DLL�У������ͷſ��ܳ�����
		for ( EnumObjectList::iterator it = mEnumObjectList.begin();
			it != mEnumObjectList.end();
			++it )
		{
			it->second->ReleaseRTTIObject();
		}

		mEnumObjectList.clear();

		RTTIObject::UnRegisterPackage("EnumObject");
	}

	EnumObject::EnumObjectList EnumObject::mEnumObjectList;

	bool EnumObject::GetEnumValue( const char* enumname, const char* k, dword& v )
	{
		NameRef refEnumName( enumname, NameBuild_Find );

		// ���Ѿ��е��б�����
		EnumObjectList::iterator it = mEnumObjectList.find( refEnumName );

		EnumObject* enumobj;

		if ( it == mEnumObjectList.end() )
		{
			// �´���
			enumobj = (EnumObject*)RTTIObject::CreateInstance( refEnumName, NameRef("EnumObject",NameBuild_Find) );

			// ���봴���б�
			mEnumObjectList[ refEnumName ] = enumobj;
		}
		else
		{
			enumobj = it->second;
		}

		// ö�ٲ�����
		if ( enumobj == null )
			return false;

		// ȡֵ
		bool r = enumobj->GetValue( k, v );

		return r;
	}






}