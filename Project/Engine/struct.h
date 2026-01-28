#pragma once

// 정점(Vertex) : 3D 공간의 좌표를 나타내는 단위
struct Vtx
{
	Vec3 vPos;
	Vec4 vColor;
	Vec2 vUV;
};

// 상수버퍼 관련 구조체
struct tTransform
{
	Matrix WorldMatrix;
	Matrix ViewMatrix;
	Matrix ProjectionMatrix;
};

extern tTransform GlobalTransform;

struct tMaterialConst
{
	int IntArray[4];
	float FloatArray[4];
	Vec2 Vec2Array[4];
	Vec4 Vec4Array[4];
	Matrix MatrixArray[4];
};