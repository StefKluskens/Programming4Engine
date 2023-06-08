#include <SDL.h>
#include "InputManager.h"
#include <iostream>
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"

bool dae::InputManager::ProcessInput(float deltaTime)
{
	const std::string& sceneName = m_pSceneManager->GetActiveScene()->GetName();
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}

		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p) {

			//Load level
			if (sceneName == "Level0")
			{
				SceneManager::GetInstance().SetActiveScene("Level1");
			}
			else if (sceneName == "Level1")
			{
				SceneManager::GetInstance().SetActiveScene("Level2");
			}
			else if (sceneName == "Level2")
			{
				SceneManager::GetInstance().SetActiveScene("Level0");
			}
		}
	}

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	
	for (const auto& command : m_SceneCommands[sceneName])
	{
		//Get the scancode from the key in the map
		SDL_Scancode scancode = command.first;

		if (command.second->GetButtonState() == Command::ButtonState::IsPressed)
		{
			//IsPressed
			if (currentKeyStates[scancode])
			{
				//Execute paired command
				command.second->Execute(deltaTime);
			}
		}
		else if (command.second->GetButtonState() == Command::ButtonState::IsDown)
		{
			//IsDown
			bool isKeyPressed = currentKeyStates[scancode];
			if (isKeyPressed && !m_PreviousKeyStates[scancode])
			{
				//Execute paired command
				command.second->Execute(deltaTime);
			}

			m_PreviousKeyStates[scancode] = isKeyPressed;
		}
	}

	Update();

	for (const auto& command : m_SceneControllerCommands[sceneName])
	{
		auto button = command.first.second;
		auto controllerIndex = command.first.first;

		if (command.second->GetButtonState() == Command::ButtonState::IsDown)
		{
			if (m_pControllers[controllerIndex]->IsDown(button))
			{
				// Execute paired command
				command.second->Execute(deltaTime);
			}
		}
		else if (command.second->GetButtonState() == Command::ButtonState::IsPressed)
		{
			if (m_pControllers[controllerIndex]->IsPressed(button))
			{
				// Execute paired command
				command.second->Execute(deltaTime);
			}
		}
	}

	//for (const auto& command : m_ConsoleCommands)
	//{
	//	auto button = command.first.second;
	//	auto controllerIndex = command.first.first;

	//	if (command.second->GetButtonState() == Command::ButtonState::IsDown)
	//	{
	//		if (m_pControllers[controllerIndex]->IsDown(button))
	//		{
	//			//Execute paired command
	//			command.second->Execute(deltaTime);
	//		}
	//	}
	//	else if (command.second->GetButtonState() == Command::ButtonState::IsPressed)
	//	{
	//		if (m_pControllers[controllerIndex]->IsPressed(button))
	//		{
	//			//Execute paired command
	//			command.second->Execute(deltaTime);
	//		}
	//	}
	//}

	return true;
}

void dae::InputManager::Update()
{
	for (auto& controller : m_pControllers)
	{
		controller->Update();
	}
}

int dae::InputManager::AddXBoxController()
{
	/*int index = static_cast<int>(m_pControllers.size());
	m_pControllers.emplace_back(std::make_unique<XBoxController>(index));
	return index;*/

	m_LastControllerIndex++;
	m_pControllers.emplace_back(std::make_unique<XBoxController>(m_LastControllerIndex));
	return m_LastControllerIndex;
}

void dae::InputManager::AddCommand(const std::string& sceneName, XBoxController::ControllerButton button, std::unique_ptr<Command> command, int controllerIndex)
{
	if (static_cast<size_t>(controllerIndex) >= m_pControllers.size() || controllerIndex < 0)
	{
		std::cout << "Invalid controller index\n";
		return;
	}

	// Make pair of controller index and the passed button
	ControllerKey key = std::make_pair(controllerIndex, button);

	// Add the key to the commands map for the specific scene
	m_SceneControllerCommands[sceneName][key] = std::move(command);
}

void dae::InputManager::AddCommand(const std::string& sceneName, SDL_Scancode key, std::unique_ptr<Command> pCommand)
{
	m_SceneCommands[sceneName][key] = std::move(pCommand);
}

dae::InputManager::InputManager()
	: m_pSceneManager(&SceneManager::GetInstance())
{
}
