#include "TrashTheCache.h"


#include <iostream>
#include <chrono>
#include <vector>

#include <algorithm>
#include <numeric> 

void TrashTheCache::PlotExercice1()
{
	const int bufferSize = 10'000'000;
	float totalElapsedTime{};
	int* pBuffer = new int[bufferSize] {};

	int amountSamples{ 20 };
	int maxSteps{ 1024 };

	for (int stepsize = 1; stepsize <= maxSteps; stepsize *= 2)
	{
		std::vector<float> samples;
		samples.reserve(amountSamples);

		for (int sample = 0; sample < amountSamples; ++sample)
		{
			auto start = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < bufferSize; i += stepsize)
			{
				pBuffer[i] *= 2;
			}

			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			samples.push_back(static_cast<float>(elapsedTime));


		}

		// Remove the highest and lowest value 

		std::sort(samples.begin(), samples.end());
		samples.erase(samples.begin());
		samples.pop_back();

		float averageElapsedTime = std::accumulate(samples.begin(), samples.end(), 0.0f) / samples.size();
		totalElapsedTime += averageElapsedTime;
	}

	delete[] pBuffer;

}


void TrashTheCache::Exercice2()
{

	//const int bufferSize = 67'108'864; // 2 ^26
	const int bufferSize = 10'000'000;
	float totalElapsedTime{};
	float totalElapsedTimeAlternative{};
	GameObject3D* pBuffer = new GameObject3D[bufferSize]{};
	GameObject3DAlternative* pBufferAlternative = new GameObject3DAlternative[bufferSize]{};

	int amountSamples{ 15 };
	int maxSteps{ 1024 };

	for (int stepsize = 1; stepsize <= maxSteps; stepsize *= 2)
	{
		std::vector<float> samples;
		samples.reserve(amountSamples);

		std::vector<float> samplesAlternative;
		samples.reserve(amountSamples);

		for (int sample = 0; sample < amountSamples; ++sample)
		{
			auto start = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < bufferSize; i += stepsize)
			{

				pBuffer[i].ID *= 2;


			}

			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			samples.push_back(static_cast<float>(elapsedTime));

			// alternative
			auto startAlternative = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < bufferSize; i += stepsize)
			{

				pBufferAlternative[i].ID *= 2;


			}
			auto endAlternative = std::chrono::high_resolution_clock::now();
			auto elapsedTimeAlternative = std::chrono::duration_cast<std::chrono::microseconds>(endAlternative - startAlternative).count();
			samplesAlternative.push_back(static_cast<float>(elapsedTimeAlternative));


		}

		// Remove the highest and lowest value 

		std::sort(samples.begin(), samples.end());
		samples.erase(samples.begin());
		samples.pop_back();

		float averageElapsedTime = std::accumulate(samples.begin(), samples.end(), 0.0f) / samples.size();
		totalElapsedTime += averageElapsedTime;

		std::cout << "GameObject3D: stepsize " << stepsize << ": average of " << averageElapsedTime / 1000.f << "ms" << std::endl;


		// alternative

		std::sort(samplesAlternative.begin(), samplesAlternative.end());
		samplesAlternative.erase(samplesAlternative.begin());
		samplesAlternative.pop_back();

		float averageElapsedTimeAlternative = std::accumulate(samplesAlternative.begin(), samplesAlternative.end(), 0.0f) / samplesAlternative.size();
		totalElapsedTimeAlternative += averageElapsedTimeAlternative;


		std::cout << "GameObject3DAlternative: stepsize " << stepsize << ": average of " << averageElapsedTimeAlternative / 1000.f << "ms" << std::endl << std::endl;
	}

	delete[] pBuffer;

	std::cout << "\nGameObject3D: total elapsed time: " << totalElapsedTime / 1000.f << "ms" << std::endl;
	std::cout << "GameObjectAlternative: total elapsed time: " << totalElapsedTimeAlternative / 1000.f << "ms" << std::endl;

}

