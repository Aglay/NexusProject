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
		3x3����
	*/
	class Matrix3
	{
	public:
		friend class Matrix4;
		union 
		{
			struct
			{
				float m11, m12, m13;
				float m21, m22, m23;
				float m31, m32, m33;
			};
			float m[3][3];
		};
		
		/// �����
		const static Matrix3 cZero;
		
		/// ��λ��
		const static Matrix3 cIdentity;

		/// Ĭ�Ϲ���
		inline Matrix3( );

		/// 9ֵ����
		inline Matrix3( float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22 );

		/// ȡ����Ԫ��
		inline float operator ( ) ( dword row, dword column ) const;
		
		/// ȡ����Ԫ�� ����
		inline float& operator ( ) ( dword row, dword column );

		/// ��
		inline Matrix3 operator - ( ) const;

		/// ȡ��
		inline Vector3 GetRow( dword row ) const;

		/// ȡ��
		inline Vector3 GetColumn( dword column ) const;

		/// �Լ�
		Matrix3& operator += ( const Matrix3& matrix );

		/// �Լ�
		Matrix3& operator -= ( const Matrix3& matrix );

		/// �Գ�
		Matrix3& operator *= ( const Matrix3& matrix );

		/// �˷�����
		Matrix3& operator *= ( float scalar );

		/// ��������
		Matrix3& operator /= ( float scalar );

		/// �Ӿ���
		Matrix3 operator + ( const Matrix3& matrix ) const;

		/// ������
		Matrix3 operator - ( const Matrix3& matrix ) const;

		/// �˾���
		Matrix3 operator * ( const Matrix3& matrix ) const;

		/// ������
		Matrix3 operator * ( float scalar ) const;

		/// matrix * vector [3x3 * 3x1 = 3x1]
		Vector3 operator* (const Vector3& rkPoint) const;

		/// ������
		Matrix3 operator / ( float scalar ) const;

		/// ��λ��
		Matrix3 Identity( );

		/// ת��
		Matrix3 Transpose( );

		/// ����
		Matrix3 Inverse( );

		/// ����
		Matrix3& Scaling( float x, float y, float z );

		/// ���� ʸ��
		Matrix3& Scaling( const Vector3& vector );

		/// ���� ����
		Matrix3& Scaling( const Vector3& vector, float factor );

		/// ��X����ת
		Matrix3& RotationX( float radian );

		/// ��Y����ת
		Matrix3& RotationY( float radian );

		/// ��Z����ת
		Matrix3& RotationZ( float radian );

		/// ������ת
		Matrix3& RotationAxis( const Vector3& axis, float radian );

		/// Ͷ�䵽XYƽ��ľ���
		Matrix3& ProjectXY( );

		/// Ͷ�䵽YZƽ��ľ���
		Matrix3& ProjectYZ( );

		/// Ͷ�䵽ZXƽ��ľ���
		Matrix3& ProjectZX( );

		/// Ͷ��ʸ��������ƽ��
		Matrix3& Project( const Vector3& vector );

		/// ����һ���������,��XYƽ��Ϊ������
		Matrix3& RefectionXY( );

		/// ����һ���������,��YZƽ��Ϊ������
		Matrix3& RefectionYZ( );

		/// ����һ���������,��ZXƽ��Ϊ������
		Matrix3& RefectionZX( );

		/// ����һ���������,Ͷ��ʸ��������ƽ��
		Matrix3& Refection( const Vector3& vector );

		/** 
			����2D���ž���
		*/
		Matrix3& Scaling2D( float x, float y );

		/** 
			����2D���ž���
		*/
		Matrix3& Scaling2D( const Vector2& vector );

		/** 
			����2D���ž���
		*/
		Matrix3& Translation2D( float x, float y);

		/** 
			����2Dƫ�ƾ���
		*/
		Matrix3& Translation2D( const Vector2& vector );

		/// ����2D������ƽ�Ʋ���
		Matrix3& SetTranslation2D( float x, float y );

		/// ����2D������ƽ�Ʋ���
		Matrix3& SetTranslation2D( const Vector2& vector );

		/// ƫ��2D����
		Matrix3& AddTranslation2D( const Vector2& vector );

		/// ��Ԫ��ת����
		Matrix3& FromQuaternion(const Quaternion& quat);
	};

	//----------------------------------------------------------------------------
	// nMatrix3 Implementation
	//----------------------------------------------------------------------------

	Matrix3::Matrix3( )
	{
	}

	Matrix3::Matrix3( float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22 )
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
	}

	float Matrix3::operator ( ) ( dword row, dword column ) const
	{
		Assert( row < 3 && column < 3 );

			return m[ row ][ column ];
	}

	float& Matrix3::operator ( ) ( dword row, dword column )
	{
		Assert( row < 3 && column < 3 );

			return m[ row ][ column ];
	}


	Matrix3 Matrix3::operator - ( ) const
	{
		return Matrix3( -m[0][0], -m[0][1], -m[0][2], -m[1][0], -m[1][1], -m[1][2], -m[2][0], -m[2][1], -m[2][2] );
	}

	Vector3 Matrix3::GetRow( dword row ) const
	{
		Assert( row < 3 );

			return Vector3( m[ row ][0], m[ row ][1], m[ row ][2] );
	}

	Vector3 Matrix3::GetColumn( dword column ) const
	{
		Assert( column < 3 );

			return Vector3( m[0][ column ], m[1][ column ], m[2][ column ] );
	}


	/** @} */
	/** @} */
}

