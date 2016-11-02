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
		������
	*/
	class Rect
	{
	public:
		int	left,top,right,bottom;

		/** 
			�վ��Σ����в���Ϊ0
		*/
		const static Rect cNullRect;

		/** 
			���캯��
		*/
		inline Rect( );

		/** 
			���캯��
			@remark
				ʹ��4������ʼ��
		*/
		inline Rect( int ll, int tt, int rr, int bb );

		/** 
			���캯��
			@remark
				ʹ�����Ͻǣ����½ǳ�ʼ��
		*/
		inline Rect( const Point& leftTop,const Point& rightBottom );

		inline Rect operator + ( ) const;

		/** 
			ȡ��
			@return
				���з���ȡ����Ķ���
		*/
		inline Rect operator - ( ) const;

		/** 
			�ж����������Ƿ����
		*/
		inline bool operator == ( const Rect& rect );

		/** 
			�ж����������Ƿ񲻵�
		*/
		inline bool operator != ( const Rect& rect );

		/** 
			�Լ�
			@param
				point ����
		*/
		inline Rect& operator += ( const Point& point );

		/** 
			�Լ�
			@param
				point ����
		*/
		inline Rect& operator -= ( const Point& point );

		/** 
			�Ӳ���
		*/
		inline Rect operator + ( const Point& point ) const;
		
		/** 
			������
		*/
		inline Rect operator - ( const Point& point ) const;

		/// ȡ���
		inline int Width( ) const;

		/// ȡ�߶�
		inline int Height( ) const;

		/// ȡ����
		inline Point Center( ) const;

		/// ȡ��С
		inline Point GetSize( ) const;

		/// ȡ����
		inline Point LeftTop( ) const;
		
		/// ȡ����
		inline Point LeftBottom( ) const;
		
		/// ȡ����
		inline Point RightTop( ) const;
		
		/// ȡ����
		inline Point RightBottom( ) const;

		/** 
			ƫ�Ʋ���
			@param
				x ����ƫ��
			@param
				y ����ƫ��
		*/
		inline void Offset( int x,int y);


		inline void Offset( const Point& pt );

		/** 
			����,�������	
			@param
				width ����
			@param
				height ����
		*/
		inline void Inflate( int width, int height );
		
		/** 
			����,�������	
			@param
				size ����
		*/
		inline void Inflate( const Point& size );
		
		/** 
			����,�������	
			@param
				width ����
			@param
				height ����
		*/
		inline void Deflate( int width, int height );

		/** 
			����,�������	
			@param
				size ����
		*/
		inline void Deflate( const Point& size );

		/// �ж�һ�����Ƿ��ھ���������
		inline bool PointInRect( const Point& point ) const;

		/** 
			ȡ�������򽻼�������
			@param
				rect1 ����1
			@param
				rect2 ����2
			@return
				ȡ����ľ���
		*/
		static Rect Intersect( const Rect& rect1, const Rect& rect2 );

		/** 
			�ϲ�������������
			@param
				rect1 ����1
			@param
				rect2 ����2
			@return
				�ϲ���ľ���
		*/
		static Rect Unite( const Rect& rect1, const Rect& rect2 );

		/// ����Դ����
		static Rect Clip( const Rect& source, const Rect& cliprc );
	};

	//----------------------------------------------------------------------------
	// Rect Implementation
	//----------------------------------------------------------------------------

	Rect::Rect( )
	{
	}

	Rect::Rect( int ll, int tt, int rr, int bb ) : left( ll ), top( tt ), right( rr ), bottom( bb )
	{
	}

	Rect::Rect( const Point& leftTop,const Point& rightBottom ):
	left(leftTop.x),top(leftTop.y),
	right(rightBottom.x),bottom(rightBottom.y)
	{

	}

	Rect Rect::operator + ( ) const
	{
		return Rect( left, top, right, bottom );
	}

	Rect Rect::operator - ( ) const
	{
		return Rect( -left, -top, -right, -bottom );
	}

	bool Rect::operator == ( const Rect& rect )
	{
		return left == rect.left && top == rect.top && right == rect.right && bottom == rect.bottom;
	}

	bool Rect::operator != ( const Rect& rect )
	{
		return left != rect.left || top != rect.top || right != rect.right || bottom != rect.bottom;
	}


	Rect& Rect::operator += ( const Point& point )
	{
		left += point.x;
		top += point.y;
		right += point.x;
		bottom += point.y;

		return *this;
	}

	Rect& Rect::operator -= ( const Point& point )
	{
		left -= point.x;
		top -= point.y;
		right -= point.x;
		bottom -= point.y;

		return *this;
	}

	Rect Rect::operator + ( const Point& point ) const
	{
		return Rect( left + point.x, top + point.y, right + point.x, bottom + point.y );
	}

	Rect Rect::operator - ( const Point& point ) const
	{
		return Rect( left - point.x, top - point.y, right - point.x, bottom - point.y );
	}

	int Rect::Width( ) const
	{
		return right - left;
	}

	int Rect::Height( ) const
	{
		return bottom - top;
	}

	Point Rect::Center( ) const
	{
		return Point( ( left + right ) / 2, ( top + bottom ) / 2 );
	}

	Point Rect::GetSize( ) const
	{
		return Point(right - left,bottom - top);
	}

	Point Rect::LeftTop( ) const
	{
		return Point( left, top );
	}

	Point Rect::LeftBottom( ) const
	{
		return Point( left, bottom );
	}

	Point Rect::RightTop( ) const
	{
		return Point( right, top );
	}

	Point Rect::RightBottom( ) const
	{
		return Point( right, bottom );
	}

	void Rect::Inflate( int width, int height )
	{
		left -= width;
		right += width;
		top -= height;
		bottom += height;
	}

	void Rect::Inflate( const Point& size )
	{
		left -= size.x;
		right += size.x;
		top -= size.y;
		bottom += size.y;
	}

	void Rect::Deflate( int width, int height )
	{
		left += width;
		right -= width;
		top += height;
		bottom -= height;
	}

	void Rect::Deflate( const Point& size )
	{
		left += size.x;
		right -= size.x;
		top += size.y;
		bottom -= size.y;
	}

	void Rect::Offset( int x,int y)
	{
		left += x;
		top += y;
		right += x;
		bottom += y;
	}

	void Rect::Offset(  const Point& pt )
	{
		left += pt.x;
		top += pt.y;
		right += pt.x;
		bottom += pt.y;
	}
	

	bool Rect::PointInRect( const Point& point ) const
	{
		return point.x >= left && point.x <= right && point.y >= top && point.y <= bottom;
	}

	/** @} */
	/** @} */
}
