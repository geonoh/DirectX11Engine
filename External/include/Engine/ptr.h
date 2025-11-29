#pragma once

template<typename T>
class Ptr
{
private:
	T* Asset;

public:
	T* Get() { return Asset; }
	T** GetAddressOf() { return &Asset; }

public:
	void operator = (T* InAsset)
	{
		if (Asset)
		{
			Asset->Release();
		}

		Asset = InAsset;

		if (Asset)
		{
			Asset->AddRef();
		}
	}

	void operator = (const Ptr<T>& Other)
	{
		if (Asset)
		{
			Asset->Release();
		}

		Asset = Other.Asset;

		if (Asset)
		{
			Asset->AddRef();
		}
	}

	T* operator->()
	{
		return Asset;
	}

public:
	Ptr()
		: Asset(nullptr)
	{
	}

	Ptr(T* InAsset)
		: Asset(InAsset)
	{
		if (Asset)
		{
			Asset->AddRef();
		}
	}

	Ptr(const Ptr<T>& Other)
		: Asset(Other.Asset)
	{
		if (Asset)
		{
			Asset->AddRef();
		}
	}

	~Ptr()
	{
		if (Asset)
		{
			Asset->Release();
		}
	}
};
