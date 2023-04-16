#include "Subject.h"

#include "Observer.h"

#include <stdexcept>



void dae::Subject::AddObserver(Observer* observer)
{
    if (observer == nullptr) return;
    for (const auto& pObserver : m_Observers)
    {
        if (pObserver == observer) throw std::runtime_error("Observer already exists in the observer container.");
    }
    m_Observers.push_back(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
    if (observer == nullptr) return;
    for (auto it = m_Observers.begin(); it != m_Observers.end(); ++it)
    {
        if (*it == observer)
        {
            m_Observers.erase(it);
            return;
        }
    }
    throw std::runtime_error("Observer does not exist in the observer container.");
}


//
//void dae::Subject::NotifyObserver(/*Event event*/)
//{
//	for (auto observer : m_Observers)
//	{
//		observer->Notify(this /*,event*/)
//	}
//}
