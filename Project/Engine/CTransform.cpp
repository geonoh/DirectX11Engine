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

	// 오브젝트의 방향정보 계산
	RelativeDirection[static_cast<int>(EDirectionType::Right)] = XAxis;
	RelativeDirection[static_cast<int>(EDirectionType::Up)] = YAxis;
	RelativeDirection[static_cast<int>(EDirectionType::Front)] = ZAxis;

	for (Vec3& Direction : RelativeDirection)
	{
		Direction = XMVector3TransformNormal(Direction, Rotation);
		Direction.Normalize();
	}
}

void CTransform::Binding() const
{
	CConstBuffer* ConstBuffer = CDevice::GetInst()->GetConstBuffer(EConstantBufferType::Transform);

	// CCamera에서 이미 뷰, 프로젝션 행렬을 곱해주기 때문에 여기서는 월드 행렬만 전달
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
