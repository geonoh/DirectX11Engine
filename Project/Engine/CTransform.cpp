#include "pch.h"
#include "CTransform.h"

#include "CConstBuffer.h"
#include "CDevice.h"

void CTransform::FinalTick()
{
	WorldMatrix = XMMatrixIdentity();

	const Matrix Scale = XMMatrixScaling(RelativeScale.x, RelativeScale.y, RelativeScale.z);
	const Matrix Rotation = XMMatrixRotationX(RelativeRotation.x) * XMMatrixRotationY(RelativeRotation.y) * XMMatrixRotationZ(RelativeRotation.z);
	const Matrix Translation = XMMatrixTranslation(RelativePos.x, RelativePos.y, RelativePos.z);

	WorldMatrix = Scale * Rotation * Translation;
}

void CTransform::Binding() const
{
	CConstBuffer* ConstBuffer = CDevice::GetInst()->GetConstBuffer(EConstantBufferType::Transform);

	GlobalTransform.WorldMatrix = WorldMatrix;

	ConstBuffer->SetData(&GlobalTransform);
	ConstBuffer->Binding();
}

CTransform::CTransform()
	: CComponent(EComponentType::Transform), RelativeScale(1.f, 1.f, 1.f)
{
}

CTransform::~CTransform()
{
}
