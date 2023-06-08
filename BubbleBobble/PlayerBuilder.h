#pragma once
#include "Singleton.h"
#include <string>
#include <memory>
#include <vector>

namespace dae
{
	class Component;
	class Scene;
	class GameObject;
}

namespace Game
{
	class PlayerComponent;

	class PlayerBuilder : public dae::Singleton<PlayerBuilder>
	{
	public:
		void BuildPlayer(std::string levelFile, dae::Scene* pScene, int controllerIndex1, int controllerIndex2);

	private:
		void BuildPlayerComponent(std::string line, int controllerIndex1, int controllerIndex2);
		void BuildAnimations(std::string line);

		void PlayerAnimator(dae::GameObject* player, std::string line);
		void SetPlayerAnimation(dae::GameObject* player);

		std::unique_ptr<std::ifstream> m_pFile{};

		dae::Scene* m_pScene;

		dae::GameObject* m_pPlayerObject;
		std::vector<dae::GameObject*> m_pPlayers;

		PlayerComponent* m_pPlayerComponent;
	};
}