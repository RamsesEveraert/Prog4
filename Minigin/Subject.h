#pragma once

#include <vector>

namespace dae
{
	class Observer;
	class Event;
	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

	protected:
		virtual void NotifyObserver(const Event& event) = 0;

	private:
		std::vector<Observer*> m_Observers;
	};
}
