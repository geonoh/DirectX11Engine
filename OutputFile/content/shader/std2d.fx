#ifndef _STD2D // Pragma once와 같은 효과
#define _STD2D

#include "value.fx"

struct VS_IN
{
	// 의도하는게 POSITION + Semantic Index가 0
	// 근데 저 뒤에 0 index를 생략할 수 있다
    float3 vPos : POSITION0;
	// 의도하는게 COLOR + Index가 0
    float4 vColor : COLOR0;
    float2 vUV : TEXCOORD0;
};

struct VS_OUT
{
	// SV : system value
	// Rasterizer에서 저 Semantic 이름을 갖다 씀
    float4 vPosition : SV_Position;
    float4 vColor : COLOR0;
    float2 vUV : TEXCOORD0;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    float4 WorldPos = mul(float4(_in.vPos, 1.f), g_WorldMatrix);
    float4 ViewPos = mul(WorldPos, g_ViewMatrix);
    float4 ProjectionPos = mul(ViewPos, g_ProjectionMatrix);

    // - 원래대로라면 w자리에 있는 값으로 x,y,z를 나눠야 하지만, 레스터 라이저에서 알아서 나눠줌

    // 행렬을 곱할 때, 3차원 좌표를 4차원으로 확장
    output.vPosition = ProjectionPos;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;

    if (g_int_0 == 0)
    {
        vColor = g_tex.Sample(g_sampler0, _in.vUV);
    }

    else if (g_int_0 == 1)
    {
        vColor = float4(1.f, 1.f, 0.f, 1.f);
    }

    return vColor;
}

#endif
