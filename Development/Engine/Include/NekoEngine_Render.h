#pragma once

// �ⲿ��ΪD3DDRV����
#include "Engine/RenderThread.h"

// Wrapper Render Object
#include "Engine/RenderResource.h"
#include "Engine/RenderState.h"
#include "Engine/VertexFormat.h"
#include "Engine/ShaderCompiler.h"
#include "Engine/RHI.h"


#include "Engine/RenderTexture.h"


#ifndef D3DDRV_HEADER
// �ⲿ��D3DDRV������

#include "NekoEngine_System.h"

// Utility
#include "Engine/RenderUtility.h"
#include "Engine/CameraController.h"

#include "Engine/RenderStateWrapper.h"

// NeObject

#include "Engine/TextureResource.h"
#include "Engine/ShaderMaster.h"
#include "Engine/GlobalShaderFactory.h"

// High Level Render Object
#include "Engine/BatchedElement.h"
#include "Engine/Canvas.h"
#include "Engine/VertexFactory.h"
#include "Engine/SceneView.h"
#include "Engine/RenderTarget.h"
#include "Engine/PresentWindow.h"
#include "Engine/RenderQueue.h"
#include "Engine/HitProxy.h"


#endif