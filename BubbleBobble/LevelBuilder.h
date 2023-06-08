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
		void BuildLevel(dae::Scene* pScene, std::string levelFile, int sceneNr, int controllerIndex1, int controllerIndex2);

	private:
		void BuildPlayer(dae::Scene* pScene, std::string line, int controllerIndex1, int controllerIndex2);
		void BuildTile(dae::Scene* pScene, std::string line, bool isSmallTile);
		void BuildBigTileColumn(dae::Scene* pScene, std::string line);
		void BuildBigTileRow(dae::Scene* pScene, std::string line);

		void BuildSmallTileColumn(dae::Scene* pScene, std::string line);
		void BuildSmallTileRow(dae::Scene* pScene, std::string line);

		std::unique_ptr<std::ifstream> m_pFile{};
		int m_NrTile{};
		int m_SceneNr{};
	};
}