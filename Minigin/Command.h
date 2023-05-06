#include "Singleton.h"

namespace dae
{
	class Command : public Singleton<Command>
	{
	public:
		enum class ButtonState
		{
			IsDown,
			IsUp,
			IsPressed,
			None
		};

		explicit Command() {};
		virtual ~Command() {};
		virtual void Execute(float deltaTime) = 0;
		virtual ButtonState GetButtonState() = 0;
	};
}