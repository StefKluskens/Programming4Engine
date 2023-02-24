#pragma once
#include "Component.h"
#include <string>

class FPSComponent : public Component
{
public:
	FPSComponent();
	virtual ~FPSComponent() = default;
	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) = delete;

	void Render() const override;
	void Update(float deltaTime) override;

	std::string GetFPS() const;

private:
};

