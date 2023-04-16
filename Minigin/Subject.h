#pragma once

#include <vector>

namespace dae
{
	class Observer;
	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

	protected:
		virtual void NotifyObserver(/*Event event*/) = 0;

	private:
		std::vector<Observer*> m_Observers;
	};
}
