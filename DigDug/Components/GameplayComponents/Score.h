#pragma once
#include "Component.h"

namespace dae 
{
	struct Event;
	class Score final : public Component
	{
	public:
		Score();
		~Score() = default;

		void SetScore(int score);
		void AddPoints(int points);

		int GetScore() const;
		int GetHighScore();

	private:
		void OnPlayerDied(const Event& event);
		int m_Score, m_HighScore;
	};

}