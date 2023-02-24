#pragma once
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
	virtual void FixedUpdate([[maybe_unused]] float deltaTime) {};
};

