#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup System
	*  @{
	*/


	/// �任�ռ�
	enum eTransformSpace
	{
		TS_Local,		///< ���󱾵�
		TS_Parent,		///< ��Ը���
		TS_World,		///< ����
	};

	/// �任����
	enum eTransformType
	{
		TT_None				= 0,		///< û��
		TT_Position			= 1,		///< λ��
		TT_Rotation			= 2,		///< ��ת
		TT_Scale			= 4,		///< ����
		TT_InheritRotate	= 8,		///< ������ת
		TT_InheritScale		= 16,		///< ��������
		TT_All = TT_Position + TT_Rotation + TT_Scale + TT_InheritScale + TT_InheritRotate,
	};

	/** 
		�ɱ任����
		@remark
			��װ�������任
	*/
	class MovableObject
	{
	public:
		MovableObject( );

		~MovableObject( );

		//////////////////////////////////////////////////////////////////////////
		// �任
		//////////////////////////////////////////////////////////////////////////

		/**
			λ���ۼ�
			@param
				Value �ۼ���
			@param
				Space �任�ռ�
		*/
		void				Translate( const Vector3& Value, eTransformSpace Space = TS_Parent );

		/**
			��ת�ۼ�
			@param
				Value �ۼ���
			@param
				Space �任�ռ�
		*/
		void				Rotate( const Quaternion& Value, eTransformSpace Space = TS_Parent );

		/**
			�����ۼ�
			@param
				Value �ۼ���
			@param
				Space �任�ռ�
		*/
		void				Scale( const Vector3& Value );

		/// ������Ը���λ��
		void				SetPosition( const Vector3& Value );

		/// ��ȡ��Ը���λ��
		const Vector3&		GetPosition( );

		/// ������Ը�����ת
		void				SetRotation( const Quaternion& Value );

		/// ��ȡ��Ը�����ת
		const Quaternion&	GetRotation( );

		/// ������Ը�������
		void				SetScale( const Vector3& Value );

		/// ��ȡ��Ը�������
		const Vector3&		GetScale( );

		/// �����Ƿ�̳�����
		void				SetInheriteScale( bool IsInherite );

		/// ��ȡ�Ƿ�̳�����
		bool				GetInheriteScale( );

		/// �����Ƿ�̳���ת
		void				SetInheriteRotate( bool IsInherite );

		/// ��ȡ�Ƿ�̳���ת
		bool				GetInheriteRotate( );

		/// ������ת
		void				ResetRotation( );

		/// �ϲ��˸������б任�ı任
		const Matrix4&		GetFullTransform( );

		/// ��ȡ������ת
		const Quaternion&	GetDerivedRotation( );

		/// ��ȡ����λ��
		const Vector3&		GetDerivedPosition( );

		/// ��ȡ��������
		const Vector3&		GetDerivedScale( );

		/// ��������λ��
		void				SetDerivedPosition( const Vector3& Value );

		/// ����������ת
		void				SetDerivedRotation( const Quaternion& Value );

		/// ������������
		void				SetDerivedScale( const Vector3& Value );

		/// ��������ת�ֲ�λ��
		Vector3				WorldToLocalPosition( const Vector3 &WorldPos );

		/// �ֲ�����׬����λ��
		Vector3				LocalToWorldPosition( const Vector3 &LocalPos );

		/// ��������ת�ֲ���ת
		Quaternion			WorldToLocalRotation( const Quaternion &WorldRotation );

		/// �ֲ�����׬������ת
		Quaternion			LocalToWorldRotation( const Quaternion &LocalRotation );		

		/**
			����ָ����һ��
			@param
				Value ����ĵ�
			@param
				UpFixed �Ƿ񱣳��Ϸ��򲻱�(����������ǰ����X������ת),�����ģʽ��Ҫѡtrue
		*/
		void SetViewTarget( const Vector3& Value, bool UpFixed = true );

		/// ��ȡ����
		Vector3 GetViewDir( );

		void Serialize( BinarySerializer& Ser );

	protected:
		/// ��Ҫʵ��:��ȡ����ӿ�
		virtual MovableObject*	GetParentMovable( ){ return null; }

		/// ��Ҫʵ��:������һ������
		virtual MovableObject* GetFirstMovable( ){ return null; }

		/// ��Ҫʵ��:������һ������
		virtual MovableObject* GetNextMovable( ){ return null; }

		/// ��Ҫʵ��: �任��֪ͨ
		virtual void OnObjectTransformed( dword TransformType ){ }

		void NeedUpdateTransform( dword TransformType );

		void UpdateFromParent( );
	
	private:
		// ����ڸ����ı任
		Vector3		mPosition;
		Quaternion	mRotation;

		// ��������
		Vector3		mScale;

		// �����Լ��Ƿ������Ը�������ת
		bool		mInheritRotate;

		// �����Լ��Ƿ������Ը�������
		bool		mInheritScale;

		// �ϲ��˸������б任�ı�������
		Quaternion	mDerivedRotation;
		Vector3		mDerivedPosition;
		Vector3		mDerivedScale;

		dword		mNeedParentUpdateType;

		bool		mNeedRebuildMatrix;
		Matrix4		mFullTransform;

		bool		mNotifyTransform;
	};

	/** @} */
	/** @} */
}