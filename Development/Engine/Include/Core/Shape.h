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
		����
	*/
	class Ray
	{
	public:
		/// ���캯��
		Ray( );

		/** 
			���캯��
			@param
				origin ���߷����
			@param
				direction ����
		*/
		Ray( const Vector3& origin, const Vector3& direction );

		/** 
			���캯��
			@param
				x ��Ļ����
			@param
				y ��Ļ����
			@param
				viewtransform �۲����
			@param
				projectiontransform Ͷ�����
		*/
		Ray( float x, float y, const Matrix4& viewtransform, const Matrix4& projectiontransform );

		/// ���ұ任�ռ�
		Ray& operator *= ( const Matrix4& matrix );

		/// �任�ռ�
		Ray  operator * ( const Matrix4& matrix ) const;

		/// ���ݾ��룬ȷ�������ϵ�һ����
		Vector3 DistanceVector( float distance ) const;

		/// ȡ���߷���
		const Vector3& GetDirection( ) const{ return mDirection; }

		/// ȡ����λ��
		const Vector3& GetOrigin( ) const { return mOrigin; }

	private:
		Vector3		mOrigin;
		Vector3		mDirection;

	};

	/** 
		��Գư󶨺�
	*/
	class AABB
	{
	public:
		/// �պ���min = 0, max=0
		const static AABB cNullBox;

		/// ��ʼ���ĺ��� min=maxfloat, max = minfloat
		const static AABB cInitBox;

		/// ������ min=minfloat, max = maxfloat
		const static AABB cMaxBox;

		Vector3		mMinVector;
		Vector3		mMaxVector;

		/// ���캯��
		AABB( );


		/// ��ֵ���캯��
		AABB( const Vector3& minvector, const Vector3& maxvector );

		/// ��Ӻ���
		AABB& operator += ( const AABB& box );

		/// ���һ����
		AABB& operator += ( const Vector3& vector );

		/// �任�ռ�
		AABB& operator *= ( const Matrix4& matrix );

		/// ���
		bool operator == ( const AABB& box ) const;

		/// ����
		bool operator != ( const AABB& box ) const;

		/// ��Ӻ���
		AABB operator + ( const AABB& box ) const;

		/// ��ӵ�
		AABB operator + ( const Vector3& vector ) const;

		/// �任����
		AABB operator * ( const Matrix4& matrix ) const;

		/// ���Ƿ��ں�����
		bool VectorInBox( const Vector3& vector ) const;

		/// ȡ����
		Vector3 GetCenter( ) const;

		/// ȡ��С
		Vector3 GetSize( ) const;

		/// ȡ���С
		Vector3 GetHalfSize( ) const;

	};

	
	/** 
		����
	*/
	class Box
	{
	public:

		/// ����ö�ٶ���
		enum eBoxEnum
		{ 
			MaxPoints = 8,											///< ����ӵ�е�����
			MaxPointConnectSide = 3,								///< ������ÿ�����ӵı���
			MaxNoneSharedPoint = MaxPoints * MaxPointConnectSide,	///< �ǹ������=24
			MaxSides = MaxNoneSharedPoint /2,						///< ���ӵı���=12
		};

		Vector3		mCornerPoint[MaxPoints];

		/// ���캯��
		Box( );

		/// �������캯��
		Box( const AABB& box );

		/// �任
		Box& operator *= ( const Matrix4& matrix );

		/// �任
		Box operator * ( const Matrix4& matrix ) const;

		/// ��ȡ���Ʊߵ�����
		static dword GetSideIndex( dword Index );

		union NeighbourIndex
		{
			struct  
			{
				dword mNeighbourX;
				dword mNeighbourY;
				dword mNeighbourZ;
			};

			dword mNeighbourPoint[3];
		};

		/// ȡ�����ڵ������
		static const NeighbourIndex& GetNeighbourIndex( dword Index );
	};

	/** 
		��
	*/
	class Sphere
	{
	public:
		Vector3		mCenter;
		float		mRadius;

		/// ���캯��
		Sphere( );

		/// ��ֵ���캯��
		Sphere( const Vector3& center, float radius );

		/// �任
		Sphere& operator *= ( const Matrix4& matrix );

		/// �任
		Sphere operator * ( const Matrix4& matrix ) const;
	};




	/** 
		������
	*/
	class Triangle
	{
	public:
		union
		{
			struct
			{
				Vector3 mPoint[3];
			};


			struct
			{
				Vector3 mP1,mP2,mP3;
			};
		};
		
		/// ���캯��
		Triangle( );

		/// ��ֵ����
		Triangle(const Vector3& p1,const Vector3& p2,const Vector3& p3);

		/// ���
		static inline float CrossProduct3(const Vector3& p1,const Vector3& p2, const Vector3& p0 );

		/// �ж�һ���Ƿ�����������
		bool Inside(float x,float y);


		/** 
			���ߴ���������
			@remark
				�����������꣨U,V��,���ǿ��Ժ����׵�������������������������ͽ���Ĳ�ֵ��ɫ����������������Ϊ����V1,V2,V3����������ֱ�ΪT1(tu1,tv1),T2(tu2,tv2),T3(tu3,tv3)�򽻵������Ϊ		
			@par
				IntersectPointTexture = T1 + U(T2-T1) + V(T3-T1)
			@param
				ray ����
			@param
				distance ���嵽�ľ���
			@param
				tU �����������ϵ�����
			@param
				tV �����������ϵ�����
			@return
				�Ƿ񴩲嵽

		*/
		bool Intersect( const Ray& ray,float& distance,float* tU = null,float* tV = null);

		/// ���������
		float Area( );


		
	};

	/** 
		ƽ��������
	*/
	class Triangle2D
	{
	public:
		union
		{
			struct
			{
				Vector2 mPoint[3];
			};


			struct
			{
				Vector2 mP1,mP2,mP3;
			};
		};

		/// ���캯��
		Triangle2D( );

		/// ��ֵ���캯��
		Triangle2D(const Vector2& p1,const Vector2& p2,const Vector2& p3);

		/// �ж�һ�����Ƿ�����������
		bool Inside( const Vector2& p );

		/** 
			�ж�һ�����Ƿ�����������
			@remark
				��Դ:IndieLib
		*/
		bool Inside2( const Vector2& p );

		/// �������
		float Area( );

		/// ���
		static float CrossProduct3(const Vector2& p1,const Vector2& p2, const Vector2& p0 );
		
	};

	/** 
		ƽ���߶�
	*/
	class Segement2D
	{
	public:
		/// �ж�4�㹹�ɵ������߶��Ƿ��ཻ
		static bool Intersect( const Vector2& p1, const Vector2& p2,const Vector2& p3, const Vector2& p4 );

		/// ȡ��2���߶εĽ����
		static Vector2 GetCrossPoint(const Vector2& p1, const Vector2& p2, const Vector2& q1, const Vector2& q2);
	};

	/** 
		��������

		˳����밴����������
			0   1
			-----
			|   |
			|   |
			-----
			3   2
	*/
	class Quadrangle
	{
	public:

		union
		{
			struct
			{
				Vector2 mPoint[4];
			};


			struct
			{
				Vector2 mP1,mP2,mP3,mP4;
			};
		};

		Quadrangle( );

		Quadrangle( Vector2* pointlist );

		Quadrangle( const Vector2& p1, const Vector2& p2, const Vector2& p3,const Vector2& p4 );

		/// �������κ�͹4���Σ�ʹ���߶��ཻ�жϣ��ٶ�������100%׼ȷ
		bool Inside( const Vector2& p );
	};

	/** 
		ƽ��
	*/
	class Plane
	{
	public:
		union
		{
			struct
			{
				Vector3 n;
				float d;
			};
			struct
			{
				float a, b, c, d;	/// ax + by + cz + d = 0
			};
		};

		Plane( ){}

		Plane(float InA,float InB,float InC,float InD) :a(InA),b(InB),c(InC),d(InD){}

		Plane( const Vector3& position, const Vector3& normal );

		Plane( const Vector3& vector1, const Vector3& vector2, const Vector3& vector3 );

		Plane operator + ( ) const;

		Plane operator - ( ) const;

		Vector3 Normal( ) const;

		float Distance( const Vector3& vector ) const;

		// This gives you the element of the input vector that is perpendicular 
		// to the normal of the plane. You can get the element which is parallel
		// to the normal of the plane by subtracting the result of this method
		// from the original vector, since parallel + perpendicular = original.
		Vector3 ProjectVector(const Vector3& p) const;


		enum eSide
		{
			NoSide,
			PositiveSide,
			NegativeSide,
			BothSide,
		};
		
		Plane::eSide GetSide( const Vector3& Center, const Vector3& HalfSize ) const;

		static bool Intersect(const Ray& ray, const Plane& plane, float& distance);

		static bool IntersectResult(const Ray& ray, const Plane& plane,Vector3& out);
		
		static const Plane cXYPlane;
		static const Plane cXZPlane;
		static const Plane cYZPlane;

	};

	enum eFrustumPlane
	{
		FrustumPlane_Front = 0,
		FrustumPlane_Back,
		FrustumPlane_Left,
		FrustumPlane_Right,
		FrustumPlane_Top,
		FrustumPlane_Bottom,
		MaxFrustumPlane,
	};

	/**
		6ƽ�湹�������壬��������׶
	*/
	class PlaneBoundedVolume
	{
	public:
		Plane		mPlanes[6];

		Vector3		mVectors[8];


		PlaneBoundedVolume( ){ }

		PlaneBoundedVolume(	const Ray& RayTopLeft, 
					const Ray& RayTopRight, 
					const Ray& RayBottomLeft, 
					const Ray& RayBottomRight, 
					float FrontDistance, 
					float BackDistance );

		bool Inside( const AABB& box ) const;
		bool Inside( const Box& box ) const;
	};


	/** 
		��׶
	*/
	class Frustum : public PlaneBoundedVolume
	{
	public:
		Frustum( );

		Frustum( const Matrix4& viewtransform, const Matrix4& projectiontransform );

		float Depth( ) const;
	};

	/** @} */
	/** @} */
}
