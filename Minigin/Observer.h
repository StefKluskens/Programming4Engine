#pragma once
#include "GameObject.h"

namespace dae 
{
	enum class Event
	{
		PlayerDied,
		EnemyDied,
		PickUpFound,
		ACH_WIN_ONE_GAME
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(Event event) = 0;
	};
}