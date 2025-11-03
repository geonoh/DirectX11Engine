#ifndef _STD2D // Pragma once와 같은 효과
#define _STD2D

cbuffer TRANSFORM : register(b0)
{
    float4 g_Position;
    float4 g_Scale;
}

struct VS_IN
{
	// 의도하는게 POSITION + Semantic Index가 0
	// 근데 저 뒤에 0 index를 생략할 수 있다
    float3 vPos : POSITION0;
	// 의도하는게 COLOR + Index가 0
    float4 vColor : COLOR0;
};

struct VS_OUT
{
	// SV : system value
	// Rasterizer에서 저 Semantic 이름을 갖다 씀
    float4 vPosition : SV_Position;
    float4 vColor : COLOR0;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    output.vPosition = float4(_in.vPos + g_Position.xyz, 1.f);
    output.vColor = _in.vColor;
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    return _in.vColor;
}

#endif
