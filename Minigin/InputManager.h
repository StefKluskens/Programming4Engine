#include "Singleton.h"
#include "XBoxController.h"
#include <map>
#include "Command.h"
#include <unordered_map>
#include <SDL_keycode.h>
#include <string>

namespace dae
{
	class SceneManager;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();

		bool ProcessInput(float deltaTime);
		void Update();

		int AddXBoxController();
		void AddCommand(XBoxController::ControllerButton button, std::unique_ptr<Command> command, int controllerIndex);
		void AddCommand(const std::string& sceneName, XBoxController::ControllerButton button, std::unique_ptr<Command> command, int controllerIndex);
		void AddCommand(const std::string& sceneName, SDL_Scancode key, std::unique_ptr<Command> pCommand);

	private:
		//Controller variables
		using ControllerKey = std::pair<unsigned, XBoxController::ControllerButton>;
		using ControllerCommandMap = std::map<ControllerKey, std::unique_ptr<Command>>;
		ControllerCommandMap m_ConsoleCommands{};
		std::vector<std::unique_ptr<XBoxController>> m_pControllers;

		std::map<std::string, ControllerCommandMap> m_SceneControllerCommands;

		//Keyboard variables
		std::map<std::string, std::map<SDL_Scancode, std::unique_ptr<Command>>> m_SceneCommands;

		std::unordered_map<SDL_Scancode, bool> m_PreviousKeyStates;

		SceneManager* m_pSceneManager{};

		int m_LastControllerIndex{ -1 };
	};

}