#pragma once
#include "GameObject.h"
#include <memory>

namespace dae
{
	class Component
	{
	public:
		Component() = default;
		~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Render() const = 0;
		virtual void Update(float deltaTime) = 0;
		//virtual void FixedUpdate([[maybe_unused]] float deltaTime) {};

		void SetGameObject(GameObject* pGameobject) { m_pGameObject = pGameobject; }
		GameObject& GetGameObject() const { return *m_pGameObject; }

	private:
		GameObject* m_pGameObject{};
	};
}