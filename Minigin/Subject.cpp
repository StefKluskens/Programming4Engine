#include "Subject.h"

dae::Subject::~Subject()
{
}

void dae::Subject::AddObserver(Observer* pObserver)
{
	m_pObservers.push_back(pObserver);
}

void dae::Subject::RemoveObserver(Observer* pObserver)
{
	for (size_t i = 0; i < m_pObservers.size(); ++i)
	{
		if (m_pObservers[i] == pObserver)
		{
			m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver));
		}
	}
}

void dae::Subject::Notify(Event event)
{
	for (auto observer : m_pObservers)
	{
		observer->Notify(event);
	}
}
