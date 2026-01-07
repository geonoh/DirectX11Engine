#include "pch.h"
#include "CTransform.h"

#include "CConstBuffer.h"
#include "CDevice.h"

void CTransform::FinalTick()
{
	WorldMatrix = XMMatrixIdentity();

	Matrix Scale = XMMatrixIdentity();
	Scale._11 = RelativeScale.x;
	Scale._22 = RelativeScale.y;
	Scale._33 = RelativeScale.z;

	Matrix Rotation = XMMatrixIdentity();
	Rotation._11 = cosf(RelativeRotation.z);
	Rotation._12 = sinf(RelativeRotation.z);
	Rotation._21 = -sinf(RelativeRotation.z);
	Rotation._22 = cosf(RelativeRotation.z);


	Matrix Translation = XMMatrixIdentity();
	Translation._41 = RelativePos.x;
	Translation._42 = RelativePos.y;
	Translation._43 = RelativePos.z;

	WorldMatrix = Scale * Rotation * Translation;
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
