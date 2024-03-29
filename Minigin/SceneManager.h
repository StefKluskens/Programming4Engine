#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render();

		Scene* GetActiveScene() const;
		void SetActiveScene(const std::string& name);

		std::vector<std::shared_ptr<Scene>>& GetScenes() { return m_scenes; }
		Scene* GetScene(const std::string& name) const;

		void MoveObjects(const std::string& sourceSceneName, const std::string& targetSceneName, const std::string& tag);

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;

		Scene* m_pActiveScene = nullptr;

		int m_LevelIndex{};
	};
}
