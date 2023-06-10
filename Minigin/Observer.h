#pragma once
#include "GameObject.h"

namespace dae 
{
	enum class Event
	{
		PlayerDied,
		EnemyDied,
		Scored
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(Event event) = 0;
	};
}