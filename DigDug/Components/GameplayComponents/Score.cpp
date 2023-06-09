 #include "Score.h"
#include "EventHandler.h"
#include "Event.h"
#include "GameObject.h"

#include <iostream>

dae::Score::Score()
	: m_Score{}
	, m_HighScore{}
{
	//EventHandler::GetInstance().AddListener("PlayerDied", [this](const dae::Event& event) { OnPlayerDied(event); });
}


void dae::Score::SetScore(int score)
{
	m_Score = score;
	
}

void dae::Score::AddPoints(int points)
{
	m_Score += points;
}

int dae::Score::GetScore() const
{
	return m_Score;
}

int dae::Score::GetHighScore()
{
	return m_HighScore;
}

void dae::Score::OnPlayerDied(const Event& event)
{
	std::string ownerName{};
	for (const auto& data : event.data)
	{
		if (data.type() == typeid(std::string))
		{
			ownerName = std::any_cast<std::string>(data);
		}
	}

	if (GetOwner()->GetObjectName() != ownerName) return; // not for this object

	if (m_Score > m_HighScore) m_HighScore = m_Score;
	m_Score = 0;
}

