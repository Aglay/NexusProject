#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Math
	*  @{
	*/

	#pragma warning(disable:4201)
	class Matrix3;

	/** 
		ʸ��2
	*/
	class Vector2
	{
	public:

		float x, y;

		/// ��
		const static Vector2 cZero;

		/// һ
		const static Vector2 cOne;

		/// x=1
		const static Vector2 cXAxis;

		/// y=1
		const static Vector2 cYAxis;

		/// Ĭ�Ϲ���
		inline Vector2( );

		/// 2ֵ����
		inline Vector2( float xx, float yy );

		/// ��
		inline Vector2 operator + ( ) const;
		
		/// ��
		inline Vector2 operator - ( ) const;

		/// �Լ�
		inline Vector2& operator += ( const Vector2& vector );
		
		/// �Լ�
		inline Vector2& operator -= ( const Vector2& vector );
		
		/// �˷�����
		inline Vector2& operator *= ( float scalar );

		/// �Գ�
		inline Vector2& operator *= ( const Vector2& vector );

		Vector2& operator *= ( const Matrix3& matrix );

		/// ��������
		inline Vector2& operator /= ( float scalar );
		
		/// �Գ�
		inline Vector2& operator /= ( const Vector2& vector );
		
		/// ��
		inline Vector2 operator + ( const Vector2& vector ) const;
		
		/// ��
		inline Vector2 operator - ( const Vector2& vector ) const;
		
		/// ������
		inline Vector2 operator * ( float scalar ) const;
		
		/// ��
		inline Vector2 operator * ( const Vector2& vector ) const;

		Vector2 operator * ( const Matrix3& matrix ) const;

		/// ������
		inline Vector2 operator / ( float scalar ) const;
		
		/// ��
		inline Vector2 operator / ( const Vector2& vector ) const;

		/// �����ж�
		bool operator == (const Vector2 &v) const;

		/// �����ж�
		bool operator != (const Vector2 &v) const;

		bool Equal( const Vector2& vector, float margin = Math::cEpsilon ) const;

		/// ��λ��
		Vector2& Normalize( );

		/// ģ
		float Magnitude( ) const;
		
		/// ƽ��ģ
		float MagnitudeSquared( ) const;

		/// ���
		static float DotProduct( const Vector2& vector1, const Vector2& vector2 );
		
		/// ���
		static float CrossProduct( const Vector2& vector1, const Vector2& vector2 );
		
		/// Ͷ��
		static Vector2 Project( const Vector2& vector1, const Vector2& vector2 );
		
		/// ���Բ�ֵ
		static Vector2 Lerp( const Vector2& vector1, const Vector2& vector2, float factor );

		/// ������������
		static float DistanceTo(const Vector2& v1, const Vector2& v2);

		/// ������������ƽ��
		static float DistanceToSqare(const Vector2& v1, const Vector2& v2);

		/// 2D�任
		Vector2& Mul2D( const Matrix3& matrix );
	};



	Vector2::Vector2( )
	{
	}

	Vector2::Vector2( float xx, float yy ) : x( xx ), y( yy )
	{
	}

	Vector2 Vector2::operator + ( ) const
	{
		return Vector2( x, y ); 
	}

	Vector2 Vector2::operator - ( ) const
	{
		return Vector2( -x, -y );
	}

	Vector2& Vector2::operator += ( const Vector2& vector )
	{
		x += vector.x;
		y += vector.y;

		return *this;
	}

	Vector2& Vector2::operator -= ( const Vector2& vector )
	{
		x -= vector.x;
		y -= vector.y;

		return *this;
	}

	Vector2& Vector2::operator *= ( float scalar )
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}

	Vector2& Vector2::operator *= ( const Vector2& vector )
	{
		x *= vector.x;
		y *= vector.y;

		return *this;
	}

	Vector2& Vector2::operator /= ( float scalar )
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	Vector2& Vector2::operator /= ( const Vector2& vector )
	{
		x /= vector.x;
		y /= vector.y;

		return *this;
	}

	Vector2 Vector2::operator + ( const Vector2& vector ) const
	{
		return Vector2( x + vector.x, y + vector.y );
	}

	Vector2 Vector2::operator - ( const Vector2& vector ) const
	{
		return Vector2( x - vector.x, y - vector.y ); 
	}

	Vector2 Vector2::operator * ( float scalar ) const
	{
		return Vector2( x * scalar, y * scalar );
	}

	Vector2 Vector2::operator * ( const Vector2& vector ) const
	{
		return Vector2( x * vector.x, y * vector.y );
	}

	Vector2 Vector2::operator / ( float scalar ) const
	{
		return Vector2( x / scalar, y / scalar );
	}

	Vector2 Vector2::operator / ( const Vector2& vector ) const
	{
		return Vector2( x / vector.x, y / vector.y );
	}

	/** @} */
	/** @} */
}
