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
		ʸ��4
	*/
	class Vector4
	{
	public:

		float x,y,z,w;

		/// ��
		const static Vector4 cZero;

		/// һ
		const static Vector4 cOne;

		/// x=1
		const static Vector4 cXAxis;

		/// y=1
		const static Vector4 cYAxis;

		/// z=1
		const static Vector4 cZAxis;

		/// w=1
		const static Vector4 cWAxis;

		const static Vector4 cMaxVector;

		const static Vector4 cMinVector;

		/// ����
		inline Vector4( );

		/// ��ֵ����
		inline Vector4( float xx, float yy, float zz, float ww );

		/// ʸ��w����
		inline Vector4( const Vector3& vector, float ww );

		/// ת��
		inline operator Vector3 ( ) const;

		/// ��
		inline Vector4 operator + ( ) const;

		/// ��
		inline Vector4 operator - ( ) const;

		/// �Լ�
		inline Vector4& operator += ( const Vector4& vector );

		/// �Լ�
		inline Vector4& operator -= ( const Vector4& vector );
		
		/// �Գ�
		inline Vector4& operator *= ( float scalar );

		/// ������
		inline Vector4& operator *= ( const Vector4& vector );

		/// �Գ�
		inline Vector4& operator /= ( float scalar );

		/// �Գ�
		inline Vector4& operator /= ( const Vector4& vector );

		/// �˾���
		Vector4& operator *= ( const Matrix4& matrix );

		/// ��
		inline Vector4 operator + ( const Vector4& vector ) const;

		/// ��
		inline Vector4 operator - ( const Vector4& vector ) const;

		/// ��
		inline Vector4 operator * ( float scalar ) const;

		/// ��
		inline Vector4 operator * ( const Vector4& vector ) const;

		/// ��
		inline Vector4 operator / ( float scalar ) const;

		/// ��
		inline Vector4 operator / ( const Vector4& vector ) const;

		/// �˾���
		Vector4 operator * ( const Matrix4& matrix ) const;

		/// ���
		bool operator == ( const Vector4& vector ) const;


		/// ����ֵ
		Vector4& Absolute( );

		/// ��λ��
		Vector4& Normalize( );

		/// ģ
		float Magnitude( ) const;

		/// ������ģ
		float MagnitudeSquared( ) const;

		/// ���
		static float DotProduct( const Vector4& vector1, const Vector4& vector2 );

		/// Ͷ��
		static Vector4 Project( const Vector4& vector1, const Vector4& vector2 );

		/// ��ֵ
		static Vector4 Lerp( const Vector4& vector1, const Vector4& vector2, float factor );
	};


	Vector4::Vector4( )
	{
	}

	Vector4::Vector4( float xx, float yy, float zz, float ww )
		: x( xx ), y( yy ), z( zz ), w( ww )
	{
	}

	Vector4::Vector4( const Vector3& vector, float ww )
		: x( vector.x ), y( vector.y ), z( vector.z ), w( ww )
	{
	}

	Vector4::operator Vector3 ( ) const
	{
		return Vector3( x, y, z );
	}

	Vector4 Vector4::operator + ( ) const
	{
		return Vector4( x, y, z, w );
	}

	Vector4 Vector4::operator - ( ) const
	{
		return Vector4( -x, -y, -z, -w );
	}

	Vector4& Vector4::operator += ( const Vector4& vector )
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
		w += vector.w;

		return *this;
	}

	Vector4& Vector4::operator -= ( const Vector4& vector )
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		w -= vector.w;

		return *this;
	}

	Vector4& Vector4::operator *= ( float scalar )
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;

		return *this;
	}

	Vector4& Vector4::operator *= ( const Vector4& vector )
	{
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
		w *= vector.w;

		return *this;
	}

	Vector4& Vector4::operator /= ( float scalar )
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;

		return *this;
	}

	Vector4& Vector4::operator /= ( const Vector4& vector )
	{
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;
		w /= vector.w;

		return *this;
	}

	Vector4 Vector4::operator + ( const Vector4& vector ) const
	{
		return Vector4( x + vector.x, y + vector.y, z + vector.z, w + vector.w );
	}

	Vector4 Vector4::operator - ( const Vector4& vector ) const
	{
		return Vector4( x - vector.x, y - vector.y, z - vector.z, w - vector.w );
	}

	Vector4 Vector4::operator * ( float scalar ) const
	{
		return Vector4( x * scalar, y * scalar, z * scalar, w * scalar );
	}

	Vector4 Vector4::operator * ( const Vector4& vector ) const
	{
		return Vector4( x * vector.x, y * vector.y, z * vector.z, w * vector.w );
	}

	Vector4 Vector4::operator / ( float scalar ) const
	{
		return Vector4( x / scalar, y / scalar, z / scalar, w / scalar );
	}

	Vector4 Vector4::operator / ( const Vector4& vector ) const
	{
		return Vector4( x / vector.x, y / vector.y, z / vector.z, w / vector.w );
	}

	/** @} */
	/** @} */
}