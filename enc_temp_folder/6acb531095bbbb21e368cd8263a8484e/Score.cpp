#include "Score.h"
#include "EventQueue.h"
#include "Event.h"

#include <iostream>

dae::Score::Score()
	: m_Score{ 0 }
{

}

void dae::Score::DecrementScore()
{
	if (m_Score >= 100) m_Score -= 100;
	
	Event decrementEvent{ "DecrementEvent", { m_Score } };
	EventQueue::GetInstance().Dispatch(decrementEvent);
}

void dae::Score::IncrementScore()
{
	if (m_Score >= 0) m_Score += 100;

	if (m_Score == 500)
	{
		std::cout << "winner event dispatched \n";
		Event winner{ "Winner", { m_Score } };
		EventQueue::GetInstance().Dispatch(winner);
		
	}

	Event incrementScore{ "IncrementScore", { m_Score } };
	EventQueue::GetInstance().Dispatch(incrementScore);
}

void dae::Score::SetScore(int score)
{
	m_Score = score;
	
}

int dae::Score::GetScore() const
{
	return m_Score;
}

