#pragma once

template<typename T>
class CSingleton
{
private:
	static T* m_This;

public:
	static T* GetInst()
	{
		if (!m_This)
		{
			m_This = new T;
		}

		return m_This;
	}

	static void Destroy()
	{
		if (!m_This)
		{
			return;
		}

		delete m_This;
		m_This = nullptr;
	}

protected:
	CSingleton()
	{
		// main 함수 종료될 때, 함수를 실행시켜줌!
		atexit(&CSingleton<T>::Destroy);
	}
	CSingleton(const CSingleton& _other) = delete;
	~CSingleton()
	{
		
	}
};

template<typename T>
T* CSingleton<T>::m_This = nullptr;