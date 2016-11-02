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
		���������
	*/
	class FRect
	{
	public:
		float	left,top,right,bottom;

		/** 
			�վ��Σ����в���Ϊ0
		*/
		const static FRect cNullRect;

		/** 
			���캯��
		*/
		inline FRect( );

		/** 
			���캯��
			@remark
				ʹ��4������ʼ��
		*/
		inline FRect( float ll, float tt, float rr, float bb );

		/** 
			���캯��
			@remark
				ʹ�����Ͻǣ����½ǳ�ʼ��
		*/
		inline FRect( const Vector2& leftTop,const Vector2& rightBottom );

		/** 
			ȡ��
			@return
				���з���ȡ����Ķ���
		*/
		inline FRect operator - ( ) const;

		/** 
			�ж����������Ƿ����
		*/
		inline bool operator == ( const FRect& rect );

		/** 
			�ж����������Ƿ񲻵�
		*/
		inline bool operator != ( const FRect& rect );

		/** 
			�Լ�
			@param
				point ����
		*/
		inline FRect& operator += ( const Vector2& point );

		/** 
			�Լ�
			@param
				point ����
		*/
		inline FRect& operator -= ( const Vector2& point );

		/** 
			�Ӳ���
		*/
		inline FRect operator + ( const Vector2& point ) const;

		/** 
			������
		*/
		inline FRect operator - ( const Vector2& point ) const;

		
		/// ȡ���
		inline float Width( ) const;

		/// ȡ�߶�
		inline float Height( ) const;

		/// ȡ����
		inline Vector2 Center( ) const;

		/// ȡ��С
		inline Vector2 GetSize( ) const;

		/// ȡ����
		inline Vector2 LeftTop( ) const;

		/// ȡ����
		inline Vector2 LeftBottom( ) const;

		/// ȡ����
		inline Vector2 RightTop( ) const;

		/// ȡ����
		inline Vector2 RightBottom( ) const;

		/** 
			ƫ�Ʋ���
			@param
				x ����ƫ��
			@param
				y ����ƫ��
		*/
		inline void Offset( float x,float y);

		/** 
			����,�������	
			@param
				width ����
			@param
				height ����
		*/
		inline void Inflate( float width, float height );

		/** 
			����,�������	
			@param
				size ����
		*/
		inline void Inflate( const Vector2& size );

		/** 
			����,�������	
			@param
				width ����
			@param
				height ����
		*/
		inline void Deflate( float width, float height );

		/** 
			����,�������	
			@param
				size ����
		*/
		inline void Deflate( const Vector2& size );

		/// �ж�һ�����Ƿ��ھ���������
		inline bool PointInRect( const Vector2& point ) const;

		/** 
			ȡ�������򽻼�������
			@param
				rect1 ����1
			@param
				rect2 ����2
			@return
				ȡ����ľ���
		*/
		static FRect Intersect( const FRect& rect1, const FRect& rect2 );

		/** 
			�ϲ�������������
			@param
				rect1 ����1
			@param
				rect2 ����2
			@return
				�ϲ���ľ���
		*/
		static FRect Unite( const FRect& rect1, const FRect& rect2 );
	};

	//----------------------------------------------------------------------------
	// FRect Implementation
	//----------------------------------------------------------------------------

	FRect::FRect( )
	{
	}

	FRect::FRect( float ll, float tt, float rr, float bb ) : left( ll ), top( tt ), right( rr ), bottom( bb )
	{
	}

	FRect::FRect( const Vector2& leftTop,const Vector2& rightBottom ):
	left(leftTop.x),top(leftTop.y),
		right(rightBottom.x),bottom(rightBottom.y)
	{

	}

	FRect FRect::operator - ( ) const
	{
		return FRect( -left, -top, -right, -bottom );
	}

	bool FRect::operator == ( const FRect& rect )
	{
		return left == rect.left && top == rect.top && right == rect.right && bottom == rect.bottom;
	}

	bool FRect::operator != ( const FRect& rect )
	{
		return left != rect.left || top != rect.top || right != rect.right || bottom != rect.bottom;
	}


	FRect& FRect::operator += ( const Vector2& point )
	{
		left += point.x;
		top += point.y;
		right += point.x;
		bottom += point.y;

		return *this;
	}

	FRect& FRect::operator -= ( const Vector2& point )
	{
		left -= point.x;
		top -= point.y;
		right -= point.x;
		bottom -= point.y;

		return *this;
	}

	FRect FRect::operator + ( const Vector2& point ) const
	{
		return FRect( left + point.x, top + point.y, right + point.x, bottom + point.y );
	}

	FRect FRect::operator - ( const Vector2& point ) const
	{
		return FRect( left - point.x, top - point.y, right - point.x, bottom - point.y );
	}

	float FRect::Width( ) const
	{
		return right - left;
	}

	float FRect::Height( ) const
	{
		return bottom - top;
	}

	Vector2 FRect::Center( ) const
	{
		return Vector2( ( left + right ) / 2, ( top + bottom ) / 2 );
	}

	Vector2 FRect::GetSize( ) const
	{
		return Vector2(right - left,bottom - top);
	}

	Vector2 FRect::LeftTop( ) const
	{
		return Vector2( left, top );
	}

	Vector2 FRect::LeftBottom( ) const
	{
		return Vector2( left, bottom );
	}

	Vector2 FRect::RightTop( ) const
	{
		return Vector2( right, top );
	}

	Vector2 FRect::RightBottom( ) const
	{
		return Vector2( right, bottom );
	}

	void FRect::Inflate( float width, float height )
	{
		left -= width;
		right += width;
		top -= height;
		bottom += height;
	}

	void FRect::Inflate( const Vector2& size )
	{
		left -= size.x;
		right += size.x;
		top -= size.y;
		bottom += size.y;
	}

	void FRect::Deflate( float width, float height )
	{
		left += width;
		right -= width;
		top += height;
		bottom -= height;
	}

	void FRect::Deflate( const Vector2& size )
	{
		left += size.x;
		right -= size.x;
		top += size.y;
		bottom -= size.y;
	}

	void FRect::Offset( float x,float y)
	{
		left += x;
		top += y;
		right += x;
		bottom += y;
	}

	bool FRect::PointInRect( const Vector2& point ) const
	{
		return point.x >= left && point.x <= right && point.y >= top && point.y <= bottom;
	}
}
