#pragma once
#include "Observer.h"

namespace dae
{
	class GameObject;

	class Subject
	{
	public:
		Subject() = default;
		~Subject();
		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
		void Notify(Event event);

	private:
		std::vector<Observer*> m_pObservers;
	};
}