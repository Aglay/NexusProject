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
		���װ��
	*/
	class Point
	{
	public:

		union
		{
			struct 
			{
				int x, y;
			};

			struct 
			{
				int width,height;
			};
		};

		/// ���
		const static Point cZero;

		/// ��������0x7FFFFFFF, 0x7FFFFFFF
		const static Point cMaxPoint;

		/// ������С��0x80000001, 0x80000001
		const static Point cMinPoint;

		/// ����
		inline Point( );

		/// ��ֵ����
		inline Point( int xx, int yy );


		inline Point operator + ( ) const;

		/// ȡ��
		inline Point operator - ( ) const;

		/// �ж����
		inline bool operator == ( const Point& point ) const;

		/// �ж�����
		inline bool operator != ( const Point& point ) const;

		/// �Լ�
		inline Point& operator += ( const Point& point );

		/// �Լ�
		inline Point& operator -= ( const Point& point );

		/// ��
		inline Point operator + ( const Point& point ) const;

		/// ��
		inline Point operator - ( const Point& point ) const;

		/// ��
		inline Point Point::operator * ( int scale ) const;

		/// ��
		inline Point Point::operator / ( int scale ) const;

		/// �����������
		static int DistanceTo(const Point& v1, const Point& v2);

		/// �����������ƽ��
		static int DistanceToSqare(const Point& v1, const Point& v2);
	};

	//----------------------------------------------------------------------------
	// Point Implementation
	//----------------------------------------------------------------------------

	Point::Point( )
	{
	}

	Point::Point( int xx, int yy ) : x( xx ), y( yy )
	{
	}

	Point Point::operator + ( ) const
	{
		return Point( x, y ); 
	}

	Point Point::operator - ( ) const
	{
		return Point( -x, -y );
	}

	bool Point::operator == ( const Point& point ) const
	{
		return x == point.x && y == point.y;
	}

	bool Point::operator != ( const Point& point ) const
	{
		return x != point.x || y != point.y;
	}

	Point& Point::operator += ( const Point& point )
	{
		x += point.x;
		y += point.y;

		return *this;
	}

	Point& Point::operator -= ( const Point& point )
	{
		x -= point.x;
		y -= point.y;

		return *this;
	}

	Point Point::operator + ( const Point& point ) const
	{
		return Point( x + point.x, y + point.y );
	}

	Point Point::operator - ( const Point& point ) const
	{
		return Point( x - point.x, y - point.y );
	}


	Point Point::operator * ( int scale ) const
	{
		return Point( x * scale, y * scale );
	}

	Point Point::operator / ( int scale ) const
	{
		return Point( x / scale, y / scale );
	}

	/** @} */
	/** @} */
};

