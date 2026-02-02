#pragma once

template<typename T>
class Ptr
{
private:
	T* Asset;

public:
	T* Get() const { return Asset; }
	T** GetAddressOf() const { return &Asset; }

public:
	bool operator == (T* InAsset)
	{
		if (Asset == InAsset)
		{
			return true;
		}

		return false;
	}

	bool operator != (T* InAsset)
	{
		if (Asset != InAsset)
		{
			return true;
		}
		return false;
	}

	bool operator == (const Ptr<T>& InAsset)
	{
		if (Asset == InAsset.Asset)
		{
			return true;
		}

		return false;
	}

	bool operator != (const Ptr<T>& InAsset)
	{
		if (Asset != InAsset.Asset)
		{
			return true;
		}
		return false;
	}

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

template<typename T>
bool operator == (void* InAsset, const Ptr<T>& Ptr)
{
	if (InAsset == Ptr.Get())
	{
		return true;
	}

	return false;
}

template<typename T>
bool operator != (void* InAsset, const Ptr<T>& Ptr)
{
	if (InAsset != Ptr.Get())
	{
		return true;
	}

	return false;
}
