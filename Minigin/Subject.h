#pragma once

#include <vector>

namespace dae
{
	class ObserverInterface;
	class Subject
	{
	public:
		void addObserver(ObserverInterface* observer);
		void removeObserver(ObserverInterface* observer);
		
	protected:
		virtual void NotifyObserver(/*Event event*/) = 0;

	private:
		std::vector<ObserverInterface*> m_Observers; 
	};
}