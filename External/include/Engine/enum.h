#pragma once

enum class EComponentType
{
	Transform,
	Camera,
	Collider2D,
	Collider3D,
	Animator2D,
	Animator3D,
	Light2D,
	Light3D,

	MeshRender,
	Decal,
	ParticleSystem,
	Tilemap,
	Landscape,

	End,	// 기본 컴포넌트

	Script,
};

enum class EAssetType
{
	Prefab,
	Mesh,
	MeshData,
	Material,
	Texture,
	Sound,
	GraphicsShader,
	ComputeShader,
	End,
};

enum class EConstantBufferType
{
	Transform,
	Material,
	Animation,
	Global,
	End,
};

enum class ERasterizerType
{
	CullBack,
	CullFront,
	CullNone,
	WireFrame,
	End,
};

enum class EDirectionType
{
	Right,
	Up,
	Front,
};

extern Vec3 XAxis;
extern Vec3 YAxis;
extern Vec3 ZAxis;

enum class ScalarParam
{
	Int_0,
	Int_1,
	Int_2,
	Int_3,

	Float_0,
	Float_1,
	Float_2,
	Float_3,

	Vec2_0,
	Vec2_1,
	Vec2_2,
	Vec2_3,

	Vec4_0,
	Vec4_1,
	Vec4_2,
	Vec4_3,

	Mat_0,
	Mat_1,
	Mat_2,
	Mat_3,

	End,
};

enum class TextureParam
{
	Texture_0,
	Texture_1,
	Texture_2,
	Texture_3,
	Texture_4,
	Texture_5,

	Texture_Cube_0,
	Texture_Cube_1,
	Texture_Cube_2,
	Texture_Cube_3,

	Texture_Array_0,
	Texture_Array_1,
	Texture_Array_2,
	Texture_Array_3,

	End,
};
