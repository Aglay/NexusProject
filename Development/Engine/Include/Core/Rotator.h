#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Math
	*  @{
	*/

	class Quaternion;
	class Vector3;

	/** 
		��ת��	
	*/
	class Rotator
	{
	public:
		// Variables.
		int Pitch; // Looking up and down (0=Straight Ahead, +Up, -Down).
		int Yaw;   // Rotating around (running in circles), 0=East, +North, -South.
		int Roll;  // Rotation about axis of screen, 0=Straight, +Clockwise, -CCW.

		/// ���캯��
		Rotator() {}

		/// ��ֵ����
		Rotator( int InPitch, int InYaw, int InRoll )
			:	Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}

		/// ��������
		Rotator( const Quaternion& Quat );

		/// �Ӳ���
		Rotator operator+( const Rotator &R ) const
		{
			return Rotator( Pitch+R.Pitch, Yaw+R.Yaw, Roll+R.Roll );
		}

		/// ������
		Rotator operator-( const Rotator &R ) const
		{
			return Rotator( Pitch-R.Pitch, Yaw-R.Yaw, Roll-R.Roll );
		}

		/// �˲���
		Rotator operator*( float Scale ) const
		{
			return Rotator( int(Pitch*Scale), int(Yaw*Scale), int(Roll*Scale) );
		}

		/// �Գ�
		Rotator operator*= (float Scale)
		{
			Pitch = int(Pitch*Scale); Yaw = int(Yaw*Scale); Roll = int(Roll*Scale);
			return *this;
		}
		
		/// ����ж�
		bool operator==( const Rotator &R ) const
		{
			return Pitch==R.Pitch && Yaw==R.Yaw && Roll==R.Roll;
		}

		/// �����ж�
		bool operator!=( const Rotator &V ) const
		{
			return Pitch!=V.Pitch || Yaw!=V.Yaw || Roll!=V.Roll;
		}
		
		/// �Լ�
		Rotator operator+=( const Rotator &R )
		{
			Pitch += R.Pitch; Yaw += R.Yaw; Roll += R.Roll;
			return *this;
		}

		/// �Լ�
		Rotator operator-=( const Rotator &R )
		{
			Pitch -= R.Pitch; Yaw -= R.Yaw; Roll -= R.Roll;
			return *this;
		}
		
		// Functions.
		Rotator Reduce() const
		{
			return Rotator( MathTable::ReduceAngle(Pitch), MathTable::ReduceAngle(Yaw), MathTable::ReduceAngle(Roll) );
		}


		/// �Ƿ�Ϊ��
		int IsZero() const
		{
			return ((Pitch&65535)==0) && ((Yaw&65535)==0) && ((Roll&65535)==0);
		}

		/// ������
		Rotator Add( int DeltaPitch, int DeltaYaw, int DeltaRoll )
		{
			Yaw   += DeltaYaw;
			Pitch += DeltaPitch;
			Roll  += DeltaRoll;
			return *this;
		}

		Vector3 ToVector() const;

		Quaternion ToQuaternion() const;

		Vector3 ToEuler() const;

		Rotator& FromEuler(const Vector3& Euler);

		/// Լ�������ڷ�Χ -65535,65535
		Rotator Clamp() const
		{
			return Rotator( Pitch&65535, Yaw&65535, Roll&65535 );
		}

		Rotator ClampPos() const
		{
			return Rotator( Math::Abs(Pitch)&65535, Math::Abs(Yaw)&65535, Math::Abs(Roll)&65535 );
		}

		static int NormalizeAxis(int Angle)
		{
			Angle &= 0xFFFF;
			if( Angle > 32767 ) 
			{
				Angle -= 0x10000;
			}
			return Angle;
		}

		/** Normalize stuff from execNormalize so we can use it in C++ */
		Rotator Normalize() const
		{
			Rotator Rot = *this;
			Rot.Pitch = NormalizeAxis(Rot.Pitch);
			Rot.Roll = NormalizeAxis(Rot.Roll);
			Rot.Yaw = NormalizeAxis(Rot.Yaw);
			return Rot;
		}

		Rotator Denormalize() const
		{
			Rotator Rot = *this;
			Rot.Pitch	= Rot.Pitch & 0xFFFF;
			Rot.Yaw		= Rot.Yaw & 0xFFFF;
			Rot.Roll	= Rot.Roll & 0xFFFF;
			return Rot;
		}

		void MakeShortestRoute();

		void GetWindingAndRemainder(Rotator& Winding, Rotator& Remainder) const;
	};

	/** @} */
	/** @} */
}
