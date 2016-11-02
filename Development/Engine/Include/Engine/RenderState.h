#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Render
	*  @{
	*/


	/** 
		����������
	*/
	enum eSamplerFilter
	{
		SF_Nearest,				///< ��������
		SF_Linear,				///< ���Բ���
		SF_AnisotropicLinear	///< �������Բ���
	};

	/** 
		������Ѱַ��ʽ
	*/
	enum eSamplerAddressMode
	{
		AM_Wrap,				///< ��װ
		AM_Clamp,				///< �ü�
		AM_Mirror				///< ����
	};

	/** 
		��դ���ģʽ
	*/
	enum eRasterizerFillMode
	{
		FM_Point,				///< ����ʾ
		FM_Wireframe,			///< �߿���ʾ
		FM_Solid				///< ʵ����ʾ
	};

	/** 
		��դ�ü���ʽ
	*/
	enum eRasterizerCullMode
	{
		CM_None,				///< �޲ü�
		CM_CW,					///< ˳ʱ��ü�
		CM_CCW					///< ��ʱ��ü�
	};

	/** 
		��ɫд���ɰ�
	*/
	enum eColorWriteMask
	{
		CW_RED		= 0x01,
		CW_GREEN	= 0x02,
		CW_BLUE		= 0x04,
		CW_ALPHA	= 0x08,

		CW_RGB		= 0x07,
		CW_RGBA		= 0x0f,
	};

	/** 
		�ȽϺ���
	*/
	enum eCompareFunction
	{
		CF_Less,			///< С��
		CF_LessEqual,		///< С�ڵ���
		CF_Greater,			///< ����
		CF_GreaterEqual,	///< ���ڵ���
		CF_Equal,			///< ����
		CF_NotEqual,		///< ����
		CF_Never,			///< ����
		CF_Always			///< ʼ��
	};

	/** 
		ģ�����
	*/
	enum eStencilOp
	{
		SO_Keep,
		SO_Zero,
		SO_Replace,
		SO_SaturatedIncrement,
		SO_SaturatedDecrement,
		SO_Invert,
		SO_Increment,
		SO_Decrement
	};

	/** 
		��ϲ���
	*/
	enum eBlendOperation
	{
		BO_Add,
		BO_Subtract,
		BO_Min,
		BO_Max
	};

	/** 
		�������
	*/
	enum eBlendFactor
	{
		BF_Zero,
		BF_One,
		BF_SourceColor,
		BF_InverseSourceColor,
		BF_SourceAlpha,
		BF_InverseSourceAlpha,
		BF_DestAlpha,
		BF_InverseDestAlpha,
		BF_DestColor,
		BF_InverseDestColor
	};





	struct SamplerStateInitializer
	{
		eSamplerFilter		Filter;
		eSamplerAddressMode AddressU;
		eSamplerAddressMode AddressV;
		eSamplerAddressMode AddressW;
	};
	struct RasterizerStateInitializer
	{
		eRasterizerFillMode FillMode;
		eRasterizerCullMode CullMode;
		float				DepthBias;
		float				SlopeScaleDepthBias;
	};
	struct DepthStateInitializer
	{
		bool				EnableDepthWrite;
		eCompareFunction	DepthTest;
	};

	struct StencilStateInitializer
	{
		bool				EnableFrontFaceStencil;
		eCompareFunction	FrontFaceStencilTest;
		eStencilOp			FrontFaceStencilFailStencilOp;
		eStencilOp			FrontFaceDepthFailStencilOp;
		eStencilOp			FrontFacePassStencilOp;
		bool				EnableBackFaceStencil;
		eCompareFunction	BackFaceStencilTest;
		eStencilOp			BackFaceStencilFailStencilOp;
		eStencilOp			BackFaceDepthFailStencilOp;
		eStencilOp			BackFacePassStencilOp;
		dword				StencilReadMask;
		dword				StencilWriteMask;
		dword				StencilRef;
	};
	struct BlendStateInitializer
	{
		eBlendOperation		ColorBlendOperation;
		eBlendFactor		ColorSourceBlendFactor;
		eBlendFactor		ColorDestBlendFactor;
		eBlendOperation		AlphaBlendOperation;
		eBlendFactor		AlphaSourceBlendFactor;
		eBlendFactor		AlphaDestBlendFactor;
		eCompareFunction	AlphaTest;
		_byte				AlphaRef;
	};



	/** @} */
	/** @} */

}