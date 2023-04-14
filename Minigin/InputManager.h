#include "Singleton.h"
#include "XBoxController.h"
#include <map>
#include "Command.h"
#include <unordered_map>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput(float deltaTime);
		void Update();

		int AddXBoxController();
		void AddCommand(XBoxController::ControllerButton button, std::unique_ptr<Command> command, int controllerIndex);
		void AddCommand(SDL_Keycode key, std::unique_ptr<Command> pCommand);

	private:
		//Controller variables
		using ControllerKey = std::pair<unsigned, XBoxController::ControllerButton>;
		using ControllerCommandMap = std::map<ControllerKey, std::unique_ptr<Command>>;
		ControllerCommandMap m_ConsoleCommands{};
		std::vector<std::unique_ptr<XBoxController>> m_pControllers;

		//Keyboard variables
		std::map<SDL_Keycode, std::unique_ptr<Command>> m_KeyboardCommands;

		std::unordered_map<SDL_Scancode, bool> m_PreviousKeyStates;
	};

}