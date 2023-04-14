#include "Component.h"
#include "GameObject.h"

dae::Component::Component(GameObject* pObject)
	: m_pAttachedObject(pObject)
{
}
