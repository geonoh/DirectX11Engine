#pragma once
#include "CComponent.h"

class CTransform : public CComponent
{
	Vec3 RelativePos;
	Vec3 RelativeScale;
	Vec3 RelativeRotation;

	Vec3 RelativeDirection[3];

	Matrix WorldMatrix;

public:
	virtual void FinalTick() override;
	void Binding() const;

	Vec3 GetRelativePos() const { return RelativePos; }
	Vec3 GetRelativeScale() const { return RelativeScale; }
	Vec3 GetRelativeRotation() const { return RelativeRotation; }
	Vec3 GetRelativeDirection(EDirectionType Type) const { return RelativeDirection[static_cast<int>(Type)]; }

	void SetRelativePos(const Vec3& InPos) { RelativePos = InPos; }
	void SetRelativeScale(const Vec3& InScale) { RelativeScale = InScale; }
	void SetRelativeRotation(const Vec3& InRotation) { RelativeRotation = InRotation; }

	void SetRelativePos(float x, float y, float z) { RelativePos = Vec3(x, y, z); }
	void SetRelativeScale(float x, float y, float z) { RelativeScale = Vec3(x, y, z); }
	void SetRelativeRotation(float x, float y, float z) { RelativeRotation = Vec3(x, y, z); }

	CTransform();
	virtual ~CTransform() override;
};
