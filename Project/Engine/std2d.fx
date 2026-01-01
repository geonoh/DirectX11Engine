#ifndef _STD2D // Pragma once와 같은 효과
#define _STD2D

cbuffer TRANSFORM : register(b0)
{
    row_major matrix g_WorldMatrix;
	// GPU가 행렬을 읽을 때, 세로로 읽기 때문에 row_major를 붙여준다
}

SamplerState g_sampler0 : register(s0);
SamplerState g_sampler1 : register(s1);

Texture2D g_tex : register(t0);

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

    // 행렬을 곱할 때, 3차원 좌표를 4차원으로 확장
    output.vPosition = mul(float4(_in.vPos, 1.f), g_WorldMatrix);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 vColor = g_tex.Sample(g_sampler0, _in.vUV);
    return vColor;
}

#endif
