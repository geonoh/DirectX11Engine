#pragma once

template<typename T>
class CSingleton
{
private:
	static T* This;

public:
	static T* GetInst()
	{
		if (!This)
		{
			This = new T;
		}

		return This;
	}

	static void Destroy()
	{
		if (!This)
		{
			return;
		}

		delete This;
		This = nullptr;
	}

protected:
	CSingleton()
	{
		// main 함수 종료될 때, 함수를 실행시켜줌!
		atexit(&CSingleton<T>::Destroy);
	}
	CSingleton(const CSingleton& Other) = delete;
	~CSingleton()
	{
		
	}
};

template<typename T>
T* CSingleton<T>::This = nullptr;