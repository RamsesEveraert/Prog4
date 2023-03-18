
#include <iostream>
#include <chrono>
#include <vector>


struct Transform
{
	float matrix[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
};

class GameObject3D
{
public:
	Transform* transform{};
	int ID{};
};

int main()
{
	const int arraySize = 1'000'000;
	GameObject3D* pBuffer = new GameObject3D[arraySize] {};


	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < arraySize; i += stepsize)
		{
			pBuffer[i].ID *= 2;
		}

		auto end = std::chrono::high_resolution_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		std::cout << "operation took " << elapsedTime / 1000.f << "ms" << std::endl;
	}
	
	delete pBuffer;
}
