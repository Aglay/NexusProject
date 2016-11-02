#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Math
	*  @{
	*/


	/** 
		4x4����
	*/
	class Matrix4
	{
	private:

		friend class Matrix3;
		friend class Quaternion;
		union 
		{
			struct
			{
				float m11, m12, m13, m14;
				float m21, m22, m23, m24;
				float m31, m32, m33, m34;
				float m41, m42, m43, m44;
			};
			float m[4][4];
		};

	public:

		const static Matrix4 cZero;

		const static Matrix4 cIdentity;

		/// Ĭ�Ϲ���
		inline Matrix4( );
		
		/// 16ֵ����
		inline Matrix4( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33 );

		/// ȡ����Ԫ��
		inline float operator ( ) ( dword row, dword column ) const;
		
		/// ȡ����Ԫ�� ����
		inline float& operator ( ) ( dword row, dword column );
		
		/// ��
		inline Matrix4 operator - ( ) const;

		/// ȡ��
		inline Vector4 GetRow( dword row ) const;

		inline Vector3 GetAxis( dword row ) const;

		inline void SetRow( dword index, float x, float y, float z, float w);

		inline void SetAxis( dword index, const Vector3& v );
		
		/// ȡ��
		inline Vector4 GetColumn( dword column ) const;

		/// �����Ƚ�
		inline bool operator == ( const Matrix4& matrix);

		inline bool operator != ( const Matrix4& matrix);

		/// �Լ�
		Matrix4& operator += ( const Matrix4& matrix );
		
		/// �Լ�
		Matrix4& operator -= ( const Matrix4& matrix );
		
		/// �Գ�
		Matrix4& operator *= ( const Matrix4& matrix );
		
		/// �˷�����
		Matrix4& operator *= ( float scalar );
		
		/// ��������
		Matrix4& operator /= ( float scalar );

		/// �Ӿ���
		Matrix4 operator + ( const Matrix4& matrix ) const;
		
		/// ������
		Matrix4 operator - ( const Matrix4& matrix ) const;
		
		/// �˾���
		Matrix4 operator * ( const Matrix4& matrix ) const;
		
		/// ������
		Matrix4 operator * ( float scalar ) const;
		
		/// ������
		Matrix4 operator / ( float scalar ) const;

		/// ����Ԫ������
		Matrix4& FromQuaternion(const Quaternion& quat);

		/// ��λ��
		Matrix4 Identity( ) const;
		
		/// ת��
		Matrix4 Transpose( ) const;
		
		/// ����
		Matrix4 Inverse( ) const;
	

		/// λ��
		Matrix4& Translation( float x, float y, float z );
		
		/// λ�� ʸ��
		Matrix4& Translation( const Vector3& vector );

		/// ֻ����ƫ��
		Matrix4& SetTranslation( const Vector3& vector );

		/// ����
		Matrix4& Scale( float x, float y, float z );
		
		/// ���� ʸ��
		Matrix4& Scale( const Vector3& vector );
		
		/// ���� ����
		Matrix4& Scale( const Vector3& vector, float factor );

		/// ��X����ת
		Matrix4& RotationX( float radian );
		
		/// ��Y����ת
		Matrix4& RotationY( float radian );
		
		/// ��Z����ת
		Matrix4& RotationZ( float radian );
		
		/// ������ת
		Matrix4& RotationAxis( const Vector3& axis, float radian );
		
		/// ����һ��������src��ת��dest
		Matrix4& Rotation( const Vector3& srcvector, const Vector3& desvector );
		
		/// ����Ԫ����ת
		Matrix4& Rotation( const Quaternion& rotation );

		
		/// Ͷ�䵽XYƽ��ľ���
		Matrix4& ProjectXY( );
		
		/// Ͷ�䵽YZƽ��ľ���
		Matrix4& ProjectYZ( );
		
		/// Ͷ�䵽ZXƽ��ľ���
		Matrix4& ProjectZX( );
		
		/// Ͷ��ʸ��������ƽ��
		Matrix4& Project( const Vector3& vector );

		/// ����һ���������,��XYƽ��Ϊ������
		Matrix4& RefectionXY( );
		
		/// ����һ���������,��YZƽ��Ϊ������
		Matrix4& RefectionYZ( );
		
		/// ����һ���������,��ZXƽ��Ϊ������
		Matrix4& RefectionZX( );
		
		/// ����һ���������,Ͷ��ʸ��������ƽ��
		Matrix4& Refection( const Vector3& vector );

		/// ��һ��3X3�����һ��ʸ������
		Matrix4& FromTranslationRotation( const Vector3& translation, const Matrix3& rotation );
		
		/// 3���任�������
		Matrix4& FromTransform( const Vector3& translation, const Quaternion& rotation, const Vector3& scaling );

		/// ����������
		Matrix4& FromMatrix3( const Matrix3& Mat );

		/// ȡ��3X3�����λ������
		void ToTranslationRotation( Vector3& translation, Matrix3& rotation ) const;

		/// ��һ����Ԫ����һ��ʸ������
		Matrix4& FromTranslationRotation( const Vector3& translation, const Quaternion& rotation );
		
		/// ȡ����Ԫ����λ������
		void ToTranslationRotation( Vector3& translation, Quaternion& rotation ) const;

		Vector4 TransformNormal( const Vector3& v );

		Vector4 TransformCoord( const Vector4& v );

		/// �������־���
		static Matrix4 OrthoLH( float width, float height, float znear, float zfar );

		/// ��������Ͷ�������viewport��Ӧ��ʵ�ʲ鿴���ھ��� ( 2Dʹ��ʱzear=0 zfar=1)
		static Matrix4 OrthoOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar );

		/// �������־���
		static Matrix4 OrthoRH( float width, float height, float znear, float zfar );

		/// ��������Ͷ�����
		static Matrix4 OrthoOffCenterRH( float left, float right, float bottom, float top, float znear, float zfar );

		/// ͸������Ͷ�����
		static Matrix4 PerspectiveLH( float width, float height, float znear, float zfar );

		/// ͸������Ͷ�����,������׶ģ��
		static Matrix4 PerspectiveFovLH( float fovy, float aspect, float znear, float zfar );

		/// ͸������Ͷ�����
		static Matrix4 PerspectiveOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar );

		/// ͸������Ͷ�����
		static Matrix4 PerspectiveRH( float width, float height, float znear, float zfar );

		/// ͸������Ͷ�����,������׶ģ��
		static Matrix4 PerspectiveFovRH( float fovy, float aspect, float znear, float zfar );

		/// ͸������Ͷ�����
		static Matrix4 PerspectiveOffCenterRH( float left, float right, float bottom, float top, float znear, float zfar );

		/// ���ֿ�����
		static Matrix4 LookAtLH( const Vector3& eye, const Vector3& lookat, const Vector3& upaxis );
		
		/// ���ֿ�����
		static Matrix4 LookAtRH( const Vector3& eye, const Vector3& lookat, const Vector3& upaxis );

		Matrix4& FromRotator( const Rotator& Rot );

		Rotator GetRotator() const;
	};

	//----------------------------------------------------------------------------
	// nMatrix4 Implementation
	//----------------------------------------------------------------------------

	Matrix4::Matrix4( )
	{
	}

	Matrix4::Matrix4( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33 )
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
		m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
	}

	float Matrix4::operator ( ) ( dword row, dword column ) const
	{
		Assert( row < 4 && column < 4 );

			return m[ row ][ column ];
	}

	float& Matrix4::operator ( ) ( dword row, dword column )
	{
		Assert( row < 4 && column < 4 );

			return m[ row ][ column ];
	}


	Matrix4 Matrix4::operator - ( ) const
	{
		return Matrix4( -m[0][0], -m[0][1], -m[0][2], -m[0][3], -m[1][0], -m[1][1], -m[1][2], -m[1][3],
			-m[2][0], -m[2][1], -m[2][2], -m[2][3], -m[3][0], -m[3][1], -m[3][2], -m[3][3] );
	}

	Vector4 Matrix4::GetRow( dword row ) const
	{
		Assert( row < 4 );

			return Vector4( m[ row ][0], m[ row ][1], m[ row ][2], m[ row ][3] );
	}

	Vector3 Matrix4::GetAxis( dword row ) const
	{
		Assert( row < 4 );

		return Vector3( m[ row ][0], m[ row ][1], m[ row ][2] );
	}

	void Matrix4::SetRow( dword index, float x, float y, float z, float w)
	{
		Assert( index < 4 );
		m[index][0] = x;
		m[index][1] = y;
		m[index][2] = z;
		m[index][3] = w;
	}

	void Matrix4::SetAxis( dword index, const Vector3& v )
	{
		Assert( index < 4 );
		m[index][0] = v.x;
		m[index][1] = v.y;
		m[index][2] = v.z;
	}


	Vector4 Matrix4::GetColumn( dword column ) const
	{
		Assert( column < 4 );

			return Vector4( m[0][ column ], m[1][ column ], m[2][ column ], m[3][ column ] );
	}


	/** @} */
	/** @} */
}

