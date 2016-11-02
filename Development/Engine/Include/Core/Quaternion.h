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
		��Ԫ��
	*/
	class Quaternion
	{
	public:
		float	x,y,z,w;

		/// ��Ԫ��Ԫ��
		const static Quaternion cIdentity;

		/// ����Ԫ��
		const static Quaternion cZero;

		/// ����
		inline Quaternion( );

		/// ��ֵ����
		inline Quaternion( float xx, float yy, float zz, float ww );

		/// ��
		inline Quaternion operator + ( ) const;

		/// ��
		inline Quaternion operator - ( ) const;

		/// �Գ�
		Quaternion& operator *= ( const Quaternion& quaternion );

		/// �Գ�
		Quaternion& operator /= ( const Quaternion& quaternion );

		/// ��
		Quaternion operator * ( const Quaternion& quaternion ) const;

		/// ��
		Vector3 operator* (const Vector3& v) const;

		/// ��
		Quaternion operator / ( const Quaternion& quaternion ) const;

		/// ���
		float operator | ( const Quaternion& v ) const;

		/// ���
		bool operator == ( const Quaternion& quaternion) const;

		/// ��λ������ʼ����
		Quaternion& Identity( );

		/// ��λ��
		Quaternion& Normalize( );

		/// ȡ��
		Quaternion Inverse () const;

		/// ģ
		float Magnitude( ) const;

		/// ������ģ
		float MagnitudeSquared( ) const;

		Quaternion& FromMatrix( const Matrix4& m );

		/// ��X��ת
		Quaternion& RotationX( float radian );
		
		/// ��Y��ת
		Quaternion& RotationY( float radian );

		/// ��Z��ת
		Quaternion& RotationZ( float radian );
		
		/// ����ת
		Quaternion& RotationAxis( const Vector3& axis, float radian );
		
		/// ��һ����Ԫ��ʹ��һ��ʸ��������������һ��ʸ��
		Quaternion& Rotation( const Vector3& srcvector, const Vector3& desvector );

		/// ȡ����ת�����ת��
		void GetAxisAndAngle( Vector3& axis, float& radian ) const;

		/// ��ȡ���ؿռ��X�����
		Vector3 GetXAxis( ) const;

		/// ��ȡ���ؿռ��Y�����
		Vector3 GetYAxis( ) const;

		/// ��ȡ���ؿռ��Z�����
		Vector3 GetZAxis( ) const;

		/// 3�ṹ��
		Quaternion& FromAxes (const Vector3& xaxis, const Vector3& yaxis, const Vector3& zaxis);

		/// ����
		static float DotProduct( const Quaternion& quaternion1, const Quaternion& quaternion2 );

		/// ƽ�����߲�ֵ
		static Quaternion Slerp( const Quaternion& quaternion1, const Quaternion& quaternion2, float factor );
		
	};

	//----------------------------------------------------------------------------
	// Quaternion Implementation
	//----------------------------------------------------------------------------

	Quaternion::Quaternion( )
	{
	}

	Quaternion::Quaternion( float xx, float yy, float zz, float ww )
		: x( xx ), y( yy ), z( zz ), w( ww )
	{
	}

	Quaternion Quaternion::operator + ( ) const
	{
		return Quaternion( x, y, z, w );
	}

	Quaternion Quaternion::operator - ( ) const
	{
		return Quaternion( -x, -y, -z, w );
	}

	/** @} */
	/** @} */
}
