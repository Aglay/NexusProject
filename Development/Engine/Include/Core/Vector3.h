#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Math
	*  @{
	*/


	class Matrix4;
	class Quaternion;

	/** 
		ʸ��3
	*/
	class Vector3
	{
	public:
		float x, y, z;

		/// ��
		static const Vector3 cZero;

		/// x=1
		static const Vector3 cXAxis;

		/// y=1
		static const Vector3 cYAxis;

		/// z=1
		static const Vector3 cZAxis;

		/// x,y,z=1
		static const Vector3 cOne;

		/// ����
		Vector3( );

		/// �������캯��
		Vector3(const Vector3 &v);

		/// 3ֵ��ʼ��
		Vector3(float nx, float ny, float nz);

		/// ��ʸ��
		Vector3 operator + ( ) const;

		/// ��ʸ��
		Vector3 operator - ( ) const;

		/// �Լ�
		Vector3& operator += (const Vector3 &v);

		/// �Լ�
		Vector3& operator -= (const Vector3 &v);

		/// ����
		Vector3& operator *= ( float scalar );

		/// �Գ�
		Vector3& operator *= ( const Vector3& vector );

		/// ����
		Vector3& operator /= ( float scalar );

		/// �Գ�
		Vector3& operator /= ( const Vector3& vector );

		/// �Գ˾���
		Vector3& operator *= ( const Matrix4& matrix );

		/// �Գ���Ԫ��
		Vector3& operator *= ( const Quaternion& quaternion );

		/// ��ʸ��
		Vector3 operator + ( const Vector3& vector ) const;

		/// ��ʸ��
		Vector3 operator - ( const Vector3& vector ) const;

		/// ����
		Vector3 operator * ( float scalar ) const;

		/// �˷�,�ǵ��
		Vector3 operator * ( const Vector3& vector ) const;

		/// ����
		Vector3 operator / ( float scalar ) const;

		/// ����
		Vector3 operator / ( const Vector3& vector ) const;

		/// �˾���
		Vector3 operator * ( const Matrix4& matrix ) const;

		/// ����Ԫ��
		Vector3 operator * ( const Quaternion& quaternion ) const;

		/// ��ֵ
		Vector3 &operator = (const Vector3 &v);

		/// �����ж�
		bool operator == (const Vector3 &v) const;

		/// �����ж�
		bool operator != (const Vector3 &v) const;

		float operator | ( const Vector3& v) const;

		bool Equal( const Vector3& vector, float margin = Math::cEpsilon ) const;

		/// ��λ��
		Vector3& Normalize( );

		/// ��ģ
		float Magnitude( ) const;

		/// δ����ģ
		float MagnitudeSquared( ) const;

		/// ȡ3�������
		float GetMax( ) const;

		/// ȡ3����С��
		float GetMin( ) const;

		/// ����ֵ�����
		Vector3& MakeMax(const Vector3& p);

		/// ����ֵ��С��
		Vector3& MakeMin(const Vector3& p);

		Vector3& TransformCoord(const Vector3& v, const Matrix4 &mat);

		Vector3 Perpendicular(void) const;

		Vector3 RandomDeviant(float angle,const Vector3& up = Vector3::cZero ) const;

		/// ���
		static float DotProduct(const Vector3& v1, const Vector3& v2);

		/// ���
		static Vector3 CrossProduct(const Vector3& v1, const Vector3& v2);

		/// 2������
		static float DistanceTo(const Vector3& v1, const Vector3& v2);

		/// 2���ƽ������
		static float DistanceToSqare(const Vector3& v1, const Vector3& v2);

		/// ���Բ�ֵ
		static Vector3 Lerp(const Vector3& v1,const Vector3& v2,float s);

		/// ����3��ȷ��������
		static void BuildTangentSpaceVector(	   const Vector3& position1
												,  const Vector3& position2
												,  const Vector3& position3
												,	float u1
												,  float v1
												,  float u2
												,  float v2
												,  float u3
												,  float v3
												,  Vector3& OutTangent
												,  Vector3& OutBinormal );

		/// ͶӰ
		Vector3 Project( const Vector3& vector1, const Vector3& vector2 );		
	};

	/** @} */
	/** @} */
}


