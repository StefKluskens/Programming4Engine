#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	/*for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}*/

	if(m_pActiveScene)
	{
		m_pActiveScene->Update(deltaTime);
	}
}

void dae::SceneManager::FixedUpdate(float deltaTime)
{
	/*for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(deltaTime);
	}*/

	if (m_pActiveScene)
	{
		m_pActiveScene->FixedUpdate(deltaTime);
	}
}

void dae::SceneManager::Render()
{
	/*for (const auto& scene : m_scenes)
	{
		scene->Render();
	}*/

	if (m_pActiveScene)
	{
		m_pActiveScene->Render();
	}
}

dae::Scene* dae::SceneManager::GetActiveScene() const
{
	return m_pActiveScene;
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	auto it = std::find_if(m_scenes.begin(), m_scenes.end(), [name](const std::shared_ptr<Scene>& pScene)
		{
			return pScene->GetName() == name;
		});

	if (it != m_scenes.end())
	{
		m_pActiveScene = it->get();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
