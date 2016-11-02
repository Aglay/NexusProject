#pragma once

namespace NekoEngine
{
	/** 
		������������
	*/
	enum eVertexDataType
	{
		VDT_Float1 = 1,
		VDT_Float2,
		VDT_Float3,
		VDT_Float4,
		VDT_Color,
	};

	/** 
		������;
	*/
	enum eVertexUsage
	{
		VU_Position = 1,
		VU_Normal,
		VU_Diffuse,
		VU_Specular,
		VU_TexCoord,
		VU_PositionRHW,
		VU_Blend_Indices,
		VU_Blend_Weights,
		VU_Binormal,
		VU_Tangent,
	};

	/** 
		����Ԫ��
	*/
	#pragma pack(push,1)
		struct VertexElement
		{
			eVertexDataType	mDataType;
			eVertexUsage	mUsage;
			word			mStreamIndex;
			word			mStride;		// �ռ任�ٶ�
			word			mUsageIndex;

			VertexElement( ){}

			VertexElement( word StreamIndex,  eVertexDataType DataType, eVertexUsage Usage, word UsageIndex = 0 );

			friend BinarySerializer& operator <<( NekoEngine::BinarySerializer& Ser, VertexElement& Data )
			{
				if ( Ser.IsLoading() )
				{
					dword DataType, Usage;
					Ser << DataType << Usage;
					Data.mDataType = (eVertexDataType)DataType;
					Data.mUsage = (eVertexUsage)Usage;
				}
				else
				{
					Ser << (dword)Data.mDataType
						<< (dword)Data.mUsage;
				}
				
				Ser << Data.mStreamIndex
					<< Data.mStride
					<< Data.mUsageIndex;

				return Ser;
			}
		};

	#pragma pack(pop)

	/** 
		�����ʽ,Ϊ����Ӳ���Ĳ���
	*/
	class VertexFormat 
	{
	public:
		enum{ MaxVertexElementCount = 16,
			MaxStreamCount = 16,
		};

		VertexFormat( );

		~VertexFormat( );

		VertexFormat( const VertexFormat& vfp );

		bool operator == ( const VertexFormat& vfp  ) const;

		/** 
			��Ӷ����ʽ
			@remark
				�Զ�����offset
		*/
		void Add( word StreamIndex, eVertexDataType DataType, eVertexUsage Usage, word UsageIndex = 0  );

		void Add( const VertexElement& Element );

		/// ������¼���
		void Clear( );

		/** 
			��ȡ�������͵Ŀ��
		*/
		static word GetElementStride( eVertexDataType type );

		/** 
			ȡһ��Ԫ��
		*/
		const VertexElement& GetElement( dword i ) const;

		/** 
			ȡԪ������
		*/
		dword GetElementCount( ) const;

		/** 
			ȡһ���Ŀ��
		*/
		dword GetTotalStride( word StreamIndex ) const;

		/** 
			ȡĳһ��Ԫ�ص�ƫ��
		*/
		dword GetElementOffset( eVertexUsage Usage, word UsageIndex = 0 ) const;

		/// ���������л�����������
		friend BinarySerializer& operator <<( NekoEngine::BinarySerializer& Ser, VertexFormat& Data )
		{
			Ser << Data.mVertexElementArray;

			return Ser;
		}

	private:
		typedef std::vector< VertexElement > VertexElementArray;
		VertexElementArray mVertexElementArray;
	};


}
