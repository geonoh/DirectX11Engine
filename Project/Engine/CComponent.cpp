#include "pch.h"
#include "CComponent.h"

#include "CGameObject.h"

EComponentType CComponent::GetComponentType() const
{
	return Type;
}

CTransform* CComponent::Transform() const
{
	return GetOwner()->Transform();
}

CMeshRender* CComponent::MeshRender() const
{
	return GetOwner()->MeshRender();
}

CCamera* CComponent::Camera() const
{
	return GetOwner()->Camera();
}

CComponent::CComponent(const EComponentType InType)
	: Type(InType)
{
}

CComponent::~CComponent()
{
}
