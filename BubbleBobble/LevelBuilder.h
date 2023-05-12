#pragma once
#include "Component.h"
#include <string>
#include <fstream>
#include "Singleton.h"

namespace dae
{
	class Component;
	class Scene;
	class GameObject;
}

namespace Game
{
	class LevelBuilder : public dae::Singleton<LevelBuilder>
	{
	public:
		void BuildLevel(dae::Scene* pScene, std::string levelFile);

	private:
		void BuildPlayer(dae::Scene* pScene, std::string line);

		std::unique_ptr< std::ifstream> m_pFile{};
	};
}