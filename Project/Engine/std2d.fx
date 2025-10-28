#ifndef _STD2D // Pragma once�� ���� ȿ��
#define _STD2D

cbuffer TRANSFORM : register(b0)
{
    float4 g_Position;
}

struct VS_IN
{
	// �ǵ��ϴ°� POSITION + Semantic Index�� 0
	// �ٵ� �� �ڿ� 0 index�� ������ �� �ִ�
    float3 vPos : POSITION0;
	// �ǵ��ϴ°� COLOR + Index�� 0
    float4 vColor : COLOR0;
};

struct VS_OUT
{
	// SV : system value
	// Rasterizer���� �� Semantic �̸��� ���� ��
    float4 vPosition : SV_Position;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    output.vPosition = float4(_in.vPos + g_Position.xyz, 1.f);
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    return float4(0.f, 1.f, 1.f, 1.f);
}

#endif
