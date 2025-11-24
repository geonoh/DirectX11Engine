#include "pch.h"
#include "CComponent.h"

COMPONENT_TYPE CComponent::GetComponentType() const
{
	return m_Type;;
}

CComponent::CComponent(const COMPONENT_TYPE _Type)
	:m_Type(_Type)
{
}

CComponent::~CComponent()
{
}
