#pragma once
#include "Component.h"

namespace dae 
{
	class Score final : public Component
	{
	public:
		Score();
		~Score() = default;

		void IncrementScore(); // temporary
		void DecrementScore(); // Temporary

		void SetScore(int score);
		int GetScore() const;

	private:
		int m_Score;
	};

}