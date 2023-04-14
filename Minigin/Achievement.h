#pragma once
#include "Observer.h"

namespace dae
{


	class Achievement : public Observer
	{
	public:
		void Notify(Event event) override;

	private:
		//void Unlock();
	};
}