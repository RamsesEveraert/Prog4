#pragma once
#include "BaseComponent.h"

namespace dae 
{
	class Score final : public BaseComponent
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