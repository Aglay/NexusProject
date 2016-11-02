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
		������ѧ���װ
	*/
	class Math
	{
	public:
		/** 
			����ת�Ƕ�
			@param
				radian ����
			@return
				�Ƕ�
		*/
		static float ToDegree( float radian );

		/// ���㷴����
		static float ArcCos( float r );

		/// ���㷴����
		static float ArcSin( float r );

		/// ���㷴����
		static float ArcTan( float r );

		/// ���㷴����˫����
		static float ArcTan2( float y, float x );

		/// ��������
		static float Sin( float r );

		/// ��������
		static float Cos( float r );

		/// ��������
		static float Tan( float r );

		/// ��������
		static float Cot( float r );

		/// �Ƕ�ת����
		static float ToRadian( float degree );

		/// ����ƽ����
		static float Sqrt( float r );

		/// ����ƽ��������
		static float InvSqrt(float fValue);

		/// ����ƽ��������
		static float Rsq( float r );

		/// ����ƽ��������
		static float Apx_rsq( float r );

		/// ��10Ϊ��ȡLog
		static float Ln(float r);

		/// ��������
		static float Fmod(float x,float y);	

		/// ����ָ��
		static float Pow( float x, float y );

		/// ����ָ��
		static dword Pow( dword x, dword y );

		/// �������������
		static void RandomSeed( dword seed );

		/// α�����
		static dword Random( );

		/// ���������Χ[0,maxvalue]
		static dword Random( dword maxvalue );

		/// ���������Χ[minvalue,maxvalue]
		static dword RandomRange( dword minvalue, dword maxvalue );

		/// ���������Χ[minvalue,maxvalue]
		static float RandomFloat( float minvalue, float maxvalue );

		/// ��������� -1��1
		static long RandomSign( );

		/// �Գ������ [-1,1]
		static float RandomSymmetric();

		/// �õ�target����С2����
		static dword NearToPower2( dword target );

		/// result = log2(arg) arg��2����
		static dword CeilLogTwo( dword Arg );

		/** 
			�ж��������Ƿ����
			@param
				Magin �ж�����
		*/
		static bool Equal( float A, float B, float Magin = Math::cEpsilon );

		/** 
			��ֵ���뵽��ӽ���������ָ����С��λ����
		*/
		static int Round( float Number );

		/// ȡ����������������
		static int Floor( float Number );

		/// ȡ��������С������
		static int Ceil(float Number);

		/// Pi = 3.141592654
		static const float cPi;

		/// 2 Pi = 6.283185308
		static const float c2Pi;

		/// 0.5 Pi = 1.570796327
		static const float cHalfPi;

		/// Pi / 180
		static const float cDeg2Rad;

		/// 180 / Pi
		static const float cRad2Deg;

		/// ��Ȼ�������� 2.718281828
		static const float cE;

		/// ��󸡵��� 3.402823466e+38
		static const float cMaxFloat;

		/// ��С������ -3.402823466e+38
		static const float cMinFloat;

		/// ��С���� 0.00001
		static const float cEpsilon;

		/// ����޷������� 4294967295
		static const dword cMaxDowrd;

		/// ����з������� 2147483647
		static const dword cMaxInt;

		/// ȡ����ֵ
		template< class T > static T Abs( const T A )
		{
			return (A>=(T)0) ? A : -A;
		}

		/** 
			ȡ��������
			@param
				A ��
			@return
				����Ϊ1������Ϊ-1��0Ϊ0
		*/
		static int Sign( int A )
		{
			return (A>0) ? 0 : ((A<0) ? -1 : 0);
		}

		/** 
			ȡ����������
			@param
				A ��
			@return
				����Ϊ1������Ϊ-1��0Ϊ0
		*/
		static float Sign( const float A )
		{
			return ( A>0.0f ) ? 1.0f : ((A<0.0f) ? -1.0f : 0.0f );
		}

		/// ȡA,B������߷���
		template< class T > static T Max( const T A, const T B )
		{
			return (A>=B) ? A : B;
		}

		/// ȡA,B����С�߷���
		template< class T > static T Min( const T A, const T B )
		{
			return (A<=B) ? A : B;
		}

		/// ȡA,B,c������߷���
		template< class T > static T Max3( const T A, const T B, const T C )
		{
			return Max ( Math::Max( A, B ), C );
		}

		/// ȡA,B,C����С�߷���
		template< class T > static T Min3( const T A, const T B, const T C )
		{
			return Min ( Math::Min( A, B ), C );
		}

		/// ����A��ƽ��
		template< class T > static T Square( const T A )
		{
			return A*A;
		}

		/// ����X���޶���Min��Max֮���ֵ
		template< class T > static T Clamp( const T X, const T Min, const T Max )
		{
			return X<Min ? Min : X<Max ? X : Max;
		}

		/// ���ر������ֵ
		template< class T > static T Align( const T Ptr, dword Alignment )
		{
			return (T)(((dword)Ptr + Alignment - 1) & ~(Alignment-1));
		}

		/// ������ֵ
		template< class T > static void Swap( T& A, T& B )
		{
			const T Temp = A;
			A = B;
			B = Temp;
		}

		/// ���Բ�ֵ
		template< class T > static T Lerp( T& A, T& B, float S )
		{
			return (T)(A + S * (B-A));
		}
		
	};

	
	class Guid
	{
	public:
		dword A,B,C,D;

		Guid();

		Guid( dword InA, dword InB, dword InC, dword InD );

		bool IsValid() const;

		friend bool operator==(const Guid& X, const Guid& Y);
		friend bool operator!=(const Guid& X, const Guid& Y);

		friend dword GetTypeHash(const Guid& guid)
		{
			return CheckSum::MemCRC(&guid,sizeof(Guid));
		}

		static Guid Create();

		static const Guid cNull;
	};


	class MathTable
	{
	public:
		// Constants.
		enum {ANGLE_SHIFT 	= 2};		// Bits to right-shift to get lookup value.
		enum {ANGLE_BITS	= 14};		// Number of valid bits in angles.
		enum {NUM_ANGLES 	= 16384}; 	// Number of angles that are in lookup table.
		enum {ANGLE_MASK    =  (((1<<ANGLE_BITS)-1)<<(16-ANGLE_BITS))};

		// Basic math functions.
		static float SinTab( int i ) ;
		static float CosTab( int i ) ;
		static float SinFloat( float F ) ;
		static float CosFloat( float F ) ;

		static void StaticInit( );

		static int ReduceAngle( int Angle );;

	private:
		// Tables.
		static float	mTrigFLOAT		[NUM_ANGLES];
		static bool		mInitialized;
	};

	/** @} */
	/** @} */
}
