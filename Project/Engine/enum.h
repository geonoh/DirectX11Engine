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