#pragma once
#include "Component.h"
#include <string>
#include <fstream>

namespace dae
{
	class Component;
	class Scene;
	class GameObject;
}

namespace Game
{
	class LevelBuilder
	{
	public:
		LevelBuilder() = default;
		void BuildLevel(dae::Scene* pScene, std::string levelFile, int sceneNr);
		void BuildMainMenu(dae::Scene* pScene, int controllerIndex1, int controllerIndex2);
		void CreateObservers(dae::Scene* pScene);

	private:
		void BuildBigTileColumn(dae::Scene* pScene, std::string line);
		void BuildBigTileRow(dae::Scene* pScene, std::string line);

		void BuildSmallTileColumn(dae::Scene* pScene, std::string line);
		void BuildSmallTileRow(dae::Scene* pScene, std::string line);

		void BuildZenChan(dae::Scene* pScene, std::string line);
		void BuildMaita(dae::Scene* pScene, std::string line);

		std::unique_ptr<std::ifstream> m_pFile{};
		int m_NrTile{};
		int m_SceneNr{};
	};
}