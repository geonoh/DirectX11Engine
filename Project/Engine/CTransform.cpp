#include "pch.h"
#include "CTransform.h"

#include "CConstBuffer.h"
#include "CDevice.h"

void CTransform::FinalTick()
{
	WorldMatrix = XMMatrixIdentity();

	// Scale
	WorldMatrix._11 = RelativeScale.x;
	WorldMatrix._22 = RelativeScale.y;
	WorldMatrix._33 = RelativeScale.z;

	// Translate
	WorldMatrix._41 = RelativePos.x;
	WorldMatrix._42 = RelativePos.y;
	WorldMatrix._43 = RelativePos.z;
}

void CTransform::Binding() const
{
	CConstBuffer* ConstBuffer = CDevice::GetInst()->GetConstBuffer(EConstantBufferType::Transform);
	tTransform trans = {};
	trans.WorldMatrix = WorldMatrix;

	ConstBuffer->SetData(&trans);
	ConstBuffer->Binding();
}

CTransform::CTransform()
	: CComponent(EComponentType::Transform), RelativeScale(1.f, 1.f, 1.f)
{
}

CTransform::~CTransform()
{
}
