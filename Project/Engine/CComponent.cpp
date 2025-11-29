#include "pch.h"
#include "CComponent.h"

EComponentType CComponent::GetComponentType() const
{
	return Type;
}

CComponent::CComponent(const EComponentType InType)
	: Type(InType)
{
}

CComponent::~CComponent()
{
}
