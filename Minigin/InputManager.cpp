#include <SDL.h>
#include "InputManager.h"
#include <iostream>

bool dae::InputManager::ProcessInput(float deltaTime)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	for (const auto& command : m_KeyboardCommands)
	{
		//Get the scancode from the key in the map
		SDL_Scancode scancode = SDL_GetScancodeFromKey(command.first);
		if (currentKeyStates[scancode])
		{
			//Execute paired command
			command.second->Execute(deltaTime);
		}
	}

	Update();

	for (const auto& command : m_ConsoleCommands)
	{
		auto button = command.first.second;
		auto controllerIndex = command.first.first;

		//Check if the button is down
		if (m_pControllers[controllerIndex]->IsPressed(button))
		{
			//Execute paired command
			command.second->Execute(deltaTime);
		}
	}

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
	int index = static_cast<int>(m_pControllers.size());
	m_pControllers.emplace_back(std::make_unique<XBoxController>(index));
	return index;
}

void dae::InputManager::AddCommand(XBoxController::ControllerButton button, std::unique_ptr<Command> command, int controllerIndex)
{
	if (static_cast<size_t>(controllerIndex) > m_pControllers.size() || controllerIndex < 0)
	{
		std::cout << "Invalid controller index\n";
		return;
	}

	//Make pair of controller index and the passed button
	ControllerKey key = std::make_pair(controllerIndex, button);

	//Add key to commands in pair with the passed command
	m_ConsoleCommands.insert(std::make_pair(key, std::move(command)));
}

void dae::InputManager::AddCommand(SDL_Keycode key, std::unique_ptr<Command> pCommand)
{
	m_KeyboardCommands.insert(std::make_pair(key, std::move(pCommand)));
}
