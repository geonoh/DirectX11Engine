#pragma once
#include "CComponent.h"

class CTransform : public CComponent
{
	Vec3 RelativePos;
	Vec3 RelativeScale;
	Vec3 RelativeRotation;

public:
	virtual void FinalTick() override;
	void Binding() const;

	Vec3 GetRelativePos() { return RelativePos; }
	Vec3 GetRelativeScale() { return RelativeScale; }
	Vec3 GetRelativeRotation() { return RelativeRotation; }

	void SetRelativePos(const Vec3& InPos) { RelativePos = InPos; }
	void SetRelativeScale(const Vec3& InScale) { RelativeScale = InScale; }
	void SetRelativeRotation(const Vec3& InRotation) { RelativeRotation = InRotation; }

	void SetRelativePos(float x, float y, float z) { RelativePos = Vec3(x, y, z); }
	void SetRelativeScale(float x, float y, float z) { RelativeScale = Vec3(x, y, z); }
	void SetRelativeRotation(float x, float y, float z) { RelativeRotation = Vec3(x, y, z); }

	CTransform();
	virtual ~CTransform() override;
};
